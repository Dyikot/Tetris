#include "Music.h"

Music::Music(std::string_view path) noexcept
{
	_music = Mix_LoadMUS(path.data());
	
	if(_music == nullptr)
	{
		std::cout << "Music: " << SDL_GetError() << '\n';
	}
}

Music::Music(Music&& other) noexcept:
	_music(std::exchange(other._music, nullptr))
{}

Music::~Music() noexcept
{
	if(_music)
	{
		Mix_FreeMusic(_music);
	}
}

void Music::Play() const noexcept
{
	Mix_PlayMusic(_music, PlayOnce);
}

void Music::Pause() const noexcept
{
	if(!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
}

void Music::Resume() const noexcept
{
	Mix_ResumeMusic();
}

void Music::Stop() const noexcept
{
	Mix_HaltMusic();
}

void Music::SetVolume(size_t volume) noexcept
{
	AdjustVolume(volume);
	Mix_VolumeMusic(ToMixVolume(volume));
}
