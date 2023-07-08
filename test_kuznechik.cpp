#include <cassert>
#include <iostream>
#include "kuznechik.h"


void TestTransformPi()
{
    for (int i = 0; i < 256; i++)
        assert(Pi[Pi_Inverse[i]] == i && "Pi(Pi_Inverse) != Id");
}

void TestTransformationS()
{
    int test_samples_size = 4;
    std::string s, sinv;

    std::string test_strings[] =
            {"ffeeddccbbaa99881122334455667700", "b66cd8887d38e8d77765aeea0c9a7efc",
             "559d8dd7bd06cbfe7e7b262523280d39", "0c3322fed531e4630d80ef5c5a81c50b" };
    std::string expected_strings[] =
            {"b66cd8887d38e8d77765aeea0c9a7efc", "559d8dd7bd06cbfe7e7b262523280d39",
             "0c3322fed531e4630d80ef5c5a81c50b", "23ae65633f842d29c5df529c13f5acda"};

    for (int i = 0; i < test_samples_size; i++)
    {
        s = S(ByteBlock(test_strings[i])).ToString();
        sinv = SInverse(ByteBlock(expected_strings[i])).ToString();

        assert(s == expected_strings[i] && "Transformation S test failed");
        assert(sinv == test_strings[i] && "Transformation SInverse test failed");
    }
}

void TestTransformationR()
{
    int test_samples_size = 4;
    std::string s, sinv;

    std::string test_strings[] =
            {"00000000000000000000000000000100", "94000000000000000000000000000001",
             "a5940000000000000000000000000000", "64a59400000000000000000000000000" };
    std::string expected_strings[] =
            {"94000000000000000000000000000001", "a5940000000000000000000000000000",
             "64a59400000000000000000000000000", "0d64a594000000000000000000000000" };

    for (int i = 0; i < test_samples_size; i++)
    {
        s = R(ByteBlock(test_strings[i])).ToString();
        sinv = RInverse(ByteBlock(expected_strings[i])).ToString();

        assert(s == expected_strings[i] && "Transformation R test failed");
        assert(sinv == test_strings[i] && "Transformation RInverse test failed");
    }
}

void TestTransformationL()
{
    int test_samples_size = 4;
    std::string s, sinv;

    std::string test_strings[] =
            {"64a59400000000000000000000000000", "d456584dd0e3e84cc3166e4b7fa2890d",
             "79d26221b87b584cd42fbc4ffea5de9a", "0e93691a0cfc60408b7b68f66b513c13" };
    std::string expected_strings[] =
            {"d456584dd0e3e84cc3166e4b7fa2890d", "79d26221b87b584cd42fbc4ffea5de9a",
             "0e93691a0cfc60408b7b68f66b513c13", "e6a8094fee0aa204fd97bcb0b44b8580"};

    for (int i = 0; i < test_samples_size; i++)
    {
        s = L(ByteBlock(test_strings[i])).ToString();
        sinv = LInverse(ByteBlock(expected_strings[i])).ToString();

        assert(s == expected_strings[i] && "Transformation L test failed");
        assert(sinv == test_strings[i] && "Transformation LInverse test failed");
    }
}

void TestComputeC()
{
    int test_samples_size = 8;
    std::string K = "8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef",
    s, fck_0, fck_1;
    ByteBlock K_1 = ByteBlock(K.substr(0, 32)), K_2 = ByteBlock(K.substr(32, 64));
    ByteBlockTuple tmp_tuple{};

    IterativeConstants IterConsts(K_1, K_2);

    std::string test_C[] = {
            "6ea276726c487ab85d27bd10dd849401", "dc87ece4d890f4b3ba4eb92079cbeb02",
            "b2259a96b4d88e0be7690430a44f7f03", "7bcd1b0b73e32ba5b79cb140f2551504",
            "156f6d791fab511deabb0c502fd18105", "a74af7efab73df160dd208608b9efe06",
            "c9e8819dc73ba5ae50f5b570561a6a07", "f6593616e6055689adfba18027aa2a08"
    };
    std::string test_XCK = "e63bdcc9a09594475d369f2399d1f276", test_SXCK = "0998ca37a7947aabb78f4a5ae81b748a",
        test_LSX = "3d0940999db75d6a9257071d5e6144a6";
    std::string test_FCK[][2] ={
            {"c3d5fa01ebe36f7a9374427ad7ca8949", "8899aabbccddeeff0011223344556677"},
            {"37777748e56453377d5e262d90903f87", "c3d5fa01ebe36f7a9374427ad7ca8949"},
            {"f9eae5f29b2815e31f11ac5d9c29fb01", "37777748e56453377d5e262d90903f87"},
            {"e980089683d00d4be37dd3434699b98f", "f9eae5f29b2815e31f11ac5d9c29fb01"},
            {"b7bd70acea4460714f4ebe13835cf004", "e980089683d00d4be37dd3434699b98f"},
            {"1a46ea1cf6ccd236467287df93fdf974", "b7bd70acea4460714f4ebe13835cf004"},
            {"3d4553d8e9cfec6815ebadc40a9ffd04", "1a46ea1cf6ccd236467287df93fdf974"},
            {"db31485315694343228d6aef8cc78c44", "3d4553d8e9cfec6815ebadc40a9ffd04"}
    };
    std::string test_K[] = {
            "8899aabbccddeeff0011223344556677", "fedcba98765432100123456789abcdef",
            "db31485315694343228d6aef8cc78c44", "3d4553d8e9cfec6815ebadc40a9ffd04",
            "57646468c44a5e28d3e59246f429f1ac", "bd079435165c6432b532e82834da581b",
            "51e640757e8745de705727265a0098b1", "5a7925017b9fdd3ed72a91a22286f984",
            "bb44e25378c73123a5f32f73cdb6e517", "72e9dd7416bcf45b755dbaa88e4a4043"
    };

    // Test entire 1 round
    s = X(IterConsts.getC(0), IterConsts.getK(0)).ToString();
    assert(s == test_XCK && "X[C][K1] test failed. Values does not match");

    s = S(ByteBlock(s)).ToString();
    assert(s == test_SXCK && "SX[C][K1] test failed. Values does not match");

    s = L( ByteBlock(s)).ToString();
    assert(s == test_LSX && "LSX[C][K1] test failed. Values does not match");

    for (int i = 0; i < 10; i++)
        assert(IterConsts.getK(i).ToString() == test_K[i] && "Iterative K_i test failed. Values does not match");


    fck_0 = IterConsts.getK(0).ToString();
    fck_1 = IterConsts.getK(1).ToString();

    for (int i = 0; i <test_samples_size; i++)
    {
        assert(IterConsts.getC(i).ToString() == test_C[i] && "Iterative C test failed. Values does not match");

        tmp_tuple = F(IterConsts.getC(i), ByteBlock(fck_0), ByteBlock(fck_1));
        fck_0 = tmp_tuple.FirstPart.ToString();
        fck_1 = tmp_tuple.SecondPart.ToString();

        assert(fck_0 == test_FCK[i][0] && fck_1 == test_FCK[i][1] && "FCK test failed. Values does not match");
    }

}

void TestEncryption()
{
    std::string K = "8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef", s;
    ByteBlockTuple key{ByteBlock(K.substr(0, 32)), ByteBlock(K.substr(32, 64))};
    IterativeConstants IterConsts(key.FirstPart, key.SecondPart);

    ByteBlock text("1122334455667700ffeeddccbbaa9988");
    ByteBlock ciphertext("7f679d90bebc24305a468d42b9d4edcd");

    std::string test_X = "99bb99ff99bb99ffffffffffffffffff", test_SX = "e87de8b6e87de8b6b6b6b6b6b6b6b6b6";
    std::string test_LSX[9] = {
            "e297b686e355b0a1cf4a2f9249140830","285e497a0862d596b36f4258a1c69072",
            "0187a3a429b567841ad50d29207cc34e","ec9bdba057d4f4d77c5d70619dcad206",
            "1357fd11de9257290c2a1473eb6bcde1","28ae31e7d4c2354261027ef0b32897df",
            "07e223d56002c013d3f5e6f714b86d2d","cd8ef6cd97e0e092a8e4cca61b38bf65",
            "0d8e40e4a800d06b2f1b37ea379ead8e"
    };

    s = X(IterConsts.getK(0), text).ToString();
    assert(s == test_X && "Encrypt test failed. X returns wrong value");

    s = S(ByteBlock(s)).ToString();
    assert(s == test_SX && "Encrypt test failed. Function SX returns wrong value");

    s = text.ToString();
    for (int i = 0; i < 9; i++) {
        s = L(S(X(IterConsts.getK(i), ByteBlock(s)))).ToString();
        assert(s == test_LSX[i] && "Encrypt test failed. Function LSX returns wrong value");
    }

    s = X(IterConsts.getK(9), ByteBlock(s)).ToString();
    assert(Encrypt(key, text).ToString() == ciphertext.ToString() && Encrypt(key, text).ToString() == s && "Encrypt test failed. Result of encryption is wrong");
}

void TestDecryption()
{
    std::string K = "8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef", s;
    ByteBlockTuple key{ByteBlock(K.substr(0, 32)), ByteBlock(K.substr(32, 64))};
    IterativeConstants IterConsts(key.FirstPart, key.SecondPart);

    ByteBlock text("1122334455667700ffeeddccbbaa9988");
    ByteBlock ciphertext("7f679d90bebc24305a468d42b9d4edcd");

    std::string test_X = "0d8e40e4a800d06b2f1b37ea379ead8e", test_LIX = "8a6b930a52211b45c5baa43ff8b91319";
    std::string test_SILIX[9] = {
            "76ca149eef27d1b10d17e3d5d68e5a72", "5d9b06d41b9d1d2d04df7755363e94a9",
            "79487192aa45709c115559d6e9280f6e", "ae506924c8ce331bb918fc5bdfb195fa",
            "bbffbfc8939eaaffafb8e22769e323aa", "3cc2f07cc07a8bec0f3ea0ed2ae33e4a",
            "f36f01291d0b96d591e228b72d011c36", "1c4b0c1e950182b1ce696af5c0bfc5df",
            "99bb99ff99bb99ffffffffffffffffff"
    };

    s = X(IterConsts.getK(9), ciphertext).ToString();
    assert(s == test_X && "Decrypt test failed. X returns wrong value");

    s = LInverse(ByteBlock(s)).ToString();
    assert(s == test_LIX && "Decrypt test failed. Function SX returns wrong value");

    s = ciphertext.ToString();
    for (int i = 8; i >= 0; i--) {
        s = SInverse( LInverse(X(IterConsts.getK(i+1), ByteBlock(s)))).ToString();
        assert(s == test_SILIX[8-i] && "Decrypt test failed. Function XS^-1L^-1 returns wrong value");
    }

    s = X(IterConsts.getK(0), ByteBlock(s)).ToString();
    assert(Decrypt(key, ciphertext).ToString() == text.ToString() && Decrypt(key, ciphertext).ToString() == s && "Decrypt test failed. Result of encryption is wrong");
}

int main()
{
    TestTransformPi();
    TestTransformationS();
    TestTransformationR();
    TestTransformationL();
    TestComputeC();
    TestEncryption();
    TestDecryption();

    std::cout << "All tests have been successfully passed" << std::endl;
    return 0;
}