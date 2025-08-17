#pragma once

#include "SDL/SDL_mixer.h"

class AudioBase
{
protected:
	static constexpr int PlayEndless = -1;
	static constexpr int PlayOnce = 0;
	static constexpr size_t MaxVolume = 100;
	static constexpr double MaxMixVolume = MIX_MAX_VOLUME;

	double _partOfMaxVolume;
public:
	AudioBase() noexcept;
	virtual ~AudioBase() = default;

	virtual void Play() const = 0;
	virtual void SetVolume(size_t volume) = 0;

	void SetMaxVolume(size_t volume);
	size_t ToMixVolume(size_t volume);
protected:
	void AdjustVolume(size_t& volume);
};