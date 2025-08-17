#pragma once

#include <iostream>
#include <chrono>

#include "SDL/SDL.h"

inline constexpr Uint32 SDL_KEYHOLD = 767;

class KeyHoldDetector
{
private:
	bool _isActive = false;
	SDL_KeyboardEvent _keyboardEvent;
	std::chrono::steady_clock::time_point _holdStartTime;
public:
	bool IsKeyHold() noexcept;
	void Start(const SDL_KeyboardEvent& keyboardEvent) noexcept;
	const SDL_KeyboardEvent& GetEvent() const noexcept;
private:
	std::chrono::milliseconds GetHoldTime() const noexcept;
};