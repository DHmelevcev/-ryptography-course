#pragma once
#include<vector>
#include<fstream>

class Vigenere_cipher
{
public:
	Vigenere_cipher(const std::string& keyfile);

	bool cipher(const std::string& input, const std::string& output) const;
	bool decipher(const std::string& input, const std::string& output) const;
	std::string get_key() const;

private:
	std::vector<char> _key;
};