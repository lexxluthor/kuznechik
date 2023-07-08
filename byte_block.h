#ifndef KUZNECHIK_BYTE_BLOCK_H
#define KUZNECHIK_BYTE_BLOCK_H

#include <cstdint>
#include <ostream>
typedef uint8_t byte;

static const int BLOCK_SIZE = 16;

class ByteBlock
{
private:
    byte Block[BLOCK_SIZE];
public:
    ByteBlock() = default;
    explicit ByteBlock(const byte *n_block);
    explicit ByteBlock(const std::string &s);
    ByteBlock(const ByteBlock &other);

    byte& operator[](const int &x);
    byte operator[](const int &x) const;
    ByteBlock& operator=(const ByteBlock &other);
    friend std::ostream& operator<<(std::ostream &os, const ByteBlock &b);

    std::string ToString() const;
};

struct ByteBlockTuple {
    ByteBlock FirstPart;
    ByteBlock SecondPart;
};

#endif //KUZNECHIK_BYTE_BLOCK_H
