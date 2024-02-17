MAKEFLAGS += --no-builtin-rules

CFILES := \
    minizip/miniunz.c \
    minizip/minizip.c \
    minizip/mztools.c \
	src/hardware/imfc_rom.c \
	src/hardware/RetroWaveLib/Board/MasterGear.c \
    src/hardware/RetroWaveLib/Board/MiniBlaster.c \
    src/hardware/RetroWaveLib/Board/OPL3.c \
    src/hardware/RetroWaveLib/Platform/Linux_SPI.c \
    src/hardware/RetroWaveLib/Platform/POSIX_SerialPort.c \
    src/hardware/RetroWaveLib/Platform/Win32_SerialPort.c \
    src/hardware/RetroWaveLib/Protocol/Serial.c \
    src/hardware/RetroWaveLib/RetroWave.c

CPPFILES := \
    main.cpp \
    src/builtin/25_com.cpp \
    src/builtin/28_com.cpp \
    src/builtin/50_com.cpp \
    src/builtin/append_exe.cpp \
    src/builtin/buffers_com.cpp \
    src/builtin/chkdsk_exe.cpp \
    src/builtin/cwsdpmi_exe.cpp \
    src/builtin/debug_exe.cpp \
    src/builtin/defrag_exe.cpp \
    src/builtin/device_com.cpp \
    src/builtin/diskcopy_exe.cpp \
    src/builtin/dos32a_exe.cpp \
    src/builtin/dos4gw_exe.cpp \
    src/builtin/dosidle_exe.cpp \
    src/builtin/dsxmenu_exe_pc.cpp \
    src/builtin/dsxmenu_exe_pc98.cpp \
    src/builtin/edit_com.cpp \
    src/builtin/fcbs_com.cpp \
    src/builtin/fc_exe.cpp \
    src/builtin/fdisk_exe.cpp \
    src/builtin/files_com.cpp \
    src/builtin/find_exe.cpp \
    src/builtin/format_exe.cpp \
    src/builtin/hexmem16_exe.cpp \
    src/builtin/hexmem32_exe.cpp \
    src/builtin/lastdriv_com.cpp \
    src/builtin/mem_com.cpp \
    src/builtin/move_exe.cpp \
    src/builtin/print_com.cpp \
    src/builtin/replace_exe.cpp \
    src/builtin/sort_exe.cpp \
    src/builtin/sys_com.cpp \
    src/builtin/xcopy_exe.cpp \
    src/cpu/callback.cpp \
    src/cpu/core_full.cpp \
    src/cpu/core_normal.cpp \
    src/cpu/core_normal_286.cpp \
    src/cpu/core_normal_8086.cpp \
    src/cpu/core_prefetch.cpp \
    src/cpu/core_prefetch_286.cpp \
    src/cpu/core_prefetch_8086.cpp \
    src/cpu/core_simple.cpp \
    src/cpu/cpu.cpp \
    src/cpu/flags.cpp \
    src/cpu/mmx.cpp \
    src/cpu/modrm.cpp \
    src/cpu/paging.cpp \
    src/dosbox.cpp \
    src/dos/cdrom.cpp \
    src/dos/cdrom_image.cpp \
    src/dos/dos.cpp \
    src/dos/dos_classes.cpp \
    src/dos/dos_devices.cpp \
    src/dos/dos_execute.cpp \
    src/dos/dos_files.cpp \
    src/dos/dos_ioctl.cpp \
    src/dos/dos_keyboard_layout.cpp \
    src/dos/dos_memory.cpp \
    src/dos/dos_misc.cpp \
    src/dos/dos_mscdex.cpp \
    src/dos/dos_programs.cpp \
    src/dos/dos_tables.cpp \
    src/dos/drives.cpp \
    src/dos/drive_cache.cpp \
    src/dos/drive_fat.cpp \
    src/dos/drive_iso.cpp \
    src/dos/drive_local.cpp \
    src/dos/drive_overlay.cpp \
    src/dos/drive_physfs.cpp \
    src/dos/drive_virtual.cpp \
    src/fpu/fpu.cpp \
    src/gui/menu.cpp \
    src/gui/menu_callback.cpp \
    src/gui/render.cpp \
    src/gui/render_scalers.cpp \
    src/gui/sdlmain.cpp \
    src/gui/sdl_gui.cpp \
    src/gui/sdl_mapper.cpp \
    src/hardware/8255.cpp \
    src/hardware/adlib.cpp \
    src/hardware/cmos.cpp \
    src/hardware/dbopl.cpp \
    src/hardware/disney.cpp \
    src/hardware/dma.cpp \
    src/hardware/dongle.cpp \
    src/hardware/floppy.cpp \
    src/hardware/gameblaster.cpp \
    src/hardware/glide.cpp \
    src/hardware/gus.cpp \
    src/hardware/hardopl.cpp \
    src/hardware/hardware.cpp \
    src/hardware/ide.cpp \
    src/hardware/innova.cpp \
    src/hardware/iohandler.cpp \
    src/hardware/ipx.cpp \
    src/hardware/ipxserver.cpp \
    src/hardware/joystick.cpp \
    src/hardware/keyboard.cpp \
    src/hardware/mame/fmopl.cpp \
    src/hardware/mame/saa1099.cpp \
    src/hardware/mame/sn76496.cpp \
    src/hardware/mame/ymdeltat.cpp \
    src/hardware/mame/ymf262.cpp \
    src/hardware/memory.cpp \
    src/hardware/mixer.cpp \
    src/hardware/mpu401.cpp \
    src/hardware/ne2000.cpp \
    src/hardware/nukedopl.cpp \
    src/hardware/opl.cpp \
    src/hardware/opl2board/opl2board.cpp \
    src/hardware/opl3duoboard/opl3duoboard.cpp \
    src/hardware/parport/directlpt.cpp \
    src/hardware/parport/filelpt.cpp \
    src/hardware/parport/parport.cpp \
    src/hardware/parport/printer.cpp \
    src/hardware/parport/printer_charmaps.cpp \
    src/hardware/parport/printer_redir.cpp \
    src/hardware/pci_bus.cpp \
    src/hardware/pcspeaker.cpp \
    src/hardware/pic.cpp \
    src/hardware/ps1_sound.cpp \
    src/hardware/reSID/envelope.cpp \
    src/hardware/reSID/extfilt.cpp \
    src/hardware/reSID/filter.cpp \
    src/hardware/reSID/pot.cpp \
    src/hardware/reSID/sid.cpp \
    src/hardware/reSID/version.cpp \
    src/hardware/reSID/voice.cpp \
    src/hardware/reSID/wave.cpp \
    src/hardware/reSID/wave6581_PST.cpp \
    src/hardware/reSID/wave6581_PS_.cpp \
    src/hardware/reSID/wave6581_P_T.cpp \
    src/hardware/reSID/wave6581__ST.cpp \
    src/hardware/reSID/wave8580_PST.cpp \
    src/hardware/reSID/wave8580_PS_.cpp \
    src/hardware/reSID/wave8580_P_T.cpp \
    src/hardware/reSID/wave8580__ST.cpp \
    src/hardware/RetroWaveLib/RetroWave_DOSBoX.cpp \
    src/hardware/sblaster.cpp \
    src/hardware/serialport/directserial.cpp \
    src/hardware/serialport/libserial.cpp \
    src/hardware/serialport/misc_util.cpp \
    src/hardware/serialport/nullmodem.cpp \
    src/hardware/serialport/serialdummy.cpp \
    src/hardware/serialport/serialfile.cpp \
    src/hardware/serialport/seriallog.cpp \
    src/hardware/serialport/serialmouse.cpp \
    src/hardware/serialport/serialport.cpp \
    src/hardware/serialport/softmodem.cpp \
    src/hardware/tandy_sound.cpp \
    src/hardware/timer.cpp \
    src/hardware/vga.cpp \
    src/hardware/vga_ati.cpp \
    src/hardware/vga_attr.cpp \
    src/hardware/vga_crtc.cpp \
    src/hardware/vga_dac.cpp \
    src/hardware/vga_draw.cpp \
    src/hardware/vga_gfx.cpp \
    src/hardware/vga_memory.cpp \
    src/hardware/vga_misc.cpp \
    src/hardware/vga_other.cpp \
    src/hardware/vga_paradise.cpp \
    src/hardware/vga_pc98_cg.cpp \
    src/hardware/vga_pc98_crtc.cpp \
    src/hardware/vga_pc98_dac.cpp \
    src/hardware/vga_pc98_egc.cpp \
    src/hardware/vga_pc98_gdc.cpp \
    src/hardware/vga_pc98_gdc_draw.cpp \
    src/hardware/vga_s3.cpp \
    src/hardware/vga_seq.cpp \
    src/hardware/vga_tseng.cpp \
    src/hardware/vga_xga.cpp \
    src/ints/bios.cpp \
    src/ints/bios_disk.cpp \
    src/ints/bios_keyboard.cpp \
    src/ints/bios_memdisk.cpp \
    src/ints/bios_vhd.cpp \
    src/ints/ems.cpp \
    src/ints/int10.cpp \
    src/ints/int10_char.cpp \
    src/ints/int10_memory.cpp \
    src/ints/int10_misc.cpp \
    src/ints/int10_modes.cpp \
    src/ints/int10_pal.cpp \
    src/ints/int10_put_pixel.cpp \
    src/ints/int10_vesa.cpp \
    src/ints/int10_video_state.cpp \
    src/ints/int10_vptable.cpp \
    src/ints/int_dosv.cpp \
    src/ints/mouse.cpp \
    src/ints/pc98_lio.cpp \
    src/ints/qcow2_disk.cpp \
    src/ints/xms.cpp \
    src/libs/gui_tk/gui_tk.cpp \
    src/misc/clipboard.cpp \
    src/misc/cross.cpp \
    src/misc/ethernet.cpp \
    src/misc/ethernet_nothing.cpp \
    src/misc/ethernet_pcap.cpp \
    src/misc/ethernet_slirp.cpp \
    src/misc/iconvpp.cpp \
    src/misc/messages.cpp \
    src/misc/mkdir_p.cpp \
    src/misc/programs.cpp \
    src/misc/regionalloctracking.cpp \
    src/misc/savestates.cpp \
    src/misc/setup.cpp \
    src/misc/shiftjis.cpp \
    src/misc/support.cpp \
    src/output/output_surface.cpp \
    src/output/output_tools.cpp \
    src/output/output_ttf.cpp \
    src/shell/shell.cpp \
    src/shell/shell_batch.cpp \
    src/shell/shell_cmds.cpp \
    src/shell/shell_misc.cpp

FILES := $(patsubst %.c,%.o,$(CFILES)) $(patsubst %.cpp,%.o,$(CPPFILES))

MYFLAGS := \
    -I./include \
    -I./zlib \
	-D__LIBRETRO__ \
    -DDISABLE_DYNAREC \
	-Wno-macro-redefined \
	-O3 \
    -s USE_SDL=2 \
    -std=c++14 \
	-fwasm-exceptions

MYFLAGSC := \
    -I./include \
    -I./zlib \
	-D__LIBRETRO__ \
    -DDISABLE_DYNAREC \
	-Wno-macro-redefined \
	-O3 \
    -s USE_SDL=2 \
	-fwasm-exceptions

all: main.js
	mv main.js ../dist/main.js
	mv main.wasm ../dist/main.wasm

main.js: $(FILES)
	emcc -o $@ $(FILES) \
	-s USE_ZLIB=1 \
    -s ASYNCIFY \
    -std=c++14 \
	-fwasm-exceptions \
	-s TOTAL_MEMORY=536870912 \
    -s ASYNCIFY_STACK_SIZE=65535 \
	--use-preload-plugins \
	-s ASSERTIONS=0 \
	-s LLD_REPORT_UNDEFINED \
	-O3 \
	-s EXIT_RUNTIME=0 \
	-s EXTRA_EXPORTED_RUNTIME_METHODS="['callMain','cwrap']" \
	-s EXPORTED_FUNCTIONS="['_main','_neilGetSoundBufferResampledAddress', \
    '_neil_serialize','_neil_unserialize','_neilGetAudioWritePosition', \
    '_neil_toggle_fps','_neil_export_files','_neil_show_toast', \
    '_neil_clear_autoexec','_neil_exit_to_dos','_neil_send_key', \
    '_neil_toggle_pause','_neil_update_cpu','_neil_send_ctrlaltdel', \
    '_neil_toggle_16_bit_color_fix','_neil_update_autoexec_additional', \
    '_neil_toggle_always_use_backbuffer','_neil_change_iso','_neil_send_dos_commands', \
    '_neil_load_floppy','_neil_change_floppy', \
    '_neil_turbo']" \
	-s INVOKE_RUN=0 \
    -sUSE_SDL=2 -sUSE_SDL_TTF=2

%.o : %.cpp
	emcc -c $< -o $@ \
	$(MYFLAGS)

%.o : %.c
	emcc -c $< -o $@ \
	$(MYFLAGSC)

clean:
	@echo "Cleaning"
	@echo $(FILES)
	rm -fr *.o */*.o */*/*.o */*/*/*.o */*/*/*/*.o

cleandata:
	@echo "Cleaning data"