#pragma once
#include <vector>

using byte_array = std::vector<unsigned char>;

enum class ModeType {
    ENCRYPT = 1,
    DECRYPT = 2,
    EXIT = 0
};

enum class CipherType {
    ATBASH = 1,
    AFFINE = 2,
    XOR = 3
};
