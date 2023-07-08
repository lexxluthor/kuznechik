#ifndef KUZNECHIK_KUZNECHIK_H
#define KUZNECHIK_KUZNECHIK_H

#include "byte_block.h"


// Kuznechik cipher constants
static const byte Pi[256] = {
        252, 238, 221,  17, 207, 110,  49,  22, 251, 196, 250,
        218,  35, 197,   4,  77, 233, 119, 240, 219, 147,  46,
        153, 186,  23,  54, 241, 187,  20, 205,  95, 193, 249,
        24, 101,  90, 226,  92, 239,  33, 129,  28,  60,  66,
        139,   1, 142,  79,   5, 132,   2, 174, 227, 106, 143,
        160,   6,  11, 237, 152, 127, 212, 211,  31, 235,  52,
        44,  81, 234, 200,  72, 171, 242,  42, 104, 162, 253,
        58, 206, 204, 181, 112,  14,  86,   8,  12, 118,  18,
        191, 114,  19,  71, 156, 183,  93, 135,  21, 161, 150,
        41,  16, 123, 154, 199, 243, 145, 120, 111, 157, 158,
        178, 177,  50, 117,  25,  61, 255,  53, 138, 126, 109,
        84, 198, 128, 195, 189,  13,  87, 223, 245,  36, 169,
        62, 168,  67, 201, 215, 121, 214, 246, 124,  34, 185,
        3, 224,  15, 236, 222, 122, 148, 176, 188, 220, 232,
        40,  80,  78,  51,  10,  74, 167, 151,  96, 115,  30,
        0,  98,  68,  26, 184,  56, 130, 100, 159,  38,  65,
        173,  69,  70, 146,  39,  94,  85,  47, 140, 163, 165,
        125, 105, 213, 149,  59,   7,  88, 179,  64, 134, 172,
        29, 247,  48,  55, 107, 228, 136, 217, 231, 137, 225,
        27, 131,  73,  76,  63, 248, 254, 141,  83, 170, 144,
        202, 216, 133,  97,  32, 113, 103, 164,  45,  43,   9,
        91, 203, 155,  37, 208, 190, 229, 108,  82,  89, 166,
        116, 210, 230, 244, 180, 192, 209, 102, 175, 194,  57,
        75,  99, 182};

static const byte Pi_Inverse[256] = {
        165,  45,  50, 143,  14,  48,  56, 192,  84, 230, 158,
        57,  85, 126,  82, 145, 100,   3,  87,  90,  28,  96,
        7,  24,  33, 114, 168, 209,  41, 198, 164,  63, 224,
        39, 141,  12, 130, 234, 174, 180, 154,  99,  73, 229,
        66, 228,  21, 183, 200,   6, 112, 157,  65, 117,  25,
        201, 170, 252,  77, 191,  42, 115, 132, 213, 195, 175,
        43, 134, 167, 177, 178,  91,  70, 211, 159, 253, 212,
        15, 156,  47, 155,  67, 239, 217, 121, 182,  83, 127,
        193, 240,  35, 231,  37,  94, 181,  30, 162, 223, 166,
        254, 172,  34, 249, 226,  74, 188,  53, 202, 238, 120,
        5, 107,  81, 225,  89, 163, 242, 113,  86,  17, 106,
        137, 148, 101, 140, 187, 119,  60, 123,  40, 171, 210,
        49, 222, 196,  95, 204, 207, 118,  44, 184, 216,  46,
        54, 219, 105, 179,  20, 149, 190,  98, 161,  59,  22,
        102, 233,  92, 108, 109, 173,  55,  97,  75, 185, 227,
        186, 241, 160, 133, 131, 218,  71, 197, 176,  51, 250,
        150, 111, 110, 194, 246,  80, 255,  93, 169, 142,  23,
        27, 151, 125, 236,  88, 247,  31, 251, 124,   9,  13,
        122, 103,  69, 135, 220, 232,  79,  29,  78,   4, 235,
        248, 243,  62,  61, 189, 138, 136, 221, 205,  11,  19,
        152,   2, 147, 128, 144, 208,  36,  52, 203, 237, 244,
        206, 153,  16,  68,  64, 146,  58,   1,  38,  18,  26,
        72, 104, 245, 129, 139, 199, 214,  32,  10,   8,   0,
        76, 215, 116};

static const byte lin_coef[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
};

ByteBlock X(const ByteBlock &k, const ByteBlock &a);
ByteBlock S(const ByteBlock &a);
ByteBlock R(const ByteBlock &a);
ByteBlock L(const ByteBlock &a);
ByteBlock SInverse(const ByteBlock &a);
ByteBlock RInverse(const ByteBlock &ra);
ByteBlock LInverse(const ByteBlock &la);
ByteBlockTuple F(const ByteBlock &k, const ByteBlock &a, const ByteBlock &b);
ByteBlock Encrypt(const ByteBlockTuple &key, const ByteBlock &block);
ByteBlock Decrypt(const ByteBlockTuple &key, const ByteBlock &block);

class IterativeConstants
{
private:
    ByteBlock iter_C[32];
    ByteBlock iter_K[10];
public:
    IterativeConstants(const ByteBlock &k_1, const ByteBlock &k_2)
    {
        ByteBlockTuple tmp_iter1 = {k_1, k_2}, tmp_iter2{};

        ComputeC();

        iter_K[0] = k_1, iter_K[1] = k_2;

        for (int i = 0; i < 4; i++ )
        {
            for (int j = 0; j < 4; j++)
            {
                tmp_iter2 = F(iter_C[0 + 2*j + 8*i], tmp_iter1.FirstPart, tmp_iter1.SecondPart);
                tmp_iter1 = F(iter_C[1 + 2*j + 8*i], tmp_iter2.FirstPart, tmp_iter2.SecondPart);
            }
            iter_K[2*i + 2] = tmp_iter1.FirstPart;
            iter_K[2*i + 3] = tmp_iter1.SecondPart;
        }
    }
    void ComputeC()
    {
        // C_i=L(Vec_128(i)), i=1,2,...,32
        // Vec_s: Z_(2^s) -> V_s  bijective mapping that maps an element from
        //           ring Z_(2^s) into its binary representation, i.e., for an
        //           element z of the ring Z_(2^s), represented by the residue z_0
        //           + (2*z_1) + ... + (2^(s-1)*z_(s-1)), where z_i in {0, 1}, i =
        //           0, ..., n-1, the equality Vec_s(z) = z_(s-1)||...||z_1||z_0
        //           holds,
        int num_of_iter_C_keys = BLOCK_SIZE*2;
        ByteBlock iter_nums[num_of_iter_C_keys];

        for (int i = 0; i < num_of_iter_C_keys; i++)
        {
            for (int j = 0; j < BLOCK_SIZE; j++)
                iter_nums[i][j] = 0;
            iter_nums[i][0] = (byte)(i+1);
        }

        for (int i = 0; i < num_of_iter_C_keys; i++)
            iter_C[i] = L(iter_nums[i]);
    }
    ByteBlock getC(const int &x) const
    {
        if (x > 31 || x < 0)
            throw std::out_of_range("Iterative constants C[i] from range [0,31]");

        return iter_C[x];
    }
    ByteBlock getK(const int &x) const
    {
        if (x > 10 || x < 0)
            throw std::out_of_range("Iterative constants K[i] from range [0,10]");

        return iter_K[x];
    }
};


#endif //KUZNECHIK_KUZNECHIK_H