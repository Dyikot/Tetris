#include "Container.h"


Container::Container(const SDL_Point& position,
					 int width,
					 int height,
					 Color background,
					 const std::vector<std::string>& items,
					 size_t currentItemIndex) noexcept:
	Control(position, width, height, background),
	Items(items),
	_currentItemIndex(IsIndexInRange(currentItemIndex) ? currentItemIndex : 0)
{
	auto currentItem = GetCurrentItem();
	_textBlock.SetText(currentItem == nullptr ? "" : *currentItem);
}

void Container::Show() const noexcept
{
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
		OnCurrentItemChanged();
	}
}

void Container::OnMouseDown(const SDL_Event& e)
{
	if(_leftButton.GetContent()->IsInRange(e.button.x, e.button.y))
	{
		MoveCurrentItemLeft();
	}
	else if(_rightButton.GetContent()->IsInRange(e.button.x, e.button.y))
	{
		MoveCurrentItemRight();
	}
}

bool Container::IsIndexInRange(size_t index) const noexcept
{
	return index < Items.size();
}

void Container::OnCurrentItemChanged() noexcept
{
	_textBlock.SetText(Items[_currentItemIndex]);
}
