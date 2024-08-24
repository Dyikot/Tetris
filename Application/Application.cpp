#include "Application.h"

Application* const Application::Current()
{
    return _current;
}

Application::Application() noexcept
{
    _current = this;
}

Application::~Application()
{
    SDL_DestroyWindow(_currentWindow);
    SDL_Quit();
}

void Application::SetNextScene(IScene* next) noexcept
{
    if(_nextScene != nullptr)
    {
        delete _nextScene;
    }

    _nextScene = next;
}

void Application::SetHiddenSceneToNext() noexcept
{
    _nextScene = _hiddenScenes.top();
    _nextScene->SetVisibility(SceneVisibility::Visible);
    _hiddenScenes.pop();
}

SDL_Window* Application::GetCurrentWindow() noexcept
{
    return _currentWindow;
}

SDL_Renderer* Application::GetRenderer() const noexcept
{
    return _renderer;
}

bool Application::IsNextSceneSet() const noexcept
{
    return _nextScene != nullptr;
}

bool Application::PollEvent(SDL_Event* e) noexcept
{
	if(SDL_PollEvent(e))
	{
		switch(e->type)
		{
			case SDL_KEYDOWN:
			{
				if(e->key.repeat)
				{
					if(_keyHoldRegister.IsKeyHold())
					{		
						e->key = _keyHoldRegister.GetEvent();
						return true;
					}

					return false;
				}
			}

			case SDL_KEYUP:
			{
				_keyHoldRegister.Register(e->key);
				break;
			}

			default:
			{
				break;
			}
		}

		return true;
	}
	else if(_keyHoldRegister.IsKeyHold())
	{
		e->key = _keyHoldRegister.GetEvent();
		return true;
	}

	return false;
}

void Application::SetWindowSize(size_t width, size_t height) noexcept
{
    SDL_SetWindowSize(_currentWindow, width, height);
}

void Application::SwitchToNextScene() noexcept
{
    if(_currentScene->GetVisibility() == SceneVisibility::Hidden)
    {
        _hiddenScenes.push(_currentScene);
    }

    if(_hiddenScenes.empty() || _currentScene != _hiddenScenes.top())
    {
        delete _currentScene;
    }

    _currentScene = _nextScene;
    _nextScene = nullptr;
}