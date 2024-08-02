#pragma once

#include <algorithm>
#include <vector>
#include <iostream>


#include "Application.h"
#include "..\Scenes\StartMenu.h"
#include "..\Events\HoldKeyEvent.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Game : public Application
{
private:
	HoldKeyEvent _holdKeyEvent;
	bool _isGameRunning = false;
public:
	Game();

	~Game();

	void Run() override;

	void Shutdown() override;

	bool PollEvents(SDL_Event* e);
};