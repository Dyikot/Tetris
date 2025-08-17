#include "SettingsMenu.h"
#include "../Application/Window.h"

SettingsMenu::SettingsMenu()
{
	_navigationButtons = { &_backButton, &_applyButton };
	Objects = { &_title, &_backButton,
				&_soundEffectsSlider, &_musicSlider,
				&_soundEffectTitle, &_musicTitle,
				&_resolutionTitle, &_resolutionContainer,
				&_applyButton };

	_title.SetText("Settings");

	MouseMove = std::bind_front(&SettingsMenu::OnMouseMove, this);
	MouseDown = std::bind_front(&SettingsMenu::OnMouseDown, this);
	KeyDown = std::bind_front(&SettingsMenu::OnKeyDown, this);
	Closed = std::bind_front(&SettingsMenu::OnClose, this);
	_applyButton.Click = std::bind_front(&SettingsMenu::OnApplyButtonClick, this);
	_backButton.Click = std::bind_front(&SettingsMenu::OnBackButtonClick, this);
	_musicSlider.ThumbMoved = std::bind_front(&SettingsMenu::OnMusicThumbMoved, this);
	_soundEffectsSlider.ThumbMoved = std::bind_front(&SettingsMenu::OnSoundEffectThumbMoved, this);
}

void SettingsMenu::OnClose(Renderable* sender, const EventArgs& e)
{
	_appSettings.WindowResolutionIndex = _resolutionContainer.GetCurrentItemIndex();
	_appSettings.SoundEffectVolume = _soundEffectsSlider.GetFilling();
	_appSettings.MusicVolume = _musicSlider.GetFilling();

	AppSettingsSerializer::Serialize(_appSettings);
}

void SettingsMenu::OnApplyButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	auto [width, height] = WindowResolutionMap.at(*_resolutionContainer.GetCurrentItem());
	_appSettings.WindowResolutionIndex = _resolutionContainer.GetCurrentItemIndex();

	Application::Current()->GetWindow()->SetActualWindowSize(width, height);
	return;
}

void SettingsMenu::OnBackButtonClick(Renderable * sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->GetWindow()->SetHiddenSceneToNext();
	Close();
}

void SettingsMenu::OnMusicThumbMoved(Renderable* sender, const ThumbMovedEventArgs& e)
{
	_audioManager->SetMusicVolume(e.Filling);
}

void SettingsMenu::OnSoundEffectThumbMoved(Renderable* sender, const ThumbMovedEventArgs& e)
{
	_audioManager->SetSoundEffectsVolume(e.Filling);
}

void SettingsMenu::OnMouseDown(Renderable* sender, const SDL_MouseButtonEvent& e)
{	
	_resolutionContainer.OnMouseDown(e);

	for(auto slider : _sliders)
	{
		if(slider->IsMouseOver(e))
		{
			slider->MoveThumbTo(e.x);
			return;
		}
	}
}

void SettingsMenu::OnMouseMove(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	_resolutionContainer.OnMouseMove(e);

	for(auto slider : _sliders)
	{
		if(SDL_GetMouseState(0, 0) & SDL_BUTTON_LMASK &&
			slider->IsMouseOver(e))
		{
			slider->MoveThumbTo(e.x);
			return;
		}
	}	
}

void SettingsMenu::OnKeyDown(Renderable* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			Application::Current()->GetWindow()->SetHiddenSceneToNext();
			Close();
			break;
		}
	}
}