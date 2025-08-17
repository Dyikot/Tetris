#include "GameAudioManager.h"
#include <string>

GameAudioManager::GameAudioManager() noexcept
{
	_gameSoundEffects.emplace("ButtonClick", "Resources/SoundEffects/buttonClick.wav");
	_gameSoundEffects.emplace("TetrominoMove", "Resources/SoundEffects/move.wav");
	_gameSoundEffects.emplace("TetrominoFall", "Resources/SoundEffects/fall.wav");
	_gameSoundEffects.emplace("SingleRowClear", "Resources/SoundEffects/clearRow.wav");
	_gameSoundEffects.emplace("UpTo3RowClear", "Resources/SoundEffects/clearUpTo3Rows.wav");
	_gameSoundEffects.emplace("UpTo4RowClear", "Resources/SoundEffects/clearUpTo4Rows.wav");
	_gameSoundEffects.emplace("GameOver", "Resources/SoundEffects/over.mp3");

	_soundEffects =
	{
		&_gameSoundEffects["ButtonClick"],
		&_gameSoundEffects["TetrominoMove"],
		&_gameSoundEffects["TetrominoFall"],
		&_gameSoundEffects["GameOver"],
		&_gameSoundEffects["SingleRowClear"],
		&_gameSoundEffects["UpTo3RowClear"],
		&_gameSoundEffects["UpTo4RowClear"]
	};

	for(size_t i = 1; i <= 14; i++)
	{
		_musicTracks.push_back(new Music("Resources/Music/" + std::to_string(i) + ".mp3"));
	}

	_gameSoundEffects["TetrominoMove"].SetMaxVolume(30);
	_gameSoundEffects["GameOver"].SetMaxVolume(40);
	_gameSoundEffects["SingleRowClear"].SetMaxVolume(50);
	_gameSoundEffects["UpTo3RowClear"].SetMaxVolume(70);
	_gameSoundEffects["UpTo4RowClear"].SetMaxVolume(50);
}

GameAudioManager::~GameAudioManager()
{
	for(auto musicTrack : _musicTracks)
	{
		delete musicTrack;
	}
}

SoundEffect& GameAudioManager::GetSoundEffect(std::string_view name)
{
	return _gameSoundEffects[name];
}