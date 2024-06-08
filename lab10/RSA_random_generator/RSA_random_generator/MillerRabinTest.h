#pragma once
#include "random_uint.h"
#include "cmath"

template<typename type_t>
constexpr uint_t byte_count_v = sizeof(type_t);
template<typename type_t>
constexpr uint_t bit_count_v = byte_count_v<type_t>*CHAR_BIT;

template<typename type_t>
bool MillerRabinTest(type_t number, Random_uint_gen<type_t> & igen)
{
	if (number < 4) return true;
	if (!(number & 1)) return false;

	const uint_t digits = static_cast<uint_t>(std::ceil((bit_count_v<type_t> -nlz(number))));

	const type_t delimer = (number - 1) & ~(number - 2); // == 2^S, S - second not zero bit
	const uint_t S = bit_count_v<type_t> -nlz(delimer) - 1; // nlz = number of leading zeros
	const type_t t = number >> S;

	uint_t rounds = 2 * static_cast<uint_t>(log2(digits));
	while (rounds)
	{
		type_t a = 2 + igen.next(digits) % (number - 4);

		if (GCD(a, number) != 1)
			return false;

		type_t z = modpow(a, t, number);
		if (z != 1 && z != number - 1)
		{
			uint_t s = S - 1;
			while (s)
			{
				z = modmul(z, z, number);
				if (z == number - 1) goto next;
				--s;
			}

			return false;
		}
	next:

		--rounds;
	}

	return true;
}
