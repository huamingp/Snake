#include<stdio.h>
#include<console.h>
#include<draw.h>


/**
 * @brief 创建游戏区域
 */
void create_game_area()
{
    int width_index = 0;
    int height_index = 0;

    //将游戏区域将被填充为白色
    SetColor(COLOR_WHITE_WHITE,&old_screen_attr);

    for(width_index = 0; width_index < WIDTH ; width_index++) {
        for(height_index = 0; height_index < HEIGHT ; height_index++) {
            //从(1,1)坐标开始，打印方块填充‘游戏区域’ 注意 一个■字符的大小为横向1，纵向1
            //这个需要自己测试，一个字符的横向大小我觉得为1，打印出来的游戏区域好看
            PrintAtCursor("■",1+width_index,1+height_index);
        }
    }

    //打印完，恢复为原来的打印颜色，不影响后面的打印
    SetColor(old_screen_attr,NULL);

}
/**
 * @brief 打印游戏区域的边框，即“墙”
 */
void create_game_area_frame()
{
    int width_index = 0;
    int height_index = 0;

    //区域将被填充为绿色
    SetColor(COLOR_GRAY_BLUE,&old_screen_attr);

    //上边框
    for(width_index = 0; width_index <WIDTH ; width_index++) {
        //从(1,0)坐标开始，横向打印方块
        PrintAtCursor("■",1+width_index,0);
    }

    //左边框
    for(height_index = 0; height_index < HEIGHT ; height_index++) {
        //从(0,1)坐标开始，纵向打印方块
        PrintAtCursor("■",0,height_index+1);
    }

    //下边框
    for(width_index = 0; width_index < WIDTH ; width_index++) {
        //从(1,HEIGHT+1)坐标开始，横向打印方块
        PrintAtCursor("■",1+width_index,HEIGHT+1);
    }

    //右边框
    for(height_index = 0; height_index < HEIGHT ; height_index++) {
        //从(0,1)坐标开始，纵向打印方块
        PrintAtCursor("■",1+WIDTH,1+height_index);
    }

    //打印完，恢复为原来的打印颜色，不影响后面的打印
    SetColor(old_screen_attr,NULL);

    //打印完毕 移动光标位置到游戏外部
    MoveCursorPosition(0,42);

}

// 游戏开始界面
void welcome_screen()
{
    char str1[] = "Welcome to Snake Game!";
    char str2[] = "Press any key to start...";
    char str3[] = "you can control the sanke with w a s d";
    char str4[] = "w means up, s means down, a means left, d means right";
    char str5[] = "  -By Huaming 2024 5";
    system("cls");

    SetColor(COLOR_BLACK_WHITE, &old_screen_attr);
    PrintAtCursor(str1, 20, 5);
    PrintAtCursor(str2, 20, 20);
    PrintAtCursor(str3, 20, 8);
    PrintAtCursor(str4, 20, 10);
    PrintAtCursor(str5, 50, 19);
    _getch(); // 等待用户按任意键继续
    system("cls");
}


void end_game(DoubleLinkList_t *Snakelist)
{
    char str1[] = "      Game Over";
    char str2[128];
    char str3[] = "Thanks for your playing!";
    char str4[] = "Press any key to exit...";
    SetColor(COLOR_BLACK_WHITE, &old_screen_attr);
    
    system("cls");

    PrintAtCursor(str1, 20, 5);
    snprintf(str2, sizeof(str2), "Scroce:%d", Snakelist->length - 3);
    PrintAtCursor(str2, 20, 8);
    PrintAtCursor(str3, 20, 10);
    PrintAtCursor(str4, 20, 20);
    

    SetColor(old_screen_attr, NULL);

    _getch();
    exit(0);
}
