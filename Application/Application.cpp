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
    _nextScene = next;
}

void Application::SaveCurrentScene() noexcept
{
    _savedScenes.push(_currentScene);
}

void Application::SetSavedSceneToNext() noexcept
{
    _nextScene = _savedScenes.top();
    _savedScenes.pop();
}

SDL_Window* Application::GetCurrentWindow()
{
    return _currentWindow;
}

SDL_Renderer* Application::GetRenderer() const
{
    return _renderer;
}

void Application::SetWindowSize(size_t width, size_t height)
{
    SDL_SetWindowSize(_currentWindow, width, height);
}

void Application::SwitchToNextScene() noexcept
{
    if(_savedScenes.empty() || _currentScene != _savedScenes.top())
    {
        delete _currentScene;
    }

    _currentScene = _nextScene;
    _nextScene = nullptr;
}