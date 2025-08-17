#pragma once

#include <vector>
#include "../UI/UIElement.h"
#include "../Base/KeyHoldDetector.h"
#include "../Base/Colors.h"

struct EventArgs {};

enum class SceneState
{
	Visible, Hidden, Closed
};

class Scene: public UIElement
{
public:
	static constexpr int Scale = 4;
	using EventHandler = std::function<void(Renderable*, const EventArgs&)>;

	EventHandler Hidden;
	EventHandler Closed;
	std::vector<Renderable*> Objects;
	SDL_Color Background = Colors::Black;
protected:
	SceneState _state = SceneState::Visible;
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Process() = 0;

	void Render(SDL_Renderer* renderer) const override;
	void HandleEvent(const SDL_Event& e);
	void Show();
	void Close();
	void Hide();
	SceneState CurrentAction() const;
protected:
	int GetWidth() const;
	int GetHeight() const;

	virtual void OnHide(const EventArgs& e);
	virtual void OnClose(const EventArgs& e);
};