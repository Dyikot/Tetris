#pragma once

#include "../Control.h"
#include "../../Base/Texture.h"

class Image: public Control
{
protected:
	Texture _texture;
public:
	Image(SDL_Point position, int width, int height, SDL_Color background, std::string_view path) noexcept;
	Image(SDL_Point position, int width, int height, std::string_view path) noexcept;
	Image(SDL_Point position, std::string_view path) noexcept;
	Image(SDL_Point position, std::string_view path, const Style& style) noexcept;

	void Render(SDL_Renderer* renderer) const override;
	void SetBackground(SDL_Color color) override;
	void OnMouseEnter(const SDL_MouseButtonEvent& e) override;
	void OnMouseLeave(const SDL_MouseButtonEvent& e) override;
};

