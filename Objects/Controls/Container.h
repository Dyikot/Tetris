#pragma once

#include <vector>
#include "TextBlock.h"
#include "Image.h"
#include "Buttons/Button.h"

class Container: public Control
{
public:
	const std::vector<std::string> const Items;
protected:
	const int ButtonWidth = _height * 0.75;
	const int ButtonHeight = _height;

	// Left button

	const SDL_Point LeftButtonPosition = _position;

	Texture _leftTexture = Texture(_renderer, "Resources/Textures/left.png");

	Image _leftButtonImage = Image(LeftButtonPosition,
								   ButtonWidth,
								   ButtonHeight,
								   Color::White,
								   &_leftTexture);	

	Button _leftButton = Button(LeftButtonPosition,
								ButtonWidth,
								ButtonHeight,
								_backgroud,
								/*border*/ Color::None,
								&_leftButtonImage);

	// Text block

	const SDL_Point TextBlockPosition =
	{
		.x = _position.x + _width / 2,
		.y = _position.y + _height / 2
	};

	TextBlock _textBlock = TextBlock(TextBlockPosition,
									 _backgroud,
									 "",
									 /*textColor*/ Color::Whitesmoke,
									 /*textSize*/ 36);

	// Right button

	const SDL_Point RightButtonPosition =
	{
		.x = _position.x + _width - ButtonWidth,
		.y = _position.y
	};

	Texture _rightTexture = Texture(_renderer, "Resources/Textures/right.png");

	Image _rightButtonImage = Image(RightButtonPosition,
									ButtonWidth,
									ButtonHeight,
									Color::White,
									&_rightTexture);

	Button _rightButton = Button(RightButtonPosition,
								 ButtonWidth,
								 ButtonHeight,
								 _backgroud,
								 /*border*/ Color::None,
								 &_rightButtonImage);

	size_t _currentItemIndex;
public:
	Container(const SDL_Point& position,
			  int width,
			  int height,
			  Color background,
			  const std::vector<std::string>& items = {},
			  size_t currentItemIndex = 0) noexcept;

	void Show() const noexcept override;

	const std::string* GetCurrentItem() const;

	size_t GetCurrentItemIndex() const;

	void MoveCurrentItemRight() noexcept;

	void MoveCurrentItemLeft() noexcept;

	void MoveCurrentItemAt(size_t index) noexcept;

	void OnMouseDown(const SDL_Event& e);
private:
	bool IsIndexInRange(size_t index) const noexcept;

	void OnCurrentItemChanged() noexcept;
};

