#pragma once

#include <iostream>
#include <chrono>

#include "SDL/SDL.h"

static constexpr Uint32 SDL_KEYHOLD = 767;

class KeyHoldRegister
{
public:
	const std::chrono::milliseconds ActivationTime = std::chrono::milliseconds(140);
	const std::chrono::milliseconds InvokeTime = std::chrono::milliseconds(30);
private:
	bool _isActive = false;
	SDL_KeyboardEvent _keyboardEvent;
	std::chrono::steady_clock::time_point _startHoldKeyTime;
public:
	bool IsKeyHold() noexcept;

	void Register(const SDL_KeyboardEvent& keyboardEvent) noexcept;

	const SDL_KeyboardEvent& GetEvent() const noexcept;
private:
	std::chrono::milliseconds GetHoldTime() const noexcept;
};

