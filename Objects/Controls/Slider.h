#pragma once

#include "Control.h"
struct ThumbMovedEventArgs
{
	size_t Filling;
};

class Slider: public Control
{
public:
	using ThumbMoveEventHandler = std::function<void(Object*, const ThumbMovedEventArgs& e)>;

	static constexpr size_t Full = 100;
	ThumbMoveEventHandler ThumbMoved;
	SDL_Color ThumbColor = Colors::Whitesmoke;
	SDL_Color BorderColor = Colors::Green;
protected:
	const int ThumbWidth;
	const int ThumbHeight;	
	const int StartThumbXPosition;
	const int EndThumbXPosition;
	SDL_Point _thumbPosition;
public:
	Slider(const SDL_Point& position,
		   int width,
		   int height,
		   const SDL_Color& background,
		   size_t filling = Full) noexcept;

	Slider(const SDL_Point& position, const Style& style, size_t filling = Full) noexcept;

	virtual ~Slider() = default;

	void OnRender() const noexcept override;

	void MoveThumbTo(const int x) noexcept;

	void SetFilling(size_t filling) noexcept;

	/// <returns>процент заполнения 0 - 100 %</returns>
	size_t GetFilling() const noexcept;
protected:
	virtual void OnThumbMoved(const ThumbMovedEventArgs& e);
};