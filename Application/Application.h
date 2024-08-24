#pragma once

#include <stack>
#include <filesystem>
#include "../Objects/Scenes/IScene.h"
#include "../EventRegisters/KeyHoldRegister.h"

class Application
{
public:
	static constexpr int WindowWidth = 400;
	static constexpr int WindowHeight = 800;
protected:
	inline static Application* _current = nullptr;

	IScene* _currentScene = nullptr;
	IScene* _nextScene = nullptr;
	std::stack<IScene*> _hiddenScenes = std::stack<IScene*>();
	SDL_Window* _currentWindow = nullptr;
	SDL_Renderer* _renderer = nullptr;
	KeyHoldRegister _keyHoldRegister;
public:
	static Application* const Current();

	Application() noexcept;

	virtual ~Application();

	virtual void Run() = 0;

	virtual void Shutdown() = 0;

	void SetNextScene(IScene* next) noexcept;

	void SetHiddenSceneToNext() noexcept;

	void SetWindowSize(size_t width, size_t height) noexcept;

	SDL_Window* GetCurrentWindow() noexcept;

	SDL_Renderer* GetRenderer() const noexcept;

	bool IsNextSceneSet() const noexcept;	

	bool PollEvent(SDL_Event* e) noexcept;
protected:
	void SwitchToNextScene() noexcept;
};