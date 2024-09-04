#include "Game.h"

Game::Game(): Application()
{
	auto serializationData = SettinsDataSerializer().Deserialize();
	auto settingsData = dynamic_cast<SettingsData*>(serializationData.get());
	
	_window = new Window
	{
		"Tetris",
		SDL_Point
		{
			.x = SDL_WINDOWPOS_CENTERED,
			.y = SDL_WINDOWPOS_CENTERED
		},
		/*width*/ 400,
		/*height*/ 800,
		/*actualWidth*/ static_cast<int>(settingsData->WindowWidth),
		/*actualHeight*/ static_cast<int>(settingsData->WindowHeight),
		SDL_WINDOW_SHOWN 
	};
	
	_audioManager = new GameAudioManager();
	_audioManager->SetMusicVolume(settingsData->MusicVolume);
	_audioManager->SetSoundEffectsVolume(settingsData->SoundEffectVolume);
	
	_delay = 6;

	_window->SetNextScene(new StartMenu());
}