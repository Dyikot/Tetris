#pragma once

#include <filesystem>
#include <fstream>

struct SerializationData
{
	char Delimetr = '\n';

	virtual std::string ToString() const = 0;
	virtual void Convert(const std::vector<std::string>& values) = 0;
};

class ISerializable
{
public:
	virtual ~ISerializable() = default;

	virtual void 
		Serialize(const std::filesystem::path& path, const SerializationData& data) const = 0;
	
	virtual std::unique_ptr<SerializationData>
		Deserialize(const std::filesystem::path& path) const = 0;
};