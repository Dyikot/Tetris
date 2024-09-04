#pragma once

#include "Control.h"
#include"../../Graphics/Texture.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
protected:
	TTF_Font* _fontFamily;
	SDL_Color _fontColor;
	std::string _text;
	Texture _textTexture;
public:
	TextBlock(const SDL_Point& position,
			  const SDL_Color& background,
			  std::string_view text,
			  const SDL_Color& fontColor,
			  int fontSize) noexcept;

	TextBlock(const SDL_Point& position,
			  std::string_view text, 
			  const SDL_Color& fontColor,
			  int fontSize) noexcept;

	TextBlock(const SDL_Point& position, std::string_view text, const Style& style) noexcept;

	~TextBlock();

	void OnRender() const noexcept override;

	void SetText(std::string_view text) noexcept;

	void SetFontColor(const SDL_Color& fontColor) noexcept;

	const std::string& GetText() const noexcept;

	const SDL_Color& GetFontColor() const noexcept;

	SDL_Point GetRealPosition() const noexcept;
private:
	SDL_Texture* GenerateTextureByText() const noexcept;

	void UpdateSizeByTexture() noexcept;
};
