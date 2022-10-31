#include <stdlib.h>
#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	LOG("Starting engine '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (App->AppTitleScreenFull == false)
			{
				//SDL_SetWindowSize(app->win->window, 1280, 720); <-- Ya se hace desde el XML
				SDL_SetWindowFullscreen(App->window->window, 0);
			}
			else if (App->AppTitleScreenFull == true)
			{
				SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);

			}

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}
			if (App->appExit == true)
			{
				const SDL_MessageBoxButtonData buttons[] = {
		   { /* .flags, .buttonid, .text */        0, 0, "No" },
		   { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
		   { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Ignore" },
				};
				const SDL_MessageBoxColorScheme colorScheme = {
					{ /* .colors (.r, .g, .b) */
						/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
						{ 255,   0,   0 },
						/* [SDL_MESSAGEBOX_COLOR_TEXT] */
						{   0, 255,   0 },
						/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
						{ 255, 255,   0 },
						/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
						{   0,   0, 255 },
						/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
						{ 255,   0, 255 }
					}
				};
				const SDL_MessageBoxData messageboxdata = {
						SDL_MESSAGEBOX_WARNING, /* .flags */
						NULL, /* .window */
						" Secure App closing - so you don't loose your work :)", /* .title ¯\_(ツ)_/¯ */
						"You are about to exit Cetreleopter Engine.\nAll unsaved progress will be lost!!", /* .message ಠ_ಠ */
						SDL_arraysize(buttons), /* .numbuttons */
						buttons, /* .buttons */
						&colorScheme /* .colorScheme */
				};
				int buttonid;
				if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
					SDL_Log("error displaying message box");
					return 1;
				}
				if (buttonid == -1) {
					SDL_Log("no selection");
					App->enginePaused = true;
				}
				else if (buttonid == 1) {
					SDL_Log("exit selection");
					state = MAIN_FINISH;
				}
				else if (buttonid == 0) {
					SDL_Log("exit continue running");
					App->enginePaused = false;
					App->appExit = false;
				}
				else if (buttonid == 2) {
					SDL_Log("exit continue running");
					App->enginePaused = false;
					App->appExit = false;
				}
				else {
					SDL_Log("selection was %s", buttons[buttonid].text);
				}

			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}