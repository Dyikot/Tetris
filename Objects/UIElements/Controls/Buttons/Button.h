#pragma once

#include <vector>
#include "../Control.h"


class Button: public Control
{
public:
	static constexpr Color DefaultBorderColor = Color::Green;

	MouseEventHandler Click;
protected:
	Color _borderColor;

	Control* _content;
public:
	Button(const SDL_Point& position,
		   int width,
		   int height,
		   Color background,
		   Color borderColor,
		   Control* content = nullptr) noexcept;

	virtual ~Button() = default;

	void Show() const override;

	void SetContent(Control* content) noexcept;

	Control* const GetContent() const;

	virtual void OnClick(const SDL_MouseButtonEvent& e);
};