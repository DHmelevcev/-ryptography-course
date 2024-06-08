#include<fstream>
#include<iostream>
#include "../../Huffman_code.h"

bool generate_text(std::ofstream& out, std::map<char, double> frequencies, unsigned int size = 1000)
{
	if (frequencies.empty())
	{
		return false;
	}

	for (size_t i = 0; i < size; i++)
	{
		double r = static_cast<double>(rand()) / RAND_MAX;

		double cumulative_sum = 0;
		auto it = frequencies.begin();
		do
		{
			cumulative_sum += it->second;
			it++;
		} while (cumulative_sum < r);
		it--;

		out << it->first;
	}

	return true;
}

int main()
{
	Huffman_code coder;
	if (coder.generate_code("./f0.txt"))
	{
		std::cout << "Text size: ";
		size_t size = 1000;

		std::cin >> size;
		if (std::cin)
	
			{
				std::ofstream out("./input.txt");
				generate_text(out, coder.get_frequencies(), size);
				out.close();
			}
	}

	return 0;
}