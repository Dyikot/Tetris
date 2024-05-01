#pragma once

#include "Control.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
protected:
	std::string _text;
	Colors _textColor;
	TTF_Font* _font;
	SDL_Surface* _textSurface;
	SDL_Texture* _textTexture;
public:
	TextBlock(
		const Coordinates& position = { .x = 0, .y = 0 },
		int width = 30,
		int height = 10,
		Colors background = Colors::None,
		const std::string& text = "Текстовый элемент управления",
		Colors textColor = Colors::Black,
		TTF_Font* font = TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 24)
	):
		Control(position, width, height, background),
		_text(text),
		_textColor(textColor),
		_font(font),
		_textSurface(TTF_RenderText_Solid(
			_font, 
			_text.c_str(), 
			Color::ToSDL_Color(textColor)
		)),
		_textTexture(SDL_CreateTextureFromSurface(_renderer, _textSurface)){}

	virtual ~TextBlock()
	{
		TTF_CloseFont(_font);
		SDL_FreeSurface(_textSurface);
		SDL_DestroyTexture(_textTexture);
	}

	void Show() override;

	void SetText(const std::string& text);

	void SetTextColor(Colors textColor);	

	const std::string& GetText() const;

	Colors GetTextColor() const;
};
