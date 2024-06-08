#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>

template<typename T>
void saveVector(std::vector<T>& sample, const std::string& filename, const std::string& delimer = "")
{
	std::ofstream file(filename);

	for (auto& i : sample)
	{
		file << i << delimer;
	}

	file.close();
}

double chi_squared_statistic(const std::vector<bool>& sample);

double balance_statistic(const std::vector<bool>& sample);

std::map<size_t, size_t> cyclicality_statistic(const std::vector<bool>& sample);

double correlation_statistic(const std::vector<bool>& sample);

double frequency_test(const std::vector<bool>& sample, const std::string& filename = "");

double chain_test(const std::vector<bool>& sample, const std::string& filename = "");

std::vector<double> extended_randomness_test(const std::vector<bool>& sample, const std::string& filename = "");