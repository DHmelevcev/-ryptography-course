#include "binary_statistics.h"

#ifdef max
#undef max
#endif // max

double chi_squared_statistic(const std::vector<bool>& sample)
{
	double result = 0;
	size_t vi = 0;

	for (const auto& it : sample) {
		if (it) ++vi;
	}

	result += pow((static_cast<double>(vi) / sample.size()) - 0.5, 2) * 0.5;
	result += pow((static_cast<double>(sample.size() - vi) / sample.size()) - 0.5, 2) * 0.5;

	return result * sample.size();
}

double balance_statistic(const std::vector<bool>& sample)
{
	double result = 0;
	size_t vi = 0, ki = 0;
	const size_t k = static_cast<size_t>((2. * sample.size()) / (1. + static_cast<double>(log2(sample.size()))));
	auto it = sample.begin();

	while (it != sample.end())
	{
		if (*it) ++vi;
		++ki;
		++it;

		if (ki == k) {
			result = std::max(std::abs(static_cast<double>(2 * vi) - ki) / ki, result);
			vi = ki = 0;
		}
	}

	if (ki > 0.5 * k) {
		result = std::max(std::abs(static_cast<double>(2 * vi) - ki) / ki, result);
	}

	return result;
}

std::map<size_t, size_t> cyclicality_statistic(const std::vector<bool>& sample)
{
	std::map<size_t, size_t> result;
	size_t ki = 0;
	bool vi = sample.at(0);

	for (const auto& it : sample) {
		if (it == vi)
			++ki;
		else {
			ki = 1;
			vi = it;
		}

		if (result.find(ki) != result.end())
			++result[ki];
		else
			result[ki] = 1;
	}

	return result;
}

double correlation_statistic(const std::vector<bool>& sample)
{
	size_t size = sample.size();

	if (size < 2)
		return 1.;

	size_t vi = 0;

	if (sample.front() == sample.back())
		++vi;

	for (size_t i = 0; i < size - 1; ++i)
		if (sample[i] == sample[i + 1])
			++vi;

	return std::abs(static_cast<double>(2 * vi) - size) / size;
}