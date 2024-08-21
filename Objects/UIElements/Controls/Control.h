#pragma once

#include <string>
#include <functional>

#include "../UIElement.h"

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
	SDL_Color _backgroundOffHover;
public:
	Control(const SDL_Point& position,
			int width,
			int height,
			const SDL_Color& background) noexcept;

	virtual ~Control() = default;

	virtual void SetWidth(int width) noexcept;

	virtual void SetHeight(int height) noexcept;

	virtual void SetPosition(const SDL_Point& position) noexcept;

	virtual void SetBackground(const SDL_Color& color) noexcept override;

	virtual void OnMouseEnter(const SDL_MouseButtonEvent& e);

	virtual void OnMouseLeave(const SDL_MouseButtonEvent& e);

	virtual int GetWight() const noexcept;

	virtual int GetHeight() const noexcept;

	virtual const SDL_Point& GetPosition() const noexcept;

	virtual bool IsMouseOver(const SDL_MouseButtonEvent& e) noexcept;
};