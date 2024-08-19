#include "TextBlock.h"

void TextBlock::SetText(const std::string& text) noexcept
{
    _text = text;

    SDL_DestroyTexture(_textTexture);
    _textTexture = GenerateTextureByText();
    SDL_QueryTexture(_textTexture, NULL, NULL, &_width, &_height);
}

void TextBlock::SetTextColor(Color textColor) noexcept
{
    _textColor = textColor;
}

TextBlock::TextBlock(const SDL_Point& position,
                     Color background, 
                     const std::string& text, 
                     Color textColor, int textSize) noexcept:
    TextBlock(position, NULL, NULL, background, text, textColor, textSize)
{
    SDL_QueryTexture(_textTexture, NULL, NULL, &_width, &_height);
}

TextBlock::~TextBlock()
{
    TTF_CloseFont(_font);
    SDL_DestroyTexture(_textTexture);
}


void TextBlock::Show() const noexcept
{
    const auto [x, y] = GetRealPosition();

    SDL_Rect textRectangle =
    {
        .x = x,
        .y = y,
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

SDL_Point TextBlock::GetRealPosition() const
{
    return { .x = _position.x - _width / 2, .y = _position.y - _height / 2 };
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
    _font(TTF_OpenFont("Resources/Fonts/CreteRound-Regular.ttf", textSize)),
    _textTexture(GenerateTextureByText())
{

}

SDL_Texture* TextBlock::GenerateTextureByText() const noexcept
{
    auto surface = TTF_RenderText_Blended(_font, _text.c_str(), Colors::ToSDL_Color(_textColor));
    auto texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
