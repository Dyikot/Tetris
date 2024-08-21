#pragma once

#include "Control.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
public:
	static constexpr SDL_Color ActiveTextColor = Colors::Whitesmoke;
	static constexpr SDL_Color InactiveTextColor = Colors::Grey;
protected:
	TTF_Font* _font;
	SDL_Color _fontColor;
	std::string _text;
	SDL_Texture* _textTexture;
public:
	TextBlock(const SDL_Point& position,
			  const SDL_Color& background,
			  const std::string& text,
			  const SDL_Color& fontColor,
			  int fontSize) noexcept;	

	~TextBlock();

	void Show() const noexcept override;

	void SetText(const std::string& text) noexcept;

	void SetFontColor(const SDL_Color& fontColor) noexcept;	

	const std::string& GetText() const noexcept;

	SDL_Color GetTextColor() const noexcept;

	SDL_Point GetRealPosition() const;
protected:
	TextBlock(const SDL_Point& position,
			  int width,
			  int height,
			  const SDL_Color& background,
			  const std::string& text,
			  const SDL_Color& fontColor,
			  int fontSize) noexcept;

	SDL_Texture* GenerateTextureByText() const noexcept;
};
