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

void Application::HideCurrentScene() noexcept
{
    _hiddenScenes.push(_currentScene);
}

void Application::SetHiddenSceneToNext() noexcept
{
    _nextScene = _hiddenScenes.top();
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

void Application::SetWindowSize(size_t width, size_t height) noexcept
{
    SDL_SetWindowSize(_currentWindow, width, height);
}

void Application::SwitchToNextScene() noexcept
{
    if(_hiddenScenes.empty() || _currentScene != _hiddenScenes.top())
    {
        delete _currentScene;
    }

    _currentScene = _nextScene;
    _nextScene = nullptr;
}