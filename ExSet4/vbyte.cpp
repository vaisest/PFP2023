#include <fstream>
#include <iostream>
#include "include/vb.hpp"
#include <cstdint>
#include <chrono>

void process(bool naive, bool timed, std::istream &in)
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
    std::uint64_t q;
    uint64_t idx;
    in.read(reinterpret_cast<char *>(&q), 8);

    for (uint64_t i = 0; i < n; i++)
    {
        in.read(reinterpret_cast<char *>(&idx), 8);

        if (naive)
        {
            vb.scan(idx);
        }
        else
        {
            vb.sum(idx);
        }
    }

    if (timed)
    {
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        std::cerr << std::fixed << duration.count() << " s" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    // i am speed
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int input_file = -1;
    bool timed = false;
    bool naive = false;

    for (int i = 1; i < argc; i++)
    {
        std::string s(argv[i]);
        if (s == "-t")
        {
            timed = true;
        }
        else if (s == "-n")
        {
            naive = true;
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

        process(naive, timed, in);
    }
    else
    {
        process(naive, timed, std::cin);
    }

    return 0;
}