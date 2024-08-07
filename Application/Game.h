#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Application.h"
#include "../Scenes/MenuScenes/StartMenu.h"
#include "../Events/HoldKeyEvent.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

class Game : public Application
{
private:
	HoldKeyEvent _holdKeyEvent;	
	bool _isGameRunning = false;
public:
	Game();

	~Game();

	void Run() override;

	void Shutdown() noexcept override;

	bool PollEvents(SDL_Event* e) noexcept;
};