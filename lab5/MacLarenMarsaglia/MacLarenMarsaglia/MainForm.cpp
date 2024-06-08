#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "MainForm.h"
#include "MacLarenMarsagliaGenerator.h"

using namespace System;
using namespace System::Windows::Forms;

template<typename T>
void saveVector(std::vector<T>& sample, const std::string& filename)
{
	std::ofstream file(filename);

	for (auto& i : sample)
	{
		file << i << " ";
	}

	file.close();
}

String^ file_to_WinString(const std::string& filename)
{
	std::ifstream file(filename);

	String^ result;

	std::stringstream buffer;
	buffer << file.rdbuf();

	result = gcnew String(buffer.str().c_str());

	file.close();

	return result;
}

// находит самое большое рассто€ние между одинаковыми элементами
// если 0, то все элементы уникальны
template<typename T>
size_t samplePeriod(std::vector<T>& sample)
{
	size_t result = 0;

	std::unordered_map<T, size_t> last_seen;
	for (size_t i = 0; i < sample.size(); ++i)
	{
		if (last_seen.find(sample[i]) == last_seen.end())
		{
			last_seen[sample[i]] = i;
			continue;
		}

		if (i - last_seen[sample[i]] > result)
			result = i - last_seen[sample[i]];
		last_seen[sample[i]] = i;
	}

	return result;
}

// получение статистики критери€ хи-квадрат ѕирсона
template<typename T>
double ChiSquaredTestStatistic(std::vector<T>& sample)
{
	double M = sample.back();

	size_t K = M < 10 ? M : 5 * log10(sample.size());
	double delta = static_cast<double>(M - sample[0]) / K;

	double result = 0;
	double vi = 0;

	auto it = sample.begin();
	double interval_end = sample[0] + delta;
	for (size_t i = 0; i < K - 1; ++i)
	{
		while (*it < interval_end)
		{
			vi++;
			it++;
		}

		result += pow(vi / sample.size() - 1. / K, 2) * K;

		vi = 0;
		interval_end += delta;
	}

	while (it != sample.end())
	{
		vi++;
		it++;
	}

	result += pow((vi / sample.size()) - (1. / K), 2) * K;

	return result * sample.size();
}

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	MacLarenMarsaglia::MainForm form;

	try
	{
		MacLarenMarsagliaGenerator generator(
			QuadraticCongruentialGenerator("input1.txt"),
			QuadraticCongruentialGenerator("input2.txt")
		);

		// генерирование последовательности длиной M
		const size_t M = 2050;
		std::vector<uint64_t> sample(M);
		for (auto& i : sample)
		{
			i = generator.generate();
		}
		saveVector(sample, "sample.txt");

		// вычисление характеристик последовательности
		size_t N = samplePeriod(sample);
		sort(sample.begin(), sample.end());
		size_t r = sample.back() < 10 ? sample.back() - 1 : 5 * log10(sample.size()) - 1;
		double stat = ChiSquaredTestStatistic(sample);
		saveVector(std::vector<double>{static_cast<double>(N), static_cast<double>(r), stat}, "sampleinfo.txt");

		form.add_page1("ѕериод: " + gcnew String(std::to_string(N).c_str()));
		form.add_page1("\n—тепени свободы: " + gcnew String(std::to_string(r).c_str()));
		form.add_page1("\n—татистика критери€: " + gcnew String(std::to_string(stat).c_str()));

		form.add_page2(file_to_WinString("sample.txt"));
	}
	catch (int err)
	{
		if (err == 0) form.add_page1("Broken input file");
		if (err == 1) form.add_page1("Incorrect params of generator");
	}

	Application::Run(% form);
	return 0;
}