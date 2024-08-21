#include "TextBlock.h"

TextBlock::TextBlock(const SDL_Point& position,
                     const SDL_Color& background, 
                     const std::string& text, 
                     const SDL_Color& fontColor,
                     int fontSize) noexcept:
    TextBlock(position, NULL, NULL, background, text, fontColor, fontSize)
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

void TextBlock::SetText(const std::string& text) noexcept
{
    _text = text;

    SDL_DestroyTexture(_textTexture);
    _textTexture = GenerateTextureByText();
    SDL_QueryTexture(_textTexture, NULL, NULL, &_width, &_height);
}

void TextBlock::SetFontColor(const SDL_Color& fontColor) noexcept
{
    _fontColor = fontColor;
}

const std::string& TextBlock::GetText() const noexcept
{
    return _text;
}

SDL_Color TextBlock::GetTextColor() const noexcept
{
    return _fontColor;
}

SDL_Point TextBlock::GetRealPosition() const
{
    return { .x = _position.x - _width / 2, .y = _position.y - _height / 2 };
}

TextBlock::TextBlock(const SDL_Point& position,
                     int width, 
                     int height,
                     const SDL_Color& background,
                     const std::string& text,
                     const SDL_Color& fontColor,
                     int fontSize) noexcept:
    Control(position, width, height, background),
    _text(text),
    _fontColor(fontColor),
    _font(TTF_OpenFont("Resources/Fonts/CreteRound-Regular.ttf", fontSize)),
    _textTexture(GenerateTextureByText())
{

}

SDL_Texture* TextBlock::GenerateTextureByText() const noexcept
{
    auto surface = TTF_RenderText_Blended(_font, _text.c_str(), _fontColor);
    auto texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
