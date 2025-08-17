#pragma once

#include <vector>
#include "../Control.h"
#include "../../Audio/GameAudioManager.h"
#include "../../Application/Application.h"

class Button: public Control
{
public:
	MouseEventHandler Click;
	SDL_Color BorderColor;
protected:
	const SoundEffect& ClickSoundEffect = Application::Current()
		->GetAudioManager()->GetSoundEffect("ButtonClick");

	Control* _content;
public:
	Button(SDL_Point position,
		   int width,
		   int height,
		   SDL_Color background,
		   SDL_Color borderColor,
		   Control* content = nullptr) noexcept;
	Button(SDL_Point position,
		   const Style& style,
		   Control* content = nullptr) noexcept;
	virtual ~Button() noexcept;


	void SetContent(Control* content) noexcept;
	Control* GetContent() const;

	void Render(SDL_Renderer* renderer) const override;
	virtual void OnClick(const SDL_MouseButtonEvent& e);
};