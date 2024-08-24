#pragma once

#include <vector>
#include "Control.h"
#include "../../BasicStructs/Style.h"

class Button: public Control
{
public:
	MouseEventHandler Click;
	SDL_Color BorderColor;
protected:
	Control* _content;
public:
	Button(const SDL_Point& position,
		   int width,
		   int height,
		   const SDL_Color& background,
		   SDL_Color borderColor,
		   Control* content = nullptr) noexcept;

	Button(const SDL_Point& position,
		   const Style& style,
		   Control* content = nullptr) noexcept;

	virtual ~Button() noexcept;

	void Show() const override;

	void SetContent(Control* content) noexcept;

	virtual void OnClick(const SDL_MouseButtonEvent& e);

	Control* const GetContent() const;
};