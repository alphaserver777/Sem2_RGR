#include "types.hpp"
#include "file_io.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

byte_array ReadFileToBytearray() { 
    string filename;
    size_t filesize;
    byte_array buffer;
    ClearCin();
    while (true) {
        try {
            cin.clear();
            cout << "   Введите относительный путь до файла > ";
            getline(cin, filename);
            if (filename.empty()) {
                throw runtime_error("Путь не введён!");
            }
            ifstream file;
            file.open(filename, ios::binary);
            if (!file.is_open()) {
                throw runtime_error("Путь введён неккоректно или файл не существует!");
            } 
            filesize = filesystem::file_size(filename);
            if (filesize == 0) {
                throw runtime_error("Файл пуст. Выберите другой.");
            }
            buffer.resize(filesize);
            file.read(reinterpret_cast<char*>(buffer.data()), filesize);
            if (!file || file.gcount() != filesize) {
                throw runtime_error("Ошибка чтения!");
            }
            break;
            
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    cout << "Успещно прочитано " << buffer.size() << " байт!" << endl;
    WaitForEnter();
    return buffer;
}

void SaveBytearrayToFile(const byte_array& data, const string& hint) {
    cout << "Желаете сохранить " << hint << " в файл? 1 - Да / 2 - Нет" << endl;
    int input = GetIntInput("Выбор", 1, 2);
    if (input == 1) {
        ClearCin();
        while(true) {
            try {
                cin.clear();
                string filepath;
                cout << "   Введите путь и имя файла (например, output.bin) > ";
                getline(cin, filepath);
                if (filepath.empty()) {
                    throw runtime_error("Путь не введён!");
                }
                if (filesystem::exists(filepath)) {
                    cout << "Файл " << filepath << " существует, перезаписать? 1 - Да / 2 - Нет" << endl;
                    int overwrite = GetIntInput("Выбор", 1, 2);
                    if (overwrite == 2) {
                        continue;
                    }
                }
                ofstream file(filepath, ios::binary);
                if (!file.is_open()) {
                    throw runtime_error("Путь введён неккоректно!");
                }
                if (!data.empty()) {
                    file.write(reinterpret_cast<const char*>(&data[0]), data.size());
                    if (!file) {
                        throw runtime_error("Ошибка записи файла!");
                    }
                }
                cout << "Сохранено " << data.size() << " байт в " << filepath << "!" << endl;
                break;
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
        }
    }
}
