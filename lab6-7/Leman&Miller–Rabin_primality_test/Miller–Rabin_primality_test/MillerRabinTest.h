#pragma once
#include <random>
#include "RandomIntGenerator.h"

extern "C" uint64_t modmul(uint64_t a, uint64_t b, uint64_t M);

template<typename T>
T GCD(T number1, T number2)
{
	while (number2)
	{
		T temp = number2;
		number2 = number1 % number2;
		number1 = temp;
	}

	return number1;
}

template<typename T>
T modular_power(T number, T power, T module)
{
	T result = 1;
	number %= module;

	if (!number) return 0;

	while (power)
	{
		if (power & 1)
			result = modmul(result, number, module);

		power = power >> 1;

		number = modmul(number, number, module);
	}

	return result;
}

class MillerRabinTest
{
public:
	bool test(uint64_t number);

private:
	RandomIntGenerator _gen;
};