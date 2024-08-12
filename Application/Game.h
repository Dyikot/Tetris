#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Application.h"
#include "../Scenes/MenuScenes/StartMenu.h"
#include "../Events/HoldKeyEvent.h"
#include "../Tools/Serialization/SettinsDataSerializer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

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