#include "SettinsDataSerializer.h"


std::filesystem::path SettinsDataSerializer::GetDefaultFilePath() const
{
	return std::filesystem::path("settings_data.tstngs");
}

std::filesystem::path SettinsDataSerializer::GetFileExtension() const
{
	return std::filesystem::path(".tstngs");
}

void SettinsDataSerializer::Serialize(const std::filesystem::path& path,
									  const SerializationData& data) const
{
	if(!IsPathRelevant(path))
	{
		std::cout << "Ошибка! Проверьте имя файла на корректность!\n";
		return;
	}

	std::ofstream stream(path);

	const auto& settingsData = static_cast<const SettingsData&>(data);

	if(stream.is_open())
	{
		stream << settingsData.WidndowWidth << std::endl;
		stream << settingsData.WidndowHeight << std::endl;
		stream << settingsData.AcvtiveResolutionIndex << std::endl;
		stream << settingsData.SoundEffectFilling << std::endl;
		stream << settingsData.MusicFilling;

		stream.close();
	}
}

void SettinsDataSerializer::Serialize(const SerializationData& data) const
{
	Serialize(GetDefaultFilePath(), data);
}


std::unique_ptr<SerializationData> SettinsDataSerializer::Deserialize(const std::filesystem::path & path) const
{
	std::unique_ptr<SettingsData> settingsData(new SettingsData());

	if(!IsPathRelevant(path))
	{
		std::cout << "Ошибка! Проверьте имя файла на корректность!\n";
		return settingsData;
	}

	if(!std::filesystem::exists(path))
	{
		return settingsData;
	}

	std::ifstream stream(path);

	std::vector<std::string> lines;

	if(stream.is_open())
	{
		std::string line;

		while(!stream.eof())
		{
			std::getline(stream, line);
			lines.push_back(std::move(line));
		}

		stream.close();
	}

	if(lines.size() == 5)
	{
		auto ToSize_t = [](std::string&& string)
		{
			size_t result;
			std::stringstream ss(std::move(string));
			ss >> result;

			return result;
		};

		settingsData->WidndowWidth = ToSize_t(std::move(lines[0]));
		settingsData->WidndowHeight = ToSize_t(std::move(lines[1]));
		settingsData->AcvtiveResolutionIndex = ToSize_t(std::move(lines[2]));
		settingsData->SoundEffectFilling = ToSize_t(std::move(lines[3]));
		settingsData->MusicFilling = ToSize_t(std::move(lines[4]));
	}

	return settingsData;
}

std::unique_ptr<SerializationData> SettinsDataSerializer::Deserialize() const
{
	return Deserialize(GetDefaultFilePath());
}

bool SettinsDataSerializer::IsPathRelevant(const std::filesystem::path& path) const
{
	return !path.empty() &&
			path.has_filename() &&
			path.has_extension() &&
			path.extension() == GetFileExtension();
}
