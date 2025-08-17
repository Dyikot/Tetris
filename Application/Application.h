#pragma once

#include <functional>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "../Audio/AudioManager.h"
#include "../Base/KeyHoldDetector.h"
#include "Window.h"

class Application
{
public:
	using QuitEventHandler = std::function<void(Application*, const SDL_QuitEvent&)>;

	QuitEventHandler Quit;
protected:
	Window* _window {};
	AudioManager* _audioManager {};
	KeyHoldDetector _keyHoldDetector;
	size_t _delay = 10;
	bool _isActive = true;
private:
	inline static Application* _current {};
public:
	Application() noexcept;
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	~Application() noexcept;

	static Application* Current() { return _current; }

	Window* GetWindow() const { return _window; }
	AudioManager* GetAudioManager() const { return _audioManager; }

	void Run();
	void Shutdown() noexcept;
protected:
	virtual void OnQuit(const SDL_QuitEvent& e);
private:
	bool PollEvent(SDL_Event* e) noexcept;
};
