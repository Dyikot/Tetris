#pragma once

#include <string_view>
#include <iostream>
#include "SDL/SDL_mixer.h"

class SoundEffect
{
private:
	Mix_Chunk* _soundEffect = nullptr;
public:
	SoundEffect(std::string_view path) noexcept;

	~SoundEffect() noexcept;

	void Play() const noexcept;
};