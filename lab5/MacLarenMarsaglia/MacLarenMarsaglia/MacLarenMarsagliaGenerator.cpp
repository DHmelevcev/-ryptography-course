#include "MacLarenMarsagliaGenerator.h"

MacLarenMarsagliaGenerator::MacLarenMarsagliaGenerator
(QuadraticCongruentialGenerator& G1, QuadraticCongruentialGenerator& G2) : _G1(G1), _G2(G2), T(_G2.N > 0xffff ? throw(1) : _G2.N)
{
	for (auto& i : T)
	{
		i = _G1.generate();
	}

	// прогоняем генератор перед использованием
	for (size_t i = 0; i < _G1.N; ++i) generate();
}

uint64_t MacLarenMarsagliaGenerator::generate()
{
	size_t index = _G2.generate();

	uint64_t result = T[index];
	T[index] = _G1.generate();

	return result;
}