#ifndef AES_DECRYPT_MENU_INCLUDED
#define AES_DECRYPT_MENU_INCLUDED
using namespace std;

#include <iostream>
#include <windows.h>
#include <cstring>
#include <cstdio>
#include <thread>
#include <future>

#include "aes_128_decrypt.h"

string aes_128d_menu();
void AES_decrypt_split(promise<string>& prom, FILE* inputFile, string encrypt_key, size_t thread_input_size, size_t thread_number);

#endif // AES_DECRYPT_MENU_INCLUDED