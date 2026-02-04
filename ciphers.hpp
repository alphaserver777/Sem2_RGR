#pragma once
#include "types.hpp"

byte_array EncryptDecrypt(const ModeType& mode, const CipherType& cipher, const byte_array& text, const byte_array& key);