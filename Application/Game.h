#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Application.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "../Objects/UIElements/Scenes/MenuScenes/StartMenu.h"
#include "../Events/Events.h"
#include "../Tools/Serialization/SettinsDataSerializer.h"

class Game : public Application
{
public:
	static constexpr Uint32 Delay = 6;
private:
	bool _isRunning = false;
public:
	Game();

	~Game();

	void Run() override;

	void Shutdown() noexcept override;
private:
	void InitSDL() const;
};