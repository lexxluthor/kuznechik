#include <stdexcept>
#include <iomanip>

#include "byte_block.h"


ByteBlock::ByteBlock(const byte *n_block)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        Block[i] = n_block[i];
}

ByteBlock::ByteBlock(const ByteBlock &other)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        Block[i] = other.Block[i];
}

ByteBlock::ByteBlock(const std::string &s)
{
    byte b;

    if (s.length() != BLOCK_SIZE*2)
        throw std::length_error("ByteBlock initialized only from strings with length BLOCK_SIZE*2");

    for (int i = 0; i < BLOCK_SIZE*2; i+=2)
    {
        b = static_cast<byte>(std::stoi(s.substr(i, 2), nullptr, 16));
        Block[BLOCK_SIZE-1-i/2] = b;
    }
}

byte& ByteBlock::operator[](const int &x)
{
    if (x >= BLOCK_SIZE || x < 0)
        throw std::invalid_argument("ByteBlock index must be in range [0, BLOCK_SIZE-1]");

    return Block[x];
}

byte ByteBlock::operator[](const int &x) const
{
    if (x >= BLOCK_SIZE || x < 0)
        throw std::invalid_argument("ByteBlock index must be in range [0, BLOCK_SIZE-1]");

    return Block[x];
}

ByteBlock& ByteBlock::operator=(const ByteBlock &other)
{
    if (this != &other)
    {
        for (int i = 0; i < BLOCK_SIZE; i++)
            Block[i] = other.Block[i];
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const ByteBlock &b)
{
    os << b.ToString();
    return os;
}

std::string ByteBlock::ToString() const
{
    std::stringstream stream;

    for (int i = BLOCK_SIZE - 1; i >= 0; --i)
        stream << std::setfill('0') << std::setw(2) << std::hex << int(this->Block[i]);

    return stream.str();
}
