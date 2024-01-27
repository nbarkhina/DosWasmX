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


extern char fps_text[250];

#ifdef _WIN32
#define USE_XINPUT 
#endif

#ifdef USE_XINPUT
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
XINPUT_STATE state;
int xGamepadIndex = -1;
#endif

SDL_Joystick* joyStick = NULL;
SDL_GameController* gameController = NULL;
bool gamepadConnected = false;
SDL_Color fontcolor = {255, 255, 255};
TTF_Font* font = TTF_OpenFont("res/arial.ttf", 24);
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* gameTexture;

// Framerate control:
int axis0 = 0;
int axis1 = 0;
int axis2 = 0;
int axis3 = 0;
int axis4 = 0;
int axis5 = 0;
Uint8* keyboardState;
bool runApp = true;

SDL_Rect rect;

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

#ifdef USE_XINPUT
bool IsPressed(WORD button)
{
	return (state.Gamepad.wButtons & button) != 0;
}
#endif

void connectGamepad()
{
#ifdef USE_XINPUT
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))
#define ERROR_SUCCESS                    0L
#define XUSER_MAX_COUNT                 4
#define ZeroMemory RtlZeroMemory
	DWORD dwResult;

	if (!gamepadConnected)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{

			ZeroMemory(&state, sizeof(XINPUT_STATE));

			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState(i, &state);

			if (dwResult == ERROR_SUCCESS)
			{
				// Controller is connected
				if (!gamepadConnected)
					printf("controller connected %d\n", i);

				xGamepadIndex = i;
				gamepadConnected = true;
			}
			else
			{
				// Controller is not connected
			}
		}
	}
	else
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		dwResult = XInputGetState(xGamepadIndex, &state);

		if (dwResult != ERROR_SUCCESS)
		{
			gamepadConnected = false;
		}
	}

	return;
#endif
	if (!gamepadConnected)
	{
		//Check for joysticks
		if (SDL_NumJoysticks() < 1)
		{
			// printf("Warning: No joysticks connected!\n");
		}
		else
		{
			for(int i = 0; i < SDL_NumJoysticks(); i++)
			{
				//Load joystick
				SDL_Joystick* tempJoyStick = SDL_JoystickOpen(i);
				const char* name = SDL_JoystickName(tempJoyStick);

				//skip logitech device
				int compare = 0;
				compare = strcmp(name,"Logitech H820e (Vendor: 046d Product: 0a4a)");
				if (compare == 0)
				{
					printf("skipping logitech device\n");
				}
				else
				{
					joyStick = tempJoyStick;
					printf("Connected Joystick %s\n", name);
					if (SDL_IsGameController(i))
					{
						gameController = SDL_GameControllerOpen(i);
						printf("Connected Connected %s\n", SDL_GameControllerName(gameController));
					}
					gamepadConnected = true;
				}

			}
			

		}

	}
	
}


void drawTexture(SDL_Texture* texture,int sourceX, int sourceY, int sourceW, int sourceH,
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

void mainLoop();
int main_sdl(int argc, char* argv[]);

extern char fat_drive_mount[250];
extern char iso_drive_mount[250];
extern char neil_autoexec_additional[500];
extern char toast_message[250];

int main(int argc, char* argv[])
{
	sprintf(fps_text, "loading...");
	sprintf(fat_drive_mount, "");
	sprintf(iso_drive_mount, "");
	sprintf(neil_autoexec_additional, "");
	sprintf(toast_message, "");


	//initialize font system
	TTF_Init();
	font = TTF_OpenFont("res/arial.ttf", 24);

	//route it to dosbox main() function
	main_sdl(argc, argv);


	return 0;
}

double fpsInterval = 1000.0 / 60.0;
int fpsThen = 0; //time in milliseconds
int fpsNow = 0; //time in milliseconds
int fpsFrameCounter = 0;
int cycleCounterNeil = 0;
int fpsAudioRemaining = 0; //used to keep relieve some audio when emulator is running too fast

bool IsFrameReady() {

	fpsNow = SDL_GetTicks();
	int elapsed = fpsNow - fpsThen;
	bool ready = true;

	int shouldBeFrames = (int)((double)elapsed / fpsInterval);
	if (fpsFrameCounter > shouldBeFrames)
	{
		ready = false;
	}
	if (ready)
		fpsFrameCounter++;

	//reset
	if (elapsed >= 1000)
	{
		fpsThen = fpsNow;
		fpsFrameCounter = 0;
	}

	return ready;
}

void mainLoop()
{


}

void DEBUG_ShowMsg(char const* format, ...)
{
	static char buf[1024];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);
	printf("DEBUG_ShowMsg: %s\n", buf);
}


/* STUBS */

#include "mapper.h"

bool log_int21 = false;
bool log_fileio = false;
static bool has_LOG_Init = false;
static bool has_LOG_EarlyInit = false;
static bool do_LOG_stderr = false;
bool logBuffSuppressConsole = false;
bool logBuffSuppressConsoleNeedUpdate = false;
int debuggerrun = 0;
int log_dev_con = 0;
FILE* debuglog = NULL;

#include <setup.h>

void VOODOO_Destroy(Section* /*sec*/) {
}
bool Voodoo_OGL_Active() { return false;  }
void Voodoo_Output_Enable(bool x) {}
void VOODOO_Init() {}
void VOODOO_PCI_InitEnable(unsigned int x) {}
void VOODOO_PCI_Enable(bool x) {}
void  VOODOO_PCI_SetLFB(unsigned int x) {}
void VOODOO_OnPowerOn(Section* /*sec*/) {}
std::string sffile = "Not available";
bool enable_autosave = false;
void CAPTURE_MultiTrackAddWave(uint32_t freq, uint32_t len, int16_t* data, const char* name) {}

#include <midi.h>
void MIDI_ListHandler(Program* caller, const char* name) {}
DB_Midi midi;
void MIDI_RawOutByte(uint8_t data) {}
bool MIDI_Available(void) {
	return false;
}
void MIDI_GUI_OnSectionPropChange(Section* x) {}
static void fmport_a_pic_event(Bitu val) {
}

static void fmport_b_pic_event(Bitu val) {
}

// save state support
void* fmport_a_pic_event_PIC_Event = (void*)((uintptr_t)fmport_a_pic_event);
void* fmport_b_pic_event_PIC_Event = (void*)((uintptr_t)fmport_b_pic_event);
int autosave_second = 0, autosave_count = 0, autosave_start[10], autosave_end[10], autosave_last[10];
std::string autosave_name[10];

namespace ptrop {
	void self_test(void) {}
}
namespace bitop {
	void self_test(void) {}
}


#include <logging.h>
void LOG::SetupConfigSection(void) {}
void LOG::EarlyInit(void) {}
void LOG::Init(void) {}
void LOG::Exit(void) {}
void HARDWARE_Init(void) {}
void CAPTURE_Init(void) {}
void MIDI_Init(void) {}
void IMFC_Init(void) {}
void update_capture_fmt_menu(void) {}

bool PC98_FM_SoundBios_Enabled(void) {
	return false;
}