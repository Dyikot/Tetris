#include "SettingsMenu.h"

void SettingsMenu::Show()
{
    
}

void SettingsMenu::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			Application::Current()->Shutdown();
			break;

		default:
			break;
	}
}

void SettingsMenu::Process()
{

}
