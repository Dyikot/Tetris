#include "SettingsMenu.h"

SettingsMenu::SettingsMenu()
{
	NavigationButtons = { &_backButton, &_applyButton };
	Objects = { &_title, &_backButton,
				&_soundEffectsSlider, &_musicSlider,
				&_soundEffectTitle, &_musicTitle,
				&_resolutionTitle, &_resolutionContainer,
				&_applyButton };

	using namespace std::placeholders;

	MouseMove = std::bind(&SettingsMenu::OnMouseMove, this, _1, _2);
	MouseDown = std::bind(&SettingsMenu::OnMouseDown, this, _1, _2);
	KeyDown = std::bind(&SettingsMenu::OnKeyDown, this, _1, _2);
	_applyButton.Click = std::bind(&SettingsMenu::OnApplyButtonClick, this, _1, _2);
	_backButton.Click = std::bind(&SettingsMenu::OnBackButtonClick, this, _1, _2);
}

void SettingsMenu::SaveSettingsAndQuit()
{
	const auto& [width, height] = WindowResolutionMap.at(*_resolutionContainer.GetCurrentItem());

	_settingsData->WidndowWidth = width;
	_settingsData->WidndowHeight = height;
	_settingsData->AcvtiveResolutionIndex = _activeResolutionIndex;
	_settingsData->SoundEffectFilling = _soundEffectsSlider.GetFilling();
	_settingsData->MusicFilling = _musicSlider.GetFilling();

	_settingsDataSerializer.Serialize(*_settingsData);

	Application::Current()->SetSavedSceneToNext();
}

void SettingsMenu::OnApplyButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	auto [width, height] = WindowResolutionMap.at(*_resolutionContainer.GetCurrentItem());
	_activeResolutionIndex = _resolutionContainer.GetCurrentItemIndex();

	Application::Current()->SetWindowSize(width, height);
	return;
}

void SettingsMenu::OnBackButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	SaveSettingsAndQuit();
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
			SaveSettingsAndQuit();
			break;

		default:
			break;
	}
}