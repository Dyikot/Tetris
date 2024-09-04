#include "SettingsMenu.h"

SettingsMenu::SettingsMenu()
{
	_navigationButtons = { &_backButton, &_applyButton };
	Objects = { &_title, &_backButton,
				&_soundEffectsSlider, &_musicSlider,
				&_soundEffectTitle, &_musicTitle,
				&_resolutionTitle, &_resolutionContainer,
				&_applyButton };

	_title.SetText("Settings");

	using namespace std::placeholders;

	MouseMove = std::bind(&SettingsMenu::OnMouseMove, this, _1, _2);
	MouseDown = std::bind(&SettingsMenu::OnMouseDown, this, _1, _2);
	KeyDown = std::bind(&SettingsMenu::OnKeyDown, this, _1, _2);
	Closed = std::bind(&SettingsMenu::OnClose, this, _1, _2);
	_applyButton.Click = std::bind(&SettingsMenu::OnApplyButtonClick, this, _1, _2);
	_backButton.Click = std::bind(&SettingsMenu::OnBackButtonClick, this, _1, _2);
	_musicSlider.ThumbMoved = std::bind(&SettingsMenu::OnMusicThumbMoved, this, _1, _2);
	_soundEffectsSlider.ThumbMoved = std::bind(&SettingsMenu::OnSoundEffectThumbMoved,
											   this, _1, _2);
}

void SettingsMenu::OnClose(Object* sender, const EventArgs& e)
{
	const auto& [width, height] = WindowResolutionMap.at(*_resolutionContainer.GetCurrentItem());

	_settingsData->WindowWidth = width;
	_settingsData->WindowHeight = height;
	_settingsData->ActiveResolutionIndex = _activeResolutionIndex;
	_settingsData->SoundEffectVolume = _soundEffectsSlider.GetFilling();
	_settingsData->MusicVolume = _musicSlider.GetFilling();

	_settingsDataSerializer.Serialize(_settingsData);
}

void SettingsMenu::OnApplyButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	auto [width, height] = WindowResolutionMap.at(*_resolutionContainer.GetCurrentItem());
	_activeResolutionIndex = _resolutionContainer.GetCurrentItemIndex();

	Application::Current()->GetWindow()->SetActualWindowSize(width, height);
	return;
}

void SettingsMenu::OnBackButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->GetWindow()->SetHiddenSceneToNext();
	Close();
}

void SettingsMenu::OnMusicThumbMoved(Object* sender, const ThumbMovedEventArgs& e)
{
	_audioManager->SetMusicVolume(e.Filling);
}

void SettingsMenu::OnSoundEffectThumbMoved(Object* sender, const ThumbMovedEventArgs& e)
{
	_audioManager->SetSoundEffectsVolume(e.Filling);
}

void SettingsMenu::OnMouseDown(Object* sender, const SDL_MouseButtonEvent& e)
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

void SettingsMenu::OnMouseMove(Object* sender, const SDL_MouseButtonEvent& e)
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

void SettingsMenu::OnKeyDown(Object* sender, const SDL_KeyboardEvent& e)
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