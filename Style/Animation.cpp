#include "Animation.h"

Animation::Animation(const int ticksAmount,
					 const int cyclesAmount,
					 const std::function<void(void)> onAnimationCompleted,
					 const std::function<void(void)> onAnimationCycleComplete) noexcept :
	TicksAmount(ticksAmount),
	CyclesAmount(cyclesAmount),
	OnAnimationCompleted(onAnimationCompleted),
	OnAnimationCycleComplete(onAnimationCycleComplete)
{

}

void Animation::Process()
{
	if(_ticksCompleted == TicksAmount)
	{
		OnAnimationCycleComplete();
		_cyclesComplated++;
		_ticksCompleted = 0;
	}

	if(_cyclesComplated == CyclesAmount)
	{
		OnAnimationCompleted();
		Stop();
		return;
	}

	_ticksCompleted++;
}

void Animation::Start() noexcept
{
	_isActivated = true;
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

int Animation::GetCompletedCyclesAmount() const noexcept
{
	return _cyclesComplated;
}
