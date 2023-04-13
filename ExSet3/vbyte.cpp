#include <fstream>
#include <iostream>
#include "include/vb.hpp"
#include <cstdint>
#include <chrono>

template <typename T>
void process(bool diffed, bool timed, uint64_t k, std::istream &in)
{
    std::uint64_t n;

    std::chrono::_V2::system_clock::time_point start;

    in.read(reinterpret_cast<char *>(&n), 8);

    if (!in.good())
    {
        std::cout << "stream not so good" << errno << std::endl;
        return;
    }

    if (n == 0)
    {
        exit(0);
    }

    if (timed)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    // data structure :^)
    pfp::vb<T> vb(k, diffed);

    // input bits
    std::uint64_t val;
    for (std::uint64_t i = 0; i < n; i++)
    {
        in.read(reinterpret_cast<char *>(&val), 8);

        vb.encode(val);
    }

    if (timed)
    {
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        std::cerr << std::fixed << duration.count() << " s" << std::endl;
        start = std::chrono::high_resolution_clock::now();
    }

    // output
    vb.printDecodeAll();

    if (timed)
    {
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        std::cerr << std::fixed << duration.count() << " s" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    int input_file = -1;
    bool timed = false;
    bool diffed = false;
    uint64_t k = 7;

    for (int i = 1; i < argc; i++)
    {
        std::string s(argv[i]);
        std::string p(argv[i - 1]);
        if (s == "-t")
        {
            timed = true;
        }
        else if (s == "-s")
        {
            diffed = true;
        }
        else if (s == "-k")
        {
            continue;
        }
        else if (p == "-k")
        {
            k = std::stoi(s);
        }
        else
        {
            input_file = i;
        }
    }

    if (input_file > 0)
    {
        // std::cout << "reading file: " << argv[input_file] << std::endl;
        std::ifstream in(argv[input_file], std::ios::binary);
        if (!in.good())
        {
            std::cout << "failed to open file" << std::endl;
            exit(-1);
        }

        // fuck c++ honestly
        if (k < 8)
        {
            process<uint8_t>(diffed, timed, k, in);
        }
        else if (k < 16)
        {
            process<uint16_t>(diffed, timed, k, in);
        }
        else if (k < 32)
        {
            process<uint32_t>(diffed, timed, k, in);
        }
        else if (k < 64)
        {
            process<uint64_t>(diffed, timed, k, in);
        }
    }
    else
    {
        if (k < 8)
        {
            process<uint8_t>(diffed, timed, k, std::cin);
        }
        else if (k < 16)
        {
            process<uint16_t>(diffed, timed, k, std::cin);
        }
        else if (k < 32)
        {
            process<uint32_t>(diffed, timed, k, std::cin);
        }
        else if (k < 64)
        {
            process<uint64_t>(diffed, timed, k, std::cin);
        }
    }

    return 0;
}