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
	/// Устаналивает фон сцены
	/// </summary>
	virtual void SetBackground() = 0;

	/// <summary>
	/// Закрывает сцену и освобождает ее ресурсы
	/// </summary>
	virtual void Close() = 0;

	/// <summary>
	/// Закрывает сцену и сохраняет ее ресурсы
	/// </summary>
	virtual void Hide() = 0;

	/// <summary>
	/// Задает текущее отображение сцены.
	/// Отображение может быть: Visible, Hidden и Closed.
	/// </summary>
	/// <param name="visibility">- отображение сцены</param>
	virtual void SetVisibility(SceneVisibility visibility) = 0;

	/// <summary>
	/// Возращает текущее отображение сцены.
	/// Отображение может быть: Visible, Hidden и Closed.
	/// </summary>
	/// <returns>Отображение сцены SceneVisibility</returns>
	virtual SceneVisibility GetVisibility() const = 0;
};