#include "AppSettingsSerializer.h"
#include <filesystem>
#include <iostream>
#include <vector>

AppSettings AppSettings::Parse(const std::vector<std::string>& values)
{
	try
	{
		AppSettings appSettins;
		appSettins.WindowResolutionIndex = std::stoi(values[0]);
		appSettins.SoundEffectVolume = std::stoi(values[1]);
		appSettins.MusicVolume = std::stoi(values[2]);
		
		return appSettins;
	}
	catch(std::exception& ex)
	{
		std::cout << std::format("Parse error: {}\n", ex.what());
		return AppSettings();
	}
}

WindowSize AppSettings::GetWindowSize() const
{
	static const std::vector<WindowSize> resolutions =
	{
		{300, 600},
		{400, 800},
		{500, 1000},
		{600, 1200},
		{700, 1400},
		{800, 1600},
		{900, 1800},
		{1000, 2000}
	};

	return WindowSize(resolutions[WindowResolutionIndex]);
}

void AppSettingsSerializer::Serialize(const AppSettings& appSettings)
{
	if(std::ofstream stream(FileName); stream.is_open())
	{
		stream << appSettings.WindowResolutionIndex << '\n';
		stream << appSettings.SoundEffectVolume << '\n';
		stream << appSettings.MusicVolume << '\n';
	}
}

AppSettings AppSettingsSerializer::Deserialize()
{
	if(!std::filesystem::exists(FileName))
	{
		return AppSettings();
	}

	if(std::ifstream stream(FileName); stream.is_open())
	{
		std::vector<std::string> values;
		std::string buffer;

		while(std::getline(stream, buffer))
		{
			values.push_back(std::move(buffer));
		}

		return AppSettings::Parse(values);
	}

	return AppSettings();
}