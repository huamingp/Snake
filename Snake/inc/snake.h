#ifndef _SNAKE_H_
#define _SNAKE_H_

#include<stdio.h>
#include<stdbool.h>


typedef struct SnakeNode
{
    int x;
    int y;
    struct SnakeNode *prev;
    struct SnakeNode *next;
} SnakeNode_t;

typedef struct DoubleLinkList
{
    SnakeNode_t *head;
    SnakeNode_t *tail;
    int length;
} DoubleLinkList_t;

typedef enum 
{ 
    UP, 
    DOWN, 
    LEFT, 
    RIGHT 
} Direction;

static DoubleLinkList_t *get_snakelist;

DoubleLinkList_t *InitSnakeList(void);
bool InitSnake(void);
void AddNodetoHead(DoubleLinkList_t *Snakelist, SnakeNode_t *Newhead);
void DeleteOldtail(DoubleLinkList_t *Snakelist);
void PrintSnake(DoubleLinkList_t *Snakelist);
Direction ReadDirection();
void SnakeMove(DoubleLinkList_t *Snakelist, bool *grow);
bool CheckCollisionWithSelf(DoubleLinkList_t *Snakelist);
bool CheckCollisionWithWall(SnakeNode_t *head);


#endif