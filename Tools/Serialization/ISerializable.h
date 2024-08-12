#pragma once

#include <filesystem>
#include <fstream>

struct SerializationData {};

class ISerializable
{
public:
	virtual void 
		Serialize(const std::filesystem::path& path, const SerializationData& data) const = 0;
	
	virtual std::unique_ptr<SerializationData>
		Deserialize(const std::filesystem::path& path) const = 0;
};