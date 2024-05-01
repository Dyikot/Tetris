#pragma once

#include "SDL/SDL.h"

class Scene
{
public:
	virtual ~Scene() = default;

	// ��������� �����
	virtual void Show() = 0;

	// ��������� �������
	virtual void HandleEvent(const SDL_Event& e) = 0;

	// ��������� �����
	virtual void Process() = 0;
};