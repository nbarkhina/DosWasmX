# Compiling DOS Wasm X from Source
You will need a Linux environment to build DOS Wasm X

- create a folder outside of this repo to install emscripten
- git clone https://github.com/emscripten-core/emsdk.git
- cd emsdk
- ./emsdk install 3.1.49
- ./emsdk activate 3.1.49
- source ./emsdk_env.sh
- replace Binaryen with special version
  - replace the file wasm-opt in `emsdk/upstream/bin/wasm-opt` with the one from this repo `code/wasm-opt`
  - navigate to the `emsdk/upstream/bin/` folder and run `chmod +x wasm-opt`
  - this is needed because default Binaryen does not support Exceptions and Asyncify together
  - huge credit goes to @Caiiiycuk for developing this! 
  - see references below if you prefer to get wasm-opt directly from his releases page
- navigate back to the code folder in the DosWasmX repo
- run `make`
  - you will get a build error towards the end saying EM_CACHE_IS_LOCKED
  - to get past this error simply copy the faulting emcc command from the terminal and run it manually (See screenshot below)
  - this should succeed and then run `make` again to finish building
  - later builds should not get this error after you do this one time fix
- this process will update the main.js and main.wasm files in your dist folder
- now serve the dist folder from a webserver and Enjoy!
#### _DOS Wasm X Online Documentation_
#### [DOS Commands](https://nbarkhina.github.io/DosWasmX/dos-commands) | [Getting Started](https://nbarkhina.github.io/DosWasmX) | [Compile from Source](https://nbarkhina.github.io/DosWasmX/compile-from-source) | [Windows 98](https://nbarkhina.github.io/DosWasmX/windows-98)