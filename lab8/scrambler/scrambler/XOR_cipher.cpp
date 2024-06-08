#pragma once
#include <fstream>
#include <random>
#include "XOR_cipher.h"
#include "LFSR.h"

template<uint64_t...>
void XOR_cipher::cipher1(const std::string& inputf, const std::string& outputf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ofstream ks(outputf + ".key.txt", std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);

	std::mt19937 gen{ std::random_device()() };

	unsigned char c, k;
	while (true) {
		is >> std::noskipws >> c;
		if (is.eof())
			break;
		k = static_cast<char>(gen());
		ks << k;
		os << static_cast<char>(c ^ k);
	}
}

template<uint64_t...>
void XOR_cipher::decipher1(const std::string& inputf, const std::string& outputf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ifstream ks(inputf + ".key.txt", std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);

	unsigned char c, k;
	while (true) {
		is >> std::noskipws >> c;
		if (is.eof())
			break;
		ks >> std::noskipws >> k;
		os << static_cast<char>(c ^ k);
	}
}

template<uint64_t first, uint64_t ...rest>
void XOR_cipher::cipher2(const std::string& inputf, const std::string& outputf, const std::string& seedf)
{
	std::ifstream is(inputf, std::ios::binary);
	std::ifstream ss(seedf, std::ios::binary);
	std::ofstream os(outputf, std::ios::binary);
	uint64_t seed = 0;
	ss >> seed;
	ss.close();

	LFSR<first, rest...> generator(seed);

	unsigned char c, k;
	while (true) {
		is >> std::noskipws >> c;
		if (is.eof())
			break;
		k = generator.next_byte();
		//std::cout << std::hex << static_cast<uint16_t>(k);
		os << static_cast<char>(c ^ k);
	}
}