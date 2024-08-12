#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	_buttons = { &_continueButton, &_settingsButton, &_exitButton };
	_controls = { &_title, &_continueButton, &_settingsButton, &_exitButton };
}

void PauseMenu::Show()
{
	ShowControls();
}

void PauseMenu::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			OnQuit(e);
			break;

		case SDL_KEYDOWN:
			OnKeyDown(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(_hoverButton == nullptr)
			{
				break;
			}

			OnMouseDown(e);
			Menu::OnMouseDown(e);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e);
			break;

		default:
			break;
	}
}

void PauseMenu::Process()
{

}

void PauseMenu::OnMouseDown(const SDL_Event & e)
{
	if(_hoverButton == &_continueButton)
	{
		Application::Current()->SetSavedSceneToNext();
	}
	else if(_hoverButton == &_settingsButton)
	{
		Application::Current()->SaveCurrentScene();
		Application::Current()->SetNextScene(new SettingsMenu());
	}
	else if(_hoverButton == &_exitButton)
	{
		Application::Current()->Shutdown();
	}
}

void PauseMenu::OnQuit(const SDL_Event& e)
{
	Application::Current()->Shutdown();
}

void PauseMenu::OnKeyDown(const SDL_Event& e)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			Application::Current()->SetSavedSceneToNext();
			break;
	}
}
