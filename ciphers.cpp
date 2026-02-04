#include <iostream>
#include "types.hpp"

using namespace std;

static unsigned char ModInverse256(unsigned char a) {
    for (int i = 1; i < 256; i++) {
        if ((a * i) % 256 == 1) {
            return static_cast<unsigned char>(i);
        }
    }
    return 0;
}

byte_array Atbash(const byte_array& text) {
    cout << "Процесс запущен!" << endl;
    cout << "Прогресс: ";
    size_t one_block = text.size() / 10;
    size_t progress = 0;
    byte_array result(text.size());
    for (size_t i = 0; i < text.size(); i++) {
        result[i] = static_cast<unsigned char>(255 - text[i]);
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return result;
}

byte_array AffineEncrypt(const byte_array& plain_text, const byte_array& key) {
    cout << "Процесс запущен!" << endl;
    cout << "Прогресс: ";
    const unsigned char a = key[0];
    const unsigned char b = key[1];
    size_t one_block = plain_text.size() / 10;
    size_t progress = 0;
    byte_array cipher_text(plain_text.size());
    for (size_t i = 0; i < plain_text.size(); i++) {
        cipher_text[i] = static_cast<unsigned char>((a * plain_text[i] + b) % 256);
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return cipher_text;
}

byte_array AffineDecrypt(const byte_array& cipher_text, const byte_array& key) {
    cout << "Запущено дешифрование!" << endl;
    cout << "Прогресс: ";
    const unsigned char a = key[0];
    const unsigned char b = key[1];
    const unsigned char a_inv = ModInverse256(a);
    size_t one_block = cipher_text.size() / 10;
    size_t progress = 0;
    byte_array plain_text(cipher_text.size());
    for (size_t i = 0; i < cipher_text.size(); i++) {
        plain_text[i] = static_cast<unsigned char>((a_inv * (256 + cipher_text[i] - b)) % 256);
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Дешифрование успешно завершено!" << endl;
    return plain_text;
}

byte_array XorCipher(const byte_array& first_text, const byte_array& key) {
    cout << "Процесс запущен!" << endl;
    cout << "Прогресс: ";
    size_t one_block = first_text.size() / 10;
    size_t progress = 0;
    byte_array second_text(first_text.size());
    for (size_t i = 0; i < first_text.size(); i++) {
        second_text[i] = first_text[i] ^ key[i % key.size()];
        if (one_block != 0 && i / one_block != progress) {
            progress += 1;
            cout << "■";
        }
    }
    if (one_block == 0) {
        cout << "■■■■■■■■■■";
    }
    cout << endl << "Процесс успешно завершен!" << endl;
    return second_text;
}

byte_array EncryptDecrypt(const ModeType& mode, const CipherType& cipher, const byte_array& text, const byte_array& key) {
    byte_array result;
    switch (mode) {
        case (ModeType::ENCRYPT): {
            switch (cipher) {
                case (CipherType::ATBASH): {
                    result = Atbash(text);
                    break;
                }
                case (CipherType::AFFINE): {
                    result = AffineEncrypt(text, key);
                    break;
                }
                case (CipherType::XOR): {
                    result = XorCipher(text, key);
                    break;
                }
            }
            break;
        }
        case (ModeType::DECRYPT): {
            switch (cipher) {
                case (CipherType::ATBASH): {
                    result = Atbash(text);
                    break;
                }
                case (CipherType::AFFINE): {
                    result = AffineDecrypt(text, key);
                    break;
                }
                case (CipherType::XOR): {
                    result = XorCipher(text, key);
                    break;
                }
            }
            break;
        }
        case (ModeType::EXIT): {
            break;
        }
    }
    return result;
}
