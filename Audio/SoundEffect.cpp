#include "SoundEffect.h"

static constexpr int ChannelAutoSelection = -1;

SoundEffect::SoundEffect(std::string_view path) noexcept
{
	_soundChunk = Mix_LoadWAV(path.data());

	if(_soundChunk == nullptr)
	{
		std::cout << SDL_GetError() << '\n';
	}
}

SoundEffect::SoundEffect(SoundEffect&& other) noexcept:
	_soundChunk(std::exchange(other._soundChunk, nullptr))
{}

SoundEffect::~SoundEffect() noexcept
{
	if(_soundChunk)
	{
		Mix_FreeChunk(_soundChunk);
	}
}

void SoundEffect::Play() const noexcept
{
	Mix_PlayChannel(ChannelAutoSelection, _soundChunk, PlayOnce);
}

void SoundEffect::Play(int channel) const noexcept
{
	Mix_PlayChannel(channel, _soundChunk, PlayOnce);
}

void SoundEffect::SetVolume(size_t volume) noexcept
{
	AdjustVolume(volume);
	Mix_VolumeChunk(_soundChunk, ToMixVolume(volume));
}
