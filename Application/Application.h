#pragma once

#include "../Scenes/Scene.h"

class Application
{
public:
	const int WindowWidth = 400;
	const int WindowHeight = 800;
protected:
	// Текущее приложение
	inline static Application* _current = nullptr;

	Scene* _currentScene = nullptr;

	Scene* _nextScene = nullptr;

	Scene* _savedScene = nullptr;

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

	void UploadSavedSceneToNext() noexcept;

	SDL_Window* GetCurrentWindow();

	SDL_Renderer* GetRenderer() const;
protected:
	void SwitchToNextScene() noexcept;
};