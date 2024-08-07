#include "TextBlock.h"

void TextBlock::SetText(const std::string& text) noexcept
{
    _text = text;
}

void TextBlock::SetTextColor(Color textColor) noexcept
{
    _textColor = textColor;
}

TextBlock::TextBlock(const SDL_Point& position,
                     Color background, 
                     const std::string& text, 
                     Color textColor, int textSize) noexcept:
    TextBlock(position, Width, Height, background, text, textColor, textSize)
{

}

TextBlock::~TextBlock()
{
    TTF_CloseFont(_font);
    SDL_FreeSurface(_textSurface);
    SDL_DestroyTexture(_textTexture);
}


void TextBlock::Show() noexcept
{
    SDL_QueryTexture(_textTexture, NULL, NULL, &_width, &_height);

    SDL_Rect textRectangle =
    {
        .x = _position.x - _width / 2,
        .y = _position.y - _height / 2,
        .w = _width,
        .h = _height
    };

    SDL_RenderCopy(_renderer, _textTexture, NULL, &textRectangle);
}

const std::string& TextBlock::GetText() const noexcept
{
    return _text;
}

Color TextBlock::GetTextColor() const noexcept
{
    return _textColor;
}

TextBlock::TextBlock(const SDL_Point& position,
                     int width, 
                     int height,
                     Color background,
                     const std::string& text,
                     Color textColor,
                     int textSize) noexcept:
    Control(position, width, height, background),
    _text(text),
    _textColor(textColor),
    _font(TTF_OpenFont("Resources/Fonts/segoeui.ttf", textSize)),
    _textSurface(TTF_RenderText_Blended(_font, _text.c_str(), Colors::ToSDL_Color(textColor))),
    _textTexture(SDL_CreateTextureFromSurface(_renderer, _textSurface))
{

}
