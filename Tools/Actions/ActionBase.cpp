#include "ActionBase.h"

ActionBase::ActionBase(std::chrono::milliseconds period) noexcept:
	Period(period)
{

}

bool ActionBase::TryProcess()
{
	if(!IsActivated())
	{
		return false;
	}

	if(IsPaused())
	{
		Start();
	}
	else
	{
		Process();
	}

	return true;
}

void ActionBase::Start() noexcept
{
	_isPaused = false;
	_tickStartTime = std::chrono::steady_clock::now();
}

void ActionBase::Pause() noexcept
{
	_isPaused = true;
	_time += GetTickDuration();
}

void ActionBase::Stop() noexcept
{
	_isActivated = false;
	_time = std::chrono::milliseconds(0);
}

bool ActionBase::IsActivated() const noexcept
{
	return _isActivated;
}

bool ActionBase::IsPaused() const noexcept
{
	return _isPaused;
}

std::chrono::milliseconds ActionBase::GetTickDuration() const noexcept
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - _tickStartTime
	);
}
