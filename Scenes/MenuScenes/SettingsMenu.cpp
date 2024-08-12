#include "SettingsMenu.h"

SettingsMenu::SettingsMenu()
{
	_buttons = { &_backButton, &_applyButton };
	_controls = { &_title, &_backButton,
				  &_soundEffectsSlider, &_musicSlider,
				  &_soundEffectTitle, &_musicTitle,
				  &_resolutionTitle, &_resolutionContainer,
				  &_applyButton };
}

void SettingsMenu::Show()
{
	ShowControls();
}

void SettingsMenu::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			OnQuit(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(e);
			Menu::OnMouseDown(e);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e);
			Menu::OnMouseMove(e);
			break;

		case SDL_KEYDOWN:
			OnKeyDown(e);
			break;

		default:
			break;
	}
}

void SettingsMenu::Process()
{

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

void SettingsMenu::OnMouseDown(const SDL_Event& e)
{
	if(_hoverButton == &_backButton)
	{
		SaveSettingsAndQuit();
		return;
	}
	else if(_hoverButton == &_applyButton)
	{
		auto [width, height] = WindowResolutionMap.at(*_resolutionContainer.GetCurrentItem());
		_activeResolutionIndex = _resolutionContainer.GetCurrentItemIndex();

		Application::Current()->SetWindowSize(width, height);
		return;
	}

	if(_resolutionContainer.IsInRange(e.button.x, e.button.y))
	{
		_resolutionContainer.OnMouseDown(e);
		return;
	}
	
	for(auto slider : _sliders)
	{
		if(slider->IsInRange(e.button.x, e.button.y))
		{
			slider->MoveThumbTo(e.button.x);
			return;
		}
	}
}

void SettingsMenu::OnMouseMove(const SDL_Event& e)
{
	for(auto slider : _sliders)
	{
		if(SDL_GetMouseState(0, 0) & SDL_BUTTON_LMASK &&
			slider->IsInRange(e.button.x, e.button.y))
		{
			slider->MoveThumbTo(e.button.x);
			return;
		}
	}	
}

void SettingsMenu::OnKeyDown(const SDL_Event& e)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_ESCAPE:
			SaveSettingsAndQuit();
			break;

		default:
			break;
	}
}

void SettingsMenu::OnQuit(const SDL_Event& e)
{
	Application::Current()->Shutdown();
}