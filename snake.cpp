#include "snake.h"
#include <unistd.h>

#define KEY_LEFT1   ('a')
#define KEY_RIGHT1  ('d')
#define KEY_UP1     ('w')
#define KEY_DOWN1   ('s')


using namespace std;

parts_of_Snake::parts_of_Snake(int col,int row)
{
    x=col;
    y=row;
}

parts_of_Snake::parts_of_Snake()
{
    x=0;
    y=0;
}
TheSnake::TheSnake()
{
    initscr();
    nodelay(stdscr,true);           //if there wasn't any key pressed don't wait for it
    keypad(stdscr,true);            //init the keyboard
    noecho();                       //don't write
    curs_set(0);                    //cursor invisible
    getmaxyx(stdscr,maxheight,maxwidth);
    partchar='x';
    oldalchar=(char)219;
    eat='*'; //snake's food
    foods.x=0;
    foods.y=0;

    for(int i=0;i<5;i++)
        snake[0].push_back(parts_of_Snake(40+i,10));


    for(int i=0;i<5;i++)
        snake[1].push_back(parts_of_Snake(20+i,10));

    score=0;
    score2=0;
    Delayy=110000;
    get[0]=0;
    direction[0]='l';
    get[1]=0;
    direction[1]='l';

    srand(time(NULL));
    KeepFood();


    //the Game-board -up-vertical
    for(int i=0;i<maxwidth-1;i++)
    {
        move(0,i);
        addch(oldalchar);
    }

    //left-horizontal
    for(int i=0;i<maxheight-1;i++)
    {
        move(i,0);
        addch(oldalchar);
    }

    //down-vertical
    for(int i=0;i<maxwidth-1;i++)
    {
        move(maxheight-2,i);
        addch(oldalchar);
    }
    //right-horizontal
    for(int i=0;i<maxheight-1;i++)
    {
        move(i,maxwidth-2);
        addch(oldalchar);
    }
    //draw the snake
    for(int i=0;i<snake[0].size();i++)
    {
        move(snake[0][i].y,snake[0][i].x);
        addch(partchar);
    }

    move(maxheight-1,0);
    printw("%d",score);
    move(foods.y,foods.x);
    addch(eat);
    refresh();

    for(int i=0;i<snake[1].size();i++)
    {
        move(snake[1][i].y,snake[1][i].x);
        addch(partchar);
    }
    move(maxheight-1,78);
    printw("%d",score2);
    move(foods.y,foods.x);
    addch(eat);
    refresh();
}



TheSnake::~TheSnake()
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void TheSnake::KeepFood()
{
    while(1)
    {
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;

        for(int i=0;i<snake[0].size();i++)
            if(snake[0][i].x==tmpx && snake[0][i].y==tmpy)
                continue;
        if(tmpx>=maxwidth-2 || tmpy>=maxheight-3)
            continue;
        foods.x=tmpx;
        foods.y=tmpy;
        break;

        for(int i=0;i<snake[1].size();i++)
            if(snake[1][i].x==tmpx && snake[1][i].y==tmpy)
                continue;
        if(tmpx>=maxwidth-2 || tmpy>=maxheight-3)
            continue;
        foods.x=tmpx;
        foods.y=tmpy;
        break;
    }
    move(foods.y,foods.x);
    addch(eat);
    refresh();
}

bool TheSnake::collision(int id)
{

if(snake[id][0].x==0 || snake[id][0].x==maxwidth-1 || snake[id][0].y==0 || snake[id][0].y==maxheight-2)
               return true;
    for(int i=2;i<snake[0].size();i++)
        {
            if(snake[id][0].x==snake[0][i].x && snake[id][0].y==snake[0][i].y)
                 return true;
        }

  //collision with the food of first snake
 if(snake[id][0].x==foods.x && snake[id][0].y==foods.y)
        {
            get[0]=true;
            KeepFood();
            score+=10;
            move(maxheight-1,0);
            printw("%d",score);
            if((score%100)==0)
                 Delayy-=10000;
        }else
             get[0]=false;
             return false;
}

bool TheSnake::collision2(int id)
{
 if(snake[id][1].x==0 || snake[id][1].x==maxwidth-1 || snake[id][1].y==0 || snake[id][1].y==maxheight-2)
                       return true;
    for(int i=2;i<snake[1].size();i++)
                {
                 if(snake[id][1].x==snake[1][i].x && snake[id][1].y==snake[1][i].y)
                        return true;
                }
  //collision of snake 2 with the food
 if(snake[id][1].x==foods.x && snake[id][1].y==foods.y)
                {
                get[1]=true;
                KeepFood();
                score2+=10;
                move(maxheight-1,78);
                printw("%d",score2);
 if((score2%100)==0)
                 Delayy-=10000;
          }else
               get[1]=false;
                  return false;
              }

void TheSnake::SnakeMovement(int id)
{
    //detect key
    int tmp=getch();
    switch(tmp)
    {
        case KEY_LEFT:
            if(direction[0]!='r')
                direction[0]='l';
            break;
        case KEY_LEFT1:
             if(direction[1]!='r')
                direction[1]='l';
             break;
        case KEY_UP:
            if(direction[0]!='d')
                direction[0]='u';
            break;
        case KEY_UP1:
            if(direction[1]!='d')
                 direction[1]='u';
            break;
        case KEY_DOWN:
            if(direction[0]!='u')
                direction[0]='d';
            break;
        case KEY_DOWN1:
             if(direction[1]!='u')
                 direction[1]='d';
             break;
        case KEY_RIGHT:
            if(direction[0]!='l')
                direction[0]='r';
            break;
       case KEY_RIGHT1:
            if(direction[1]!='l')
               direction[1]='r';
            break;
        case KEY_BACKSPACE:
            direction[0]='q';
            break;

    }


//if there wasn't a collision with food

if(!get[0])
        {
         move(snake[0][snake[0].size()-1].y,snake[0][snake[0].size()-1].x);
         printw(" ");
         refresh();
         snake[0].pop_back();
        }
switch (direction[id])
    {
     case 'l': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][0].x-1,snake[id][0].y)); break;
     case 'r': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][0].x+1,snake[id][0].y)); break;
     case 'u': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][0].x,snake[id][0].y-1)); break;
     case 'd': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][0].x,snake[id][0].y+1)); break;
     }

         move(snake[id][0].y,snake[id][0].x);
         addch(partchar);
         refresh();
if(!get[1])
        {
         move(snake[1][snake[1].size()-1].y,snake[1][snake[1].size()-1].x);
         printw(" ");
         refresh();
         snake[1].pop_back();
        }

switch (direction[id])
            {
            case 'l': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][1].x-1,snake[id][1].y)); break;
            case 'r': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][1].x+1,snake[id][1].y)); break;
            case 'u': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][1].x,snake[id][1].y-1)); break;
            case 'd': snake[id].insert(snake[id].begin(),parts_of_Snake(snake[id][1].x,snake[id][1].y+1)); break;
             }

           move(snake[id][1].y,snake[id][1].x);
           addch(partchar);
           refresh();
 }


void TheSnake::start()
{
    while(1)
    {
        if(collision(0))
        {
            move(12,36);
            printw("Game_Over");
            break;
        }

        SnakeMovement(0);
                if(direction[0]=='q')				//exit
                break;
                usleep(Delayy);			//Linux delay


        if(collision2(1))
        {
            move(12,36);
            printw("Game_Over \n");
            break;
            }
        SnakeMovement(1);
            if(direction[1]=='q')				//exit
                break;
            usleep(Delayy);			//Linux delay
}
        if (score2 > score)
                printw("Snake[2] Won the Game!");
        else if (score > score2)
                printw("Snake[1] Won the Game!");
        else
            return;
            }





