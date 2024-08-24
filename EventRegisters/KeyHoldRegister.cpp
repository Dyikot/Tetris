#include "KeyHoldRegister.h"

bool KeyHoldRegister::IsKeyHold() noexcept
{
	if(_keyboardEvent.state == SDL_PRESSED)
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

void KeyHoldRegister::Register(const SDL_KeyboardEvent& keyboardEvent) noexcept
{
	_keyboardEvent = keyboardEvent;
	_keyboardEvent.type = SDL_KEYHOLD;
	_isActive = false;
	_startHoldKeyTime = std::chrono::high_resolution_clock::now();
}

const SDL_KeyboardEvent& KeyHoldRegister::GetEvent() const noexcept
{
	return _keyboardEvent;
}

std::chrono::milliseconds KeyHoldRegister::GetHoldTime() const noexcept
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - _startHoldKeyTime
	);
}