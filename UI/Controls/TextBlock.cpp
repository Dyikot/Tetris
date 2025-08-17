#include "TextBlock.h"
#include "../../Application/Application.h"

static SDL_Renderer* GetRenderer()
{
    return Application::Current()->GetWindow()->Renderer;
}

TextBlock::TextBlock(SDL_Point position,
                     SDL_Color background,
                     std::string_view text,
                     SDL_Color fontColor,
                     int fontSize) noexcept:
    Control(position, /*width*/ 0, /*height*/ 0, background),
    _text(text),
    _fontColor(fontColor),
    _fontFamily(TTF_OpenFont("Resources/Fonts/CreteRound-Regular.ttf", fontSize)),
    _textTexture(GetRenderer(), CreateTextTexture())
{
    SetSize(_textTexture.Size());
}

TextBlock::TextBlock(SDL_Point position,
                     std::string_view text, 
                     SDL_Color fontColor,
                     int fontSize) noexcept:
    TextBlock(position, Colors::Transparent, text, fontColor, fontSize)
{}

TextBlock::TextBlock(SDL_Point position, 
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

void TextBlock::SetText(std::string_view text) noexcept
{
    _text = text;
    _textTexture = CreateTextTexture();
    SetSize(_textTexture.Size());
}

void TextBlock::SetFontColor(SDL_Color fontColor) noexcept
{
    _fontColor = fontColor;
    _textTexture.SetColor(fontColor);
}

const std::string& TextBlock::GetText() const noexcept
{
    return _text;
}

SDL_Color TextBlock::GetFontColor() const noexcept
{
    return _fontColor;
}

SDL_Point TextBlock::GetRealPosition() const noexcept
{
    return { .x = _position.x - _width / 2, .y = _position.y - _height / 2 };
}

void TextBlock::Render(SDL_Renderer* renderer) const
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
    SetRenderColor(renderer, _background);
    SDL_RenderFillRect(renderer, &textRectangle);

    // Text
    _textTexture.Render(renderer, textRectangle);
}

SDL_Texture* TextBlock::CreateTextTexture() const noexcept
{
    auto surface = TTF_RenderText_Blended(_fontFamily, _text.c_str(), _fontColor);
    auto texture = SDL_CreateTextureFromSurface(GetRenderer(), surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextBlock::SetSize(std::pair<int, int> size) noexcept
{
    _width = size.first;
    _height = size.second;
}
