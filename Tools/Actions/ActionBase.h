#pragma once

#include <chrono>
#include <functional>

class ActionBase
{
public:
	const std::chrono::milliseconds Period;
protected:
	bool _isActivated = false;

	bool _isPaused = false;

	std::chrono::steady_clock::time_point _tickStartTime;

	std::chrono::milliseconds _time = std::chrono::milliseconds(0);
public:
	ActionBase(std::chrono::milliseconds period) noexcept;

	virtual ~ActionBase() = default;

	bool TryProcess();

	virtual void Process() = 0;

	virtual void Start() noexcept;

	virtual void Pause() noexcept;

	virtual void Stop() noexcept;

	bool IsActivated() const noexcept;

	bool IsPaused() const noexcept;
protected:
	std::chrono::milliseconds GetTickDuration() const noexcept;
};