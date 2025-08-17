#include "AudioBase.h"

AudioBase::AudioBase() noexcept
{
	SetMaxVolume(MaxVolume);
}

void AudioBase::SetMaxVolume(size_t volume)
{
	AdjustVolume(volume);
	_partOfMaxVolume = volume;
	_partOfMaxVolume /= MaxVolume;
}

void AudioBase::AdjustVolume(size_t& volume)
{
	if(volume > MaxVolume)
	{
		volume = MaxVolume;
	}
}

size_t AudioBase::ToMixVolume(size_t volume)
{
	return volume * _partOfMaxVolume * MaxMixVolume / MaxVolume;
}
