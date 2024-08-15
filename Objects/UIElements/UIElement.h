#pragma once

#include <functional>
#include "../Object.h"

class UIElement: public Object
{
public:
	using MouseEventHandler = std::function<void(Object*, const SDL_MouseButtonEvent& e)>;
	using KeyEventHandler = std::function<void(Object*, const SDL_KeyboardEvent& e)>;
	
	MouseEventHandler MouseDown;
	MouseEventHandler MouseMove;
	KeyEventHandler KeyDown;
	KeyEventHandler KeyHold;
public:
	UIElement(Color backgound = DefaultBackgroundColor);

	virtual void OnMouseDown(const SDL_MouseButtonEvent& e);

	virtual void OnMouseMove(const SDL_MouseButtonEvent& e);

	virtual void OnKeyDown(const SDL_KeyboardEvent& e);

	virtual void OnKeyHold(const SDL_KeyboardEvent& e);
};