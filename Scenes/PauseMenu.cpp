#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	_buttons = { &_continueButton, &_exitButton };
}

void PauseMenu::Show()
{
	_pauseTextBlock.Show();
	_continueButton.Show();
	_exitButton.Show();
}

void PauseMenu::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			Application::Current()->Shutdown();
			break;

		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					Application::Current()->UploadSavedSceneToNext();
					break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(_continueButton.IsInRange(e.button.x, e.button.y))
			{
				Application::Current()->UploadSavedSceneToNext();
			}
			else if(_exitButton.IsInRange(e.button.x, e.button.y))
			{
				Application::Current()->Shutdown();
			}
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e.button.x, e.button.y);
			break;

		default:
			break;
	}
}

void PauseMenu::Process()
{}
