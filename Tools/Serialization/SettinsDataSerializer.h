#pragma once

#include <iostream>
#include <ranges>

#include "ISerializable.h"
#include "../../Application/Application.h"

struct SettingsData: SerializationData
{
	size_t WidndowWidth = 400;
	size_t WidndowHeight = 800;
	size_t AcvtiveResolutionIndex = 1;
	size_t SoundEffectFilling = 100;
	size_t MusicFilling = 100;

	std::string ToString() const override;

	void Convert(const std::vector<std::string>& values) override;
};

class SettinsDataSerializer: public ISerializable
{
public:
	std::filesystem::path GetDefaultFilePath() const;

	std::filesystem::path GetFileExtension() const;

	void Serialize(const std::filesystem::path& path, 
				   const SerializationData& data) const override;

	void Serialize(const SerializationData& data) const;

	std::unique_ptr<SerializationData> Deserialize(const std::filesystem::path& path) const override;

	std::unique_ptr<SerializationData> Deserialize() const;
private:
	bool IsPathRelevant(const std::filesystem::path& path) const;
};

