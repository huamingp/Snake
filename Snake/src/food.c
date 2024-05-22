#include<food.h>
#include<stdio.h>
#include<stdint.h>
#include<console.h>
#include<time.h>
#include<stdlib.h>
#include<snake.h>


// 初始化随机数，只用初始化一次
void init_random()
{
    srand((unsigned)time(NULL));
}

// 产生随机数
int get_random_number()
{
    return rand();
}

food_t *generate_food(foodlist_t *foodlist)
{
    food_t *food = (food_t *)malloc(sizeof(food_t));
    if (food == NULL)
    {
        return NULL;
    }

    food->x = get_random_number() % WIDTH + 1;
    food->y = get_random_number() % HEIGHT + 1;
    food->next = NULL;

    return food;
}

/**
 * @brief 检查新生成的食物是否在蛇身上,有bug
 */
int check_food_on_body(DoubleLinkList_t *Snakelist, foodlist_t *foodlist)
{


    // 取出食物链表的头节点，因为游戏中一次只能有一个食物，所以只需检查一个食物节点
    food_t *food = foodlist->header;
    //！ 没有食物
    if (food == NULL) {
        return 0; 
    }

    // 遍历蛇的链表
    SnakeNode_t *current_snake = Snakelist->head;
    while (current_snake != NULL) {
        if (current_snake->x == food->x && current_snake->y == food->y) {
            return 1; // 食物与蛇身重合
        }
        current_snake = current_snake->next;
    }
    return 0; // 食物未与蛇身重合
}


//  bool check_food_on_body(DoubleLinkList_t *Snakelist, foodlist_t *foodlist)
// {

//     SnakeNode_t *current_snake = Snakelist->head;
//     food_t *food = foodlist->header;
//     while (current_snake->next != NULL)
//     {
//         if (current_snake->x == food->x && current_snake->y == food->y)
//         {
//             return true;
//         }
//         current_snake = current_snake->next;
//         food = food->next;
//     }

//     return false;
// }



/**
 * @brief 产生食物节点，并初始化节点信息
 */
food_t *NULL_generate_food(DoubleLinkList_t *Snakelist, foodlist_t *foodlist)
{

    food_t *food = (food_t *)malloc(sizeof(food_t));
    do {
        food->x = get_random_number() % WIDTH;
        food->y = get_random_number() % HEIGHT;

        //！！ 如果食物列表为空，则创建新的食物节点
        if (foodlist->header == NULL) {
            foodlist->header = food;
            foodlist->header->next = NULL;
        }

        // 更新食物位置
        foodlist->header->x = food->x;
        foodlist->header->y = food->y;       
    } while (check_food_on_body(Snakelist, foodlist)); // 确保新食物位置不与蛇身重合

    return food;
}

// 用■打印食物的位置坐标
void print_food(food_t *food)
{
    SetColor(COLOR_BLACK_GREEN, &old_screen_attr);
    PrintAtCursor("■", food->x, food->y);
    SetColor(old_screen_attr, NULL);
}

// 将食物添加到食物链表中
void Addfoodtolist(DoubleLinkList_t *Snakelist, foodlist_t *foodlist)
{
    food_t *new_food = NULL_generate_food(Snakelist, foodlist);
    if (new_food == NULL)
        return;
    new_food->next = foodlist->header;
    foodlist->header = new_food;
    print_food(new_food);
}

/**
 * @brief 初始化食物链表，用来存储食物节点的坐标
 */
foodlist_t *init_food_list(DoubleLinkList_t *Snakelist)
{
    foodlist_t *foodlist = (foodlist_t *)malloc(sizeof(foodlist_t));
    if (foodlist == NULL)
    {
        return NULL;
    }
    foodlist->header = NULL;
    Addfoodtolist(Snakelist, foodlist);
    return foodlist;
}
/**
 * @brief 检测蛇是否吃到了食物，如果吃到了则删掉当前食物，并重新生成食物
 * @param grow  标志位 用来表示蛇是否吃到了食物
 * 
 */
void check_snake_eat_food(DoubleLinkList_t *Snakelist, foodlist_t *foodlist, bool *grow)
{
    //链表为空，没有食物，直接返回
    if (foodlist == NULL || foodlist->header == NULL)
        return;
    // 比较蛇头的坐标和食物的坐标，判断是否吃到食物    
    SnakeNode_t *snakeHead = Snakelist->head;
    food_t *prev = NULL;
    food_t *current_food = foodlist->header;
    while (current_food != NULL)
    {
        if (current_food->x == snakeHead->x && current_food->y == snakeHead->y)
        {
            *grow = true;
            // 判断当前节点是不是食物链表的首节点
            if (prev == NULL)
            {
                //current_food就是要删掉的节点，更新食物链表的头节点
                foodlist->header = current_food->next;
            }
            else
            {   
                
                prev->next = current_food->next;
            }
            free(current_food);
            Addfoodtolist(Snakelist,foodlist);
            break;
        }
        prev = current_food;
        current_food = current_food->next;
    }
}

// 打印食物链表，其实感觉有点多余，本来想仿造PrintSnake
void print_food_list(foodlist_t *foodlist)
{
    food_t *current = foodlist->header;
    while (current != NULL)
    {
        print_food(current);
        current = current->next;
    }
}
