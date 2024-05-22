#include<console.h>



// 移动光标到指定位置
void MoveCursorPosition(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;

    HANDLE hcmdWindows = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hcmdWindows, pos);
}

// 打印字符到指定位置
void PrintAtCursor(char* ch, int x , int y) 
{
    MoveCursorPosition(x,y);
    printf("%s",ch);
}


//修改当前打印将使用的颜色 （并且保存修改前的设置）
void SetColor(WORD  NewColor /*颜色值*/, WORD  *old /*记住修改前的屏幕属性*/)
{
    //1. 获得打印窗口的操作句柄
    HANDLE hOutput;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //2. 记住当前正在使用的颜色
    if(old) {
        CONSOLE_SCREEN_BUFFER_INFO Info; 
        GetConsoleScreenBufferInfo(hOutput, &Info);
        *old = Info.wAttributes; 
    }

    //3. 根据函数参数指定的颜色值，修改屏幕的打印颜色属性
    SetConsoleTextAttribute(hOutput,NewColor);
    
}

VOID HideConsoleCursor(VOID)
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),
                         &cursor_info);
}

void ConsoleInit()
{
    system("mode con:cols=140 lines=50");
    system("chcp 65001");
    system("cls");
    HideConsoleCursor();
}
