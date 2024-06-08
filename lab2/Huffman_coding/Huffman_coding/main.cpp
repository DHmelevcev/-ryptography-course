#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <bitset>
#include <string>

bool is_empty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

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

class huff_code
{
public:
	bool generate_code(std::ifstream& frequencies)
	{
		struct node
		{
			node* left;
			node* right;
			char symb;
			char codelength;
			unsigned short code;
		};

		std::multimap<float, node> map;

		while (!is_empty(frequencies))
		{
			char symb;
			frequencies >> symb;
			float f;
			frequencies >> f;

			map.insert(std::make_pair(f, node{ nullptr, nullptr, symb, 0, 0 }));
		}

		if (map.size() < 2)
		{
			return false;
		}

		_code.clear();
		_reverse_code.clear();
		_frequencies.clear();

		//Constructing a Huffman Tree
		std::multimap<float, node>::iterator rarest = map.begin();
		std::multimap<float, node>::iterator secondrarest = ++map.begin();
		for (size_t size = map.size(); size > 1; size--)
		{
			map.insert(std::make_pair(rarest->first + secondrarest->first, node{ &rarest->second, &secondrarest->second, '\0', 0, 0 }));
			rarest = secondrarest;
			rarest++;
			secondrarest = rarest;
			secondrarest++;
		}

		//Reversing a Huffman Tree
		std::queue<node*> queue;
		queue.push(&map.rbegin()->second);
		while (!queue.empty())
		{
			node* it = queue.front();
			if (it->left)
			{
				it->left->codelength = it->codelength + 1;
				it->left->code = it->code << 1 | 1;
				queue.push(it->left);
			}
			if (it->right)
			{
				it->right->codelength = it->codelength + 1;
				it->right->code = it->code << 1;
				queue.push(it->right);
			}

			queue.pop();
		}

		constexpr size_t U_SHORT_SIZE_IN_BITS = sizeof(unsigned short) * 8;

		for (auto it = map.begin(); it != map.end(); it++)
		{
			if (it->second.symb)
			{
				auto ñode = std::bitset<U_SHORT_SIZE_IN_BITS>(it->second.code).to_string().substr(U_SHORT_SIZE_IN_BITS - it->second.codelength, it->second.codelength);
				_code.insert(std::make_pair(it->second.symb, ñode));
				_reverse_code.insert(std::make_pair(ñode, it->second.symb));
				_frequencies.insert(std::make_pair(it->second.symb, it->first));
			}
		}

		return true;
	}

	std::string code_to_string() const
	{
		std::string result;
		for (auto it = _code.begin(); it != _code.end(); it++)
		{
			result += it->first;
			result += ' ';
			result += it->second;
			result += '\n';
		}

		return result;
	}

	double average_code_length() const
	{
		if (_code.empty())
		{
			return -1;
		}

		double result = 0;
		for (auto it = _code.begin(); it != _code.end(); it++)
		{
			result += it->second.length() * _frequencies.at(it->first);
		}

		return result;
	}

	double redundancy() const
	{
		if (_frequencies.empty())
		{
			return -1;
		}

		double result = 0;
		for (auto it = _frequencies.begin(); it != _frequencies.end(); it++)
		{
			if (it->second)
			{
				result += it->second * log2(it->second);
			}
		}

		return 1 + result / log2(_code.size());
	}

	double kraft_inequality() const
	{
		if (_code.empty())
		{
			return -1;
		}

		double result = 0;
		for (auto it = _code.begin(); it != _code.end(); it++)
		{
			result += pow(2, -(int)it->second.length());
		}

		return result;
	}

	unsigned int encode(std::ifstream& input, std::ofstream& out) const
	{
		if (is_empty(input))
		{
			return 0;
		}

		unsigned int result = 0;

		while (!is_empty(input))
		{
			char symb;
			input >> symb;
			std::string str = _code.at(symb);
			out << str;
			result += str.length();
		}

		return result;
	}

	unsigned int decode(std::ifstream& input, std::ofstream& out) const
	{
		if (is_empty(input))
		{
			return 0;
		}

		unsigned int result = 0;

		std::string buffer;
		while (!is_empty(input))
		{
			char symb;
			input >> symb;
			buffer += symb;
			auto it = _reverse_code.find(buffer);
			if (it != _reverse_code.end())
			{
				out << it->second;
				result++;
				buffer = "";
			}
		}

		return result;
	}

	inline std::map<char, double> get_frequencies() const
	{
		return _frequencies;
	}

private:
	std::map<char, std::string> _code;
	std::map<std::string, char> _reverse_code;
	std::map<char, double> _frequencies;
};

int main()
{
	srand(time(0));

	std::ifstream frequencies("../../f1.txt");
	huff_code coder;
	int result = coder.generate_code(frequencies);
	if (!result)
	{
		std::cout << "The alphabet is too small, there is nothing to encode" << std::endl;
	}
	else
	{
		std::cout << coder.code_to_string();
		std::cout << "Average code word length: " << coder.average_code_length() << std::endl;
		std::cout << "Redundancy: " << coder.redundancy() << std::endl;
		std::cout << "Kraft inequality: " << coder.kraft_inequality() << std::endl;
	}
	std::ofstream input_generation("../../input.txt");
	result = generate_text(input_generation, coder.get_frequencies(), 1000);
	if (!result)
	{
		std::cout << "Frequencies is empty" << std::endl;
	}
	input_generation.close();

	std::ifstream input_reading("../../input.txt");
	std::ofstream coded_writting("../../coded.txt");
	result = coder.encode(input_reading, coded_writting);
	if (!result)
	{
		std::cout << "Input is empty" << std::endl;
	}
	else
	{
		std::cout << "Coded Input lenght: " << result << std::endl;
	}
	coded_writting.close();

	std::ifstream coded_reading("../../coded.txt");
	std::ofstream output("../../output.txt");
	result = coder.decode(coded_reading, output);
	if (!result)
	{
		std::cout << "Coded Input is empty" << std::endl;
	}
	else
	{
		std::cout << "Output lenght: " << result << std::endl;
	}
	output.close();

	return 0;
}