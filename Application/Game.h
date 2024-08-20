#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Application.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "../Objects/UIElements/Scenes/MenuScenes/StartMenu.h"
#include "../Events/HoldKeyEvent.h"
#include "../Tools/Serialization/SettinsDataSerializer.h"

class Game : public Application
{
private:
	bool _isGameRunning = false;
	HoldKeyEvent _holdKeyEvent;
public:
	Game();

	~Game();

	void Run() override;

	void Shutdown() noexcept override;

	bool PollEvents(SDL_Event* e) noexcept;
};