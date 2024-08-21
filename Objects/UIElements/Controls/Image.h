#pragma once

#include "Control.h"
#include "../../../Style/Texture.h"

class Image: public Control
{
protected:
	Texture* _texture = nullptr;
public:
	Image(const SDL_Point& position,
		  int width,
		  int height,
		  const SDL_Color& background,
		  Texture* texture) noexcept;

	void Show() const override;

	void SetTexture(Texture* texture);

	Texture* GetTexture() const;
};

