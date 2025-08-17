#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <ranges>

#include "MenuScene.h"
#include "../UI/Controls/Slider.h"
#include "../UI/Controls/Container.h"
#include "../Serialization/AppSettingsSerializer.h"

class SettingsMenu: public MenuScene
{
private:
	static constexpr Style ResolutionContainerStyle =
	{
		.Width = 280,
		.Height = 50
	};

	static constexpr Style SliderStyle =
	{
		.Width = 200,
		.Height = 30,
		.Background = Colors::Green
	};

	static constexpr Style SettingTitleStyle =
	{
		.FontSize = FontSizeH4,
		.FontColor = Colors::Whitesmoke
	};

	const int SliderHorizontalPosition = GetWidth() / 2 - SliderStyle.Width / 2;

	const std::map <std::string, std::pair<size_t, size_t>> WindowResolutionMap =
	{
		{"300x600",   {300, 600}},
		{"400x800",   {400, 800}},
		{"500x1000",  {500, 1000}},
		{"600x1200",  {600, 1200}},
		{"700x1400",  {700, 1400}},
		{"800x1600",  {800, 1600}},
		{"900x1800",  {900, 1800}},
		{"1000x2000", {1000, 2000}}
	};

	const std::vector<std::string> WindowResolutions =
	{
		"300x600",
		"400x800",
		"500x1000",
		"600x1200",
		"700x1400",
		"800x1600",
		"900x1800",
		"1000x2000"
	};

	AppSettings _appSettings = AppSettingsSerializer::Deserialize();
	AudioManager* _audioManager = Application::Current()->GetAudioManager();

	TextBlock _resolutionTitle = 
	{
		SDL_Point
		{
			.x = _title.GetPosition().x,
			.y = FirstControlVerticalPosition
		},
		"Window resolution",
		SettingTitleStyle 
	};	
	
	Container _resolutionContainer = 
	{
		SDL_Point
		{
			.x = _title.GetPosition().x - ResolutionContainerStyle.Width / 2,
			.y = _resolutionTitle.GetRealPosition().y
				 + _resolutionTitle.GetHeight()
				 + VerticalSpacing
		},
		ResolutionContainerStyle,
		WindowResolutions,
		_appSettings.WindowResolutionIndex 
	};

	TextButton _applyButton = 
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = _resolutionContainer.GetPosition().y
				 + _resolutionContainer.GetHeight()
				 + VerticalSpacing
		},
		"Apply",
		NavigationButtonStyle
	};

	TextBlock _soundEffectTitle = 
	{
		SDL_Point
		{
			.x = _title.GetPosition().x ,
			.y = _applyButton.GetPosition().y
				 + static_cast<int>(_applyButton.GetHeight() * 1.5)
				 + 3 * VerticalSpacing
		},
		"Sound effects",
		SettingTitleStyle 
	};

	Slider _soundEffectsSlider = 
	{
		SDL_Point
		{
			.x = SliderHorizontalPosition,
			.y = _soundEffectTitle.GetRealPosition().y
				 + _soundEffectTitle.GetHeight()
				 + VerticalSpacing
		},
		SliderStyle,
		_appSettings.SoundEffectVolume
	};

	TextBlock _musicTitle = 
	{
		SDL_Point
		{
			.x = _title.GetPosition().x,
			.y = _soundEffectsSlider.GetPosition().y
				 + static_cast<int>(_soundEffectsSlider.GetHeight() * 1.5)
				 + 3 * VerticalSpacing
		},
		"Music",
		SettingTitleStyle 
	};

	Slider _musicSlider = 
	{
		SDL_Point
		{
			.x = SliderHorizontalPosition,
			.y = _musicTitle.GetRealPosition().y
				 + _musicTitle.GetHeight()
				 + VerticalSpacing
		},
		SliderStyle,
		_appSettings.MusicVolume
	};

	TextButton _backButton = 
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = _musicSlider.GetPosition().y
				 + static_cast<int>(_musicSlider.GetHeight() * 1.5)
				 + 3 * VerticalSpacing
		},
		"Back",
		NavigationButtonStyle 
	};

	std::vector<Slider*> _sliders = { &_soundEffectsSlider, &_musicSlider };
public:
	SettingsMenu();
private:
	void OnClose(Renderable* sender, const EventArgs& e);
	void OnMouseMove(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnMouseDown(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnKeyDown(Renderable* sender, const SDL_KeyboardEvent& e);
	void OnApplyButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnBackButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnMusicThumbMoved(Renderable* sender, const ThumbMovedEventArgs& e);
	void OnSoundEffectThumbMoved(Renderable* sender, const ThumbMovedEventArgs& e);
};