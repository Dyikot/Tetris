#pragma once

#include <iostream>
#include <ranges>

#include "ISerializable.h"
#include "../Application/Window.h"

struct SettingsData: SerializationData
{
	size_t WindowWidth = 400;
	size_t WindowHeight = 800;
	size_t ActiveResolutionIndex = 1;
	size_t SoundEffectVolume = 100;
	size_t MusicVolume = 100;

	std::string ToString() const override;

	void Convert(const std::vector<std::string>& values);
};

class SettinsDataSerializer: public ISerializable
{
public:
	static constexpr char Delimetr = '\n';
public:
	std::filesystem::path GetDefaultFilePath() const;

	std::filesystem::path GetFileExtension() const;

	void Serialize(const std::filesystem::path& path, 
				   const SerializationData* data) const override;

	void Serialize(const SerializationData* data) const;

	std::unique_ptr<SerializationData> Deserialize(
		const std::filesystem::path& path) const override;

	std::unique_ptr<SerializationData> Deserialize() const;
private:
	bool IsPathRelevant(const std::filesystem::path& path) const;
};