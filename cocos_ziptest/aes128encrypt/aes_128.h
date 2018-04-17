#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdio>

#include "mix_columns.h"
#include "shift_rows.h"
using namespace std;

string aes_128(FILE *inputFile, string key, size_t thread_input_size, size_t thread_number);

#endif // AES_H_INCLUDED