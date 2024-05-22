#include <snake.h>
#include <stdlib.h>
#include <console.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>

/**
 * @brief 初始化蛇为给定的长度
 * @return snake 新创建的蛇链表
 */
DoubleLinkList_t *InitSnakeList(void)
{
    // 初始化蛇链表
    DoubleLinkList_t *Snakelist = (DoubleLinkList_t *)malloc(sizeof(DoubleLinkList_t));
    if (Snakelist == NULL)
    {
        return NULL;
    }
    Snakelist->head = NULL;
    Snakelist->tail = NULL;
    Snakelist->length = 0;
    //  添加蛇的节点，游戏开始时有三个节点
    int initlength = 3;
    for (int i = 0; i < initlength; i++)
    {
        SnakeNode_t *newNode = (SnakeNode_t *)malloc(sizeof(SnakeNode_t));
        newNode->x = WIDTH / 2 + i;
        newNode->y = HEIGHT / 2;
        newNode->prev = NULL;
        newNode->next = Snakelist->head;
        if (Snakelist->head != NULL) // 判断链表是否为空，if里面的内容只执行一次
        {
            Snakelist->head->prev = newNode;
        }
        Snakelist->head = newNode;
        if (Snakelist->tail == NULL) // 判断链表是否为空，if里面的内容只执行一次
        {
            Snakelist->tail = newNode;
        }
        Snakelist->length++;
    }

    return Snakelist;
}

/**
 * @brief  判断蛇是否初始化成功
 */

bool InitSnake(void)
{

    // get_snakelist = InitSnakeList();
    // if (get_snakelist == NULL)
    // {
    //     return false;
    // }
    // return true;
    return (get_snakelist = InitSnakeList()) != NULL;
}

/**
 * @brief 在蛇的头部添加新节点
 * @param Snakelist 要添加的蛇的链表
 * @param Newhead   新节点
 */
void AddNodetoHead(DoubleLinkList_t *Snakelist, SnakeNode_t *Newhead)
{
    Newhead->next = Snakelist->head;
    Newhead->prev = NULL;
    if (Snakelist->head != NULL) // 判断链表是否为空，if里面的内容只执行一次
    {
        Snakelist->head->prev = Newhead;
    }

    Snakelist->head = Newhead;
    if (Snakelist->tail == NULL) // 判断链表是否为空，if里面的内容只执行一次
    {
        Snakelist->tail = Newhead;
    }

    Snakelist->length++;
}

/**
 * @brief 删除蛇的链表的尾节点，删除蛇的尾巴，
 * @param Snakelist
 * @param oldTail   要删除的尾节点
 */
void DeleteOldtail(DoubleLinkList_t *Snakelist)
{
    // 检查链表是否为空
    if (Snakelist->tail == NULL)
    {
        return;
    }
    SnakeNode_t *oldTail = Snakelist->tail;
    Snakelist->tail = oldTail->prev;
    if (Snakelist->tail != NULL) // 判断链表是否为空，不为空则将尾节点指针指向NULL
    {
        Snakelist->tail->next = NULL;
    }
    else
    {
        Snakelist->head = NULL;
    }
    SetColor(COLOR_WHITE_WHITE, &old_screen_attr);
    PrintAtCursor("■", oldTail->x, oldTail->y); // 清除旧尾巴
    SetColor(old_screen_attr, NULL);

    free(oldTail);
    Snakelist->length--;
}

/**
 * @brief 打印蛇，遍历蛇的链表，用 ■打印每个蛇的节点的位置信息
 * @param Snakelist
 */
void PrintSnake(DoubleLinkList_t *Snakelist)
{
    SnakeNode_t *current = Snakelist->head;
    while (current != NULL)
    {
        SetColor(COLOR_BLACK_RED, &old_screen_attr);
        PrintAtCursor("■", current->x, current->y);
        current = current->next;
    }
    SetColor(old_screen_attr, NULL);
}
/**
 * @brief 读取用户输入的方向，和上一个方向比较，判断是否需要改变方向
 * @return Direction 枚举变量，表示用户输入的方向
 */
Direction ReadDirection()
{
    // 蛇的初始方向为向右，即游戏开始时，蛇自动为右移动
    static Direction currentDirection = RIGHT;
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            if (currentDirection != DOWN)
            {
                currentDirection = UP;
            }
            break;

        case 's':
            if (currentDirection != UP)
            {
                currentDirection = DOWN;
            }
            break;
        case 'a':
            if (currentDirection != RIGHT)
            {
                currentDirection = LEFT;
            }

            break;
        case 'd':
            if (currentDirection != LEFT)
            {
                currentDirection = RIGHT;
                break;
            }
        }
    }
    return currentDirection;
}

/**
 * @brief 蛇移动，根据标志位来判断蛇是正常移动还是在移动时吃到食物
 * @param Snakelist
 * @param grow
 */
void SnakeMove(DoubleLinkList_t *Snakelist, bool *grow)
{
    // 蛇的移动效果可以由同时增加头节点和删除尾节点，再加上延时，延时结束再重新打印蛇即可实现

    Direction direction = ReadDirection();
    //根据当前移动的方向计算下一个蛇头的坐标
    int new_x = Snakelist->head->x;
    int new_y = Snakelist->head->y;
    switch (direction)
    {
    case UP:
        new_y -= 1;
        break;
    case DOWN:
        new_y += 1;
        break;
    case LEFT:
        new_x -= 1;
        break;
    case RIGHT:
        new_x += 1;
        break;
    }
    // 生成新的头节点，并添加到链表
    SnakeNode_t *newHead = (SnakeNode_t *)malloc(sizeof(SnakeNode_t));
    newHead->x = new_x;
    newHead->y = new_y;
    AddNodetoHead(Snakelist, newHead);

    // 判断是否吃到食物，grow默认为false
    if (!*grow)
    {
        DeleteOldtail(Snakelist);
    }
    else
    {
        *grow = false;
    }
}
/**
 * @brief 碰撞检测函数，检查蛇是否碰撞到自己
 * @param Snakelist
 * @return true
 * @return false
 */
bool CheckCollisionWithSelf(DoubleLinkList_t *Snakelist)
{
    // 遍历法，将头节点的位置信息和其他节点的位置信息进行判断，检查蛇是否碰撞到自己
    SnakeNode_t *head = Snakelist->head;
    SnakeNode_t *current = head->next;
    while (current != NULL)
    {
        if (head->x == current->x && head->y == current->y)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

/**
 * @brief 碰撞检测函数，检查蛇是否碰撞到墙
 * @param head 蛇的头节点
 */

bool CheckCollisionWithWall(SnakeNode_t *head)
{
    // if (head->x == 0 || head->x == WIDTH - 1 || head->y == 0 || head->y == HEIGHT - 1)
    // {
    //     return true;
    // }
    // return false;
    return head->x <= 0 || head->x > WIDTH || head->y <= 0 || head->y > HEIGHT;
}