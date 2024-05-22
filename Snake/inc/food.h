#ifndef _FOOD_H_
#define _FOOD_H_


#include<stdio.h>
#include<stdbool.h>
#include<snake.h>

typedef struct food 
{
    int x;
    int y;
    struct food *next;
}food_t;

typedef struct foodlist
{
    food_t *header;
    // food_t *tail;

}foodlist_t;


// food_t  *Initfood(void);
// food_t Create_new_food();
// void Printf_food(food_t *food);

void init_random();
int get_random_number();
int check_food_on_body(DoubleLinkList_t *Snakelist, foodlist_t *foodlist);
food_t *generate_food( foodlist_t *foodlist);
void print_food(food_t *food);
void Addfoodtolist(DoubleLinkList_t *Snakelist, foodlist_t *foodlist);
foodlist_t *init_food_list(DoubleLinkList_t *Snakelist);
void check_snake_eat_food(DoubleLinkList_t *Snakelist, foodlist_t *foodlist, bool *grow);
void print_food_list(foodlist_t *foodlist);
food_t *NULL_generate_food(DoubleLinkList_t *Snakelist,foodlist_t *foodlist);


#endif