//
// Created by caiiiycuk on 13.11.2019.
//
#include <jsdos-asyncify.h>
#include <atomic>

#define EMSCRIPTEN

#ifdef EMSCRIPTEN
// clang-format off
#include <emscripten.h>

EM_JS(void, syncSleep, (unsigned int ms, bool nonSkippable), {
    if (!Module.sync_sleep) {
      throw new Error("Async environment does not exists");
      return;
    }

    const now = Date.now();
    if (Asyncify.state === 0) { // NORMAL
      if (!nonSkippable && (now - Module.last_wakeup) < 24 /* 30 FPS */) {
        return;
      }
      
      if (nonSkippable) {
        Module.wakeUpAt = Date.now() + ms;
        ++Module.nonskippable_sleep_count;
      }

      ++Module.sleep_count;
      
      Module.cycles += Module._getAndResetCycles();
      Module.sleep_started_at = now;
    } else if (Asyncify.state === 2) { // REWIND
      Module.sleep_time += now - Module.sleep_started_at;
      Module.last_wakeup = now;

      if (Asyncify.asyncPromiseHandlers === null) {
        Asyncify.whenDone().catch(Module.uncaughtAsyncify);
      }
    }

    Asyncify.handleSleep(Module.sync_sleep);
  });

EM_JS(bool, initTimeoutSyncSleep, (), {
    Module.alive = true;
    Module.nonskippable_sleep_count = 0;
    Module.sleep_count = 0;
    Module.sleep_time = 0;
    Module.cycles = 0;
    Module.last_wakeup = Date.now();
    Module.sync_sleep = function(wakeUp) {
      setTimeout(function() {
          if (!Module.alive) {
            return;
          }

          if (Module.paused === true) {
            var checkIntervalId = setInterval(function() {
              if (Module.paused === false) {
                clearInterval(checkIntervalId);
                wakeUp();
              }
            }, 16);
          } else {
            wakeUp();
          } 
        });
    };

    Module.destroyAsyncify = function() {
      Module.alive = false;
      delete Module.sync_sleep;
    };
    Module.uncaughtAsyncify = function(error) {
      console.error(error);
      Module.destroyAsyncify();
      Module.uncaught(error);
    };

    return true;
  });

EM_JS(bool, initMessageSyncSleep, (bool worker), {
    console.log("initMessageSyncSleep");
    Module.alive = true;
    Module.nonskippable_sleep_count = 0;
    Module.sleep_count = 0;
    Module.sleep_time = 0;
    Module.cycles = 0;
    Module.sessionId = "123";
    Module.last_wakeup = Date.now();

    function postWakeUpMessage() {
      if (worker) {
        postMessage({name : "ws-sync-sleep", props: { sessionId : Module.sessionId } });
      } else {
        window.postMessage({name : "ws-sync-sleep", props: { sessionId : Module.sessionId } },
                            "*");
      }
    }

    Module.sync_sleep = function(wakeUp) {
      if (Module.sync_wakeUp) {
        throw new Error("Trying to sleep in sleeping state!");
        return;  // already sleeping
      }

      Module.sync_wakeUp = wakeUp;
      
      if (Module.paused === true) {
        var checkIntervalId = setInterval(function() {
          if (Module.paused === false) {
            clearInterval(checkIntervalId);
            postWakeUpMessage();
          }
        }, 16);
      } else {
        postWakeUpMessage();
      }
    };

    Module.receive = function(ev) {
      var data = ev.data;
      if (ev.data.name === "wc-sync-sleep" &&
          Module.sessionId === ev.data.props.sessionId) {
        if (Module.wakeUpAt !== undefined && Date.now() < Module.wakeUpAt) {
          postWakeUpMessage();
          return;
        }
        var wakeUp = Module.sync_wakeUp;
        delete Module.sync_wakeUp;
        delete Module.wakeUpAt;

        if (Module.alive) {
          wakeUp();
        }
      }
    };

    if (worker) {
      self.addEventListener("message", Module.receive, { passive: true });
    } else {
      window.addEventListener("message", Module.receive, { passive: true });
    }

    Module.destroyAsyncify = function() {
      console.log('destroyAsyncify');

      if (worker) {
        self.removeEventListener("message", Module.receive);
      } else {
        window.removeEventListener("message", Module.receive);
      }

      Module.alive = false;
      delete Module.sync_sleep;
    };
    Module.uncaughtAsyncify = function(error) {
      console.error(error);
      Module.destroyAsyncify();
      Module.uncaught(error);
    };

    return true;
  });

EM_JS(void, destroyAsyncify, (), {
    Module.destroyAsyncify();
  });

EM_JS(bool, isWorker, (), {
    return typeof importScripts === "function";
  });

EM_JS(bool, isNode, (), {
    return typeof process === "object" && typeof process.versions === "object" && typeof process.versions.node === "string";
  });

// clang-format on
#else
#include <thread>
#endif

volatile bool paused = false;

void server_pause() {
  paused = true;
#ifdef EMSCRIPTEN
  EM_ASM(({
      Module.paused = true;
  }));
#endif
}

void server_resume() {
  paused = false;
#ifdef EMSCRIPTEN
  EM_ASM(({
      Module.paused = false;
  }));
#endif
}

void jsdos::initAsyncify() {
#ifdef EMSCRIPTEN
  if (isNode()) {
    initTimeoutSyncSleep();
  } else {
    initMessageSyncSleep(isWorker());
  }
#endif
}

void jsdos::destroyAsyncify() {
#ifdef EMSCRIPTEN
    ::destroyAsyncify();
#endif
}

int asyncifyLockCount = 0;
void jsdos::asyncifyLock() {
  ++asyncifyLockCount;
}

void jsdos::asyncifyUnlock() {
  --asyncifyLockCount;
}

extern "C" void asyncify_sleep(unsigned int ms, bool nonSkippable) {
  if (asyncifyLockCount != 0) {
    return;
  }
#ifdef EMSCRIPTEN
  syncSleep(ms, nonSkippable);
#else
  while (paused) {
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  if (ms == 0 || !nonSkippable) {
    return;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

namespace {
  std::atomic_uint32_t cycles(0);
}

void jsdos::incCycles(int32_t count) {
    if (count > 0) {
        ::cycles += count;
    }
}

uint32_t jsdos::getAndResetCycles() {
    uint32_t tmp = ::cycles;
    ::cycles = 0;
    return tmp;
}

#ifdef EMSCRIPTEN
extern "C" uint32_t EMSCRIPTEN_KEEPALIVE getAndResetCycles() {
    return jsdos::getAndResetCycles();
}
#endif