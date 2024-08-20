#include "Music.h"

Music::Music(std::string_view path) noexcept
{
	_music = Mix_LoadMUS(path.data());

	if(_music == nullptr)
	{
		std::cout << SDL_GetError() << '\n';
	}
}

Music::~Music() noexcept
{
	Mix_FreeMusic(_music);
}

void Music::Play() const noexcept
{
	if(!Mix_PlayingMusic())
	{
		Mix_PlayMusic(_music, 0);
	}
	else if(Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void Music::Pause() const noexcept
{
	if(!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
}

void Music::Stop() const noexcept
{
	Mix_HaltMusic();
}