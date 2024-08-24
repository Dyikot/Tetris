#include "PauseMenu.h"

PauseMenu::PauseMenu()
{

	_navigationButtons = { &_continueButton, &_settingsButton, &_exitButton };
	Objects = { &_title, &_continueButton, &_settingsButton, &_exitButton };

	_title.SetText("Pause");

	using namespace std::placeholders;

	_continueButton.Click = std::bind(&PauseMenu::OnContinueButtonClick, this, _1, _2);
	_settingsButton.Click = std::bind(&PauseMenu::OnSettingsButtonClick, this, _1, _2);
	_exitButton.Click = std::bind(&PauseMenu::OnExitButtonClick, this, _1, _2);
	KeyDown = std::bind(&PauseMenu::OnKeyDown, this, _1, _2);
}

void PauseMenu::OnKeyDown(Object* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			Application::Current()->SetHiddenSceneToNext();
			Close();
			break;
		}
	}
}

void PauseMenu::OnContinueButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SetHiddenSceneToNext();
	Close();
}

void PauseMenu::OnSettingsButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SetNextScene(new SettingsMenu());
	Hide();
}

void PauseMenu::OnExitButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	Close();
}
