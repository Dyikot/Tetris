#include "Window.h"


Window::Window(std::string_view title, 
               const SDL_Point& position, 
               int width,
               int height,
               int actualWidth,
               int actualHeight,
               SDL_WindowFlags flags) noexcept:
    _width(width),
    _height(height),
    _actualWidth(actualWidth),
    _actualHeight(actualHeight),
    SDLWindow(SDL_CreateWindow(title.data(), 
                               position.x, position.y,
                               actualWidth, actualHeight,
                               flags)),
    Renderer(SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED))
{
    if(SDLWindow == nullptr)
    {
        std::cout << SDL_GetError() << '\n';
    }

    if(Renderer == nullptr)
    {
        std::cout << SDL_GetError() << '\n';
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderSetLogicalSize(Renderer, width, height);
}

Window::~Window()
{
    SDL_DestroyWindow(SDLWindow);
    SDL_DestroyRenderer(Renderer);
}

void Window::Render()
{
    switch(_currentScene->CurrentAction())
    {
        case SceneAction::Hide:
        {
            _hiddenScenes.push(_currentScene);
            __fallthrough;
        }

        case SceneAction::Close:
        {
            if(IsNextSceneSet())
            {
                SwitchToNextScene();
            }
            else
            {
                Application::Current()->Shutdown();
                return;
            }
        }
    }    

    _currentScene->Process();

    SetCurrentSceneBackground();
    SDL_RenderClear(Renderer);
    _currentScene->OnRender();
    SDL_RenderPresent(Renderer);
}

Scene* const Window::CurrentScene() const noexcept
{
    return _currentScene;
}

void Window::SetNextScene(Scene* next) noexcept
{
    if(_currentScene == nullptr)
    {
        _currentScene = next;
        return;
    }

    if(_nextScene != nullptr)
    {
        delete _nextScene;
    }

    _nextScene = next;
}

void Window::SetHiddenSceneToNext() noexcept
{
    _nextScene = _hiddenScenes.top();
    _nextScene->Show();
    _hiddenScenes.pop();
}

bool Window::IsNextSceneSet() const noexcept
{
    return _nextScene != nullptr;
}

void Window::SetWindowSize(int width, int height) noexcept
{
    _width = width;
    _height = height;
    SDL_RenderSetLogicalSize(Renderer, width, height);
}

void Window::SetActualWindowSize(int width, int height) noexcept
{
    _actualWidth = width;
    _actualHeight = height;
    SDL_SetWindowSize(SDLWindow, width, height);
}

int Window::Width() const noexcept
{
    return _width;
}

int Window::Height() const noexcept
{
    return _height;
}

int Window::ActualWidth() const noexcept
{
    return _actualWidth;
}

int Window::ActualHeight() const noexcept
{
    return _actualHeight;
}

void Window::SwitchToNextScene() noexcept
{
    if(_hiddenScenes.empty() || _currentScene != _hiddenScenes.top())
    {
        delete _currentScene;
    }

    _currentScene = _nextScene;
    _nextScene = nullptr;
}

void Window::SetCurrentSceneBackground() const noexcept
{
    auto [r, g, b, a] = _currentScene->Background;
    SDL_SetRenderDrawColor(Renderer, r, g, b, a);
}