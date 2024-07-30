#pragma once

#include <string>
#include "..\Object.h"

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
			Colors background
	):
		_position(position),
		_width(width),
		_height(height),
		Object(background){}

	void SetWidth(int width);

	void SetHeight(int height);

	void SetPosition(const Coordinates& position);

	int GetWight() const;

	int GetHeight() const;

	const Coordinates& GetPosition() const;

	bool IsInRange(const Coordinates& position) const;
};