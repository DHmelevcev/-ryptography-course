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

double frequency_test(const std::vector<bool>& sample, const std::string& filename)
{
	double result = 0.;
	for (const auto& it : sample) {
		if (it == true)
			result++;
	}
	result = 2. * result - sample.size();

	if (filename != "")
		saveVector(std::vector<double>(1, result), filename);

	return abs(result) / sqrt(sample.size());
}

double chain_test(const std::vector<bool>& sample, const std::string& filename)
{
	double one_freq = 0.;
	double v = 1.;
	for (size_t i = 0; i < sample.size() - 1; ++i) {
		if (sample[i] == true)
			one_freq++;
		
		if (sample[i] != sample[i + 1])
			v++;
	}
	if (sample[sample.size() - 1] == true)
		one_freq++;
	one_freq /= sample.size();

	if (filename != "")
		saveVector(std::vector<double>(1, one_freq), filename + "1.txt");

	if (filename != "")
		saveVector(std::vector<double>(1, v), filename + "2.txt");

	return abs(v - 2. * sample.size() * one_freq * (1. - one_freq))
		/ (2. * sqrt(sample.size() * 2) * one_freq * (1. - one_freq));
}

std::vector<double> extended_randomness_test(const std::vector<bool>& sample, const std::string& filename)
{
	std::vector<int64_t> s(sample.size() + 2, 0);
	for (size_t i = 0; i < sample.size(); ++i) {
		if (sample[i] == true)
			s[i + 1] = s[i] + 1;
		else
			s[i + 1] = s[i] - 1;
	}

	if (filename != "")
		saveVector(s, filename + "1.txt", "\n");

	int64_t L = 0;
	std::vector<int64_t> ksi(18, 0);
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] == 0)
			L++;
		else if (-9 <= s[i] && s[i] <= 9)
			ksi[s[i] > 0 ? s[i] + 8 : s[i] + 9]++;
	}

	if (filename != "")
		saveVector(std::vector<int64_t>(1, L), filename + "2.txt");

	if (filename != "")
		saveVector(ksi, filename + "3.txt", "\n");

	std::vector<double> result(18, 0);
	for (size_t i = 0; i < result.size(); ++i) {
		result[i] = abs(ksi[i] - L)
			/ sqrt(2. * L * (4 * (i < 9 ? -9 + i : i - 8) - 2));
	}

	return result;
}
