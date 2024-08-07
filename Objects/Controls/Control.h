#pragma once

#include <string>
#include "../Object.h"

class Control : public Object
{
protected:
	SDL_Point _position;
	int _width;
	int _height;
public:
	Control(const SDL_Point& position,
			int width,
			int height,
			Color background) noexcept;

	void SetWidth(int width) noexcept;

	void SetHeight(int height) noexcept;

	void SetPosition(const SDL_Point& position) noexcept;

	int GetWight() const noexcept;

	int GetHeight() const noexcept;

	const SDL_Point& GetPosition() const noexcept;

	bool IsInRange(const SDL_Point& position) const noexcept;

	bool IsInRange(const int x, const int y) const noexcept;
};