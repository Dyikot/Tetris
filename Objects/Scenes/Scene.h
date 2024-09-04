#pragma once

#include <vector>
#include "../../EventRegisters/KeyHoldRegister.h"
#include "../UIElement.h"
#include "../../Graphics/Colors.h"

struct EventArgs
{
	Object* Source;
};

enum class SceneAction
{
	Show,
	Hide,
	Close
};

class Scene: public UIElement
{
public:
	static constexpr int Scale = 4;
	using EventHandler = std::function<void(Object* sender, const EventArgs&)>;

	EventHandler Hidden;
	EventHandler Closed;
	std::vector<Object*> Objects;
	SDL_Color Background = Colors::Black;
protected:
	SceneAction _currentAction = SceneAction::Show;
public:
	virtual ~Scene() = default;

	void OnRender() const;

	virtual void Process() = 0;

	void HandleEvent(const SDL_Event& e);

	void Show();

	void Close();

	void Hide();

	SceneAction CurrentAction() const;
protected:
	virtual void OnHide(const EventArgs& e);

	virtual void OnClose(const EventArgs& e);
};