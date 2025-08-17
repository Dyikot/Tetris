#pragma once

#include "Tetromino.h"
#include "CellStorage.h"
#include "../Actions/Action.h"

class ActiveTetromino: public Tetromino
{
public:
	static constexpr SDL_Color PlaceholderColor = Colors::Grey;

	Tetromino Placeholder;
	Action Movement = Action(std::chrono::milliseconds(700));
	bool CanReselected = true;
	bool NeedsToFall = false;
public:
	ActiveTetromino(const Tetromino& other);
	virtual ~ActiveTetromino() = default;

	void Render(SDL_Renderer* renderer) const override;
	void UpdatePlaceholderPositionIn(const CellStorage& cellStorage);
	bool IsLocatedAtBottomOf(const CellStorage& cellStorage);

	Tetromino& operator=(const Tetromino& other) noexcept;
protected:
	virtual void OnActiveTetrominoActionCompleted(Action* sender, const ActionEventArgs& e);
};