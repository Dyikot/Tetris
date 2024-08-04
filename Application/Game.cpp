#include "Game.h"

Game::Game()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "������ ������������� SDL: " << SDL_GetError() << '\n';
	}

	if(TTF_Init() < 0)
	{
		std::cout << "������ ������������� TTF: " << SDL_GetError() << '\n';
	}

	if(!IMG_Init(IMG_InitFlags::IMG_INIT_PNG | IMG_InitFlags::IMG_INIT_JPG))
	{
		std::cout << "������ ������������� IMG: " << SDL_GetError() << '\n';
	}
	
	_currentWindow = SDL_CreateWindow("Tetris",
									  SDL_WINDOWPOS_CENTERED,
									  SDL_WINDOWPOS_CENTERED,
									  WindowWidth,
									  WindowHeight,
									  SDL_WINDOW_SHOWN);

	if(_currentWindow == nullptr)
	{
		std::cout << "�� ������� ������� ���� : " << SDL_GetError() << '\n';
	}
	
	_renderer = SDL_CreateRenderer(_currentWindow, -1, SDL_RENDERER_ACCELERATED);
	_isGameRunning = true;
	_currentScene = new StartMenu();
}

Game::~Game()
{
	SDL_DestroyWindow(_currentWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Run()
{		
	SDL_Event event;

	// �������� �������
	constexpr Uint32 Delay = 10;

	// ������� ����
	while(_isGameRunning)
	{
		while(PollEvents(&event))
		{
			_currentScene->HandleEvent(event);
		}

		if(_nextScene != nullptr)
		{
			SwitchToNextScene();
		}
				
		_currentScene->Process();

		// ������������� ���� ���� ����
		Colors::SetRenderColor(_renderer, Color::Black);
		
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

bool Game::PollEvents(SDL_Event* e)
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
