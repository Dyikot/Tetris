#pragma once

#include "Control.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
public:
	static constexpr Color ActiveTextColor = Color::Whitesmoke;
	static constexpr Color InactiveTextColor = Color::Grey;
protected:
	std::string _text;

	Color _textColor;

	TTF_Font* _font;

	SDL_Texture* _textTexture;
public:
	TextBlock(const SDL_Point& position,
			  Color background,
			  const std::string& text,
			  Color textColor,
			  int textSize) noexcept;	

	~TextBlock();

	void Show() const noexcept override;

	void SetText(const std::string& text) noexcept;

	void SetTextColor(Color textColor) noexcept;	

	const std::string& GetText() const noexcept;

	Color GetTextColor() const noexcept;

	SDL_Point GetRealPosition() const;
protected:
	TextBlock(const SDL_Point& position,
			  int width,
			  int height,
			  Color background,
			  const std::string& text,
			  Color textColor,
			  int textSize) noexcept;

	SDL_Texture* GenerateTextureByText() const noexcept;
};
