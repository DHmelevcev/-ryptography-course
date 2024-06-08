#include <limits>
#include <fstream>
#include "feistel_cipher.h"
#include "LFSR.h"

template<uint64_t ...f_agrs>
void feistel_cipher<f_agrs...>::cipher(const std::string& inputf, const std::string& outputf, const std::string& keyf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ifstream ks(keyf, std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);
	uint64_t key = 0;
	ks.read(reinterpret_cast<char*>(&key), sizeof(key));
	ks.close();

	uint64_t m, c;
	while (true) {
		is.read(reinterpret_cast<char*>(&m), sizeof(m));
		if (is.eof())
			break;
		c = cipher(m, key);
		os.write(reinterpret_cast<char*>(&c), sizeof(m));
	}
}

template<uint64_t ...f_agrs>
void feistel_cipher<f_agrs...>::decipher(const std::string& inputf, const std::string& outputf, const std::string& keyf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ifstream ks(keyf, std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);
	uint64_t key = 0;
	ks.read(reinterpret_cast<char*>(&key), sizeof(key));
	ks.close();

	uint64_t m, c;
	while (true) {
		is.read(reinterpret_cast<char*>(&m), sizeof(m));
		if (is.eof())
			break;
		c = decipher(m, key);
		os.write(reinterpret_cast<char*>(&c), sizeof(m));
	}
}

template<uint64_t ...f_agrs>
template<uint64_t first, uint64_t ...rest>
void feistel_cipher<f_agrs...>::cipher(const std::string& inputf, const std::string& outputf, const std::string& keyf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ifstream ks(keyf, std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);
	uint64_t key = 0;
	ks.read(reinterpret_cast<char*>(&key), sizeof(key));
	ks.close();

	uint64_t m, c;
	while (true) {
		is.read(reinterpret_cast<char*>(&m), sizeof(m));
		if (is.eof())
			break;
		c = cipher<first, rest...>(m, key);
		os.write(reinterpret_cast<char*>(&c), sizeof(m));
	}
}

template<uint64_t ...f_agrs>
template<uint64_t first, uint64_t ...rest>
void feistel_cipher<f_agrs...>::decipher(const std::string& inputf, const std::string& outputf, const std::string& keyf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ifstream ks(keyf, std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);
	uint64_t key = 0;
	ks.read(reinterpret_cast<char*>(&key), sizeof(key));
	ks.close();

	uint64_t m, c;
	while (true) {
		is.read(reinterpret_cast<char*>(&m), sizeof(m));
		if (is.eof())
			break;
		c = decipher<first, rest...>(m, key);
		os.write(reinterpret_cast<char*>(&c), sizeof(m));
	}
}

template<uint64_t ...f_agrs>
inline uint64_t feistel_cipher<f_agrs...>::cipher(uint64_t text, const uint64_t& key)
{
	for (uint32_t round = 0; round < number_of_rounds; ++round) {
		uint32_t key_i = static_cast<uint32_t>(key >> shift_per_round * round | key << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * round));

		text = ((text ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text >> CHAR_BIT * 4), key_i))) << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
	}

	return (text << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
}

template<uint64_t ...f_agrs>
inline uint64_t feistel_cipher<f_agrs...>::decipher(uint64_t text, const uint64_t& key)
{
	for (uint32_t round = number_of_rounds; round > 0; --round) {
		uint32_t key_i = static_cast<uint32_t>(key >> shift_per_round * (round - 1) | key << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * (round - 1)));

		text = ((text ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text >> CHAR_BIT * 4), key_i))) << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
	}

	return (text << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
}

template<uint64_t ...f_agrs>
template<uint64_t first, uint64_t ...rest>
inline uint64_t feistel_cipher<f_agrs...>::cipher(uint64_t text, const uint64_t& key)
{
	for (uint32_t round = 0; round < number_of_rounds; ++round) {
		LFSR<first, rest...> gen(key >> shift_per_round * round | key << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * round));

		text = ((text ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text >> CHAR_BIT * 4), gen.next_int()))) << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
	}

	return (text << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
}

template<uint64_t ...f_agrs>
template<uint64_t first, uint64_t ...rest>
inline uint64_t feistel_cipher<f_agrs...>::decipher(uint64_t text, const uint64_t& key)
{
	for (uint32_t round = number_of_rounds; round > 0; --round) {
		LFSR<first, rest...> gen(key >> shift_per_round * (round - 1) | key << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * (round - 1)));

		text = ((text ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text >> CHAR_BIT * 4), gen.next_int()))) << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
	}

	return (text << CHAR_BIT * 4) | (text >> CHAR_BIT * 4);
}

template<>
inline uint32_t feistel_cipher<>::F(const uint32_t& text, const uint32_t& key)
{
	return key;
}

template<uint64_t ...f_agrs>
inline uint32_t feistel_cipher<f_agrs...>::F(const uint32_t& text, const uint32_t& key)
{
	LFSR<f_agrs...> gen(key);

	return text ^ gen.next_int() ^ key;
}

template<uint64_t ...f_agrs>
void feistel_cipher<f_agrs...>::avalanche_test(const std::string& outputf, uint64_t text1, const uint64_t& key1, uint64_t text2, const uint64_t& key2)
{
	std::ofstream os(outputf);

	for (uint32_t round = 0; round < number_of_rounds; ++round) {
		uint32_t key1_i = static_cast<uint32_t>(key1 >> shift_per_round * round | key1 << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * round));
		text1 = ((text1 ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text1 >> CHAR_BIT * 4), key1_i))) << CHAR_BIT * 4) | (text1 >> CHAR_BIT * 4);

		uint32_t key2_i = static_cast<uint32_t>(key2 >> shift_per_round * round | key2 << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * round));
		text2 = ((text2 ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text2 >> CHAR_BIT * 4), key2_i))) << CHAR_BIT * 4) | (text2 >> CHAR_BIT * 4);

		uint64_t bits = 0;
		for (uint64_t res = text1 ^ text2; res;)
		{
			res &= res - 1;
			++bits;
		}

		os << round << '\t' << bits << '\n';
	}
}

template<uint64_t ...f_agrs>
template<uint64_t first, uint64_t ...rest>
void feistel_cipher<f_agrs...>::avalanche_test(const std::string& outputf, uint64_t text1, const uint64_t& key1, uint64_t text2, const uint64_t& key2)
{
	std::ofstream os(outputf);

	for (uint32_t round = 0; round < number_of_rounds; ++round) {
		LFSR<first, rest...> gen1(key1 >> shift_per_round * round | key1 << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * round));
		text1 = ((text1 ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text1 >> CHAR_BIT * 4), gen1.next_int()))) << CHAR_BIT * 4) | (text1 >> CHAR_BIT * 4);

		LFSR<first, rest...> gen2(key2 >> shift_per_round * round | key2 << (CHAR_BIT * sizeof(uint64_t) - shift_per_round * round));
		text2 = ((text2 ^ static_cast<uint64_t>(F(static_cast<uint32_t>(text2 >> CHAR_BIT * 4), gen2.next_int()))) << CHAR_BIT * 4) | (text2 >> CHAR_BIT * 4);

		uint64_t bits = 0;
		for (uint64_t res = text1 ^ text2; res;)
		{
			res &= res - 1;
			++bits;
		}

		os << round << '\t' << bits << '\n';
	}
}