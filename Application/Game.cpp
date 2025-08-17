#include "Game.h"

Game::Game(): Application()
{
	auto appSettings = AppSettingsSerializer().Deserialize();
	auto [width, height] = appSettings.GetWindowSize();

	_window = new Window
	{
		/* title */ "Tetris",
		/* position */ SDL_Point(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
		/* width */ 400,
		/* height */ 800,
		/* actualWidth */ width,
		/* actualHeight */ height,
		/* flags*/ SDL_WINDOW_SHOWN
	};
	
	_audioManager = new GameAudioManager();
	_audioManager->SetMusicVolume(appSettings.MusicVolume);
	_audioManager->SetSoundEffectsVolume(appSettings.SoundEffectVolume);
	
	_delay = 6;

	_window->SetNextScene(new StartMenu());
}