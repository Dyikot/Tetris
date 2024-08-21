#pragma once

#include <vector>
#include "../Control.h"


class Button: public Control
{
public:
	static constexpr SDL_Color DefaultBorderColor = Colors::Green;
	MouseEventHandler Click;
protected:
	SDL_Color _borderColor;
	Control* _content;
public:
	Button(const SDL_Point& position,
		   int width,
		   int height,
		   const SDL_Color& background,
		   SDL_Color borderColor,
		   Control* content = nullptr) noexcept;

	virtual ~Button() = default;

	void Show() const override;

	void SetContent(Control* content) noexcept;

	virtual void OnClick(const SDL_MouseButtonEvent& e);

	Control* const GetContent() const;
};