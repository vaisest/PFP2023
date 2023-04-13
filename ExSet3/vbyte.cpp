#include <fstream>
#include <iostream>
#include "include/vb.hpp"
#include <cstdint>
#include <chrono>

// template <class DS>
void process(bool diffed, bool timed, std::istream &in)
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
    pfp::vb vb;

    // input bits
    std::uint64_t val;
    std::uint64_t last;
    for (std::uint64_t i = 0; i < n; i++)
    {
        in.read(reinterpret_cast<char *>(&val), 8);
        vb.encode(val);
        last = val;
    }

    vb.printDecodeAll();

    if (timed)
    {
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        std::cerr << std::fixed << duration.count() << " s" << std::endl;
        start = std::chrono::high_resolution_clock::now();
    }

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

    for (int i = 1; i < argc; i++)
    {
        std::string s(argv[i]);
        if (s == "-t")
        {
            timed = true;
        }
        else if (s == "-s")
        {
            diffed = true;
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

        process(diffed, timed, in);
    }
    else
    {
        process(diffed, timed, std::cin);
    }

    return 0;
}