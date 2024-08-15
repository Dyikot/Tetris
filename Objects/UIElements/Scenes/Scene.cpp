#include "Scene.h"

Scene::Scene()
{

}

void Scene::Show() const
{
	for(auto control : Objects)
	{
		control->Show();
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

void Scene::OnQuit(const SDL_QuitEvent& e)
{
	Application::Current()->Shutdown();

	if(Quit)
	{
		Quit(this, e);
	}
}
