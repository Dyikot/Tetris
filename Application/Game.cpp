#include "Game.h"

Game::Game()
{
	// Initialization

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
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
	
	// Set window, render, audio

	auto serializationData = SettinsDataSerializer().Deserialize();
	auto settingsData = dynamic_cast<SettingsData*>(serializationData.get());

	_currentWindow = SDL_CreateWindow("Tetris",
									  SDL_WINDOWPOS_CENTERED,
									  SDL_WINDOWPOS_CENTERED,
									  settingsData->WidndowWidth,
									  settingsData->WidndowHeight,
									  SDL_WINDOW_SHOWN);

	if(_currentWindow == nullptr)
	{
		std::cout << SDL_GetError() << '\n';
	}

	_renderer = SDL_CreateRenderer(_currentWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(_renderer, WindowWidth, WindowHeight);

	_isGameRunning = true;
	_currentScene = new StartMenu();
}

Game::~Game()
{
	TTF_Quit();
	IMG_Quit();
}

void Game::Run()
{		
	SDL_Event event;
	constexpr Uint32 Delay = 6;

	// Игровой цикл
	while(_isGameRunning)
	{
		while(PollEvents(&event))
		{
			_currentScene->HandleEvent(event);
		}

		if(IsNextSceneSet() && _currentScene->GetVisibility() != SceneVisibility::Visible)
		{
			SwitchToNextScene();
		}
				
		_currentScene->Process();
		_currentScene->SetBackground();
		
		SDL_RenderClear(_renderer);
		_currentScene->Show();
		SDL_RenderPresent(_renderer);

		SDL_Delay(Delay);
	}
}

void Game::Shutdown() noexcept
{
	_isGameRunning = false;
}

bool Game::PollEvents(SDL_Event* e) noexcept
{
	if(SDL_PollEvent(e))
	{
		switch(e->type)
		{
			case SDL_KEYDOWN:
				if(e->key.repeat)
				{
					if(_holdKeyEvent.IsHold())
					{
						e->key = _holdKeyEvent;
						return true;
					}

					return false;
				}

			case SDL_KEYUP:
				_holdKeyEvent = e->key;
				break;

			default:
				break;
		}

		return true;
	}
	else if(_holdKeyEvent.IsHold())
	{
		e->key = _holdKeyEvent;
		return true;
	}
	
	return false;
}
