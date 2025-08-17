#include "PauseMenu.h"
#include "../Application/Window.h"

PauseMenu::PauseMenu()
{

	_navigationButtons = { &_continueButton, &_settingsButton, &_exitButton };
	Objects = { &_title, &_continueButton, &_settingsButton, &_exitButton };

	_title.SetText("Pause");

	_continueButton.Click = std::bind_front(&PauseMenu::OnContinueButtonClick, this);
	_settingsButton.Click = std::bind_front(&PauseMenu::OnSettingsButtonClick, this);
	_exitButton.Click = std::bind_front(&PauseMenu::OnExitButtonClick, this);
	KeyDown = std::bind_front(&PauseMenu::OnKeyDown, this);
}

void PauseMenu::OnKeyDown(Renderable* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			Application::Current()->GetWindow()->SetHiddenSceneToNext();
			Close();
			break;
		}
	}
}

void PauseMenu::OnContinueButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->GetWindow()->SetHiddenSceneToNext();
	Close();
}

void PauseMenu::OnSettingsButtonClick(Renderable * sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->GetWindow()->SetNextScene(new SettingsMenu());
	Hide();
}

void PauseMenu::OnExitButtonClick(Renderable * sender, const SDL_MouseButtonEvent& e)
{
	Close();
}