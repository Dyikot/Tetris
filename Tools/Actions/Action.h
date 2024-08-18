#pragma once

#include <chrono>
#include <functional>

#include "ActionBase.h"

struct ActionEventArgs
{
	std::chrono::milliseconds Period;
};

class Action: public ActionBase
{
public:
	using ActionEventHandler = std::function<void(Action*, const ActionEventArgs&)>;

	ActionEventHandler ActionCompleted;
public:
	Action(std::chrono::milliseconds period) noexcept;

	virtual ~Action() = default;

	virtual void Process() override;

	virtual void Start() noexcept override;
protected:
	virtual void OnActionCompleted(const ActionEventArgs& e);
};