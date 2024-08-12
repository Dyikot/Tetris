#pragma once

#include "SDL/SDL.h"

class Scene
{
public:
	static constexpr int Scale = 4;
public:
	virtual ~Scene() = default;

	/// <summary>
	/// Отрисовка сцены
	/// </summary>
	virtual void Show() = 0;

	/// <summary>
	/// Обработка события
	/// </summary>
	/// <param name="e"> - событие</param>
	virtual void HandleEvent(const SDL_Event& e) = 0;

	/// <summary>
	/// Обработка сцены
	/// </summary>
	virtual void Process() = 0;
};