#include <stdint.h>        //uint8_t...uint64_t int8_t...int64_t
#include <stdbool.h>       //bool true false
#include <iso646.h>        //and or not
#include "FcTaskCyclic1.h" //Задача вызывается циклически.
#include "GlobalVar.h"     //Глобальные переменные ПЛК.

extern struct GlobalVar GV; //Глобальные переменные ПЛК.

void FcTaskCyclic1(bool Reset, uint32_t Ts_ms) //Задача выполняется с плавающим временем цикла.
{
  GV.Di0 = false;
  return;
}

//  +---------+
//  | GNU GPL |
//  +---------+
//  |
//  |
//  .= .-_-. =.
// ((_/)o o(\_))
//  `-'(. .)`-'
//  |/| \_/ |\
//  ( |     | )
//  /"\_____/"\
//  \__)   (__/
// @COPYLEFT ALL WRONGS RESERVED :)
// Author: VA
// Contacts: DIY.PLC.314@gmail.com
// License: GNU GPL v2
//
// https://www.youtube.com/@DIY_PLC
// https://github.com/DIYPLC
