#pragma once

#include "HoldKeyEvent.h"

static HoldKeyEvent HoldKey;

static bool PollEvent(SDL_Event* e) noexcept
{
	if(SDL_PollEvent(e))
	{
		switch(e->type)
		{
			case SDL_KEYDOWN:
				if(e->key.repeat)
				{
					if(HoldKey.IsHold())
					{
						e->key = HoldKey;
						return true;
					}

					return false;
				}

			case SDL_KEYUP:
				HoldKey = e->key;
				break;

			default:
				break;
		}

		return true;
	}
	else if(HoldKey.IsHold())
	{
		e->key = HoldKey;
		return true;
	}

	return false;
}