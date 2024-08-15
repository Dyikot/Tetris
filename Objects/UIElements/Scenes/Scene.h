#pragma once

#include <vector>
#include <functional>

#include "IScene.h"
#include "../UIElement.h"
#include "../../Events/HoldKeyEvent.h"

class Scene: public UIElement, public IScene
{
public:
	using QuitEventHandler = std::function<void(Object* sender, const SDL_QuitEvent&)>;

	QuitEventHandler Quit;

	std::vector<Object*> Objects;
public:
	Scene();

	void Show() const override;

	void HandleEvent(const SDL_Event& e) override;

	virtual void OnQuit(const SDL_QuitEvent& e);
};

