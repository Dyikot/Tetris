#include "AudioManager.h"

void AudioManager::SetVolume(size_t volume)
{
	SetSoundEffectsVolume(volume);
	SetMusicVolume(volume);
}

void AudioManager::SetSoundEffectsVolume(size_t volume)
{
	for(auto soundEffect : _soundEffects)
	{
		soundEffect->SetVolume(volume);
	}
}

void AudioManager::SetMusicVolume(size_t volume)
{
	for(auto music : _musicTracks)
	{
		music->SetVolume(volume);
	}
}

void AudioManager::PlayMusic()
{
	if(_musicTracks.empty())
	{
		return;
	}

	if(!Mix_PlayingMusic())
	{
		if(_currentTrackIndex >= _musicTracks.size())
		{
			ShuffleMusicTracks();
		}

		CurrentTrack()->Play();
		_currentTrackIndex++;
	}
	else if(Mix_PausedMusic())
	{
		CurrentTrack()->Resume();
	}
}

void AudioManager::ShuffleMusicTracks()
{
	_currentTrackIndex = 0;
	Random().Shuffle(_musicTracks);
}

Music* AudioManager::CurrentTrack() const noexcept
{
	return _musicTracks.empty() ? nullptr : _musicTracks[_currentTrackIndex];
}
