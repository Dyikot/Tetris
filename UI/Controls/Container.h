#pragma once

#include <vector>
#include "TextBlock.h"
#include "Image.h"
#include "Button.h"

struct CurrentItemEventArgs
{
	size_t ItemIndex;
	const std::string* CurrentItem;
};

class Container: public Control
{
public:
	using CurrentItemChangedEventHanler = std::function<void(Renderable*, const CurrentItemEventArgs&)>;

	CurrentItemChangedEventHanler CurrentItemChanged;
	const std::vector<std::string> Items;
protected:
	const Style ButtonStyle =
	{
		.Width = static_cast<int>(_height * 0.75),
		.Height = _height,
		.Background = Colors::Transparent
	};

	const Style ImageStyle =
	{
		.Width = static_cast<int>(_height * 0.75),
		.Height = _height,
		.Background = Colors::Green,
		.BackgroundOnHover = Colors::Lightgreen
	};

	const Style TextBlockStyle =
	{
		.FontSize = 36,
		.Background = _background,
		.FontColor = Colors::Whitesmoke
	};
	
	Button* _hoverButton = nullptr;

	Button _leftButton = 
	{
		_position,
		ButtonStyle,
		new Image
		{
			_position,
			"Resources/Textures/left.png",
			ImageStyle
		}
	};

	TextBlock _textBlock =
	{
		SDL_Point
		{
			.x = _position.x + _width / 2,
			.y = _position.y + _height / 2
		},
		"",
		TextBlockStyle
	};

	const SDL_Point RightButtonPosition =
	{
		.x = _position.x + _width - ButtonStyle.Width,
		.y = _position.y
	};
	Button _rightButton =
	{
		RightButtonPosition,
		ButtonStyle,
		new Image
		{
			RightButtonPosition,
			"Resources/Textures/right.png",
			ImageStyle
		}
	};

	size_t _currentItemIndex;
	const std::vector<Button*> _buttons = { &_rightButton, &_leftButton };
public:
	Container(SDL_Point position,
			  int width,
			  int height,
			  SDL_Color background,
			  const std::vector<std::string>& items = {},
			  size_t currentItemIndex = 0) noexcept;
	Container(SDL_Point position, 
			  const Style& style,
			  const std::vector<std::string>& items = {},
			  size_t currentItemIndex = 0) noexcept;
	virtual ~Container() = default;

	void Render(SDL_Renderer* renderer) const override;

	void MoveCurrentItemRight() noexcept;
	void MoveCurrentItemLeft() noexcept;
	void MoveCurrentItemAt(size_t index) noexcept;

	const std::string* GetCurrentItem() const;
	size_t GetCurrentItemIndex() const;

	const Button& GetRightButton() const noexcept;
	const Button& GetLeftButton() const noexcept;
protected:
	virtual void OnCurrentItemChanged(const CurrentItemEventArgs& e) noexcept;
private:
	void OnHover(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnLeftButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnRightButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	bool IsIndexInRange(size_t index) const noexcept;
};

