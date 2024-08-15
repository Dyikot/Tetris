#pragma once

#include <functional>

struct AnimationEventArgs
{
	int TicksCompleted;
	int CyclesCompleted;
};

class Animation
{
public:
	using AnimationEventHandler = std::function<void(Animation*, const AnimationEventArgs&)>;

	AnimationEventHandler AnimationCompleted;
	AnimationEventHandler AnimationCycleCompleted;

	const int TicksAmount;
	const int CyclesAmount;
private:
	bool _isActivated = false;

	int _ticksCompleted = 0;
	int _cyclesComplated = 0;
public:
	Animation(int ticksAmount, int cyclesAmount) noexcept;

	void Process();

	void Start() noexcept;

	void Pause() noexcept;

	void Stop() noexcept;

	bool IsActivated() const noexcept;
protected:
	virtual void OnAnimationCompleted(const AnimationEventArgs& e);

	virtual void OnAnimationCycleCompleted(const AnimationEventArgs& e);
};