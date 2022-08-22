#pragma once

#include "Singleton.h"
#include "Scene.h"
#include "string"
 


class JsonFileReader : public Singleton<JsonFileReader>
{
public:
	~JsonFileReader() override = default;
	JsonFileReader(const JsonFileReader& other) = delete;
	JsonFileReader(JsonFileReader&& other) noexcept = delete;
	JsonFileReader& operator=(const JsonFileReader& other) = delete;
	JsonFileReader& operator=(JsonFileReader&& other) noexcept = delete;

	void ReadFile(Scene & scene, const std::string & path);

private:
	friend class Singleton<JsonFileReader>;
	JsonFileReader() = default;
};

