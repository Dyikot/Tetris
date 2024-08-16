#include "Action.h"

Action::Action(std::chrono::milliseconds period) noexcept:
	ActionBase(period)
{
	
}

void Action::Process()
{
	if(_time >= Period)
	{
		OnActionCompleted({ .Period = Period });
		_time = std::chrono::milliseconds(0);
	}

	_time += GetTickDuration();
	_tickStartTime = std::chrono::steady_clock::now();
}

void Action::Start() noexcept
{
	_isActivated = ActionCompleted.operator bool();
	ActionBase::Start();
}

void Action::OnActionCompleted(const ActionEventArgs& e)
{
	if(ActionCompleted)
	{
		ActionCompleted(this, e);
	}
}
