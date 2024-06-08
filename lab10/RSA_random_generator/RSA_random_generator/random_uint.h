#pragma once
#include <cstdint>
#include <random>
#include <slimcpplib/long_uint.h>

using uint_t = slim::uint_t;

template<typename type_t>
class Random_uint_gen
{
	std::mt19937_64 _gen;
	std::uniform_int_distribution<> _dist;

public:
	Random_uint_gen(uint_t seed = 0) : _gen(seed), _dist(0, 1) {}

	type_t next(uint_t digits) {
		type_t result = 0;

		for (uint_t i = 0; i < digits - 1; ++i) {
			result |= type_t(_dist(_gen)) << i;
		}

		result |= type_t(1) << (digits - 1);
		return result;
	}
};
