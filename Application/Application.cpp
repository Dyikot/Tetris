#include "Application.h"
#include "Window.h"

Application::Application() noexcept
{
	_current = this;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
	{
		std::cout << SDL_GetError() << '\n';
	}

	if(TTF_Init() < 0)
	{
		std::cout << SDL_GetError() << '\n';
	}

	if(!IMG_Init(IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_JPG))
	{
		std::cout << SDL_GetError() << '\n';
	}

	if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
	{
		std::cout << SDL_GetError() << '\n';
	}
}

Application::~Application() noexcept
{
	delete _audioManager;
	delete _window;
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void Application::Run()
{
	SDL_Event e;

	while(_isActive)
	{
		while(PollEvent(&e))
		{
			_window->CurrentScene()->HandleEvent(e);
		}

		_window->Render();

		SDL_Delay(_delay);
	}
}

void Application::Shutdown() noexcept
{
	OnQuit(SDL_QuitEvent(SDL_QUIT, SDL_GetTicks()));
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
					if(_keyHoldDetector.IsKeyHold())
					{
						e->key = _keyHoldDetector.GetEvent();
						return true;
					}

					return false;
				}
				__fallthrough;
			}

			case SDL_KEYUP:
			{
				_keyHoldDetector.Start(e->key);
				break;
			}

			case SDL_QUIT:
			{
				OnQuit(e->quit);
				return false;
			}
		}

		return true;
	}
	else if(_keyHoldDetector.IsKeyHold())
	{
		e->key = _keyHoldDetector.GetEvent();
		return true;
	}

	return false;
}

void Application::OnQuit(const SDL_QuitEvent& e)
{
	_isActive = false;

	if(Quit)
	{
		Quit(this, e);
	}
}
