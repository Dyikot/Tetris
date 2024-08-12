#pragma once

#include <stack>
#include <filesystem>
#include "../Scenes/Scene.h"

class Application
{
public:
	static constexpr int WindowWidth = 400;
	static constexpr int WindowHeight = 800;
protected:
	inline static Application* _current = nullptr;

	Scene* _currentScene = nullptr;
	Scene* _nextScene = nullptr;

	std::stack<Scene*> _savedScenes = std::stack<Scene*>();

	SDL_Window* _currentWindow = nullptr;

	SDL_Renderer* _renderer = nullptr;
public:
	static Application* const Current();

	Application() noexcept;

	virtual ~Application();

	virtual void Run() = 0;

	virtual void Shutdown() = 0;

	void SetNextScene(Scene* next) noexcept;

	void SaveCurrentScene() noexcept;

	void SetSavedSceneToNext() noexcept;

	SDL_Window* GetCurrentWindow();

	SDL_Renderer* GetRenderer() const;

	void SetWindowSize(size_t width, size_t height);
protected:
	void SwitchToNextScene() noexcept;
};