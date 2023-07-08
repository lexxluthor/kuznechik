#include "kuznechik.h"

ByteBlock X(const ByteBlock &k, const ByteBlock &a)
{
    // X[k](a)=k(xor)a
    ByteBlock c{};

    for (int i = 0; i < BLOCK_SIZE; i++)
        c[i] = k[i] ^ a[i];

    return c;
}

ByteBlock S(const ByteBlock &a)
{
    // S(a)=(a_15||...||a_0)=pi(a_15)||...||pi(a_0)
    ByteBlock sa{};

    for (int i = BLOCK_SIZE - 1; i >=0; i--)
        sa[i] = Pi[int(a[i])];

    return sa;
}

byte GaluaFieldMult(byte a, byte b)
{
    byte c = 0;
    int high_bit;

    for (int i = 0; i < 8; i++)
    {
        if ((b&1) == 1)
            c ^= a;
        high_bit = a & 0x80; // 2**7 = 128 = 0x80
        a <<= 1;
        if (high_bit)
            a ^= 0xc3; // polynomial x^8 + x^7 + x^6 + x + 1 = 451 % 256 = 195
        b >>= 1;
    }

    return c;
}

ByteBlock R(const ByteBlock &a)
{
    // R(a_15||...||a_0)=l(a_15,...,a_0)||a_15||...||a_1
    byte l = 0;
    ByteBlock ra{};

    for (int i = BLOCK_SIZE - 1; i >= 0; i--)
    {
        l ^= GaluaFieldMult(a[i], lin_coef[i]);

        if (i != 0)
            ra[i-1] = a[i];
        else
            ra[BLOCK_SIZE-1] = l;
    }
    return ra;
}

ByteBlock L(const ByteBlock &a)
{
    // L(a)=R^(16)(a)
    ByteBlock la = a;

    for (int i = 0; i < BLOCK_SIZE; i++)
        la = R(la);

    return la;
}

ByteBlock SInverse(const ByteBlock &a)
{
    // S^-1(a)=(a_15||...||a_0)=pi^-1(a_15)||...||pi^-1(a_0)
    ByteBlock sa{};

    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        int data = a[i];
        data = (data > 0) ? data : data + 256;
        sa[i] = Pi_Inverse[data];
    }

    return sa;
}

ByteBlock RInverse(const ByteBlock &ra)
{
    // R^(-1)(a_15||...||a_0)=a_14||a_13||...||a_0||l(a_14,a_13,...,a_0,a_15)
    ByteBlock a{};
    byte l = ra[BLOCK_SIZE-1];

    for (int i = BLOCK_SIZE - 1; i >= 0; i--)
    {
        a[i] = (i == 0) ? l : ra[i-1];
        l ^= GaluaFieldMult(a[i], lin_coef[i]);
    }

    return a;
}

ByteBlock LInverse(const ByteBlock &la)
{
    // L^(-1)(a)=(R^(-1))^(16)(a)
    ByteBlock a = la;

    for (int i = 0; i < BLOCK_SIZE; i++)
        a = RInverse(a);

    return a;
}

ByteBlockTuple F(const ByteBlock &k, const ByteBlock &a, const ByteBlock &b)
{
    // F[k](a_1,a_0)=(LSX[k](a_1)(xor)a_0,a_1)
    ByteBlockTuple key{};

    ByteBlock lsx = L(S(X(k, a)));
    key.FirstPart = X(lsx, b);
    key.SecondPart = a;

    return key;
}

ByteBlock Encrypt(const ByteBlockTuple &key, const ByteBlock &block)
{
    ByteBlock k_1 = key.FirstPart, k_2 = key.SecondPart;
    ByteBlock ciphered_block = block;
    IterativeConstants IterConsts(k_1, k_2);

    for (int i = 0; i < 9; i++)
        ciphered_block = L(S(X(IterConsts.getK(i), ciphered_block)));

    ciphered_block = X(IterConsts.getK(9), ciphered_block);

    return ciphered_block;
}

ByteBlock Decrypt(const ByteBlockTuple &key, const ByteBlock &ciphered_block)
{
    ByteBlock k_1 = key.FirstPart, k_2 = key.SecondPart;
    ByteBlock block = ciphered_block;
    IterativeConstants IterConsts(k_1, k_2);

    block = X(IterConsts.getK(9), block);

    for (int i = 8; i >= 0; i--) {
        block = X(IterConsts.getK(i), SInverse(LInverse(block)));
    }

    return block;
}