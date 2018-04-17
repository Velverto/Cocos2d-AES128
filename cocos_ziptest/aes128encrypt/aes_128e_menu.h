#ifndef AES_ENCRYPT_MENU_INCLUDED
#define AES_ENCRYPT_MENU_INCLUDED
using namespace std;

#include <iostream>
#include <windows.h>
#include <cstring>
#include <cstdio>
#include <thread>
#include <future>

#include "aes_128.h"

static void purger(void);
static void clean(char *chaine);

void aes_128e_menu();
void AES_split(promise<string>& prom, FILE* inputFile, string encrypt_key, size_t thread_input_size, size_t thread_number);

#endif // AES_ENCRYPT_MENU_INCLUDED