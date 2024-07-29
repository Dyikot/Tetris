#include "Game.h"

Game::Game()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "Ошибка инициализации SDL: " << SDL_GetError();
	}

	if(TTF_Init() < 0)
	{
		std::cout << "Ошибка инициализации TTL: " << SDL_GetError();
	}
	
	_currentWindow = SDL_CreateWindow(/*title*/ "Tetris",
									  /*x*/ SDL_WINDOWPOS_CENTERED,
									  /*y*/ SDL_WINDOWPOS_CENTERED,
									  /*w*/ WindowWidth,
									  /*h*/ WindowHeight,
									  /*flags*/ SDL_WINDOW_SHOWN);

	if(_currentWindow == nullptr)
	{
		std::cout << "Не удалось создать окно : " << SDL_GetError();
	}

	_renderer = SDL_CreateRenderer(_currentWindow, -1, SDL_RENDERER_ACCELERATED);

	_isGameRunning = true;
	_currentScene = new StartMenu();
}

Game::~Game()
{
	SDL_DestroyWindow(_currentWindow);
	TTF_Quit();
	SDL_Quit();
}

void Game::Run()
{		
	SDL_Event event;
	constexpr Uint32 Delay = 10;
	
	// Игровой цикл
	while(_isGameRunning)
	{
		while(SDL_PollEvent(&event))
		{
			_currentScene->HandleEvent(event);
		}

		if(_nextScene != nullptr)
		{
			SwitchToNextScene();
		}
				
		_currentScene->Process();

		// Устанавливает цвет фона окна
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

		SDL_RenderClear(_renderer);
		_currentScene->Show();
		SDL_RenderPresent(_renderer);

		SDL_Delay(Delay);
	}
}

void Game::Shutdown()
{
	_isGameRunning = false;
}
