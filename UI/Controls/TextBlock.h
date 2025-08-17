#pragma once

#include "../Control.h"
#include"../../Base/Texture.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
protected:
	TTF_Font* _fontFamily;
	SDL_Color _fontColor;
	std::string _text;
	Texture _textTexture;
public:
	TextBlock(SDL_Point position, 
			  SDL_Color background,
			  std::string_view text,
			  SDL_Color fontColor,
			  int fontSize) noexcept;

	TextBlock(SDL_Point position,
			  std::string_view text, 
			  SDL_Color fontColor,
			  int fontSize) noexcept;

	TextBlock(SDL_Point position, std::string_view text, const Style& style) noexcept;
	~TextBlock();

	void SetText(std::string_view text) noexcept;
	const std::string& GetText() const noexcept;

	void SetFontColor(SDL_Color fontColor) noexcept;
	SDL_Color GetFontColor() const noexcept;

	SDL_Point GetRealPosition() const noexcept;

	void Render(SDL_Renderer* renderer) const override;
private:
	SDL_Texture* CreateTextTexture() const noexcept;
	void SetSize(std::pair<int, int> size) noexcept;
};
