#pragma once

using uint64_t = unsigned long long;
using uint8_t = unsigned char;

template<uint64_t first, uint64_t ...rest>
class LFSR
{
public:
	LFSR() = default;

	LFSR(uint64_t seed);

private:
	uint64_t shift_register;

public:
	uint8_t next_bit();
	uint8_t next_byte();
	uint32_t next_int();

	uint64_t period();

private:
	void shift(uint64_t by);
};