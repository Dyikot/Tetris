#pragma once

#include "../Objects/Object.h"
#include "../Events/HoldKeyEvent.h"

using EventHandler = std::function<void(Object*, const SDL_Event& e)>; 