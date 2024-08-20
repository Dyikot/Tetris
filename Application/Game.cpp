#include "Game.h"

Game::Game()
{
	InitSDL();
	
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

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetLogicalSize(_renderer, WindowWidth, WindowHeight);

	_isRunning = true;
	_currentScene = new StartMenu();
}

Game::~Game()
{
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
}

void Game::Run()
{		
	SDL_Event event;	

	while(_isRunning)
	{
		while(PollEvent(&event))
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
	_isRunning = false;
}

void Game::InitSDL() const
{
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
