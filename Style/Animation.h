#pragma once

#include <functional>

class Animation
{
public:
	const int TicksAmount;
	const int CyclesAmount;
private:
	bool _isActivated = false;

	int _ticksCompleted = 0;
	int _cyclesComplated = 0;

	const std::function<void(void)> OnAnimationCompleted;
	const std::function<void(void)> OnAnimationCycleComplete;
public:
	Animation(const int ticksAmount,
			  const int cyclesAmount,
			  std::function<void(void)> onAnimationCompleted,
			  std::function<void(void)> onAnimationCycleComplete) noexcept;

	void Process();

	void Start() noexcept;

	void Stop() noexcept;

	bool IsActivated() const noexcept;

	int GetCompletedCyclesAmount() const noexcept;
};