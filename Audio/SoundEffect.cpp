#include "SoundEffect.h"

SoundEffect::SoundEffect(std::string_view path) noexcept
{
	_soundEffect = Mix_LoadWAV(path.data());

	if(_soundEffect == nullptr)
	{
		std::cout << SDL_GetError() << '\n';
	}
}

SoundEffect::~SoundEffect() noexcept
{
	Mix_FreeChunk(_soundEffect);
}

void SoundEffect::Play() const noexcept
{
	Mix_PlayChannel(-1, _soundEffect, 0);
}
