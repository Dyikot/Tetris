#include "Animation.h"

Animation::Animation(int ticksAmount, int cyclesAmount) noexcept:
	TicksAmount(ticksAmount),
	CyclesAmount(cyclesAmount)
{

}

void Animation::Process()
{
	if(_ticksCompleted == TicksAmount)
	{
		OnAnimationCycleCompleted({_ticksCompleted, _cyclesComplated});
		_cyclesComplated++;
		_ticksCompleted = 0;
	}

	if(_cyclesComplated == CyclesAmount)
	{
		OnAnimationCompleted({ _ticksCompleted, _cyclesComplated });
		Stop();
		return;
	}

	_ticksCompleted++;
}

void Animation::Start() noexcept
{
	_isActivated = AnimationCompleted && AnimationCycleCompleted;
}

void Animation::Pause() noexcept
{
	_isActivated = false;
}

void Animation::Stop() noexcept
{
	_ticksCompleted = 0;
	_cyclesComplated = 0;
	_isActivated = false;
}

bool Animation::IsActivated() const noexcept
{
	return _isActivated;
}

void Animation::OnAnimationCompleted(const AnimationEventArgs& e)
{
	if(AnimationCompleted)
	{
		AnimationCompleted(this, e);
	}
}

void Animation::OnAnimationCycleCompleted(const AnimationEventArgs & e)
{
	if(AnimationCycleCompleted)
	{
		AnimationCycleCompleted(this, e);
	}
}
