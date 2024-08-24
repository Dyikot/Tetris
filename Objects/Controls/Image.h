#pragma once

#include "Control.h"
#include "../../Graphics/Texture.h"

class Image: public Control
{
protected:
	Texture _texture;
public:
	Image(const SDL_Point& position,
		  int width,
		  int height,
		  const SDL_Color& background,
		  std::string_view path) noexcept;

	Image(const SDL_Point& position,
		  int width,
		  int height,
		  std::string_view path) noexcept;

	Image(const SDL_Point& position, std::string_view path) noexcept;

	Image(const SDL_Point& position, std::string_view path, const Style& style) noexcept;

	void Show() const override;

	void SetBackground(const SDL_Color& color) override;

	void OnMouseEnter(const SDL_MouseButtonEvent& e) override;

	void OnMouseLeave(const SDL_MouseButtonEvent& e) override;
};

