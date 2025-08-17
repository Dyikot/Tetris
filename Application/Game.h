#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Application.h"
#include "../Scenes/StartMenu.h"
#include "../Serialization/AppSettingsSerializer.h"
#include "../Audio/GameAudioManager.h"

class Game : public Application
{
public:
	Game();
};