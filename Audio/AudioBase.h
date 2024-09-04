#pragma once

#include "SDL/SDL_mixer.h"

class AudioBase
{
protected:
	static constexpr int PlayEndless = -1;
	static constexpr int PlayOnce = 0;
	static constexpr size_t MaxVolumeInPercent = 100;
	static constexpr double MaxMixVolume = MIX_MAX_VOLUME;

	double _partOfMaxVolume;
public:
	AudioBase() noexcept;

	virtual ~AudioBase() = default;

	virtual void Play() const = 0;

	/// <summary>
	/// Set volume for all sound effects
	/// </summary>
	/// <param name="volume"> - percent value 0 ... 100 %</param>
	virtual void SetVolume(size_t volume) = 0;

	void SetMaxVolume(size_t volume);
protected:
	/// <summary>
	/// Correct volume if its value is greater than 100 %
	/// </summary>
	/// <param name="volume">- percent value 0 ... 100 %</param>
	void CorrectVolume(size_t& volume);

	size_t ToMixVolume(size_t volume);
};