#pragma once

#include <stack>
#include <filesystem>
#include <iostream>
#include "../Graphics/Colors.h"
#include "Application.h"

class Window
{
public:
	SDL_Window* const SDLWindow;
	SDL_Renderer* const Renderer;
protected:	
	Scene* _currentScene = nullptr;
	Scene* _nextScene = nullptr;
	std::stack<Scene*> _hiddenScenes;
	int _width;
	int _height;
	int _actualWidth;
	int _actualHeight;
public:
	Window(std::string_view title, 
		   const SDL_Point& position, 
		   int width, 
		   int height,
		   int actualWidth,
		   int actualHeight,
		   SDL_WindowFlags flags) noexcept;

	~Window();

	void Render();

	Scene* const CurrentScene() const noexcept;

	void SetNextScene(Scene* next) noexcept;

	void SetHiddenSceneToNext() noexcept;

	void SetWindowSize(int width, int height) noexcept;

	void SetActualWindowSize(int width, int height) noexcept;

	int Width() const noexcept;

	int Height() const noexcept;

	int ActualWidth() const noexcept;

	int ActualHeight() const noexcept;

	bool IsNextSceneSet() const noexcept;
protected:
	void SwitchToNextScene() noexcept;

	void SetCurrentSceneBackground() const noexcept;
};