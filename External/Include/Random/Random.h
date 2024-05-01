#pragma once
#include <random>

class Random
{
private:
	Random() = default;

	std::random_device device;
	std::uniform_int_distribution<int> range;
public:
	Random(const Random&) = delete;

	static Random& Current();
	int GenerateNumber(int min, int max);
};
