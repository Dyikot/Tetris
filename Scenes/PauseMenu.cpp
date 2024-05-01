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
			if(e.button.x >= _continueButton.GetPosition().x &&
				e.button.x <= _continueButton.GetPosition().x + _continueButton.GetWight() &&
				e.button.y >= _continueButton.GetPosition().y &&
				e.button.y <= _continueButton.GetPosition().y + _continueButton.GetHeight())
			{
				Application::Current()->UploadSavedSceneToNext();
			}
			else if(e.button.x >= _exitButton.GetPosition().x &&
				e.button.x <= _exitButton.GetPosition().x + _exitButton.GetWight() &&
				e.button.y >= _exitButton.GetPosition().y &&
				e.button.y <= _exitButton.GetPosition().y + _exitButton.GetHeight())
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
