#include "Application.h"

Application* const Application::Current()
{
    return _current;
}

Application::Application()
{
    _current = this;
}

void Application::SwitchToNextScene()
{
    if(_currentScene != _savedScene)
    {
        delete _currentScene;
    }

    _currentScene = _nextScene;
    _nextScene = nullptr;
}

void Application::SetNextScene(Scene* next)
{
    _nextScene = next;
}

void Application::SaveCurrentScene()
{
    _savedScene = _currentScene;
}

void Application::UploadSavedSceneToNext()
{
    _nextScene = _savedScene;
    _savedScene = nullptr;
}

SDL_Window* Application::GetCurrentWindow()
{
    return _currentWindow;
}

SDL_Renderer* Application::GetRenderer() const
{
    return _renderer;
}
