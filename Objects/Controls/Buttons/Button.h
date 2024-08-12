#pragma once

#include <vector>
#include "../Control.h"


class Button: public Control
{
public:
	static constexpr Color DefaultBorderColor = Color::Green;

protected:
	Color _borderColor;
	Color _backgroundSaved;
private:
	Control* _content;
public:
	Button(const SDL_Point& position,
		   int width,
		   int height,
		   Color background,
		   Color borderColor,
		   Control* content = nullptr) noexcept;

	void Show() const override;

	void SetBackground(Color color) noexcept override;

	void SetPosition(const SDL_Point& position) noexcept override;

	void SetContent(Control* content) noexcept;

	const Control* GetContent() const;

	Control* GetContent() noexcept;
	
	virtual void OnHover() noexcept;

	virtual void OnLeave() noexcept;
};