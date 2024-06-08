#pragma once
#include <fstream>
#include <map>
#include <bitset>
#include <vector>
#include <string>

class Hamming_code
{
public:
	Hamming_code();

	std::string code_to_string() const;

	unsigned int encode(const std::string& input, const std::string& out) const;

	std::vector<unsigned int> decode(const std::string& input, const std::string& out) const;

private:
	void generate_code();

	unsigned short _n;
	unsigned short _k;
	unsigned short _r;
	std::vector<unsigned short> _generative_matrix;
	std::vector<unsigned short> _check_matrix;
	std::map<char, std::string> _code;
	std::map<std::string, char> _reverse_code;
};