#pragma once

#include "Tetromino.h"
#include "../../Tools/Actions/Action.h"

class ActiveTetromino: public Tetromino
{
public:
	static constexpr Color PlaceHolderColor = Color::Grey;

	Tetromino PlaceHolder;

	Action Movement = Action(/*period*/ std::chrono::milliseconds(700));
public:
	ActiveTetromino(TetrominoType type, const std::array<Cell, 4>& cells) noexcept;

	ActiveTetromino(const Tetromino& other);

	void UpdatePlaceHolder();

	Tetromino& operator=(const Tetromino& other) noexcept;
protected:
	void OnActiveTetrominoActionCompleted(Action* sender, const ActionEventArgs& e);
private:
	void BindMovement();
};