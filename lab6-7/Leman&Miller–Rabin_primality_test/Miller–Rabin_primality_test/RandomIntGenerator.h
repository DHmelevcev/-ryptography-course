#pragma once
#include <random>

class RandomIntGenerator
{
public:
	RandomIntGenerator();

	// returns a random number with the given amount of binary digits
	uint64_t next(uint16_t num_of_digits = 64);

private:
	std::random_device _rd;
	// Mersenne twister // Вихрь Мерсенна // T = 2^19937 - 1
	std::mt19937_64 _gen;
	std::uniform_int_distribution<> _dist;
};