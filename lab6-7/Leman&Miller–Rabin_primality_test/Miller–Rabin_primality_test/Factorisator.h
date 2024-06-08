#pragma once
#include <map>
#include <sstream>
#include <chrono>
#include "MillerRabinTest.h"

class Factorisator
{
public:
	// returns number of loops of main cycle
	inline uint32_t loops() { return _loop_counter; }

	// returns time in milliseconds spent
	inline std::chrono::microseconds time() { return _exec_time_microseconds; }

	static std::string to_string(std::map<uint64_t, uint64_t> result);

	std::map<uint64_t, uint64_t> factorise(uint64_t number);

private:
	MillerRabinTest _primality_test;

	uint32_t _loop_counter;
	std::chrono::microseconds _exec_time_microseconds;
};