#include "Object.h"
#include "../Application/Window.h"

Object::Object() noexcept:
	_renderer(Application::Current()->GetWindow()->Renderer)
{
}

void Object::SetRenderColor(const SDL_Color& color) const noexcept
{
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}
