#include <iostream>
#include <set>
#include "LFSR.h"

template<uint64_t...>
constexpr uint64_t mask = 0ull;

template<uint64_t first, uint64_t ...rest>
constexpr uint64_t mask<first, rest...> = (1ull << first) ^ (mask<rest...>);

template<uint64_t digits>
constexpr uint64_t fill_mask = (1ull << digits) - 1;

inline uint8_t reverse(uint8_t b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

template<uint64_t first, uint64_t ...rest>
LFSR<first, rest...>::LFSR(uint64_t seed) : shift_register(seed & fill_mask<first>) {}

template<uint64_t first, uint64_t ...rest>
uint8_t LFSR<first, rest...>::next_bit()
{	
	uint8_t result = static_cast<uint8_t>(shift_register & 1ull);
	shift(1);
	return result;
}

template<uint64_t first, uint64_t ...rest>
uint8_t LFSR<first, rest...>::next_byte()
{	
	uint8_t result = 0;
	for (uint8_t i = 0; i < 8; ++i)
		result |= next_bit() << i;
	return reverse(result);
}

template<uint64_t first, uint64_t ...rest>
void LFSR<first, rest...>::shift(uint64_t by)
{
	while (by--) {
		uint64_t bits = 0;
		for (uint64_t res_and = shift_register & mask<rest...>; res_and;)
		{
			res_and &= res_and - 1;
			++bits;
		}
		shift_register = ((bits & 1ull) << (first - 1)) | (shift_register >> 1);
	}
}

template<uint64_t first, uint64_t ...rest>
size_t LFSR<first, rest...>::period()
{
	LFSR<first, rest...> copy = *this;
	std::set<uint64_t> registers_seen;
	
	while (true) {
		if (registers_seen.find(copy.shift_register) == registers_seen.end())
		{
			registers_seen.insert(copy.shift_register);
			copy.shift(1);
		}
		else {
			return registers_seen.size();
		}
	}
}

template<uint64_t first, uint64_t ...rest>
std::ostream& operator<<(std::ostream& os, LFSR<first, rest...>& lfsr)
{
	os << lfsr.next();
	return os;
}