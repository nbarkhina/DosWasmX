# DOS Wasm X
Welcome to the online documentation for DOS Wasm X.
# Getting Started
You will need:
1. A [release](https://github.com/nbarkhina/DosWasmX/releases) of DOS Wasm X **or** a Linux machine to compile from source
2. A web server **or** Docker to host DOS Wasm X
3. A decent computer with a modern web browser
4. Something to play, like a game or an app

First, get yourself a copy of DOS Wasm X.
# Getting DOS Wasm X
You can (1) [download a release](https://github.com/nbarkhina/DosWasmX/releases) or (2) [compile the emulator from source](https://nbarkhina.github.io/DosWasmX/compile-from-source).
# Hosting and Running
DosWasmX is a web-based DOS emulator.
It is hosted by a web server and runs in your web browser.
Simply host the files from the release, or that you compiled yourself, on a web server, then browse there.
For example, if you are running Apache2 on a Linux server named `foo`, and you added a folder called `doswasmx` in `/var/www/html` with the DosWasmX release or compiled files, then you can run DosWasmX by simply opening a browser to `http://foo/doswasmx` and your browser will start the app.
This assumes that your web server will treat `index.html` as the default page.
# Settings
Before you startup DOS Wasm X, you should configure your preferred `Settings` for your virtual machine.<br/>
![Settings](https://nbarkhina.github.io/DosWasmX/settings.png)<br/>
### _NOTE: You cannot resize the virtual disk later_
The size you pick now will be the size later.
You can always export the hard drive and load a new one, but always make sure to select the size you need for your use up-front.
# Operating Systems
The next step is to pick an operating system.
## DOS
If you are planning to do everything in `DOS` mode, like play DOS games, there is no need to install an operating system.
Simply drag and drop a ZIP file of whatever game or app you want to play, and DOS Wasm X will startup automatically.
Keep in mind your hard disk will __NOT__ be saved automatically.
Before you close your web browser, to save changes, click __Save Drive__ in the menu.<br/>
![Settings](https://nbarkhina.github.io/DosWasmX/save-drive.png)<br/>
## Windows
You can install Windows 95 or Windows 98 Second Edition on DOS Wasm X.
For instructions on Windows 98, see the [Windows 98 page here](https://nbarkhina.github.io/DosWasmX/windows-98).
#### _DOS Wasm X Online Documentation_
#### [DOS Commands](https://nbarkhina.github.io/DosWasmX/dos-commands) | [Getting Started](https://nbarkhina.github.io/DosWasmX) | [Compile from Source](https://nbarkhina.github.io/DosWasmX/compile-from-source) | [Windows 98](https://nbarkhina.github.io/DosWasmX/windows-98)