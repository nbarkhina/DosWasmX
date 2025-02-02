/*
 *  Copyright (C) 2002-2021  The DOSBox Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

//#include "bitmapinfoheader.h"
#include "dosbox.h"
#include "control.h"
#include "hardware.h"
#include "logging.h"
#include "setup.h"
#include "support.h"
#include "mem.h"
#include "mapper.h"
#include "pic.h"
#include "mixer.h"
#include "render.h"
#include "cross.h"
#include "wave_mmreg.h"

std::string capturedir;
Bitu CaptureState = 0;
bool video_debug_overlay = false;
bool skip_encoding_unchanged_frames = false, show_recorded_filename = true;
std::string pathvid = "", pathwav = "", pathmtw = "", pathmid = "", pathopl = "", pathscr = "", pathprt = "", pathpcap = "";
bool native_zmbv = false;
bool export_ffmpeg = false;

bool enable_autosave = false;
int autosave_second = 0, autosave_count = 0, autosave_start[10], autosave_end[10], autosave_last[10];
std::string autosave_name[10];

void CAPTURE_MultiTrackAddWave(uint32_t freq, uint32_t len, int16_t* data, const char* name) {}
void CAPTURE_Init(void) {}
void HARDWARE_Init(void) {}

void CAPTURE_StartCapture(void) {
}

void CAPTURE_StopCapture(void) {
}

void CAPTURE_StartWave(void) {

}

void CAPTURE_StopWave(void) {

}

void CAPTURE_StartMTWave(void) {

}

void CAPTURE_StopMTWave(void) {

}


void CAPTURE_StartOPL(void) {

}

void CAPTURE_StopOPL(void) {

}


void CAPTURE_VideoStart() {
}

void CAPTURE_VideoStop() {
}


void CAPTURE_ScreenShotEvent(bool pressed) {
}

void CAPTURE_RawScreenShotEvent(bool pressed) {
}

void Capture_WritePacket(bool /*send*/, const unsigned char* buf, size_t len) {}

void CAPTURE_AddWave(uint32_t freq, uint32_t len, int16_t* data) {}

void CAPTURE_MTWaveEvent(bool pressed) {}

void CAPTURE_NetworkEvent(bool pressed) {}
void CAPTURE_WaveEvent(bool pressed) {}

void CAPTURE_AddMidi(bool sysex, Bitu len, uint8_t* data) {}

void CAPTURE_MidiEvent(bool pressed) {}

void CAPTURE_Destroy(Section* sec) {}

FILE* OpenCaptureFile(const char* type, const char* ext) { return NULL; }