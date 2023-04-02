#include <fstream>
#include <iostream>
#include "include/barray.hpp"
#include "include/parray.hpp"
#include <cstdint>
#include <chrono>

void process(bool summed, bool timed, bool located, bool packed, std::istream &in)
{
    std::uint64_t val;
    std::uint64_t entryCount;
    std::uint64_t bits;

    std::chrono::_V2::system_clock::time_point start;

    in.read(reinterpret_cast<char *>(&entryCount), 8);
    in.read(reinterpret_cast<char *>(&bits), 8);

    std::cout << "entries: " << entryCount << ", bits: " << bits << std::endl;

    if (!in.good())
    {
        std::cout << "stream not so good" << errno << std::endl;
        return;
    }

    if (entryCount == 0)
    {
        exit(0);
    }

    pfp::bit_array ba(entryCount);
    pfp::packed_array pa(bits, entryCount);

    if (timed)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    // input bits
    for (std::uint64_t i = 0; i < entryCount; i++)
    {
        in.read(reinterpret_cast<char *>(&val), 8);
        if (packed)
        {
            pa.append(val);
        }
        else
        {
            ba.set(val);
        }
    }

    if (timed)
    {
        std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - start;
        std::cerr << std::fixed << duration.count() << " s" << std::endl;
        start = std::chrono::high_resolution_clock::now();
    }

    // query bits
    for (std::uint64_t i = 0; i < entryCount; i++)
    {
        in.read(reinterpret_cast<char *>(&val), 8);
        if (summed)
        {
            std ::cout << ba.sum(val) << std::endl;
        }
        else if (located)
        {
            std::cout << ba.location(val) << std::endl;
        }
        else if (packed)
        {
            std::cout << pa.get(val) << std::endl;
        }
        else
        {
            std::cout << ba.get(val) << std::endl;
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
    int input_file = -1;
    bool timed = false;
    bool summed = false;
    bool located = false;
    bool packed = false;

    for (int i = 1; i < argc; i++)
    {
        std::string s(argv[i]);
        if (s == "-b")
        {
            // mode = 1;
        }
        else if (s == "-t")
        {
            timed = true;
        }
        else if (s == "-s")
        {
            summed = true;
        }
        else if (s == "-l")
        {
            located = true;
        }
        else if (s == "-i")
        {
            packed = true;
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
        process(summed, timed, located, packed, in);
    }
    else
    {
        process(summed, timed, located, packed, std::cin);
    }

    return 0;
}