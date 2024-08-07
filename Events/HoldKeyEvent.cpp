#include "HoldKeyEvent.h"

std::chrono::milliseconds HoldKeyEvent::GetHoldTime() const noexcept
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - _startHoldKeyTime
	);
}

bool HoldKeyEvent::IsHold() noexcept
{
	if(state == SDL_PRESSED)
	{
		if(_isActive && GetHoldTime() > InvokeTime)
		{
			_startHoldKeyTime = std::chrono::high_resolution_clock::now();
			return true;
		}

		if(GetHoldTime() > ActivationTime)
		{
			_isActive = true;
			_startHoldKeyTime = std::chrono::high_resolution_clock::now();
			return true;
		}
	}

	return false;
}

HoldKeyEvent& HoldKeyEvent::operator=(const SDL_KeyboardEvent& event) noexcept
{
	type = SDL_KEYHOLD;
	keysym = event.keysym;
	timestamp = event.timestamp;
	windowID = event.windowID;
	state = event.state;
	padding2 = event.padding2;
	padding3 = event.padding3;

	_isActive = false;
	_startHoldKeyTime = std::chrono::high_resolution_clock::now();

	return *this;
}