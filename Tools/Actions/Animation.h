#pragma once

#include <functional>
#include <chrono>

#include "ActionBase.h"

struct AnimationEventArgs
{
	std::chrono::milliseconds Period;
	size_t ActionsCompleted;
};

class Animation: public ActionBase
{
public:
	using AnimationEventHandler = std::function<void(Animation*, const AnimationEventArgs&)>;

	AnimationEventHandler AnimationCompleted;
	AnimationEventHandler ActionCompleted;

	const size_t Actions;
protected:
	size_t _actionsCompleted = 0;
public:
	Animation(std::chrono::milliseconds period, size_t actions) noexcept;

	virtual ~Animation() = default;

	void Process() override;

	void Start() noexcept override;

	void Stop() noexcept override;
protected:
	virtual void OnAnimationCompleted(const AnimationEventArgs& e);

	virtual void OnActionCompleted(const AnimationEventArgs& e);
};