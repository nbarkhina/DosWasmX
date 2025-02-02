#include <iostream>
#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#endif
#ifdef LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

extern char fps_text[50];
SDL_Texture* gameTexture;
extern int doswidth;
extern int dosheight;
int audioDeviceId = 0;
int16_t resampled_out_buf[64000];

#include "neil_vars.h"

extern struct NeilButtons neilbuttons;


#ifdef _WIN32
#define USE_XINPUT //COMMENT OUT TO FALL BACK TO SDL JOYSTICK CODE (UNRELIABLE)
#endif

#ifdef USE_XINPUT
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
XINPUT_STATE state;
int xGamepadIndex = -1;
#endif

extern bool redrawNextFrame;


SDL_Joystick* joyStick = NULL;
SDL_GameController* gameController = NULL;
bool gamepadConnected = false;
TTF_Font* font = TTF_OpenFont("res/arial.ttf", 24);
SDL_Color fontcolor = { 255, 255, 255 };
SDL_Window* window;
SDL_Renderer* renderer;

// Framerate control:
const int FPS = 60;
const int DELAY = 1000.0f / FPS;
int axis0 = 0;
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;
int axis4 = 0;
int axis5 = 0;
extern Uint8* keyboardState;
bool runApp = true;

SDL_Rect rect;

extern unsigned char neil_back_buffer[16788288];

bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool startKey = false;
bool selectKey = false;
bool aKey = false;
bool bKey = false;
int xLocation = 0;
int yLocation = 0;


#include <keyboard.h>
#include <unordered_map>

// Define a mapping from JavaScript keycodes to SDL_Scancode values
extern std::unordered_map<int, SDL_Scancode> keycodeToScancode;

static const struct { unsigned short retroID; int dosboxID; } keymap[] =
{
	{SDL_SCANCODE_1, KBD_1}, {SDL_SCANCODE_2, KBD_2}, {SDL_SCANCODE_3, KBD_3}, {SDL_SCANCODE_4, KBD_4},
	{SDL_SCANCODE_5, KBD_5}, {SDL_SCANCODE_6, KBD_6}, {SDL_SCANCODE_7, KBD_7}, {SDL_SCANCODE_8, KBD_8},
	{SDL_SCANCODE_9, KBD_9}, {SDL_SCANCODE_0, KBD_0}, {SDL_SCANCODE_A, KBD_a}, {SDL_SCANCODE_B, KBD_b},
	{SDL_SCANCODE_C, KBD_c}, {SDL_SCANCODE_D, KBD_d}, {SDL_SCANCODE_E, KBD_e}, {SDL_SCANCODE_F, KBD_f},
	{SDL_SCANCODE_G, KBD_g}, {SDL_SCANCODE_H, KBD_h}, {SDL_SCANCODE_I, KBD_i}, {SDL_SCANCODE_J, KBD_j},
	{SDL_SCANCODE_K, KBD_k}, {SDL_SCANCODE_L, KBD_l}, {SDL_SCANCODE_M, KBD_m}, {SDL_SCANCODE_N, KBD_n},
	{SDL_SCANCODE_O, KBD_o}, {SDL_SCANCODE_P, KBD_p}, {SDL_SCANCODE_Q, KBD_q}, {SDL_SCANCODE_R, KBD_r},
	{SDL_SCANCODE_S, KBD_s}, {SDL_SCANCODE_T, KBD_t}, {SDL_SCANCODE_U, KBD_u}, {SDL_SCANCODE_V, KBD_v},
	{SDL_SCANCODE_W, KBD_w}, {SDL_SCANCODE_X, KBD_x}, {SDL_SCANCODE_Y, KBD_y}, {SDL_SCANCODE_Z, KBD_z},
	{SDL_SCANCODE_F1, KBD_f1}, {SDL_SCANCODE_F2, KBD_f2}, {SDL_SCANCODE_F3, KBD_f3}, {SDL_SCANCODE_F4, KBD_f4},
	{SDL_SCANCODE_F5, KBD_f5}, {SDL_SCANCODE_F6, KBD_f6}, {SDL_SCANCODE_F7, KBD_f7}, {SDL_SCANCODE_F8, KBD_f8},
	{SDL_SCANCODE_F9, KBD_f9}, {SDL_SCANCODE_F10, KBD_f10}, {SDL_SCANCODE_F11, KBD_f11}, {SDL_SCANCODE_F12, KBD_f12},
	{SDL_SCANCODE_ESCAPE, KBD_esc}, {SDL_SCANCODE_TAB, KBD_tab}, {SDL_SCANCODE_BACKSPACE, KBD_backspace},
	{SDL_SCANCODE_RETURN, KBD_enter}, {SDL_SCANCODE_SPACE, KBD_space}, {SDL_SCANCODE_LALT, KBD_leftalt},
	{SDL_SCANCODE_RALT, KBD_rightalt}, {SDL_SCANCODE_LCTRL, KBD_leftctrl}, {SDL_SCANCODE_RCTRL, KBD_rightctrl},
	{SDL_SCANCODE_LSHIFT, KBD_leftshift}, {SDL_SCANCODE_RSHIFT, KBD_rightshift}, {SDL_SCANCODE_CAPSLOCK, KBD_capslock},
	{SDL_SCANCODE_SCROLLLOCK, KBD_scrolllock},
	{SDL_SCANCODE_NUMLOCKCLEAR, KBD_numlock},
	{SDL_SCANCODE_MINUS, KBD_minus},
	{SDL_SCANCODE_EQUALS, KBD_equals}, {SDL_SCANCODE_BACKSLASH, KBD_backslash}, {SDL_SCANCODE_LEFTBRACKET, KBD_leftbracket},
	{SDL_SCANCODE_RIGHTBRACKET, KBD_rightbracket}, {SDL_SCANCODE_SEMICOLON, KBD_semicolon},
	{SDL_SCANCODE_APOSTROPHE , KBD_quote},
	{SDL_SCANCODE_PERIOD, KBD_period}, {SDL_SCANCODE_COMMA, KBD_comma}, {SDL_SCANCODE_SLASH, KBD_slash},
	//{RETROK_PRINT, KBD_printscreen}, {RETROK_SYSREQ, KBD_printscreen}, {RETROK_PAUSE, KBD_pause},
	{SDL_SCANCODE_INSERT, KBD_insert}, {SDL_SCANCODE_HOME, KBD_home}, {SDL_SCANCODE_PAGEUP, KBD_pageup},
	{SDL_SCANCODE_PAGEDOWN, KBD_pagedown}, {SDL_SCANCODE_DELETE, KBD_delete}, {SDL_SCANCODE_END, KBD_end},
	{SDL_SCANCODE_LEFT, KBD_left}, {SDL_SCANCODE_UP, KBD_up}, {SDL_SCANCODE_DOWN, KBD_down}, {SDL_SCANCODE_RIGHT, KBD_right},
	{SDL_SCANCODE_KP_1, KBD_kp1}, {SDL_SCANCODE_KP_2, KBD_kp2}, {SDL_SCANCODE_KP_3, KBD_kp3}, {SDL_SCANCODE_KP_4, KBD_kp4},
	{SDL_SCANCODE_KP_5, KBD_kp5}, {SDL_SCANCODE_KP_6, KBD_kp6}, {SDL_SCANCODE_KP_7, KBD_kp7}, {SDL_SCANCODE_KP_8, KBD_kp8},
	{SDL_SCANCODE_KP_9, KBD_kp9}, {SDL_SCANCODE_KP_0, KBD_kp0},
	{SDL_SCANCODE_KP_DIVIDE, KBD_kpdivide},
	//{RETROK_KP_MULTIPLY, KBD_kpmultiply}, {RETROK_KP_MINUS, KBD_kpminus},
	//{RETROK_KP_PLUS, KBD_kpplus}, {RETROK_KP_ENTER, KBD_kpenter}, {RETROK_KP_PERIOD, KBD_kpperiod},
	//{SDL_SCANCODE_GRAVE, KBD_grave}
};



void drawTexture(SDL_Texture* texture, int sourceX, int sourceY, int sourceW, int sourceH,
	int destX, int destY, int destW, int destH)
{
	SDL_Rect SourceR;

	SourceR.x = sourceX;
	SourceR.y = sourceY;
	SourceR.w = sourceW;
	SourceR.h = sourceH;

	SDL_Rect DestR;

	DestR.x = destX;
	DestR.y = destY;
	DestR.w = destW;
	DestR.h = destH;

	if (sourceX == -1 && destX == -1)
	{
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	}
	else if (sourceX == -1)
	{
		SDL_RenderCopy(renderer, texture, NULL, &DestR);
	}
	else if (destX == -1)
	{
		SDL_RenderCopy(renderer, texture, &SourceR, NULL);
	}
	else
	{
		SDL_RenderCopy(renderer, texture, &SourceR, &DestR);
	}


}

void drawText(const char* text, int x, int y)
{
	SDL_Surface* sf = TTF_RenderText_Solid(font, text, fontcolor);
	SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, sf);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(fontTexture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { x, y, texW, texH };
	SDL_RenderCopy(renderer, fontTexture, nullptr, &dstrect);

	SDL_FreeSurface(sf);

	//if we don't destroy this you will see in 
	//windows task manager the memory will keep growing
	SDL_DestroyTexture(fontTexture);
}

void mainLoop();
extern void runDosbox();


int main(int argc, char* argv[])
{


	Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO;

	if (SDL_Init(flags) < 0) {
		printf("Could not initialize SDL\n");
	}

	window = SDL_CreateWindow("DosWasmX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		doswidth, dosheight, 0);

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
	}

	gameTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		doswidth, dosheight);

	SDL_AudioSpec AudioSettings = { 0 };
	AudioSettings.freq = 48000;
	AudioSettings.format = AUDIO_S16;
	AudioSettings.channels = 2;
	SDL_AudioSpec AudioSettingsObtained = { 0 };
	SDL_AudioDeviceID deviceid = SDL_OpenAudioDevice(NULL, 0, &AudioSettings, &AudioSettingsObtained, 1);
	SDL_PauseAudioDevice(deviceid, 0);
	audioDeviceId = deviceid;


	//initialize font system
	TTF_Init();
	font = TTF_OpenFont("res/arial.ttf", 24);


    runDosbox();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_CloseAudio();
	SDL_Quit();


	return 0;
}

#include <mouse.h>
int lastLeftMousePressed = 0;
int lastRightMousePressed = 0;
extern MOUSE_EMULATION user_cursor_emulation;
extern bool user_cursor_locked;

extern bool lastGravePressed;
extern bool globalOnscreenKeyboard;


void resetNeilButtons();

extern int user_cursor_x;
extern int user_cursor_y;
extern int user_cursor_sw;
extern int user_cursor_sh;

#include <sdlmain.h>


extern "C" {
	void neil_send_dos_controls(char* controls, char* axis0, char* axis1,
		unsigned char* keyArray, int keyLength);

	void neil_send_mouse_movement(int mouseX, int mouseY);
}

unsigned char keyArray[500];
char controls[10];
Uint32 current_frameStart_windows = 0;

void winDosControls()
{
	sprintf(controls, "0000000000");

	//MOUSE
	int mouseX = 0;
	int mouseY = 0;
	int mouseXPosition = 0;
	int mouseYPosition = 0;
	int mouseLeftPressed = 0;
	int mouseRightPressed = 0;
	int mousePressed = SDL_GetMouseState(&mouseXPosition, &mouseYPosition);
	SDL_GetRelativeMouseState(&mouseX, &mouseY);

	if (mousePressed == 1)
	{
		mouseLeftPressed = 1;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(SDL_DISABLE);
	}

	if (mousePressed == 4)
		mouseRightPressed = 1;

	if (mouseLeftPressed)
		controls[4] = '1';

	if (mouseRightPressed)
		controls[5] = '1';


	//KEYBOARD
	Uint8* keyboardStateLocal = (Uint8*)SDL_GetKeyboardState(NULL);
	int keyLength = 0;
	
	for (unsigned char keycode = 0; keycode < 255; keycode++)
	{
		bool down = keyboardStateLocal[keycode];
		if (down)
		{
			keyArray[keyLength] = keycode;
			keyLength++;
		}
	}


	if (keyboardStateLocal[SDL_SCANCODE_ESCAPE])
	{
#ifdef _WIN32
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_ShowCursor(SDL_ENABLE);
#endif
	}

	std::string axis0 = std::to_string(mouseX);
	std::string axis1 = std::to_string(mouseY);

	neil_send_dos_controls(controls, (char*)axis0.c_str(), (char*)axis1.c_str(), keyArray, keyLength);

	if (mouseX != 0 || mouseY != 0)
	{
		neil_send_mouse_movement(mouseX, mouseY);
	}

}

void mainRender()
{
	//clear screen
	SDL_SetRenderDrawColor(renderer, 22, 50, 90, 255);
	SDL_RenderClear(renderer);


	SDL_Event windowEvent;

	if (SDL_PollEvent(&windowEvent) != 0)
	{
		if (windowEvent.type == SDL_QUIT)
		{
			runApp = false;
		}
	}

	void* pixels;
	int pitch;
	SDL_LockTexture(gameTexture, nullptr, &pixels, &pitch);

	// filling texture with pixel data 
	for (int y = 0; y < dosheight; ++y)
	{
		for (int x = 0; x < doswidth; ++x)
		{
			//if (x < 640 && y < 480)
			{
				Uint32* pixelRow = (Uint32*)((Uint8*)pixels + y * pitch);
				int ptr = (y * doswidth + x) * 4;

				Uint32 pixelColor =
					(neil_back_buffer[ptr] << 16) |
					(neil_back_buffer[ptr + 1] << 8) |
					(neil_back_buffer[ptr + 2]) |
					(neil_back_buffer[ptr + 3] << 24);

				pixelRow[x] = pixelColor;
			}
		}
	}
	// unlock texture 
	SDL_UnlockTexture(gameTexture);

	SDL_RenderCopy(renderer, gameTexture, NULL, NULL);

	//draw the screen
	SDL_RenderPresent(renderer);
}

void neil_resolution_changed(int width, int height)
{
	printf("neil_resolution_changed %d %d\n", width, height);

	//resize texture
	SDL_DestroyTexture(gameTexture);
	gameTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		doswidth, dosheight);

	//set window size
	SDL_SetWindowSize(window, width, height);
}

void neil_update_frame(unsigned char* data)
{

}

/* STUBS */

void VOODOO_PCI_InitEnable(unsigned int x) {}
void VOODOO_PCI_Enable(bool x) {}
void  VOODOO_PCI_SetLFB(unsigned int x) {}

/* STUBS */

void update_capture_fmt_menu(void) {}