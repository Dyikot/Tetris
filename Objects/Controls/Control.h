#pragma once

#include <string>
#include "../Object.h"

class Control : public Object
{
protected:
	Coordinates _position;
	int _width;
	int _height;
public:
	Control(const Coordinates& position,
			int width,
			int height,
			Color background) noexcept;

	void SetWidth(int width) noexcept;

	void SetHeight(int height) noexcept;

	void SetPosition(const Coordinates& position) noexcept;

	int GetWight() const noexcept;

	int GetHeight() const noexcept;

	const Coordinates& GetPosition() const noexcept;

	bool IsInRange(const Coordinates& position) const noexcept;

	bool IsInRange(const int x, const int y) const noexcept;
};