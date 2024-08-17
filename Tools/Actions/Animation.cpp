#include "Animation.h"

Animation::Animation(std::chrono::milliseconds period, size_t actions) noexcept:
	ActionBase(period),
	Actions(actions)
{
	
}

void Animation::Process()
{
	if(_time >= Period)
	{
		OnActionCompleted({ Period, _actionsCompleted });
		_time = std::chrono::milliseconds(0);
		_tickStartTime = std::chrono::steady_clock::now();
		_actionsCompleted++;
	}
	
	if(_actionsCompleted == Actions)
	{
		OnAnimationCompleted({ Period, _actionsCompleted });
		Stop();
		return;
	}

	_time += GetTickDuration();
	_tickStartTime = std::chrono::steady_clock::now();
}

void Animation::Start() noexcept
{
	_isActivated = AnimationCompleted && ActionCompleted;
	ActionBase::Start();
}


void Animation::Stop() noexcept
{
	_actionsCompleted = 0;
	ActionBase::Stop();
}

void Animation::OnAnimationCompleted(const AnimationEventArgs& e)
{
	if(AnimationCompleted)
	{
		AnimationCompleted(this, e);
	}
}

void Animation::OnActionCompleted(const AnimationEventArgs& e)
{
	if(ActionCompleted)
	{
		ActionCompleted(this, e);
	}
}
