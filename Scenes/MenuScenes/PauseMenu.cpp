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
			OnQuit(e);
			break;

		case SDL_KEYDOWN:
			OnKeyDown(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(e);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e);
			break;

		default:
			break;
	}
}

void PauseMenu::Process()
{}

void PauseMenu::OnMouseDown(const SDL_Event & e)
{
	if(_continueButton.IsInRange(e.button.x, e.button.y))
	{
		Application::Current()->UploadSavedSceneToNext();
	}
	else if(_exitButton.IsInRange(e.button.x, e.button.y))
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
			Application::Current()->UploadSavedSceneToNext();
			break;
	}
}
