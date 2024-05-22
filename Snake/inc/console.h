#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include<stdio.h>
#include <windows.h>
#include <conio.h>

#define COLOR_WHITE_GRAY    0x78       // 白底灰字
#define COLOR_BLACK_GRAY    0x70       // 黑底灰字
#define COLOR_WHITE_BLACK   0x70       // 白底黑字 
#define COLOR_BLACK_WHITE   0x07       // 黑底白字
#define COLOR_GRAY_GRAY     0x88       // 灰底灰字 
#define COLOR_WHITE_RED     0x74       // 白底红字
#define COLOR_GRAY_RED      0x84       // 灰底红字
#define COLOR_GRAY_BLUE     0x81       // 灰底蓝字

#define COLOR_WHITE_BLUE    0x71      // 白底蓝字 墙壁
#define COLOR_WHITE_WHITE   0x77      // 白底白字 背景
#define COLOR_BLACK_RED     0x04      // 黑底红字 蛇头 
#define COLOR_BLACK_GREEN   0x02      // 黑底绿字 食物

#define WIDTH  40
#define HEIGHT WIDTH/2

static WORD old_screen_attr = 0;

void MoveCursorPosition(int x, int y);
void PrintAtCursor(char *ch, int x , int y) ;
void SetColor(WORD  NewColor /*颜色值*/, WORD  *old /*记住修改前的屏幕属性*/);
VOID HideConsoleCursor(VOID);
void ConsoleInit();

#endif