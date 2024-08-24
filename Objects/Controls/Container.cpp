#include "Container.h"


Container::Container(const SDL_Point& position,
					 int width,
					 int height,
					 const SDL_Color& background,
					 const std::vector<std::string>& items,
					 size_t currentItemIndex) noexcept:
	Control(position, width, height, background),
	Items(items),
	_currentItemIndex(IsIndexInRange(currentItemIndex) ? currentItemIndex : 0)
{
	auto currentItem = GetCurrentItem();
	_textBlock.SetText(currentItem == nullptr ? "" : *currentItem);

	using namespace std::placeholders;

	_leftButton.Click = std::bind(&Container::OnLeftButtonClick, this, _1, _2);
	_rightButton.Click = std::bind(&Container::OnRightButtonClick, this, _1, _2);
	MouseMove = std::bind(&Container::OnHover, this, _1, _2);
	MouseDown = std::bind(&Container::OnClick, this, _1, _2);
}

Container::Container(const SDL_Point& position,
					 const Style& style,
					 const std::vector<std::string>& items, 
					 size_t currentItemIndex) noexcept:
	Container(position, style.Width, style.Height, style.Background, items, currentItemIndex)
{
	BackgroundOnHover = style.BackgroundOnHover;
}

void Container::Show() const noexcept
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	// Backgroud
	SetRenderColor(_renderer, _background);
	SDL_RenderFillRect(_renderer, &rectangle);

	_leftButton.Show();
	_rightButton.Show();
	_textBlock.Show();
}

const std::string* Container::GetCurrentItem() const
{
	return IsIndexInRange(_currentItemIndex) ? &Items[_currentItemIndex] : nullptr;
}

size_t Container::GetCurrentItemIndex() const
{
	return _currentItemIndex;
}

void Container::MoveCurrentItemRight() noexcept
{
	MoveCurrentItemAt(_currentItemIndex + 1);
}

void Container::MoveCurrentItemLeft() noexcept
{
	MoveCurrentItemAt(_currentItemIndex - 1);
}

void Container::MoveCurrentItemAt(size_t index) noexcept
{
	if(IsIndexInRange(index))
	{
		_currentItemIndex = index;
		OnCurrentItemChanged({.ItemIndex = index, .CurrentItem = &Items.at(index)});
	}
}

const Button& Container::GetRightButton() const noexcept
{
	return _rightButton;
}

const Button& Container::GetLeftButton() const noexcept
{
	return _leftButton;
}

void Container::OnHover(Object* sender, const SDL_MouseButtonEvent& e)
{
	for(auto button : _buttons)
	{
		if(button->GetContent()->IsMouseOver(e))
		{
			button->GetContent()->OnMouseEnter(e);
			_hoverButton = button;
			return;
		}
		else
		{
			button->GetContent()->OnMouseLeave(e);
		}
	}

	_hoverButton = nullptr;
}

void Container::OnClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	if(_hoverButton != nullptr)
	{
		_hoverButton->OnClick(e);
	}
}

bool Container::IsIndexInRange(size_t index) const noexcept
{
	return index < Items.size();
}

void Container::OnCurrentItemChanged(const CurrentItemEventArgs& e) noexcept
{
	if(CurrentItemChanged)
	{
		CurrentItemChanged(this, e);
	}

	_textBlock.SetText(Items[_currentItemIndex]);
}

void Container::OnLeftButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	MoveCurrentItemLeft();
}

void Container::OnRightButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	MoveCurrentItemRight();
}
