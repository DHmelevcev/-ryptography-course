#include "Factorisator.h"

std::string Factorisator::to_string(std::map<uint64_t, uint64_t> map)
{
	std::stringstream buffer;

	for (auto& e : map)
		buffer << e.first << "^" << e.second << " * ";

	std::string result = buffer.str();
	result.erase(result.end() - 3, result.end());

	return result;
}

void get_primal_factor(uint64_t& number, std::map<uint64_t, uint64_t>& result, uint32_t& counter)
{
	if (number % 2 == 0) {
		auto res_f = result.find(2);
		if (res_f != result.end())
			res_f->second++;
		else
			result.emplace(std::make_pair(2u, 1u));
		number /= 2;
		return;
	}

	uint64_t cub_root = uint64_t(pow(number, 1. / 3));

	for (uint64_t a = 3; a <= cub_root; a += 2) {
		counter++;
		if (number % a == 0) {
			auto res_f = result.find(a);
			if (res_f != result.end())
				res_f->second++;
			else
				result.emplace(std::make_pair(a, 1u));
			number /= a;
			return;
		}
	}

	uint64_t A, B, D;
	for (uint64_t k = 1; k <= cub_root; ++k) {
		uint64_t d_last = uint64_t(pow(number, 1. / 6) / (4 * sqrt(k))) + 1;
		for (uint64_t d = 0; d <= d_last; ++d) {
			counter++;
			A = sqrt(4 * k * number) + d;

			double AA = sqrt(A * A - 4 * k * number);
			if (abs(AA - uint64_t(AA)) < 1e-7) {
				B = AA;
				D = GCD(A - B, number);

				if (D > 1 && D < number) {
					auto res_f = result.find(D);
					if (res_f != result.end())
						res_f->second++;
					else
						result.emplace(std::make_pair(D, 1u));
					number /= D;
					res_f = result.find(number);
					if (res_f != result.end())
						res_f->second++;
					else
						result.emplace(std::make_pair(number, 1u));
					number = 1;
					return;
				}
			}
		}
	}

	auto res_a = result.find(number);
	if (res_a != result.end())
		res_a->second++;
	else
		result.emplace(std::make_pair(number, 1u));
	number = 1;
}

std::map<uint64_t, uint64_t> Factorisator::factorise(uint64_t number)
{
	std::map<uint64_t, uint64_t> result;

	if (_primality_test.test(number)) {
		_loop_counter++;
		result.emplace(std::make_pair(number, 1u));
		number = 0;
	}

	if (number == 4) {
		_loop_counter += 2u;
		result.emplace(std::make_pair(2u, 2u));
		number = 0;
	}
	if (number == 6) {
		_loop_counter += 2u;
		result.emplace(std::make_pair(2u, 1u));
		result.emplace(std::make_pair(3u, 1u));
		number = 0;
	}
	if (number == 8) {
		_loop_counter += 3u;
		result.emplace(std::make_pair(2u, 3u));
		number = 0;
	}

	_loop_counter = 0;
	using namespace std::chrono;
	auto start = high_resolution_clock::now();

	while (number > 1) {
		++_loop_counter;
		get_primal_factor(number, result, _loop_counter);
	}

	_exec_time_microseconds = duration_cast<microseconds>(high_resolution_clock::now() - start);

	return result;
}