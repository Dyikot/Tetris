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

	virtual void SetWidth(int width) noexcept;

	virtual void SetHeight(int height) noexcept;

	virtual void SetPosition(const SDL_Point& position) noexcept;

	virtual int GetWight() const noexcept;

	virtual int GetHeight() const noexcept;

	virtual const SDL_Point& GetPosition() const noexcept;

	virtual bool IsInRange(const SDL_Point& position) const noexcept;

	virtual bool IsInRange(const int x, const int y) const noexcept;
};