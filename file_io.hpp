#pragma once
#include "types.hpp"
#include <string>

byte_array ReadFileToBytearray();

void SaveBytearrayToFile(const byte_array& data, const std::string& hint);
