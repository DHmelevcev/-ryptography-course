#pragma once
#include <string>

using uint64_t = unsigned long long;
using uint32_t = unsigned int;

template<uint64_t ...f_agrs>
class feistel_cipher
{	
private:
	static const uint32_t number_of_rounds = 16;
	static const uint32_t shift_per_round = 1;

public:
	static void cipher(const std::string& inputf, const std::string& outputf, const std::string& keyf);

	static void decipher(const std::string& inputf, const std::string& outputf, const std::string& keyf);

	template<uint64_t first, uint64_t ...rest>
	static void cipher(const std::string& inputf, const std::string& outputf, const std::string& keyf);

	template<uint64_t first, uint64_t ...rest>
	static void decipher(const std::string& inputf, const std::string& outputf, const std::string& keyf);

	static void avalanche_test(const std::string& outputf, uint64_t text1, const uint64_t& key1, uint64_t text2, const uint64_t& key2);

	template<uint64_t first, uint64_t ...rest>
	static void avalanche_test(const std::string& outputf, uint64_t text1, const uint64_t& key1, uint64_t text2, const uint64_t& key2);

private:
	static uint64_t cipher(uint64_t text, const uint64_t& key);

	static uint64_t decipher(uint64_t text, const uint64_t& key);

	template<uint64_t first, uint64_t ...rest>
	static uint64_t cipher(uint64_t text, const uint64_t& key);

	template<uint64_t first, uint64_t ...rest>
	static uint64_t decipher(uint64_t text, const uint64_t& key);

private:
	static uint32_t F(const uint32_t& text, const uint32_t& key);
};