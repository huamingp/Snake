#include <stdio.h>
#include <console.h>
#include <draw.h>
#include <snake.h>
#include <food.h>

int main()
{

    ConsoleInit();
    welcome_screen();

    create_game_area();
    create_game_area_frame();
    DoubleLinkList_t *Snakelist = InitSnakeList();
    if (!InitSnake())
    {

        return -1;
    }
    foodlist_t *foodlist = init_food_list(Snakelist);
    if (foodlist == NULL)
    {
        return -1;
    }
    init_random();

    bool grow = false;

    while (1)
    {
        char str_buff[10];
        snprintf(str_buff, sizeof(str_buff), "Score:%d", Snakelist->length - 3);
        PrintAtCursor(str_buff, 50, 11);

        SnakeMove(Snakelist, &grow);
        if (CheckCollisionWithSelf(Snakelist) || CheckCollisionWithWall(Snakelist->head))
        {
            end_game(Snakelist);
        }
        check_snake_eat_food(Snakelist,foodlist, &grow);
        print_food_list(foodlist);
        PrintSnake(Snakelist);
        Sleep(300);
    }

    return 0;
}