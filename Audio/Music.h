#pragma once

#include <string_view>
#include <iostream>
#include "SDL/SDL_mixer.h"

class Music
{
private:
	Mix_Music* _music = nullptr;
public:
	Music(std::string_view path) noexcept;
	
	~Music() noexcept;

	void Play() const noexcept;

	void Pause() const noexcept;

	void Stop() const noexcept;
};

