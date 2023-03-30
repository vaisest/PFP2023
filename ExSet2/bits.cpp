#include <fstream>
#include <iostream>
#include "include/barray.hpp"

// template <class query_structure>
void process(int mode, std::istream &in)
{
    unsigned long long val;
    unsigned long long bitCount;
    unsigned long long m;

    in >> bitCount;
    in >> m;
    std::cout << bitCount << "/" << m << std::endl;

    pfp::bit_array ba(bitCount);

    for (unsigned long long i = 0; i < bitCount; i++)
    {
        in >> val;
        std::cout << val << "/" << std::endl;
        ba.set(val);
    }

    for (unsigned long long i = 0; i < bitCount; i++)
    {
        in >> val;
        std::cout << ba.get(val) << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    int i = 1;
    int input_file = -1;
    int mode = -1;
    while (i < argc)
    {
        std::string s(argv[i++]);
        if (s.compare("-b") == 0)
        {
            mode = 1;
        }
        else
        {
            input_file = i - 1;
        }
        i++;
    }

    if (input_file > 0)
    {
        std::ifstream in(argv[input_file]);
        process(mode, in);
    }
    else
    {
        process(mode, std::cin);
    }

    return 0;
}