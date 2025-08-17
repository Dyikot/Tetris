#pragma once

#include <string_view>
#include <unordered_map>
#include "../Audio/Music.h"
#include "../Audio/SoundEffect.h"
#include "../Audio/AudioManager.h"

class GameAudioManager: public AudioManager
{
private:
	std::unordered_map<std::string_view, SoundEffect> _gameSoundEffects;
public:
	GameAudioManager() noexcept;
	~GameAudioManager();

	SoundEffect& GetSoundEffect(std::string_view name) override;
};

