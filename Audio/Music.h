#pragma once

#include <string_view>
#include <iostream>
#include "SDL/SDL_mixer.h"
#include "AudioBase.h"

class Music: public AudioBase
{
private:
	Mix_Music* _music {};
public:
	Music() = default;
	Music(std::string_view path) noexcept;
	Music(const Music&) = delete;
	Music(Music&& other) noexcept;	
	~Music() noexcept;

	void Play() const noexcept override;
	void Pause() const noexcept;
	void Resume() const noexcept;
	void Stop() const noexcept;
	void SetVolume(size_t volume) noexcept override;
};

