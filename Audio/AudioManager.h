#pragma once

#include <vector>
#include "Music.h"
#include "SoundEffect.h"
#include "Random/Random.h"

class AudioManager
{
protected:
	std::vector<Music*> _musicTracks;
	std::vector<SoundEffect*> _soundEffects;
	int _currentTrackIndex = 0;
public:
	virtual ~AudioManager() = default;

	void SetVolume(size_t volume);

	void SetSoundEffectsVolume(size_t volume);

	void SetMusicVolume(size_t volume);

	virtual void PlayMusic();

	virtual void ShuffleMusicTracks();

	Music* const CurrentTrack() const noexcept;
};

template<typename T>
concept AudioManagerType = std::derived_from<T, AudioManager>;