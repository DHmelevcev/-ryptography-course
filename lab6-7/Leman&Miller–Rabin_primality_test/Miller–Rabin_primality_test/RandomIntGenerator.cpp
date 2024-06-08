#include "RandomIntGenerator.h"

RandomIntGenerator::RandomIntGenerator() : _gen(_rd()), _dist(0, 1) {}

uint64_t RandomIntGenerator::next(uint16_t num_of_digits)
{
	if (!num_of_digits) throw(1);
	if (num_of_digits > 64) throw(2);

	uint64_t random_number = 0;

	for (uint16_t i = 0; i < num_of_digits - 1; ++i)
	{
		random_number |= static_cast<uint64_t>(_dist(_gen)) << i;
	}

	random_number |= static_cast<uint64_t>(1) << (num_of_digits - 1);

	return random_number;
}