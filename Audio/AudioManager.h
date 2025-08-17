#pragma once

#include <vector>
#include "Music.h"
#include "SoundEffect.h"
#include "Random.h"

class AudioManager
{
protected:
	std::vector<Music*> _musicTracks;
	std::vector<SoundEffect*> _soundEffects;
	int _currentTrackIndex = 0;
public:
	AudioManager() = default;
	virtual ~AudioManager() = default;

	virtual SoundEffect& GetSoundEffect(std::string_view name) = 0;

	void SetVolume(size_t volume);
	void SetSoundEffectsVolume(size_t volume);
	void SetMusicVolume(size_t volume);
	virtual void PlayMusic();
	virtual void ShuffleMusicTracks();
	Music* CurrentTrack() const noexcept;
};