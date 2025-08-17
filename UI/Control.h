#pragma once

#include <string>

#include "UIElement.h"
#include "../Base/Style.h"

class Control : public UIElement
{
public:
	SDL_Color BackgroundOnHover;
	MouseEventHandler MouseEnter;
	MouseEventHandler MouseLeave;
protected:
	SDL_Point _position;
	int _width;
	int _height;
	SDL_Color _background;
	SDL_Color _backgroundOffHover;
public:
	Control(SDL_Point position, int width, int height, SDL_Color background) noexcept;
	virtual ~Control() = default;

	virtual void SetWidth(int width);
	virtual void SetHeight(int height);
	virtual void SetPosition(SDL_Point position);
	virtual void SetBackground(SDL_Color color);
	virtual void OnMouseEnter(const SDL_MouseButtonEvent& e);
	virtual void OnMouseLeave(const SDL_MouseButtonEvent& e);
	virtual int GetWight() const;
	virtual int GetHeight() const;
	virtual SDL_Point GetPosition() const;
	virtual SDL_Color GetBackground() const;
	virtual bool IsMouseOver(const SDL_MouseButtonEvent& e);
};