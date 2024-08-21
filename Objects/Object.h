#pragma once

#include "SDL/SDL.h"
#include "../Application/Application.h"
#include "../Style/Colors.h"

class Object
{
public:
	static constexpr SDL_Color DefaultBackgroundColor = Colors::None;
protected:
	SDL_Color _backgroud;
	SDL_Renderer* _renderer = Application::Current()->GetRenderer();
public:
	Object(const SDL_Color& background = DefaultBackgroundColor) noexcept;

	virtual ~Object() = default;

	virtual void Show() const = 0;
		
	virtual const SDL_Color& GetBackground() const noexcept;

	virtual void SetBackground(const SDL_Color& color) noexcept;
};