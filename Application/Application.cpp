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

void Application::SetNextScene(Scene* next) noexcept
{
    _nextScene = next;
}

void Application::SaveCurrentScene() noexcept
{
    _savedScene = _currentScene;
}

void Application::UploadSavedSceneToNext() noexcept
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

void Application::SwitchToNextScene() noexcept
{
    if(_currentScene != _savedScene)
    {
        delete _currentScene;
    }

    _currentScene = _nextScene;
    _nextScene = nullptr;
}