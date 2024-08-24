#pragma once

#include "SDL/SDL.h"

enum class SceneVisibility
{
	Visible, 
	Hidden, 
	Closed
};

class IScene
{
public:
	static constexpr int Scale = 4;
public:
	virtual ~IScene() = default;

	/// <summary>
	/// ��������� �����
	/// </summary>
	virtual void Show() const = 0;

	/// <summary>
	/// ��������� �������
	/// </summary>
	/// <param name="e"> - �������</param>
	virtual void HandleEvent(const SDL_Event& e) = 0;

	/// <summary>
	/// ��������� �����
	/// </summary>
	virtual void Process() = 0;

	/// <summary>
	/// ������������ ��� �����
	/// </summary>
	virtual void SetBackground() = 0;

	/// <summary>
	/// ��������� ����� � ����������� �� �������
	/// </summary>
	virtual void Close() = 0;

	/// <summary>
	/// ��������� ����� � ��������� �� �������
	/// </summary>
	virtual void Hide() = 0;

	/// <summary>
	/// ������ ������� ����������� �����.
	/// ����������� ����� ����: Visible, Hidden � Closed.
	/// </summary>
	/// <param name="visibility">- ����������� �����</param>
	virtual void SetVisibility(SceneVisibility visibility) = 0;

	/// <summary>
	/// ��������� ������� ����������� �����.
	/// ����������� ����� ����: Visible, Hidden � Closed.
	/// </summary>
	/// <returns>����������� ����� SceneVisibility</returns>
	virtual SceneVisibility GetVisibility() const = 0;
};