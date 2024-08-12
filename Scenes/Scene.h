#pragma once

#include "SDL/SDL.h"

class Scene
{
public:
	static constexpr int Scale = 4;
public:
	virtual ~Scene() = default;

	/// <summary>
	/// ��������� �����
	/// </summary>
	virtual void Show() = 0;

	/// <summary>
	/// ��������� �������
	/// </summary>
	/// <param name="e"> - �������</param>
	virtual void HandleEvent(const SDL_Event& e) = 0;

	/// <summary>
	/// ��������� �����
	/// </summary>
	virtual void Process() = 0;
};