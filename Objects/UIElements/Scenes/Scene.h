#pragma once

#include <vector>

#include "IScene.h"
#include "../UIElement.h"
#include "../../Events/HoldKeyEvent.h"

class Scene: public UIElement, public IScene
{
public:
	using QuitEventHandler = std::function<void(Object* sender, const SDL_QuitEvent&)>;

	using EventHandler = std::function<void(Object* sender, const EventArgs&)>;

	QuitEventHandler Quit;

	EventHandler Hidden;

	EventHandler Closed;

	std::vector<Object*> Objects;
protected:
	SceneVisibility _visibility = SceneVisibility::Visible;
public:
	virtual ~Scene() = default;

	void Show() const override;

	void HandleEvent(const SDL_Event& e) override;

	void Close() override;

	void Hide() override;

	void SetVisibility(SceneVisibility visibility) override;
	
	SceneVisibility GetVisibility() const override;
protected:
	virtual void OnQuit(const SDL_QuitEvent& e);

	virtual void OnHide(const EventArgs& e);

	virtual void OnClose(const EventArgs& e);
};

