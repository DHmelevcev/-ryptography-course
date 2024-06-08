#pragma once
//{
#include <chrono>
//}
#include "RandomIntGenerator.h"
#include "MillerRabinTest.h"

class RandomPrimalGenerator
{
public:
	RandomPrimalGenerator();

	// returns a random primal number with the given amount of binary digits
	uint64_t next(uint16_t num_of_digits = 32);

	// returns number of loops of main cycle
	inline uint32_t loops() { return _loop_counter; }

	//{
	// returns time in milliseconds spent to generate
	inline std::chrono::microseconds time() { return _exec_time_microseconds; }
	//}

private:
	RandomIntGenerator _gen;
	MillerRabinTest _primality_test;

	uint32_t _loop_counter;
	//{
	std::chrono::microseconds _exec_time_microseconds;
	//}
};