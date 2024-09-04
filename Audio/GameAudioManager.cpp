#include "GameAudioManager.h"

GameAudioManager::GameAudioManager() noexcept
{
	_soundEffects =
	{
		&SoundEffects.ButtonClick,
		&SoundEffects.TetrominoMove,
		&SoundEffects.TetrominoFall,
		&SoundEffects.GameOver,
		&SoundEffects.SingleRowClear,
		&SoundEffects.UpTo3RowClear,
		&SoundEffects.UpTo4RowClear
	};

	for(size_t i = 1; i <= MusicTracksCount; i++)
	{
		_musicTracks.push_back(new Music("Resources/Music/" + std::to_string(i) + ".mp3"));
	}

	SoundEffects.TetrominoMove.SetMaxVolume(30);
	SoundEffects.GameOver.SetMaxVolume(40);
	SoundEffects.SingleRowClear.SetMaxVolume(50);
	SoundEffects.UpTo3RowClear.SetMaxVolume(70);
	SoundEffects.UpTo4RowClear.SetMaxVolume(50);
}

GameAudioManager::~GameAudioManager()
{
	for(auto musicTrack : _musicTracks)
	{
		delete musicTrack;
	}
}
