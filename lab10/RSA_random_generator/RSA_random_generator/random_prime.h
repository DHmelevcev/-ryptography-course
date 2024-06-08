#pragma once
#include "random_uint.h"
#include "MillerRabinTest.h"

template<typename type_t>
type_t random_prime(uint_t digits, Random_uint_gen<type_t>& igen)
{
	type_t d = igen.next(digits);
	if (d % 2 == 0) d++;
	while (!MillerRabinTest(d, igen))
		d += 2;

	return d;
}
