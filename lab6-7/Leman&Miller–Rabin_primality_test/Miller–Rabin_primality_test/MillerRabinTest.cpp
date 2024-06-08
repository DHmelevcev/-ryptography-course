#include "MillerRabinTest.h"

bool MillerRabinTest::test(uint64_t number)
{
	if (number < 1) throw(3);
	if (number < 4) return true;
	if (!(number & 1)) return false;

	uint16_t digits = log2(number) + 1;

	uint64_t delimer = (number - 1) & ~(number - 2); // == 2^S, S - smallest bit
	uint16_t S = log2(delimer);
	uint64_t t = (number - 1) / delimer;

	uint16_t rounds = digits;
	while (rounds)
	{
		uint64_t a = 2 + _gen.next(digits) % (number - 4);

		if (GCD(a, number) != 1) return false;

		uint64_t z = modular_power(a, t, number);
		if (z != 1 && z != number - 1)
		{
			uint16_t s = S - 1;
			while (s)
			{
				z = modular_power(z, static_cast<uint64_t>(2), number);
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