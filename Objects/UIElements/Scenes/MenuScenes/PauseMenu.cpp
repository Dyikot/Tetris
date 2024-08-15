#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	NavigationButtons = { &_continueButton, &_settingsButton, &_exitButton };
	Objects = { &_title, &_continueButton, &_settingsButton, &_exitButton };

	using namespace std::placeholders;

	KeyDown = std::bind(&PauseMenu::OnKeyDown, this, _1, _2);
	_continueButton.Click = std::bind(&PauseMenu::OnContinueButtonClick, this, _1, _2);
	_settingsButton.Click = std::bind(&PauseMenu::OnSettingsButtonClick, this, _1, _2);
	_exitButton.Click = std::bind(&PauseMenu::OnExitButtonClick, this, _1, _2);
}

void PauseMenu::OnKeyDown(Object* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_ESCAPE:
			Application::Current()->SetSavedSceneToNext();
			break;
	}
}

void PauseMenu::OnContinueButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SetSavedSceneToNext();
}

void PauseMenu::OnSettingsButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SaveCurrentScene();
	Application::Current()->SetNextScene(new SettingsMenu());
}

void PauseMenu::OnExitButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	OnQuit({.type = SDL_QUIT, .timestamp = e.timestamp});
}
