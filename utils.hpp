#pragma once
#include <string>
#include "types.hpp"

void ClearCin();

void WaitForEnter();

int GetMin(const int& a, const int& b);

std::string NameOfCipher(CipherType CP);

std::string DisplayKey(CipherType CP, byte_array Key);

int GetIntInput(const std::string& prompt, const int& min, const int& max);