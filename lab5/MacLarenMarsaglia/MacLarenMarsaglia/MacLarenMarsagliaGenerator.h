#pragma once
#include <vector>
#include "QuadraticCongruentialGenerator.h"

class MacLarenMarsagliaGenerator
{
public:
	MacLarenMarsagliaGenerator
	(QuadraticCongruentialGenerator& G1, QuadraticCongruentialGenerator& G2);

	uint64_t generate();

private:
	QuadraticCongruentialGenerator _G1, _G2;
	std::vector<uint64_t> T;
};