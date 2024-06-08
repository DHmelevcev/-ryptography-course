#include "Huffman_code.h"

bool is_empty(std::ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}

bool Huffman_code::generate_code(const std::string& filename)
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

	std::ifstream frequencies(filename);

	while (!is_empty(frequencies))
	{
		char symb;
		frequencies >> symb;
		float f;
		frequencies >> f;

		map.insert(std::make_pair(f, node{ nullptr, nullptr, symb, 0, 0 }));
	}

	frequencies.close();

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
			unsigned short ones = 0;
			unsigned short code = it->second.code;
			while (code)
			{
				code = code & (code - 1);
				ones++;
			}
			it->second.code = (it->second.code << 1) + ones % 2;
			it->second.codelength++;
			auto ñode = std::bitset<U_SHORT_SIZE_IN_BITS>(it->second.code).to_string().substr(U_SHORT_SIZE_IN_BITS - it->second.codelength, it->second.codelength);
			_code.insert(std::make_pair(it->second.symb, ñode));
			_reverse_code.insert(std::make_pair(ñode, it->second.symb));
			_frequencies.insert(std::make_pair(it->second.symb, it->first));
		}
	}

	return true;
}

std::string Huffman_code::code_to_string() const
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

unsigned int Huffman_code::encode(const std::string& input, const std::string& out) const
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

std::vector<unsigned int> Huffman_code::decode(const std::string& input, const std::string& out) const
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
			result.push_back(result[0]);
			buffer = "";
		}
	}

	inputfile.close();
	outfile.close();

	return result;
}