#include "Scene.h"
#include "../Application/Application.h"

void Scene::Render(SDL_Renderer* renderer) const
{
	for(auto object : Objects)
	{
		object->Render(renderer);
	}
}

void Scene::HandleEvent(const SDL_Event & e)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
		{
			OnKeyDown(e.key);
			break;
		}

		case SDL_KEYHOLD:
		{
			OnKeyHold(e.key);
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			OnMouseDown(e.button);
			break;
		}

		case SDL_MOUSEMOTION:
		{
			OnMouseMove(e.button);
			break;
		}
	}
}

void Scene::Show()
{
	_state = SceneState::Visible;
}

void Scene::Close()
{	
	_state = SceneState::Closed;
	OnClose(EventArgs());
}

void Scene::Hide()
{
	_state = SceneState::Hidden;
	OnHide(EventArgs());
}

SceneState Scene::CurrentAction() const
{
	return _state;
}

int Scene::GetWidth() const
{
	return Application::Current()->GetWindow()->Width();
}

int Scene::GetHeight() const
{
	return Application::Current()->GetWindow()->Height();
}

void Scene::OnHide(const EventArgs& e)
{
	if(Hidden)
	{
		Hidden(this, e);
	}
}

void Scene::OnClose(const EventArgs & e)
{
	if(Closed)
	{
		Closed(this, e);
	}
}