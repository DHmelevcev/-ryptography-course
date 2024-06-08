#pragma once
#include <string>

class XOR_cipher
{
public:
	template<uint64_t...>
	static void cipher1(const std::string& inputf, const std::string& outputf);

	template<uint64_t...>
	static void decipher1(const std::string& inputf, const std::string& outputf);
	
	template<uint64_t first, uint64_t ...rest>
	static void cipher2(const std::string& inputf, const std::string& outputf, const std::string& seedf);
};