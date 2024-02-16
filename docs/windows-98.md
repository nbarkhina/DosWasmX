# Installing Windows 98
To install Windows 98, you should use a __bootable ISO of Windows 98 Second Edition__, such as the one that can be found on archive.org.
When you first run [DOS Wasm X](https://github.com/nbarkhina/DosWasmX) with your web browser, you will see a startup screen like this.</br>
![Startup](https://nbarkhina.github.io/doswasmx/win98-01-start.png)</br>
Drag the Windows 98 Second Edition ISO from your file explorer onto the square that says `Drag/Drop Files`.</br>
[DOS Wasm X](https://github.com/nbarkhina/DosWasmX) will mount the ISO, boot it, and start the Windows installer.</br>
Run through the Windows installation like you would have on a normal computer.
Once installation is complete, which will take a while (depending on your computer's CPU power), be sure to tell Windows to Shut Down.
Shutting down Windows will automaticaly save your new virtual disk to your browser cache, allowing you to close the window and come back later to start it back up again.
# Booting Into Windows 98
When you shutdown Windows 98 on [DOS Wasm X](https://github.com/nbarkhina/DosWasmX) you will return to the `Z:\>` command line.
It will look like this.</br>
![Shutdown](https://nbarkhina.github.io/doswasmx/win98-02-shutdown.png)</br>
If you want to get back into Windows 98 from here, simply type `boot c:` as instructed by the prompt.
This command will tell [DOS Wasm X](https://github.com/nbarkhina/DosWasmX) to boot the C: drive which is the drive where you installed Windows 98 Second Edition earlier.
## Windows 98 SR1 White Screen
There is a known issue with Windows 98 SR1, when installed using a ZIP file, or possibly also with an ISO, but so far only tested with a ZIP file.
When you shutdown Windows 98 SR1, and try to reboot it using `boot c:` from the `Z:\>` command line, Windows 98 fails to boot and "white screens".
The emulator throws an error and stops execution.
This does not happen with Windows 98 Second Edition, but does happen with Windows 98 SR1, the first release of Windows 98.
This issue has been logged [here](https://github.com/nbarkhina/DosWasmX/issues/2) as a known issue with Windows 98 SR1.
If you are having this problem, unfortunately the only option is to delete your hard disk and install Windows 98 Second Edition.
#### _DOS Wasm X Online Documentation_
#### [DOS Commands](https://nbarkhina.github.io/doswasmx/dos-commands) | [Getting Started](https://nbarkhina.github.io/doswasmx) | [Compile from Source](https://nbarkhina.github.io/doswasmx/compile-from-source) | [Windows 98](https://nbarkhina.github.io/doswasmx/windows-98)