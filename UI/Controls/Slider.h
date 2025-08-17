#pragma once

#include "../Control.h"

struct ThumbMovedEventArgs
{
	size_t Filling;
};

class Slider: public Control
{
public:
	using ThumbMoveEventHandler = std::function<void(Renderable*, const ThumbMovedEventArgs&)>;

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
	Slider(SDL_Point position,
		   int width,
		   int height,
		   SDL_Color background,
		   size_t filling = Full) noexcept;
	Slider(SDL_Point position, const Style& style, size_t filling = Full) noexcept;
	virtual ~Slider() = default;

	void Render(SDL_Renderer* renderer) const override;

	void MoveThumbTo(int x) noexcept;

	void SetFilling(size_t filling) noexcept;
	size_t GetFilling() const noexcept;
protected:
	virtual void OnThumbMoved(const ThumbMovedEventArgs& e);
};