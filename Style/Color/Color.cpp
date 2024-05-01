#include "Color.h"

void Color::SetRenderColor(SDL_Renderer* renderer, Colors color)
{
	switch(color)
	{
		case Colors::None:
			break;
		case Colors::Black:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			break;
		case Colors::Green:
			SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
			break;
		case Colors::Blue:
			SDL_SetRenderDrawColor(renderer, 123, 104, 238, 255);
			break;
		case Colors::Red:
			SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
			break;
		case Colors::Cyan:
			SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
			break;
		case Colors::Yellow:
			SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
			break;
		case Colors::Magenta:
			SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
			break;
		case Colors::White:
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			break;
		case Colors::Grey:
			SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
			break;
		default:
			break;
	}
}

SDL_Color Color::ToSDL_Color(Colors color)
{
	switch(color)
	{
		case Colors::None:
			return SDL_Color();
		case Colors::Black:
			return SDL_Color(0, 0, 0);
		case Colors::Green:
			return SDL_Color(0, 128, 0);
		case Colors::Blue:
			return SDL_Color(123, 104, 238);
		case Colors::Red:
			return SDL_Color(128, 0, 0);
		case Colors::Cyan:
			return SDL_Color(0, 128, 128);
		case Colors::Yellow:
			return SDL_Color(128, 128, 0);
		case Colors::Magenta:
			return SDL_Color(128, 0, 128);
		case Colors::White:
			return SDL_Color(255, 255, 255);
		case Colors::Grey:
			return SDL_Color(128, 128, 128);
		default:
			return SDL_Color();
	}
}
