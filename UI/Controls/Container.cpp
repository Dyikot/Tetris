#include "Container.h"


Container::Container(SDL_Point position,
					 int width,
					 int height,
					 SDL_Color background,
					 const std::vector<std::string>& items,
					 size_t currentItemIndex) noexcept:
	Control(position, width, height, background),
	Items(items),
	_currentItemIndex(IsIndexInRange(currentItemIndex) ? currentItemIndex : 0)
{
	auto currentItem = GetCurrentItem();
	_textBlock.SetText(currentItem == nullptr ? "" : *currentItem);

	using namespace std::placeholders;

	_leftButton.Click = std::bind_front(&Container::OnLeftButtonClick, this);
	_rightButton.Click = std::bind_front(&Container::OnRightButtonClick, this);
	MouseMove = std::bind_front(&Container::OnHover, this);
	MouseDown = std::bind_front(&Container::OnClick, this);
}

Container::Container(SDL_Point position,
					 const Style& style,
					 const std::vector<std::string>& items, 
					 size_t currentItemIndex) noexcept:
	Container(position, style.Width, style.Height, style.Background, items, currentItemIndex)
{
	BackgroundOnHover = style.BackgroundOnHover;
}

void Container::Render(SDL_Renderer* renderer) const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	// Backgroud
	SetRenderColor(renderer, _background);
	SDL_RenderFillRect(renderer, &rectangle);

	_leftButton.Render(renderer);
	_rightButton.Render(renderer);
	_textBlock.Render(renderer);
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

void Container::OnHover(Renderable* sender, const SDL_MouseButtonEvent& e)
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

void Container::OnClick(Renderable* sender, const SDL_MouseButtonEvent& e)
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

void Container::OnLeftButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	MoveCurrentItemLeft();
}

void Container::OnRightButtonClick(Renderable * sender, const SDL_MouseButtonEvent& e)
{
	MoveCurrentItemRight();
}
