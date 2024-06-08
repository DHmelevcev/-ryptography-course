#include "RandomPrimalGenerator.h"

RandomPrimalGenerator::RandomPrimalGenerator() :
	_loop_counter(0), _exec_time_microseconds(0) {}

uint64_t RandomPrimalGenerator::next(uint16_t num_of_digits)
{
	const uint32_t max_loops = 1e6;

	_loop_counter = 0;
	//{
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	//}

	uint64_t result;

	while (_loop_counter < max_loops)
	{
		++_loop_counter;

		result = _gen.next(num_of_digits) | 1;

		if (_primality_test.test(result))
			break;
	}

	//{
	_exec_time_microseconds = duration_cast<microseconds>(high_resolution_clock::now() - start);
	//}

	if (_loop_counter == max_loops)
		return 0;
	return result;
}