#include "Scene.h"

void Scene::OnRender() const
{
	for(auto object : Objects)
	{
		object->OnRender();
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
	_currentAction = SceneAction::Show;
}

void Scene::Close()
{	
	_currentAction = SceneAction::Close;
	OnClose(EventArgs{ .Source = this });
}

void Scene::Hide()
{
	_currentAction = SceneAction::Hide;
	OnHide(EventArgs{ .Source = this });
}

SceneAction Scene::CurrentAction() const
{
	return _currentAction;
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