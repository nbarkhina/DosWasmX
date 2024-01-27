# DOS Wasm X
intro

Supports the following features -
- TBD

You can try it here: https://www.neilb.net/doswasmx/

# Build Instructions
You will need a Linux environment to build DOS Wasm X

- create a folder outside of this repo to install emscripten
- git clone https://github.com/emscripten-core/emsdk.git
- cd emsdk
- ./emsdk install 3.1.49
- ./emsdk activate 3.1.49
- source ./emsdk_env.sh
- replace Binaryen with special version
  - copy the file wasm-opt from this repo `code/wasm-opt` to the emscripten folder here `emsdk/upstream/bin/wasm-opt`
  - this is needed because default Binaryen does not support Exceptions and Asyncify together
  - huge credit goes to @Caiiiycuk for developing this! 
  - see references below if you prefer to get wasm-opt directly from his releases page
- navigate back to the code folder in the DosWasmX repo
- run `make`
- you will get a build error towards the end saying EM_CACHE_IS_LOCKED
  - to get past this error simply copy the faulting emcc command from the terminal and run it manually (See screenshot below)
  - this should succeed and then run `make` again to finish building
  - later builds should not get this error after you do this one time fix
- then copy these 2 files from the code\ folder into the dist\ folder
  - main.js
  - main.wasm

The emscripten instructions above are a one time setup however you will need to always run `source ./emsdk_env.sh` every time you close the terminal. This is because the emscripten compiler does not get saved to the PATH

![builderror](screenshots/builderror2.PNG)

# Hosting
TBD

Copy everything in the `dist\` folder to your web server to host the app yourself

```javascript

var DOSWASMSETTINGS = {
    CLOUDSAVEURL: "",
    ISOURL: "",
    DEFAULTIMG: ""
}

```

# Installing Windows
TBD

![screenshot](screenshots/win95error.PNG)

# Common DOS Commands
TBD

# Screenshots
TBD

# References
- DOSBox-X https://github.com/joncampbell123/dosbox-x
- Binaryen with Exceptions and Asyncify https://github.com/caiiiycuk/binaryen-fwasm-exceptions
- Emscripten https://github.com/emscripten-core/emscripten
