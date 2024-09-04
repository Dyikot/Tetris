#include "AudioBase.h"

AudioBase::AudioBase() noexcept
{
	SetMaxVolume(MaxVolumeInPercent);
}

void AudioBase::SetMaxVolume(size_t volume)
{
	CorrectVolume(volume);
	_partOfMaxVolume = volume;
	_partOfMaxVolume /= MaxVolumeInPercent;
}

void AudioBase::CorrectVolume(size_t& volume)
{
	if(volume > MaxVolumeInPercent)
	{
		volume = MaxVolumeInPercent;
	}
}

size_t AudioBase::ToMixVolume(size_t volume)
{
	return volume * _partOfMaxVolume * MaxMixVolume / MaxVolumeInPercent;
}
