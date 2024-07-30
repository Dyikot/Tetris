#include "PauseMenu.h"

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
			if(_continueButton.IsInRange({ .x = e.button.x, .y = e.button.y }))
			{
				Application::Current()->UploadSavedSceneToNext();
			}
			else if(_exitButton.IsInRange({ .x = e.button.x, .y = e.button.y }))
			{
				Application::Current()->Shutdown();
			}
			break;

		default:
			break;
	}
}

void PauseMenu::Process()
{}
