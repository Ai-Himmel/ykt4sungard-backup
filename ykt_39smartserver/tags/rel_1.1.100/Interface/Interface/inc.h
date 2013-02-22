#ifndef __INC_H
#define __INC_H
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdarg.h>
#include <windows.h>

#include "mytypes.h"								/* 类型定义头文件 */
#include "loadcf.h"									/* 读取配置文件 */
#include "cpack.h"									/* 包结构头文件 */
#include "DRTPApi.h"
#pragma comment(lib,"..\\lib\\DRTPApi.lib") 
#pragma message("Automatically linking with DRTPApi.dll")
#endif
