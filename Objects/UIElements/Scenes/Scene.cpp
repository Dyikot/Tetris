#include "Scene.h"

Scene::Scene()
{

}

void Scene::Show() const
{
	for(auto object : Objects)
	{
		object->Show();
	}
}

void Scene::HandleEvent(const SDL_Event & e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			OnQuit(e.quit);
			break;

		case SDL_KEYDOWN:
			OnKeyDown(e.key);
			break;

		case SDL_KEYHOLD:
			OnKeyHold(e.key);
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(e.button);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e.button);
			break;

		default:
			break;
	}
}

void Scene::Close()
{
	OnClose(EventArgs{ .Source = this });

	if(!Application::Current()->IsNextSceneSet())
	{
		OnQuit({ .type = SDL_QUIT, .timestamp = SDL_GetTicks() });
	}
}

void Scene::Hide()
{
	OnHide(EventArgs{ .Source = this });
	Application::Current()->HideCurrentScene();
}

void Scene::OnQuit(const SDL_QuitEvent& e)
{
	if(Quit)
	{
		Quit(this, e);
	}

	Application::Current()->Shutdown();
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
