#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <ranges>

#include "../IScene.h"
#include "MenuScene.h"
#include "../../Controls/Slider.h"
#include "../../Controls/Container.h"
#include "../../Tools/Serialization/SettinsDataSerializer.h"

class SettingsMenu: public MenuScene
{
private:
	static constexpr int ResolutionContainerWidth = 280;
	static constexpr int ResolutionContainerHeight = 50;

	const int DefaultSliderWidth = 200;
	const int DefaultSliderHeight = 30;
	const int DefaultSliderHorizontalPosition = Application::Current()->WindowWidth / 2
												- DefaultSliderWidth / 2;

	// Window resolutions

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

	// Settings data serialization

	SettinsDataSerializer _settingsDataSerializer = SettinsDataSerializer();
	std::unique_ptr<SerializationData> _serializationData = _settingsDataSerializer
															.Deserialize();
	SettingsData* _settingsData = dynamic_cast<SettingsData*>(_serializationData.get());

	// Main title

	TextBlock _title = TextBlock(MainTitlePosition,
								 Object::DefaultBackgroundColor,
								 "Settings",
								 TextBlock::ActiveTextColor,
								 Header1TextSize);

	// Resolution title

	const SDL_Point ResolutionContainerTitlePosition =
	{
		.x = MainTitlePosition.x,
		.y = FirstControlVerticalPosition
	};
	TextBlock _resolutionTitle = TextBlock(ResolutionContainerTitlePosition,
										   Object::DefaultBackgroundColor,
										   "Window resolution",
										   TextBlock::ActiveTextColor,
										   Header4TextSize);

	// Resolution container
	
	size_t _activeResolutionIndex = _settingsData->AcvtiveResolutionIndex;
	const SDL_Point ResolutionContainerPosition =
	{
		.x = MainTitlePosition.x - ResolutionContainerWidth / 2,
		.y = _resolutionTitle.GetRealPosition().y 
			 + _resolutionTitle.GetHeight() 
			 + VerticalSpacing
	};
	Container _resolutionContainer = Container(ResolutionContainerPosition,
											   ResolutionContainerWidth,
											   ResolutionContainerHeight,
											   Container::DefaultBackgroundColor,
											   WindowResolutions,
											   _activeResolutionIndex);

	// Apply button

	const SDL_Point ApplyButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = ResolutionContainerPosition.y + _resolutionContainer.GetHeight() + VerticalSpacing
	};
	TextButton _applyButton = TextButton(ApplyButtonPosition,
										 DefaultButtonWidth,
										 DefaultButtonHeight,
										 Button::DefaultBackgroundColor,
										 Button::DefaultBorderColor,
										 "Apply",
										 TextBlock::ActiveTextColor,
										 TextButton::DefaultTextSize);

	// Sound effect title

	const SDL_Point SoundEffectsTitlePosition =
	{
		.x = MainTitlePosition.x ,
		.y = ApplyButtonPosition.y
			 + static_cast<int>(_applyButton.GetHeight() * 1.5)
			 + 3 * VerticalSpacing
	};
	TextBlock _soundEffectTitle = TextBlock(SoundEffectsTitlePosition,
											Object::DefaultBackgroundColor,
											"Sound effects",
											TextBlock::ActiveTextColor,
											Header4TextSize);

	// Sound effect slider

	const SDL_Point SoundEffectsSliderPosition =
	{
		.x = DefaultSliderHorizontalPosition,
		.y = _soundEffectTitle.GetRealPosition().y 
			 + _soundEffectTitle.GetHeight() 
			 + VerticalSpacing
	};
	Slider _soundEffectsSlider = Slider(SoundEffectsSliderPosition,
										DefaultSliderWidth,
										DefaultSliderHeight,
										Slider::DefaultColor,
										_settingsData->SoundEffectFilling);

	// Music title

	const SDL_Point MusicTitlePosition =
	{
		.x = MainTitlePosition.x,
		.y = SoundEffectsSliderPosition.y 
			 + static_cast<int>(_soundEffectsSlider.GetHeight() * 1.5)
			 + 3 * VerticalSpacing
	};
	TextBlock _musicTitle = TextBlock(MusicTitlePosition,
									  Object::DefaultBackgroundColor,
									  "Music",
									  TextBlock::ActiveTextColor,
									  Header4TextSize);

	// Music slider

	const SDL_Point MusicSliderPosition = 
	{
		.x = DefaultSliderHorizontalPosition,
		.y = _musicTitle.GetRealPosition().y
			 + _musicTitle.GetHeight() 
			 + VerticalSpacing
	};	
	Slider _musicSlider = Slider(MusicSliderPosition,
								 DefaultSliderWidth,
								 DefaultSliderHeight,
								 Slider::DefaultColor,
								 _settingsData->MusicFilling);

	// Back button

	const SDL_Point BackButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = MusicSliderPosition.y 
			 + static_cast<int>(_musicSlider.GetHeight() * 1.5)
			 + 3 * VerticalSpacing
	};
	TextButton _backButton = TextButton(BackButtonPosition,
										DefaultButtonWidth,
										DefaultButtonHeight,
										Button::DefaultBackgroundColor,
										Button::DefaultBorderColor,
										"Back",
										TextBlock::ActiveTextColor,
										TextButton::DefaultTextSize);

	const std::vector<Slider*> _sliders = { &_soundEffectsSlider, &_musicSlider };
public:
	SettingsMenu();
private:
	void OnClose(Object* sender, const EventArgs& e);

	void OnMouseMove(Object* sender, const SDL_MouseButtonEvent& e);

	void OnMouseDown(Object* sender, const SDL_MouseButtonEvent& e);

	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnApplyButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnBackButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};