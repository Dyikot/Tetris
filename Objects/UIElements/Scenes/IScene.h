#pragma once

#include "SDL/SDL.h"

class IScene
{
public:
	static constexpr int Scale = 4;
public:
	virtual ~IScene() = default;

	/// <summary>
	/// Отрисовка сцены
	/// </summary>
	virtual void Show() const = 0;

	/// <summary>
	/// Обработка события
	/// </summary>
	/// <param name="e"> - событие</param>
	virtual void HandleEvent(const SDL_Event& e) = 0;

	/// <summary>
	/// Обработка сцены
	/// </summary>
	virtual void Process() = 0;

	/// <summary>
	/// Устаналивает фон
	/// </summary>
	virtual void SetBackground() = 0;
};