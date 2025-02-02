#include <iostream>
#ifdef __EMSCRIPTEN__
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <emscripten.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#endif
#ifdef LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

#include <config.h>

Uint8* keyboardState;

#include "neil_vars.h"

struct NeilButtons neilbuttons;


#include <fstream>
#include <string>
#include <sstream>

struct MyConfig neilConfiguration;

//overlay menu
void drawOverlay();
void processMenuItemButtons();
bool lastSaveStateKeyPressed = false;
bool lastLoadStateKeyPressed = false;
bool lastOverlayKeyPressed = false;
bool lastMenuUpPressed = false;
bool lastMenuDownPressed = false;
bool lastMenuOkPressed = false;
bool menuMoveUp = false;
bool menuMoveDown = false;
bool menuOk = false;
bool showOverlay = false;
bool firstBoot = true;
char menuItems[][30] = {
	"New Rom",
	"Toggle FPS",
	"Slow Down",
	"Speed Up",
	"Slower Mouse Speed",
	"Faster Mouse Speed",
	"On Screen Keyboard",
	"Exit to Dos",
	"Save Cloud Drive",
	"CPU Max",
	"Pause",
	"Full Screen",
};
int selectedMenuItem = 0;
void resetNeilButtons();
extern bool redrawNextFrame;


void processMenuItemButtons()
{
	int menuItemsCount = sizeof(menuItems) / 30;
	if (menuMoveDown) selectedMenuItem++;
	if (menuMoveUp) selectedMenuItem--;
	if (selectedMenuItem < 0) selectedMenuItem = menuItemsCount - 1;
	if (selectedMenuItem > menuItemsCount - 1) selectedMenuItem = 0;

	if (menuOk)
	{

#ifdef __EMSCRIPTEN__
		//"New Rom" - 0
		if (selectedMenuItem == 0)
		{
			EM_ASM(
				myApp.newRom();
			);
		}

		//"Toggle FPS" - 1
		if (selectedMenuItem == 1)
		{
			EM_ASM(
				myApp.toggleFPS();
			);
		}

		//"Slow Down" - 2
		if (selectedMenuItem == 2)
		{
			EM_ASM(
				myApp.slowDown();
			);
		}

		//"Speed Up" - 3
		if (selectedMenuItem == 3)
		{
			EM_ASM(
				myApp.speedUp();
			);
		}

		//"Slower Mouse Speed" - 4
		if (selectedMenuItem == 4)
		{
			EM_ASM(
				myApp.mouseDecreaseSpeed();
			);
		}

		//"Faster Mouse Speed" - 5
		if (selectedMenuItem == 5)
		{
			EM_ASM(
				myApp.mouseIncreaseSpeed();
			);
		}

		//"On Screen Keyboard" - 6
		if (selectedMenuItem == 6)
		{
			EM_ASM(
				myApp.toggleOnscreenKeyboard();
			);
		}

		//"Exit to Dos" - 7
		if (selectedMenuItem == 7)
		{
			EM_ASM(
				myApp.exitToDos();
			);
		}

		//"Save Cloud Drive" - 8
		if (selectedMenuItem == 8)
		{
			EM_ASM(
				myApp.saveHardDriveDiffs();
			);
		}

		//"CPU Max" - 9
		if (selectedMenuItem == 9)
		{
			EM_ASM(
				myApp.updateCPU('max');
			);
		}

		//"Pause" - 10
		if (selectedMenuItem == 10)
		{
			EM_ASM(
				myApp.togglePause();
			);
		}

		//"Full Screen" - 11
		if (selectedMenuItem == 11)
		{
			EM_ASM(
				myApp.fullscreen();
			);
		}
#endif

		showOverlay = false;
		redrawNextFrame = true;
	}
}

bool isPressedOnce(bool condition, bool* lastPressedVar)
{
	if (condition)
	{
		if (!*lastPressedVar)
		{
			*lastPressedVar = true;
			return true;
		}
	}
	else
		*lastPressedVar = false;

	return false;
}

bool isReleasedOnce(bool condition, bool* lastPressedVar)
{
	bool wasReleased = false;
	if (condition)
	{
		*lastPressedVar = true;
	}
	else
	{
		if (*lastPressedVar)
		{
			wasReleased = true;
		}
		*lastPressedVar = false;
	}

	return wasReleased;
}

void processOverlay()
{
	menuMoveUp = false;
	menuMoveDown = false;
	menuOk = false;

	if (isPressedOnce(keyboardState[SDL_SCANCODE_GRAVE], &lastOverlayKeyPressed))
	{
		if (!showOverlay)
		{
			selectedMenuItem = 0;
		}
		showOverlay = !showOverlay;
		redrawNextFrame = true;
	}


	if (showOverlay)
	{
		if (isPressedOnce(keyboardState[SDL_SCANCODE_UP], &lastMenuUpPressed)) menuMoveUp = true;
		if (isPressedOnce(keyboardState[SDL_SCANCODE_DOWN], &lastMenuDownPressed)) menuMoveDown = true;
		if (isReleasedOnce(
			keyboardState[SDL_SCANCODE_RETURN] || neilbuttons.aKey, 
			&lastMenuOkPressed)) menuOk = true;

		resetNeilButtons(); //don't process game buttons while overlay is showing
		processMenuItemButtons();
	}
}

void readConfig()
{
	try
	{

		std::ifstream infile("config.txt");
		std::string line;

		std::size_t pos;
		std::string newstr;

		int counter = 0;
		while (std::getline(infile, line))
		{
			// printf("Counter: %d Line %s\n", counter, line.c_str());


			if (counter == 0) strcpy(neilConfiguration.startupScript, line.c_str());
			if (counter == 1) strcpy(neilConfiguration.cpu, line.c_str());
			if (counter == 2) strcpy(neilConfiguration.ram, line.c_str());
			if (counter == 3) neilConfiguration.mouseMode = atoi(line.c_str());
			if (counter == 4) neilConfiguration.mouseXOffset = atoi(line.c_str());
			if (counter == 5) neilConfiguration.mouseYOffset = atoi(line.c_str());
			if (counter == 6) neilConfiguration.mobileMode = atoi(line.c_str());

			counter++;
		}

		if (neilConfiguration.mobileMode)
		{
			printf("mobileMode detected\n");
		}

		printf("Finished Reading Config\n");
	}
	catch (...)
	{
		printf("No Config File Found\n");
	}
}

#include <unordered_map>


std::vector<int> mouseXEvents;
std::vector<int> mouseYEvents;


// Define a mapping from JavaScript keycodes to SDL_Scancode values
std::unordered_map<int, SDL_Scancode> keycodeToScancode = {
	{8, SDL_SCANCODE_BACKSPACE},
	{9, SDL_SCANCODE_TAB},
	{13, SDL_SCANCODE_RETURN},
	{16, SDL_SCANCODE_LSHIFT},  // Left Shift
	{17, SDL_SCANCODE_LCTRL},   // Left Control
	{18, SDL_SCANCODE_LALT},    // Left Alt
	{19, SDL_SCANCODE_PAUSE},
	{20, SDL_SCANCODE_CAPSLOCK},
	{27, SDL_SCANCODE_ESCAPE},
	{32, SDL_SCANCODE_SPACE},
	{33, SDL_SCANCODE_PAGEUP},
	{34, SDL_SCANCODE_PAGEDOWN},
	{35, SDL_SCANCODE_END},
	{36, SDL_SCANCODE_HOME},
	{37, SDL_SCANCODE_LEFT},
	{38, SDL_SCANCODE_UP},
	{39, SDL_SCANCODE_RIGHT},
	{40, SDL_SCANCODE_DOWN},
	{45, SDL_SCANCODE_INSERT},
	{46, SDL_SCANCODE_DELETE},
	{48, SDL_SCANCODE_0},
	{49, SDL_SCANCODE_1},
	{50, SDL_SCANCODE_2},
	{51, SDL_SCANCODE_3},
	{52, SDL_SCANCODE_4},
	{53, SDL_SCANCODE_5},
	{54, SDL_SCANCODE_6},
	{55, SDL_SCANCODE_7},
	{56, SDL_SCANCODE_8},
	{57, SDL_SCANCODE_9},
	{65, SDL_SCANCODE_A},
	{66, SDL_SCANCODE_B},
	{67, SDL_SCANCODE_C},
	{68, SDL_SCANCODE_D},
	{69, SDL_SCANCODE_E},
	{70, SDL_SCANCODE_F},
	{71, SDL_SCANCODE_G},
	{72, SDL_SCANCODE_H},
	{73, SDL_SCANCODE_I},
	{74, SDL_SCANCODE_J},
	{75, SDL_SCANCODE_K},
	{76, SDL_SCANCODE_L},
	{77, SDL_SCANCODE_M},
	{78, SDL_SCANCODE_N},
	{79, SDL_SCANCODE_O},
	{80, SDL_SCANCODE_P},
	{81, SDL_SCANCODE_Q},
	{82, SDL_SCANCODE_R},
	{83, SDL_SCANCODE_S},
	{84, SDL_SCANCODE_T},
	{85, SDL_SCANCODE_U},
	{86, SDL_SCANCODE_V},
	{87, SDL_SCANCODE_W},
	{88, SDL_SCANCODE_X},
	{89, SDL_SCANCODE_Y},
	{90, SDL_SCANCODE_Z},
	{91, SDL_SCANCODE_LGUI},    // Left Windows/Command key
	{92, SDL_SCANCODE_RGUI},    // Right Windows/Command key
	{96, SDL_SCANCODE_KP_0},
	{97, SDL_SCANCODE_KP_1},
	{98, SDL_SCANCODE_KP_2},
	{99, SDL_SCANCODE_KP_3},
	{100, SDL_SCANCODE_KP_4},
	{101, SDL_SCANCODE_KP_5},
	{102, SDL_SCANCODE_KP_6},
	{103, SDL_SCANCODE_KP_7},
	{104, SDL_SCANCODE_KP_8},
	{105, SDL_SCANCODE_KP_9},
	{106, SDL_SCANCODE_KP_MULTIPLY},
	{107, SDL_SCANCODE_KP_PLUS},
	{109, SDL_SCANCODE_KP_MINUS},
	{110, SDL_SCANCODE_KP_PERIOD},
	{111, SDL_SCANCODE_KP_DIVIDE},
	{112, SDL_SCANCODE_F1},
	{113, SDL_SCANCODE_F2},
	{114, SDL_SCANCODE_F3},
	{115, SDL_SCANCODE_F4},
	{116, SDL_SCANCODE_F5},
	{117, SDL_SCANCODE_F6},
	{118, SDL_SCANCODE_F7},
	{119, SDL_SCANCODE_F8},
	{120, SDL_SCANCODE_F9},
	{121, SDL_SCANCODE_F10},
	{122, SDL_SCANCODE_F11},
	{123, SDL_SCANCODE_F12},
	{144, SDL_SCANCODE_NUMLOCKCLEAR},
	{145, SDL_SCANCODE_SCROLLLOCK},
	{186, SDL_SCANCODE_SEMICOLON},
	{187, SDL_SCANCODE_EQUALS},
	{188, SDL_SCANCODE_COMMA},
	{189, SDL_SCANCODE_MINUS},
	{190, SDL_SCANCODE_PERIOD},
	{191, SDL_SCANCODE_SLASH},
	{192, SDL_SCANCODE_GRAVE},
	{219, SDL_SCANCODE_LEFTBRACKET},
	{220, SDL_SCANCODE_BACKSLASH},
	{221, SDL_SCANCODE_RIGHTBRACKET},
	{222, SDL_SCANCODE_APOSTROPHE}
};


#include <keyboard.h>

unsigned char dbp_keys_down[500];

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
};

SDL_Scancode convertJavaScriptKeycodeToSDLScancode(int jsKeycode) {
	auto it = keycodeToScancode.find(jsKeycode);
	if (it != keycodeToScancode.end()) {
		return it->second;
	}
	return SDL_SCANCODE_UNKNOWN;
}

void resetNeilButtons()
{
	neilbuttons.upKey = 0;
	neilbuttons.downKey = 0;
	neilbuttons.leftKey = 0;
	neilbuttons.rightKey = 0;
	neilbuttons.startKey = 0;
	neilbuttons.selectKey = 0;
	neilbuttons.lKey = 0;
	neilbuttons.rKey = 0;
	neilbuttons.aKey = 0;
	neilbuttons.bKey = 0;
	neilbuttons.xKey = 0;
	neilbuttons.yKey = 0;
	neilbuttons.axis0 = 0;
	neilbuttons.axis1 = 0;
	neilbuttons.axis2 = 0;
	neilbuttons.axis3 = 0;
	neilbuttons.touch = 0;
}

int neilMouseX = 0;
int neilMouseY = 0;
bool lastGravePressed = false;

#include <sdlmain.h>

int neilCounter = 0;
extern MOUSE_EMULATION user_cursor_emulation;
extern bool user_cursor_locked;
void HandleMouseMotion(SDL_MouseMotionEvent* motion);
void HandleMouseButton(SDL_MouseButtonEvent* button, SDL_MouseMotionEvent* motion);
void Mouse_CursorMoved(float xrel, float yrel, float x, float y, bool emulate);
void Mouse_ButtonPressed(uint8_t button);
void Mouse_ButtonReleased(uint8_t button);

int mouseLeftLast = 0;
int mouseRightLast = 0;
extern bool globalOnscreenKeyboard;
float mousePlane = 0.0f;
float mouseJoyMoveX = 0.0f;
float mouseJoyMoveY = 0.0f;

void calculateJoyMouse(int axis, int* mouseMove, float* mouseJoyMove)
{
	//deadzone
	if (axis < 3000 && axis > -3000)
	{
		*mouseMove = 0;
		mousePlane = 0;
	}
	else
	{
		int axisCopy = axis;

		if (axisCopy > 0) axisCopy -= 3000; //start it from zero after deadzone
		if (axisCopy < 0) axisCopy += 3000;

		if (globalOnscreenKeyboard)
		{
			if (abs(axisCopy) < 20000)
			{
				mousePlane = (((float)axisCopy) * ((float)(2) / 32768.0f));
			}
			else if (abs(axisCopy) < 25000)
			{
				mousePlane = (((float)axisCopy) * ((float)(3) / 32768.0f));
			}
			else
			{
				mousePlane = (((float)axisCopy) * ((float)(5) / 32768.0f));
			}
		}
		else
		{
			if (abs(axisCopy) < 20000)
			{
				mousePlane = (((float)axisCopy) * ((float)(2) / 32768.0f));
			}
			else if (abs(axisCopy) < 25000)
			{
				mousePlane = (((float)axisCopy) * ((float)(5) / 32768.0f));
			}
			else
			{
				mousePlane = (((float)axisCopy) * ((float)(10) / 32768.0f));
			}
		}

		*mouseJoyMove += mousePlane;
		if (abs(*mouseJoyMove) > 1)
		{
			int rounded = (int)*mouseJoyMove;
			*mouseMove = rounded;
			*mouseJoyMove -= (float)rounded;
		}
		else
		{
			*mouseMove = 0;
		}
	}
}


void init_myinput()
{
	printf("init_myinput\n");
	for (int i = 0; i < 500; i++)
	{
		dbp_keys_down[i] = false;
	}
	keyboardState = (Uint8*)malloc(500 * sizeof(Uint8));
	for (int i = 0; i < 500; i++)
	{
		keyboardState[i] = false;
	}
}

extern int user_cursor_x;
extern int user_cursor_y;
extern int user_cursor_sw;
extern int user_cursor_sh;

float mouseSensitivity = 1.0f;

// I copied this functionality from HandleMouseMotion()
// in sdlmain.cpp - otherwise without this transport tycoon
// was not working. Not sure why yet need dig into it more.
void MoveCursor(int mouseX, int mouseY, int mouseXPosition, int mouseYPosition)
{
	sdl.mouse.locked = true;
	user_cursor_x = mouseXPosition - sdl.clip.x;
	user_cursor_y = mouseYPosition - sdl.clip.y;
	user_cursor_locked = sdl.mouse.locked;
	user_cursor_emulation = sdl.mouse.emulation;
	user_cursor_sw = sdl.clip.w;
	user_cursor_sh = sdl.clip.h;

	auto xrel = static_cast<float>(mouseX) * mouseSensitivity;
	auto yrel = static_cast<float>(mouseY) * mouseSensitivity;
	auto x = static_cast<float>(mouseXPosition - sdl.clip.x) / (sdl.clip.w - 1) * mouseSensitivity;
	auto y = static_cast<float>(mouseYPosition - sdl.clip.y) / (sdl.clip.h - 1) * mouseSensitivity;
	auto emu = sdl.mouse.locked;

	const auto inside =
		mouseXPosition >= sdl.clip.x && mouseXPosition < sdl.clip.x + sdl.clip.w &&
		mouseYPosition >= sdl.clip.y && mouseYPosition < sdl.clip.y + sdl.clip.h;

	Mouse_CursorMoved(xrel, yrel, x, y, emu);
}

void neil_mouse_events()
{
	// don't send regular mouse events while osk or overlay are display
	if (!globalOnscreenKeyboard && !showOverlay)
	{
		if (mouseXEvents.size() > 0 && mouseXEvents.size() == mouseYEvents.size())
		{
			for (int i = 0; i < mouseXEvents.size(); i++)
			{
				int mouseXElement = mouseXEvents[i];
				int mouseYElement = mouseYEvents[i];

				user_cursor_emulation = MOUSE_EMULATION_LOCKED;
				user_cursor_locked = true;
				MoveCursor(mouseXElement, mouseYElement, mouseXElement, mouseYElement);
			}

			// clear the queue
			mouseXEvents.clear();
			mouseYEvents.clear();
		}
	}
}


// this should only be called 60 times a second
void neil_event_loop()
{
	resetNeilButtons();


	//grab the controls from the client right before we process the events
#ifdef __EMSCRIPTEN__
	EM_ASM(
		myApp.rivetsData.inputController.updateDosControls();
	);
#else
	void winDosControls();
	winDosControls();
#endif

	if (neilConfiguration.mobileMode)
	{
		//to make it "feel" like the DosWasm version I copied
		//the calculateJoyMouse method from that code
		calculateJoyMouse(neilbuttons.axis0, &neilMouseX, &mouseJoyMoveX);
		calculateJoyMouse(neilbuttons.axis1, &neilMouseY, &mouseJoyMoveY);

		if (!globalOnscreenKeyboard && !showOverlay)
		{
			if (neilMouseX != 0 || neilMouseY != 0)
			{
				user_cursor_emulation = MOUSE_EMULATION_LOCKED;
				user_cursor_locked = true;
				MoveCursor(neilMouseX, neilMouseY, neilMouseX, neilMouseY);
			}
		}
	}
	else
	{
		if (globalOnscreenKeyboard)
		{
			neilMouseX = neilbuttons.axis0;
			neilMouseY = neilbuttons.axis1;
		}

		if (neilbuttons.axis0 != 0 || neilbuttons.axis1 != 0)
		{
			if (!globalOnscreenKeyboard && !showOverlay)
			{
				user_cursor_emulation = MOUSE_EMULATION_LOCKED;
				user_cursor_locked = true;
				MoveCursor(neilbuttons.axis0, neilbuttons.axis1, neilbuttons.axis0, neilbuttons.axis1);
			}
		}
	}

	// don't send regular mouse events while osk or overlay are display
	if (!globalOnscreenKeyboard && !showOverlay)
	{
		if (neilbuttons.aKey != mouseLeftLast)
		{
			if (neilbuttons.aKey)
			{
				// printf("mouse 0 pressed\n");
				Mouse_ButtonPressed(0);
			}
			else
			{
				// printf("mouse 0 released\n");
				Mouse_ButtonReleased(0);
			}

			mouseLeftLast = neilbuttons.aKey;
		}

		if (neilbuttons.bKey != mouseRightLast)
		{
			if (neilbuttons.bKey)
			{
				// printf("mouse 1 pressed\n");
				Mouse_ButtonPressed(1);
			}
			else
			{
				// printf("mouse 1 released\n");
				Mouse_ButtonReleased(1);
			}
			mouseRightLast = neilbuttons.bKey;
		}
	}


}


extern "C" {

	void neil_send_mouse_movement(int mouseX, int mouseY)
	{
		mouseXEvents.push_back(mouseX);
		mouseYEvents.push_back(mouseY);
	}

	void neil_send_dos_controls(char* controls, char* axis0, char* axis1, unsigned char* keyArray, int keyLength)
	{
		if (controls[0] == '1') neilbuttons.upKey = true;
		if (controls[1] == '1') neilbuttons.downKey = true;
		if (controls[2] == '1') neilbuttons.leftKey = true;
		if (controls[3] == '1') neilbuttons.rightKey = true;
		if (controls[4] == '1') neilbuttons.aKey = true;
		if (controls[5] == '1') neilbuttons.bKey = true;
		if (controls[6] == '1') neilbuttons.startKey = true;
		if (controls[7] == '1') neilbuttons.lKey = true;
		if (controls[8] == '1') neilbuttons.rKey = true;
		if (controls[9] == '1') neilbuttons.touch = true;

		//clear keyboardState
		for (int i = 0; i < 500; i++)
		{
			keyboardState[i] = false;
		}

		//apply keys
		for (int i = 0; i < keyLength; i++)
		{
#ifdef WIN32
			SDL_Scancode sdlScancode = (SDL_Scancode)keyArray[i];
#else
			SDL_Scancode sdlScancode = convertJavaScriptKeycodeToSDLScancode((int)keyArray[i]);
#endif
			keyboardState[sdlScancode] = true;
		}

		if (neilConfiguration.mobileMode)
		{
			keyboardState[SDL_SCANCODE_LEFT] = neilbuttons.leftKey;
			keyboardState[SDL_SCANCODE_RIGHT] = neilbuttons.rightKey;
			keyboardState[SDL_SCANCODE_UP] = neilbuttons.upKey;
			keyboardState[SDL_SCANCODE_DOWN] = neilbuttons.downKey;
		}

		// don't send regular keyboard events while overlay is displayed
		if (!showOverlay)
		{
			for (int i = 0; i != (sizeof(keymap) / sizeof(keymap[0])); i++)
			{

				int keycode = keymap[i].retroID;
				int val = keymap[i].dosboxID;

				bool down = keyboardState[keycode];
				if (!val) return;
				if (down && dbp_keys_down[val] == false)
				{
					KEYBOARD_AddKey((KBD_KEYS)val, true);
					dbp_keys_down[val] = true;
				}
				else if (!down && dbp_keys_down[val] == true)
				{
					KEYBOARD_AddKey((KBD_KEYS)val, false);
					dbp_keys_down[val] = false;
				}
			}
		}

		//gamepad and mobile use axis0 and axis1 while
		//real mouse uses the seperate neil_send_mouse_movement()
		std::string axis0String(axis0);
		float axis0Float = std::stof(axis0String);

		std::string axis1String(axis1);
		float axis1Float = std::stof(axis1String);

		if (neilConfiguration.mobileMode)
		{
			if (globalOnscreenKeyboard) axis0Float /= 2;
			if (globalOnscreenKeyboard) axis1Float /= 2;

			//this is copied from DosWasm purely for Mobile Mode
			neilbuttons.axis0 = (int)((float)32000*axis0Float);
        	neilbuttons.axis1 = -(int)((float)32000*axis1Float);
		}
		else
		{
			if (globalOnscreenKeyboard) axis0Float /= 4;
			if (globalOnscreenKeyboard) axis1Float /= 4;

			neilbuttons.axis0 = axis0Float;
			neilbuttons.axis1 = axis1Float;
		}

	}
}