#include "QuadraticCongruentialGenerator.h"

bool is_empty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

QuadraticCongruentialGenerator::QuadraticCongruentialGenerator
(uint64_t seed, uint64_t a, uint64_t c, uint64_t d, uint64_t N) : x(seed), a(a), c(c), d(d), N(N > 0 ? N : throw(1)) {};

QuadraticCongruentialGenerator::QuadraticCongruentialGenerator
(const std::string& file)
{
	std::ifstream inputfile(file);
	if (is_empty(inputfile))
	{
		throw 0;
	}

	uint64_t num;

	inputfile >> num;
	x = num;

	inputfile >> num;
	a = num;

	inputfile >> num;
	c = num;

	inputfile >> num;
	d = num;

	inputfile >> num;
	if (num <= 0) throw(1);
	N = num;

	if (!inputfile) throw 0;

	inputfile.close();
}

uint64_t QuadraticCongruentialGenerator::generate()
{
	return x = (d * x * x + a * x + c) % N;
}