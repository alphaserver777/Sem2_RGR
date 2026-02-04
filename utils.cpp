#include <iostream>
#include <string>
#include <limits>
#include "utils.hpp"
#include "types.hpp"

using namespace std;

void ClearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void WaitForEnter() {
    cout << "Нажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int GetMin(const int& a, const int& b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

string NameOfCipher(CipherType cipher) {
    switch (cipher) {
        case (CipherType::ATBASH): {
            return "Атбаш";
        }
        case (CipherType::AFFINE): {
            return "Аффинный";
        }
        case (CipherType::XOR): {
            return "XOR";
        }
    }
    return "Неизвестно";
}

string DisplayKey(CipherType cipher, byte_array key) {
    switch (cipher) {
        case (CipherType::ATBASH): {
            return "Не требуется";
        }
        case (CipherType::AFFINE): {
            if (key.size() < 2) {
                return "Некорректный";
            }
            return "a=" + to_string(key[0]) + ", b=" + to_string(key[1]);
        }
        case (CipherType::XOR): {
            if (key.empty()) {
                return "Некорректный";
            }
            string res = "длина=" + to_string(key.size()) + " [";
            for (int i = 0; i < GetMin(10, key.size()); i++) {
                res += to_string(key[i]);
                if (i + 1 < GetMin(10, key.size())) {
                    res += " ";
                }
            }
            if (key.size() > 10) {
                res += " ...";
            }
            res += "]";
            return res;
        }
    }
    return "Неизвестно";
}

int GetIntInput(const string& prompt, const int& min, const int& max) {
    int value;
    while (true) {
        try {
            cout << "   " << prompt << " > ";
            if (!(cin >> value)) {
                throw invalid_argument("Некорректный ввод!");
            } else if (value < min || value > max) {
                throw invalid_argument("Введённое значение должно быть от " + to_string(min) + " до " + to_string(max) + "!");
            }
            break;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            ClearCin();
        }
    }
    return value;
}
