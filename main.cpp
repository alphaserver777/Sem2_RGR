#include <iostream>
#include "types.hpp"
#include "utils.hpp"
#include "file_io.hpp"
#include "get_keys.hpp"
#include "ciphers.hpp"

using namespace std;

int main() {
    while (true) {
        system("clear");
        cout << "========== МЕНЮ ==========" << endl;
        cout << "Добро пожаловать!" << endl << endl;
        cout << "Выберите действие:" << endl;
        cout << "1. Шифрование" << endl;
        cout << "2. Дешифрование" << endl;
        cout << "0. Выход" << endl;
        int input_mode = GetIntInput("Ввод", 0, 2);
        auto mode = static_cast<ModeType>(input_mode);
        if (mode == ModeType::EXIT) {return 0;}

        system("clear");
        cout << "========== ВЫБОР ШИФРА ==========" << endl;
        cout << "Выбранный режим: " << (mode == ModeType::ENCRYPT ? "Шифрование" : "Дешифрование") << endl << endl;
        cout << "Выберите шифр:" << endl;
        cout << "1. Атбаш" << endl;
        cout << "2. Аффинный" << endl;
        cout << "3. XOR" << endl;
        int input_cipher = GetIntInput("Ввод", 1, 3);
        auto cipher = static_cast<CipherType>(input_cipher);

        system("clear");
        cout << "========== ВЫБОР ФАЙЛА ==========" << endl << endl;
        byte_array file = ReadFileToBytearray();
        
        byte_array key = GetKey(mode, cipher, file.size());
        

        system("clear");
        cout << "========== ПОДТВЕРЖДЕНИЕ ==========" << endl;
        cout << "Выбранный режим: " << (mode == ModeType::ENCRYPT ? "Шифрование" : "Дешифрование") << endl;
        cout << "Выбранный шифр: " << NameOfCipher(cipher) << endl;
        cout << "Файл: Загружен, " << file.size() << " байт." << endl;
        cout << "Ключ: " << DisplayKey(cipher, key) << endl << endl;
        cout << "Продолжить? 1 - Да / 2 - В меню" << endl;

        int confirm = GetIntInput("Ввод",1,2);
        byte_array result;
        if (confirm == 1) {
            result = EncryptDecrypt(mode, cipher, file, key);
            SaveBytearrayToFile(result, "результат");
            WaitForEnter();   
        }
    }
}
