#pragma once

#include "Control.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
public:
	static constexpr Color ActiveTextColor = Color::White;
	static constexpr Color InactiveTextColor = Color::Grey;
protected:
	std::string _text;
	Color _textColor;
	TTF_Font* _font;
	SDL_Surface* _textSurface;
	SDL_Texture* _textTexture;
private:
	const int Width = 0;
	const int Height = 0;
public:
	TextBlock(const Coordinates& position,
			  Color background,
			  const std::string& text,
			  Color textColor,
			  int textSize
	):
		TextBlock(position, Width, Height, background, text, textColor, textSize){}
	

	virtual ~TextBlock()
	{
		TTF_CloseFont(_font);
		SDL_FreeSurface(_textSurface);
		SDL_DestroyTexture(_textTexture);
	}

	void Show() override;

	void SetText(const std::string& text);

	void SetTextColor(Color textColor);	

	const std::string& GetText() const;

	Color GetTextColor() const;

protected:
	TextBlock(const Coordinates& position,
		int width,
		int height,
		Color background,
		const std::string& text,
		Color textColor,
		int textSize
	):
		Control(position, width, height, background),
		_text(text),
		_textColor(textColor),
		_font(TTF_OpenFont("Style/Fonts/segoeui.ttf", textSize)),
		_textSurface(TTF_RenderText_Blended(_font, _text.c_str(), Colors::ToSDL_Color(textColor))),
		_textTexture(SDL_CreateTextureFromSurface(_renderer, _textSurface))
	{}
};
