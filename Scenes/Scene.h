#pragma once

#include "SDL/SDL.h"

class Scene
{
public:
	virtual ~Scene() = default;

	// Отрисовка сцены
	virtual void Show() = 0;

	// Обработка события
	virtual void HandleEvent(const SDL_Event& e) = 0;

	// Обработка сцены
	virtual void Process() = 0;
};