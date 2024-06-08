#include "Vigenere_cipher.h"

const char zero = '@';
const char delimer = '_';
const char begin = 'A';
const char end = 'Z';
constexpr int range = end - begin + 2;

bool is_empty(std::ifstream& file)
{
    return file.peek() == std::ifstream::traits_type::eof();
}

Vigenere_cipher::Vigenere_cipher(const std::string& keyfile)
{
    std::ifstream inputfile(keyfile);
    if (is_empty(inputfile))
    {
        throw 0;
    }

    while (!is_empty(inputfile))
    {
        char symb;
        inputfile >> symb;
        if (!inputfile)
            break;
        if (symb == delimer)
            symb = zero;
        else if (symb < begin || symb > end)
            throw 1;
        _key.emplace_back(symb);
    }

    inputfile.close();
}

bool Vigenere_cipher::cipher(const std::string& input, const std::string& out) const
{
    std::ifstream inputfile(input);
    std::ofstream outfile(out);

    if (is_empty(inputfile))
    {
        return false;
    }

    auto it = _key.begin();
    while (!is_empty(inputfile))
    {
        char symb;
        inputfile >> symb;
        if (symb == delimer)
            symb = zero;
        else if (symb < begin || symb > end)
            throw 1;
        symb = char((symb - zero + *it++ - zero) % range + zero);
        if (symb == zero)
            symb = delimer;
        outfile << symb;
        it = it == _key.end() ? _key.begin() : it;
    }

    inputfile.close();
    outfile.close();

    return true;
}

bool Vigenere_cipher::decipher(const std::string& input, const std::string& out) const
{
    std::ifstream inputfile(input);
    std::ofstream outfile(out);

    if (is_empty(inputfile))
    {
        return false;
    }

    auto it = _key.begin();
    while (!is_empty(inputfile))
    {
        char symb;
        inputfile >> symb;
        if (symb == delimer)
            symb = zero;
        else if (symb < begin || symb > end)
            throw 1;
        symb = char((symb - *it++ + range) % range + zero);
        if (symb == zero)
            symb = delimer;
        outfile << symb;
        it = it == _key.end() ? _key.begin() : it;
    }

    inputfile.close();
    outfile.close();

    return true;
}

std::string Vigenere_cipher::get_key() const
{
    std::string result;
    for (auto ch : _key)
    {
        if (ch == zero)
            ch = delimer;
        result += ch;
    }
    return result;
}