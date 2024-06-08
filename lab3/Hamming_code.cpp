#include "Hamming_code.h"

bool is_empty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

Hamming_code::Hamming_code() :
	_n(9),
	_k(5),
	_r(4),
	_generative_matrix({ 0b10000, 0b01011, 0b01110, 0b10111 }),
	_check_matrix({ 0b100001000, 0b010110100, 0b011100010, 0b101110001 })
{
	generate_code();
}

void Hamming_code::generate_code()
{
	for (unsigned short number = 0; number < pow(2, _k); ++number)
	{
		unsigned short code = number << _r;

		unsigned short ones;
		unsigned short buffer;
		
		for (unsigned short row = 0; row < _r; ++row)
		{
			ones = 0;
			buffer = number & _generative_matrix[row];
			while (buffer)
			{
				buffer = buffer & (buffer - 1);
				ones++;
			}
			code = code | ((ones & 0b1) << (_r - 1 - row));
		}

		constexpr size_t U_SHORT_SIZE_IN_BITS = sizeof(unsigned int) * 8;

		auto string = std::bitset<U_SHORT_SIZE_IN_BITS>(code).to_string().substr(U_SHORT_SIZE_IN_BITS - _n, _n);
		_code.insert(std::make_pair(number + (number > 9 ? 0x37: 0x30), string));
		_reverse_code.insert(std::make_pair(string, number + (number > 9 ? 0x37 : 0x30)));
	}
}

std::string Hamming_code::code_to_string() const
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

unsigned int Hamming_code::encode(const std::string& input, const std::string& out) const
{
	std::ifstream inputfile(input);
	std::ofstream outfile(out);

	if (is_empty(inputfile))
	{
		return 0;
	}

	unsigned int result = 0;

	while (!is_empty(inputfile))
	{
		char symb;
		inputfile >> symb;
		auto it = _code.find(symb);
		std::string str = (it != _code.end() ? it->second : "");
		outfile << str;
		result += str.length();
	}

	inputfile.close();
	outfile.close();

	return result;
}

std::vector<unsigned int> Hamming_code::decode(const std::string& input, const std::string& out) const
{
	std::ifstream inputfile(input);
	std::ofstream outfile(out);

	if (is_empty(inputfile))
	{
		return std::vector<unsigned int>();
	}

	std::vector<unsigned int> result({ 0 });

	std::string buffer;
	while (!is_empty(inputfile))
	{
		char symb;
		inputfile >> symb;
		buffer += symb;
		auto it = _reverse_code.find(buffer);
		if (it != _reverse_code.end())
		{
			outfile << it->second;
			result[0]++;
			buffer = "";
		}
		if (buffer.length() == _code.begin()->second.length())
		{
			unsigned short code = std::stoi(buffer, 0, 2);
			unsigned short sind = 0;

			unsigned short ones;
			unsigned short counter;
			for (unsigned short row = 0; row < _r; ++row)
			{
				ones = 0;
				counter = code & _check_matrix[row];
				while (counter)
				{
					counter = counter & (counter - 1);
					ones++;
				}
				sind |= ((ones & 0b1) << (_r - 1 - row));
			}

			switch (sind)
			{
			case 3:
				sind = 7;
				break;
			case 4:
				sind = 3;
				break;
			case 6:
				sind = 8;
				break;
			case 7:
				sind = 6;
				break;
			case 8:
				sind = 4;
				break;
			default:
				break;
			}

			code ^= 1 << (sind - 1);

			constexpr size_t U_SHORT_SIZE_IN_BITS = sizeof(unsigned int) * 8;
			auto string = std::bitset<U_SHORT_SIZE_IN_BITS>(code).to_string().substr(U_SHORT_SIZE_IN_BITS - _n, _n);
			it = _reverse_code.find(string);
			outfile << it->second;

			result.push_back(result[0]);
			result[0]++;
			buffer = "";
		}
	}

	inputfile.close();
	outfile.close();

	return result;
}