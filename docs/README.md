# DOS Wasm X
Welcome to the online documentation for DOS Wasm X.
# Getting Started
You will need:
1. A release of DOS Wasm X **or** a Linux machine to compile from source
2. A web server **or** Docker to host DOS Wasm X
3. A decent computer with a modern web browser
4. Something to play, like a game or an app

First, get yourself a copy of DOS Wasm X.
# Getting DOS Wasm X
You can [download a release](https://github.com/nbarkhina/DosWasmX/releases) or [compile the emulator from source](https://nbarkhina.github.io/doswasmx/compile-from-source).
# Settings
Before you startup DOS Wasm X, you should configure your preferred `Settings` for your virtual machine.<br/>
![Settings](https://nbarkhina.github.io/doswasmx/settings.png)<br/>
### _NOTE: You cannot resize the virtual disk later_
The size you pick now will be the size later.
You can always export the hard drive and load a new one, but always make sure to select the size you need for your use up-front.
# Operating Systems
The next step is to pick an operating system.
If you are planning to do everything in `DOS` mode, like play DOS games, there is no need to install an operating system.
Simply drag and drop a ZIP file of whatever game or app you want to play, and DOS Wasm X will startup automatically.
## DOS Commands
DOS Wasm X emulates DOS and supports all the commands found in the DOSBox-X emulator on which DOS Wasm X is based.
You can find out more in the [DOSBox-X online wiki](https://dosbox-x.com/wiki/).
# Installing Windows 95/98
To install Windows 95 or Windows 98, make a ZIP file of the Windows installer and drag it onto the startup screen.
DOS Wasm X will unpack the ZIP file and drop you into the `C:\WIN98` directory where you can then run `setup.exe` to start the install.
The directory name will be based on the name of the ZIP file you create.
Run through the Windows installation like you would have on a normal computer.<br/><br/>
Once installation is complete, which will take a while (depending on your computer's CPU power), be sure to tell Windows to Shut Down.
Shutting down Windows will automaticaly save your new virtual disk to your browser cache, allowing you to close the window and come back later to start it back up again.
#### _DOS Wasm X Online Documentation_
#### [Getting Started](https://nbarkhina.github.io/doswasmx) | [Compile from Source](https://nbarkhina.github.io/doswasmx/compile-from-source)