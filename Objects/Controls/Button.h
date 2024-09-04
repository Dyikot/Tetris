#pragma once

#include <vector>
#include "Control.h"
#include "../../BasicStructs/Style.h"
#include "../../Audio/GameAudioManager.h"
#include "../../Application/Application.h"

class Button: public Control
{
public:
	MouseEventHandler Click;
	SDL_Color BorderColor;
protected:
	const SoundEffect& ClickSoundEffect = Application::Current()
		->AudioManager<GameAudioManager>()->SoundEffects.ButtonClick;
	Control* _content;
public:
	Button(const SDL_Point& position,
		   int width,
		   int height,
		   const SDL_Color& background,
		   SDL_Color borderColor,
		   Control* content = nullptr) noexcept;

	Button(const SDL_Point& position,
		   const Style& style,
		   Control* content = nullptr) noexcept;

	virtual ~Button() noexcept;

	void OnRender() const override;

	void SetContent(Control* content) noexcept;

	virtual void OnClick(const SDL_MouseButtonEvent& e);

	Control* const GetContent() const;
};