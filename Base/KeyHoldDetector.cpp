#include "KeyHoldDetector.h"

using namespace std::chrono;

static constexpr milliseconds ActivationTime = milliseconds(140);
static constexpr milliseconds InvokeTime = milliseconds(30);

bool KeyHoldDetector::IsKeyHold() noexcept
{
	if(_keyboardEvent.state == SDL_PRESSED)
	{
		if(_isActive && GetHoldTime() > InvokeTime)
		{
			_holdStartTime = high_resolution_clock::now();
			return true;
		}

		if(GetHoldTime() > ActivationTime)
		{
			_isActive = true;
			_holdStartTime = high_resolution_clock::now();
			return true;
		}
	}

	return false;
}

void KeyHoldDetector::Start(const SDL_KeyboardEvent& keyboardEvent) noexcept
{
	_keyboardEvent = keyboardEvent;
	_keyboardEvent.type = SDL_KEYHOLD;
	_isActive = false;
	_holdStartTime = high_resolution_clock::now();
}

const SDL_KeyboardEvent& KeyHoldDetector::GetEvent() const noexcept
{
	return _keyboardEvent;
}

milliseconds KeyHoldDetector::GetHoldTime() const noexcept
{
	return duration_cast<milliseconds>(high_resolution_clock::now() - _holdStartTime);
}