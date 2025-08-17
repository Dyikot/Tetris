#pragma once

#include <fstream>
#include <format>
#include <vector>
#include <string>

struct WindowSize
{
	int Width;
	int Height;
};

struct AppSettings
{
	size_t WindowResolutionIndex = 1;
	size_t SoundEffectVolume = 100;
	size_t MusicVolume = 100;

	static AppSettings Parse(const std::vector<std::string>& values);
	WindowSize GetWindowSize() const;
};

class AppSettingsSerializer
{
public:
	static constexpr auto FileName = "settings_data.tstngs";
	static constexpr auto FileExtension = ".tstngs";
public:
	static void Serialize(const AppSettings& appSettings);
	static AppSettings Deserialize();
};