#pragma once

#include <string_view>
#include <iostream>
#include "SDL/SDL_mixer.h"
#include "AudioBase.h"

class SoundEffect: public AudioBase
{
private:
	Mix_Chunk* _soundChunk {};
public:
	SoundEffect() = default;
	SoundEffect(std::string_view path) noexcept;
	SoundEffect(const SoundEffect&) = delete;
	SoundEffect(SoundEffect&& other) noexcept;
	~SoundEffect() noexcept;

	void Play() const noexcept override;
	void Play(int channel) const noexcept;
	void SetVolume(size_t volume) noexcept override;
};