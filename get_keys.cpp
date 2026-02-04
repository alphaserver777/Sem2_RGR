#include "types.hpp"
#include "utils.hpp"
#include "file_io.hpp"
#include "get_keys.hpp"
#include <iostream>
#include <random>

using namespace std;

byte_array InputKey(const CipherType& Cipher, const size_t& size_of_file) {
    byte_array key_in_array;
    int key;
    switch (Cipher) {
        case CipherType::ATBASH: {
            cout << "Шифр Атбаш не требует ключа." << endl;
            break;
        }
        case CipherType::AFFINE: {
            cout << "Выбран аффинный шифр, введите параметры a и b." << endl;
            cout << "a должно быть нечётным (взаимно простым с 256)." << endl;
            int a = GetIntInput("a", 1, 255);
            while (a % 2 == 0) {
                cout << "Ошибка: a должно быть нечётным!" << endl;
                a = GetIntInput("a", 1, 255);
            }
            int b = GetIntInput("b", 0, 255);
            key_in_array.push_back(a);
            key_in_array.push_back(b);
            break;
        }
        case CipherType::XOR: {
            int key_len = GetIntInput("Длина ключа", 1, GetMin(255, size_of_file));
            cout << "Введите числа 0..255 для " << key_len << " байт ключа." << endl;
            for (int i = 0; i < key_len; i++) {
                key = GetIntInput("Байт " + to_string(i), 0, 255);
                key_in_array.push_back(key);
            }
            break;
        }
    }
    return key_in_array;
}

byte_array ReadKey(const CipherType& Cipher, const size_t& size_of_file) { 
    byte_array key;
    while (true) {
        try {
            key = ReadFileToBytearray();
            switch (Cipher) {
                case(CipherType::ATBASH): {
                    if (!key.empty()) {
                        throw runtime_error("Для Атбаш ключ не нужен. Выберите пустой файл или ввод без ключа.");
                    }
                    break;
                }
                case(CipherType::AFFINE): {
                    if (key.size() != 2) {
                        throw runtime_error("Ключ должен состоять из 2 байт (a и b).");
                    }
                    if (key[0] % 2 == 0) {
                        throw runtime_error("Параметр a должен быть нечётным.");
                    }
                    break;
                }
                case(CipherType::XOR): {
                    if (key.empty()) {
                        throw runtime_error("Ключ не может быть пустым.");
                    }
                    break;
                }
            }
            break;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    return key;
}

byte_array GenKey(const CipherType& Cipher, const size_t& size_of_file) {
    byte_array key_in_array;
    random_device rd;
    mt19937 gen(rd());
    switch (Cipher) {
        case CipherType::ATBASH: {
            cout << "Шифр Атбаш не требует ключа." << endl;
            break;
        }
        case CipherType::AFFINE: {
            uniform_int_distribution<> a_distribution(1, 255);
            uniform_int_distribution<> b_distribution(0, 255);
            unsigned char a = static_cast<unsigned char>(a_distribution(gen));
            while (a % 2 == 0) {
                a = static_cast<unsigned char>(a_distribution(gen));
            }
            unsigned char b = static_cast<unsigned char>(b_distribution(gen));
            key_in_array.push_back(a);
            key_in_array.push_back(b);
            cout << "Сгенерированный ключ: a=" << int(a) << ", b=" << int(b) << endl;
            break;
        }
        case CipherType::XOR: {
            uniform_int_distribution<> length_distribution(1, GetMin(32, size_of_file));
            uniform_int_distribution<> value_distribution(0, 255);
            size_t key_length = length_distribution(gen);
            key_in_array.resize(key_length);
            cout << "Сгенерированный ключ:";
            for (size_t i = 0; i < key_length; i++) {
                key_in_array[i] = value_distribution(gen);
                cout << " " << int(key_in_array[i]);
            }
            cout << " ... Сохраните в файл!" << endl;
            break;
        }
    }
    return key_in_array;
}

byte_array GetKey(const ModeType& Mode, const CipherType& Cipher, const size_t& size_of_file) {
    if (Cipher == CipherType::ATBASH) {
        system("clear");
        cout << "========== ВЫБОР КЛЮЧА ==========" << endl << endl;
        cout << "Для шифра Атбаш ключ не требуется." << endl;
        WaitForEnter();
        return {};
    }
    system("clear");
    cout << "========== ВЫБОР КЛЮЧА ==========" << endl << endl;
    cout << "Выберите источник ключа:" << endl;
    cout << "1. Ввести" << endl;
    cout << "2. Из файла (bin)";
    cout << ((Mode == ModeType::ENCRYPT) ? "\n3. Сгенерировать" : "") << endl;
    cout << endl;
    int source_of_key = GetIntInput("Выбор", 1, (Mode == ModeType::ENCRYPT) ? 3 : 2);
    byte_array key;
    switch (source_of_key) {
        case 1: {
            key = InputKey(Cipher, size_of_file);
            if (Mode == ModeType::ENCRYPT) {
                SaveBytearrayToFile(key, "ключ"); 
            }
            break;
        }
        case 2: {
            key = ReadKey(Cipher, size_of_file);
            break;
        }
        case 3: {
            key = GenKey(Cipher, size_of_file);
            if (Mode == ModeType::ENCRYPT) {
                SaveBytearrayToFile(key, "ключ");    
            }
            break;
        }
    }
    ClearCin();
    WaitForEnter();
    return key;
}
