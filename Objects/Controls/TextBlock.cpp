#include "TextBlock.h"

TextBlock::TextBlock(const SDL_Point& position,
                     const SDL_Color& background,
                     std::string_view text,
                     const SDL_Color& fontColor,
                     int fontSize) noexcept:
    Control(position, /*width*/ 0, /*height*/ 0, background),
    _text(text),
    _fontColor(fontColor),
    _fontFamily(TTF_OpenFont("Resources/Fonts/CreteRound-Regular.ttf", fontSize)),
    _textTexture(GenerateTextureByText())
{
    UpdateSizeByTexture();
}

TextBlock::TextBlock(const SDL_Point& position,
                     std::string_view text, 
                     const SDL_Color& fontColor,
                     int fontSize) noexcept:
    TextBlock(position, /*background*/ Colors::Transparent, text, fontColor, fontSize)
{
    
}

TextBlock::TextBlock(const SDL_Point& position, 
                     std::string_view text, 
                     const Style& style) noexcept:
    TextBlock(position, style.Background, text, style.FontColor, style.FontSize)
{
    BackgroundOnHover = style.BackgroundOnHover;
}

TextBlock::~TextBlock()
{
    TTF_CloseFont(_fontFamily);
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

    // Backgroud
    SetRenderColor(_renderer, _background);
    SDL_RenderFillRect(_renderer, &textRectangle);

    // Text
    _textTexture.Render(_renderer, textRectangle);
}

void TextBlock::SetText(std::string_view text) noexcept
{
    _text = text;
    _textTexture = GenerateTextureByText();
    UpdateSizeByTexture();
}

void TextBlock::SetFontColor(const SDL_Color& fontColor) noexcept
{
    _fontColor = fontColor;
    _textTexture.SetColor(fontColor);
}

const std::string& TextBlock::GetText() const noexcept
{
    return _text;
}

const SDL_Color& TextBlock::GetFontColor() const noexcept
{
    return _fontColor;
}

SDL_Point TextBlock::GetRealPosition() const noexcept
{
    return { .x = _position.x - _width / 2, .y = _position.y - _height / 2 };
}

SDL_Texture* TextBlock::GenerateTextureByText() const noexcept
{
    auto surface = TTF_RenderText_Blended(_fontFamily, _text.c_str(), _fontColor);
    auto texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextBlock::UpdateSizeByTexture() noexcept
{
    auto [width, height] = _textTexture.QuerySize();
    _width = width;
    _height = height;
}
