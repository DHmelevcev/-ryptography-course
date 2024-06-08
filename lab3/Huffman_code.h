#pragma once
#include <fstream>
#include <map>
#include <queue>
#include <bitset>
#include <string>

class Huffman_code
{
public:
	bool generate_code(const std::string& filename);

	std::string code_to_string() const;

	unsigned int encode(const std::string& input, const std::string& out) const;

	std::vector<unsigned int> decode(const std::string& input, const std::string& out) const;

	inline std::map<char, double> get_frequencies() const
	{
		return _frequencies;
	}

private:
	std::map<char, std::string> _code;
	std::map<std::string, char> _reverse_code;
	std::map<char, double> _frequencies;
};