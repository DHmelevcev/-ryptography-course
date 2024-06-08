#pragma once
#include <string>
#include <fstream>

typedef unsigned long long uint64_t;

class MacLarenMarsagliaGenerator;

class QuadraticCongruentialGenerator
{
public:
	QuadraticCongruentialGenerator
	(uint64_t seed, uint64_t a, uint64_t c, uint64_t d, uint64_t N);

	QuadraticCongruentialGenerator
	(const std::string& file);

	uint64_t generate();

private:
	uint64_t x;

	uint64_t a;
	uint64_t c;
	uint64_t d;
	uint64_t N;

	friend class MacLarenMarsagliaGenerator;
};