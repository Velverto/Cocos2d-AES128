#ifndef __MAIN_H__
#define __MAIN_H__

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#define _WINDOWS _WINDOWS_
#endif             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <tchar.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <thread>
#include <future>
#include <Windows.h>
#include <ctime>

#include "cocos2d.h"
#include "aes128encrypt/aes_128e_menu.h"
#include "aes128decrypt/aes_128d_menu.h"

// C RunTime Header Files/#include "platform/CCStdC.h"

#endif    // __MAIN_H__