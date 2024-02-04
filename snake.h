#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>

struct parts_of_Snake{
    int x,y;
    parts_of_Snake(int col, int row);
    parts_of_Snake();
};

class TheSnake{
    int score, score2, Delayy;
    //the snake got the food, makes its lenght longer)
    bool get[2];
    //the current direction of the snake
    char direction[2];

    int maxwidth;
    int maxheight;
    char partchar;
    char oldalchar;
    char eat;
    parts_of_Snake foods;
    std::vector<parts_of_Snake> snake[2]; //represent the snake

    void KeepFood();
    bool collision(int id);
    bool collision2(int id);
    void SnakeMovement(int id);

public:
    TheSnake();
    ~TheSnake();
    void start();

};

#endif
