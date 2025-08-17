#pragma once

#include <functional>
#include <SDL/SDL_events.h>
#include "../Render/Renderable.h"

class UIElement: public Renderable
{
public:
	using MouseEventHandler = std::function<void(Renderable*, const SDL_MouseButtonEvent&)>;
	using KeyEventHandler = std::function<void(Renderable*, const SDL_KeyboardEvent&)>;

	MouseEventHandler MouseDown;
	MouseEventHandler MouseMove;
	KeyEventHandler KeyDown;
	KeyEventHandler KeyHold;
public:
	virtual ~UIElement() = default;

	virtual void OnMouseDown(const SDL_MouseButtonEvent& e);
	virtual void OnMouseMove(const SDL_MouseButtonEvent& e);
	virtual void OnKeyDown(const SDL_KeyboardEvent& e);
	virtual void OnKeyHold(const SDL_KeyboardEvent& e);
};