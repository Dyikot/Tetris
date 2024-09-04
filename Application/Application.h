#pragma once

#include <functional>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "../Objects/Scenes/Scene.h"
#include "../EventRegisters/KeyHoldRegister.h"
#include "../Audio/AudioManager.h"

class Window;

class Application
{
public:
	using QuitEventHandler = std::function<void(Application* sender, const SDL_QuitEvent&)>;

	QuitEventHandler Quit;
protected:
	Window* _window = nullptr;
	AudioManager* _audioManager = nullptr;
	KeyHoldRegister _keyHoldRegister;
	Uint32 _delay = 10;
	bool _isActive = true;
private:
	inline static Application* _current = nullptr;
public:
	static Application* const Current();

	Application() noexcept;

	~Application() noexcept;

	void Run();

	void Shutdown() noexcept;

	Window* const GetWindow() const;

	template<AudioManagerType AudioManagerType = AudioManager>
	AudioManagerType* const AudioManager() const;
protected:
	virtual void OnQuit(const SDL_QuitEvent& e);
private:
	bool PollEvent(SDL_Event* e) noexcept;
};

template<AudioManagerType AudioManagerType>
inline AudioManagerType* const Application::AudioManager() const
{
	return static_cast<AudioManagerType* const>(_audioManager);
}
