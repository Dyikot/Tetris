#pragma once

#include <iostream>
#include <chrono>

#include "SDL/SDL.h"

constexpr Uint32 SDL_KEYHOLD = 767;

class HoldKeyEvent: public SDL_KeyboardEvent
{
public:
	const std::chrono::milliseconds ActivationTime = std::chrono::milliseconds(140);
	const std::chrono::milliseconds InvokeTime = std::chrono::milliseconds(30);
private:
	bool _isActive = false;
	std::chrono::steady_clock::time_point _startHoldKeyTime;
public:
	bool IsHold() noexcept;

	HoldKeyEvent& operator=(const SDL_KeyboardEvent& event) noexcept;
private:
	std::chrono::milliseconds GetHoldTime() const noexcept;
};

