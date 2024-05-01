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
    SDL_Rect text =
    {
        .x = _position.x,
        .y = _position.y,
        .w = _width,
        .h = _height
    };

    SDL_RenderCopy(_renderer, _textTexture, NULL, &text);
}

const std::string& TextBlock::GetText() const
{
    return _text;
}

Colors TextBlock::GetTextColor() const
{
    return _textColor;
}
