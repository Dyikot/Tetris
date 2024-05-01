#pragma once

#include "Scene.h"
#include "../Application/Application.h"

class SettingsMenu: public Scene
{
public:
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
};