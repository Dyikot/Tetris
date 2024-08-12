#pragma once

#include <functional>

class Animation
{
public:
	const int TicksAmount;
	const int CyclesAmount;
private:
	const std::function<void(void)> OnAnimationCompleted;
	const std::function<void(void)> OnAnimationCycleComplete;

	bool _isActivated = false;

	int _ticksCompleted = 0;
	int _cyclesComplated = 0;
public:
	Animation(const int ticksAmount,
			  const int cyclesAmount,
			  std::function<void(void)> onAnimationCompleted,
			  std::function<void(void)> onAnimationCycleComplete) noexcept;

	void Process();

	void Start() noexcept;

	void Pause() noexcept;

	void Stop() noexcept;

	bool IsActivated() const noexcept;

	int GetCompletedCyclesAmount() const noexcept;
};