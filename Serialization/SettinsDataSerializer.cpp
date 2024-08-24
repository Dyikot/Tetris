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
									  const SerializationData* data) const
{
	if(!IsPathRelevant(path))
	{
		std::cout << "Ошибка! Проверьте имя файла на корректность!\n";
		return;
	}	

	auto settingsData = dynamic_cast<const SettingsData*>(data);

	if(std::ofstream stream(path); stream.is_open() && settingsData != nullptr)
	{
		stream << settingsData->ToString();
	}
}

void SettinsDataSerializer::Serialize(const SerializationData* data) const
{
	Serialize(GetDefaultFilePath(), data);
}


std::unique_ptr<SerializationData> SettinsDataSerializer::Deserialize(const std::filesystem::path & path) const
{
	auto settingsData = std::make_unique<SettingsData>();

	if(!IsPathRelevant(path))
	{
		std::cout << "Ошибка! Проверьте имя файла на корректность!\n";
		return settingsData;
	}

	if(!std::filesystem::exists(path))
	{
		return settingsData;
	}		

	if(std::ifstream stream(path); stream.is_open())
	{		
		std::vector<std::string> values;
		std::string buffer;

		while(std::getline(stream, buffer, settingsData->Delimetr))
		{
			values.push_back(std::move(buffer));
		} 

		settingsData->Convert(values);
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

std::string SettingsData::ToString() const
{
	std::stringstream ss;
	ss << WidndowWidth << Delimetr;
	ss << WidndowHeight << Delimetr;
	ss << AcvtiveResolutionIndex << Delimetr;
	ss << SoundEffectFilling << Delimetr;
	ss << MusicFilling << Delimetr;
	
	return ss.str();
}

void SettingsData::Convert(const std::vector<std::string>& values)
{
	if(values.size() != 5)
	{
		return;
	}
	
	auto ToSize_t = [](const std::string& string)
	{
		size_t result;
		std::stringstream ss(string);
		ss >> result;

		return result;
	};

	auto properties = values | std::ranges::views::transform(ToSize_t);

	WidndowWidth = properties[0];
	WidndowHeight = properties[1];
	AcvtiveResolutionIndex = properties[2];
	SoundEffectFilling = properties[3];
	MusicFilling = properties[4];
}
