#pragma once

#include <string>
#include "../Audio/Music.h"
#include "../Audio/SoundEffect.h"
#include "../Audio/AudioManager.h"

class GameAudioManager: public AudioManager
{
public:
	static constexpr size_t MusicTracksCount = 14;

	struct GameSoundEffects
	{
		SoundEffect ButtonClick = SoundEffect("Resources/SoundEffects/buttonClick.wav");
		SoundEffect TetrominoMove = SoundEffect("Resources/SoundEffects/move.wav");
		SoundEffect TetrominoFall = SoundEffect("Resources/SoundEffects/fall.wav");
		SoundEffect SingleRowClear = SoundEffect("Resources/SoundEffects/clearRow.wav");
		SoundEffect UpTo3RowClear = SoundEffect("Resources/SoundEffects/clearUpTo3Rows.wav");
		SoundEffect UpTo4RowClear = SoundEffect("Resources/SoundEffects/clearUpTo4Rows.wav");
		SoundEffect GameOver = SoundEffect("Resources/SoundEffects/over.mp3");
	}SoundEffects;
public:
	GameAudioManager() noexcept;

	~GameAudioManager();
};

