#pragma once
#include <cstdint>
#include "random_uint.h"
#include "random_prime.h"

namespace RSArandomgenerator
{

	template<typename type_t>
	class RSA_gen
	{
		Random_uint_gen<type_t> _igen;

		type_t N;
		type_t k;
		type_t u;

	public:
		RSA_gen(uint_t seed = 0) : _igen(seed) {
			type_t p = random_prime(bit_count_v<type_t> / 2 + 1, _igen);
			type_t q = random_prime(bit_count_v<type_t> / 2 + 1, _igen);

			N = p * q;
			const type_t phi = (p - 1) * (q - 1);
			k = (_igen.next(bit_count_v<type_t>) % (phi - 2)) + 2;
			while (GCD(k, phi) != 1)
				k = _igen.next(bit_count_v<type_t>) % phi;

			u = (_igen.next(bit_count_v<type_t>) % (N - 3)) + 2;
		}

		bool next_bit() {
			bool result = static_cast<bool>(u & 1);
			u = modmul(u, k, N);
			return result;
		}
	};
}
