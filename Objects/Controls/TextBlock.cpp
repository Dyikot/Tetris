#include "TextBlock.h"

void TextBlock::SetText(const std::string& text)
{
    _text = text;
}

void TextBlock::SetTextColor(Colors textColor)
{
    _textColor = textColor;
}

void TextBlock::Show()
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

const std::string& TextBlock::GetText() const
{
    return _text;
}

Colors TextBlock::GetTextColor() const
{
    return _textColor;
}
