#pragma once

#include "SDL/SDL.h"
#include "../Application/Application.h"
#include "../Style/Color.h"

class Object
{
public:
	static constexpr Color DefaultBackgroundColor = Color::None;
protected:
	Color _backgroud;
	SDL_Renderer* _renderer = Application::Current()->GetRenderer();
public:
	Object(Color background = DefaultBackgroundColor) noexcept;

	virtual ~Object() = default;

	virtual void Show() const = 0;
		
	virtual Color GetBackground() const noexcept;

	virtual void SetBackground(Color color) noexcept;
};