#pragma once

#include <vector>
#include "TextBlock.h"
#include "Image.h"
#include "Buttons/Button.h"

struct CurrentItemEventArgs
{
	size_t ItemIndex;
	const std::string* CurrentItem;
};

class Container: public Control
{
public:
	using CurrentItemChangedEventHanler = std::function<void(Object*, const CurrentItemEventArgs&)>;

	CurrentItemChangedEventHanler CurrentItemChanged;

	const std::vector<std::string> const Items;
protected:
	Button* _hoverButton = nullptr;

	const int ButtonWidth = _height * 0.75;
	const int ButtonHeight = _height;

	// Left button

	const SDL_Point LeftButtonPosition = _position;

	Texture _leftTexture = Texture(_renderer, "Resources/Textures/left.png");

	Image _leftButtonImage = Image(LeftButtonPosition,
								   ButtonWidth,
								   ButtonHeight,
								   Color::Green,
								   &_leftTexture);	

	Button _leftButton = Button(LeftButtonPosition,
								ButtonWidth,
								ButtonHeight,
								DefaultBackgroundColor,
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
									Color::Green,
									&_rightTexture);

	Button _rightButton = Button(RightButtonPosition,
								 ButtonWidth,
								 ButtonHeight,
								 DefaultBackgroundColor,
								 /*border*/ Color::None,
								 &_rightButtonImage);

	size_t _currentItemIndex;

	const std::vector<Button*> _buttons = { &_rightButton, &_leftButton };
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

	const Button& GetRightButton() const noexcept;

	const Button& GetLeftButton() const noexcept;
protected:
	void OnCurrentItemChanged(const CurrentItemEventArgs& e) noexcept;
private:
	bool IsIndexInRange(size_t index) const noexcept;

	void OnHover(Object* sender, const SDL_MouseButtonEvent& e);

	void OnClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnLeftButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnRightButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};

