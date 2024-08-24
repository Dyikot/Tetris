#include "Action.h"

Action::Action(std::chrono::milliseconds period) noexcept:
	ActionBase(period)
{
	
}

void Action::Process()
{
	if(_time >= Period)
	{
		OnCompleted({ .Period = Period });
		_time = std::chrono::milliseconds(0);
		_tickStartTime = std::chrono::steady_clock::now();
	}

	_time += GetTickDuration();
	_tickStartTime = std::chrono::steady_clock::now();
}

void Action::Start() noexcept
{
	_isActivated = Completed.operator bool();
	ActionBase::Start();
}

void Action::OnCompleted(const ActionEventArgs& e)
{
	if(Completed)
	{
		Completed(this, e);
	}
}
