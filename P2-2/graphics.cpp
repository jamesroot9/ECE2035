// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.


#include "graphics.h"

#include "globals.h"



int plus_five[11][11] = {
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK},
    {BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK},
    {BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
};

int poison[11][11] = {
    {BLACK, BLACK, BLACK, LGREY, LGREY, BLACK, LGREY, LGREY, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, LGREY, _RED_, LGREY, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, LGREY, _RED_, _RED_, _RED_, LGREY, BLACK, BLACK, BLACK},
    {BLACK, BLACK, LGREY, _RED_, _RED_, _RED_, _RED_, _RED_, LGREY, BLACK, BLACK},
    {BLACK, LGREY, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, LGREY, BLACK},
    {LGREY, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, LGREY},
    {LGREY, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, LGREY},
    {BLACK, LGREY, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, LGREY, BLACK},
    {BLACK, LGREY, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, LGREY, BLACK},
    {BLACK, BLACK, LGREY, LGREY, _RED_, _RED_, _RED_, LGREY, LGREY, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, LGREY, LGREY, LGREY, BLACK, BLACK, BLACK, BLACK}   
};

int speed[11][11] = {
    {BLACK, BLACK, BLACK, BLACK, YELLW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, YELLW, YELLW, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, YELLW, YELLW, YELLW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, YELLW, YELLW, YELLW, YELLW, BLACK, BLACK, BLACK},
    {YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, BLACK, BLACK},
    {BLACK, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, BLACK},
    {BLACK, BLACK, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW, YELLW},
    {BLACK, BLACK, BLACK, YELLW, YELLW, YELLW, YELLW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, YELLW, YELLW, YELLW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, YELLW, YELLW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, YELLW, BLACK, BLACK, BLACK, BLACK}
};

int slow[11][11] = {
    {BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, WHITE, WHITE, LGREY, BLACK, LGREY, WHITE, WHITE, BLACK, BLACK},
    {BLACK, WHITE, LGREY, LGREY, LGREY, BLACK, LGREY, LGREY, LGREY, WHITE, BLACK},
    {BLACK, WHITE, LGREY, LGREY, LGREY, BLACK, LGREY, LGREY, LGREY, WHITE, BLACK},
    {WHITE, LGREY, LGREY, LGREY, LGREY, BLACK, LGREY, LGREY, LGREY, LGREY, WHITE},
    {WHITE, LGREY, LGREY, LGREY, LGREY, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE},
    {WHITE, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, WHITE},
    {BLACK, WHITE, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, WHITE, BLACK},
    {BLACK, WHITE, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, LGREY, WHITE, BLACK},
    {BLACK, BLACK, WHITE, WHITE, LGREY, LGREY, LGREY, WHITE, WHITE, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK}
};

int good[11][11] = {
    {BLACK, BLACK, BLACK, BLACK, _BLUE, _BLUE, _BLUE, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, BLACK, BLACK, BLACK},
    {BLACK, BLACK, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, BLACK, BLACK},
    {BLACK, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, BLACK},
    {_BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE},
    {_BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE},
    {_BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE},
    {BLACK, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, BLACK},
    {BLACK, BLACK, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, BLACK, BLACK},
    {BLACK, BLACK, BLACK, _BLUE, _BLUE, _BLUE, _BLUE, _BLUE, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, _BLUE, _BLUE, _BLUE, BLACK, BLACK, BLACK, BLACK}
};

int plant[11][11] = {
    {BLACK, BLACK, BLACK, _RED_, _RED_, _RED_, _RED_, _RED_, BLACK, BLACK, BLACK},
    {BLACK, BLACK, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, BLACK, BLACK},
    {BLACK, _RED_, BLACK, _RED_, _RED_, _RED_, _RED_, _RED_, BLACK, _RED_, BLACK},
    {_RED_, _RED_, _RED_, BLACK, _RED_, YELLW, _RED_, BLACK, _RED_, _RED_, _RED_},
    {_RED_, _RED_, _RED_, _RED_, YELLW, YELLW, YELLW, _RED_, _RED_, _RED_, _RED_},
    {_RED_, _RED_, _RED_, YELLW, YELLW, YELLW, YELLW, YELLW, _RED_, _RED_, _RED_},
    {_RED_, _RED_, _RED_, _RED_, YELLW, YELLW, YELLW, _RED_, _RED_, _RED_, _RED_},
    {BLACK, _RED_, BLACK, BLACK, _RED_, YELLW, _RED_, BLACK, _RED_, _RED_, _RED_},
    {BLACK, BLACK, BLACK, _RED_, _RED_, _RED_, _RED_, _RED_, BLACK, _RED_, BLACK},
    {BLACK, BLACK, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, _RED_, BLACK, BLACK},
    {BLACK, BLACK, BLACK, _RED_, _RED_, _RED_, _RED_, _RED_, BLACK, BLACK, BLACK}
};

int snake_head[4][11][11] = 
{
    //north
{
    {BLACK, BLACK, BLACK, GREEN, _RED_, GREEN, _RED_, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, _RED_, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, _RED_, GREEN, GREEN, GREEN, GREEN, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, _RED_, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {GREEN, BLACK, WHITE, BLACK, GREEN, GREEN, GREEN, BLACK, WHITE, BLACK, GREEN},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN}
},
//east
{
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {GREEN, BLACK, WHITE, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, _RED_},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, _RED_, _RED_, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, _RED_},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, BLACK, WHITE, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK}
},
//south
{
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {GREEN, BLACK, WHITE, BLACK, GREEN, GREEN, GREEN, BLACK, WHITE, BLACK, GREEN},
    {GREEN, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, _RED_, GREEN, GREEN, GREEN, GREEN, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, _RED_, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, _RED_, GREEN, _RED_, GREEN, BLACK, BLACK, BLACK}
},
//west
{
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, WHITE, BLACK, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {_RED_, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, _RED_, _RED_, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {_RED_, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, WHITE, BLACK, GREEN},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, GREEN},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN}
}
};

int snake_tail[4][11][11] = 
{
{
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
},{
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN}
},{
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN}
},{
    {GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
}
};

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = _RED_;
        else if (img[i] == 'Y') colors[i] = 0xFFFF00; // YELLW
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = 0xD2691E; // "Dirt"
        else if (img[i] == '5') colors[i] = LGREY; // 50% grey
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_menu() {
    uLCD.filled_rectangle(1, 1, 128, 128, BLACK);
    uLCD.text_string("SNAKE", 10, 10, 20, GREEN);
    uLCD.text_string("press button 1 to start", 50, 5, 10, GREEN);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, _RED_);
}

void draw_plant(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    uLCD.BLIT(u, v, 11, 11, &plant[0][0]);
}

void draw_goodie(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    uLCD.BLIT(u, v, 11, 11, &good[0][0]);
}

void draw_snake_body_H(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_snake_body_V(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_snake_head_N(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    uLCD.BLIT(u, v, 11, 11, &snake_head[0][0][0]);
}

void draw_snake_head_E(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    uLCD.BLIT(u, v, 11, 11, &snake_head[1][0][0]);
}

void draw_snake_head_S(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    uLCD.BLIT(u, v, 11, 11, &snake_head[2][0][0]);
}

void draw_snake_head_W(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    uLCD.BLIT(u, v, 11, 11, &snake_head[3][0][0]);
}

void draw_snake_tail_N(int u, int v)
{
     //May need to design a snake tail sprite
     //Tile still need to be designed on paper
     
     uLCD.BLIT(u, v, 11, 11, &snake_tail[0][0][0]);
}
void draw_snake_tail_E(int u, int v)
{
     //May need to design a snake tail sprite
     //Tile still need to be designed on paper
     
     uLCD.BLIT(u, v, 11, 11, &snake_tail[1][0][0]);
}

void draw_snake_tail_S(int u, int v)
{
     //May need to design a snake tail sprite
     //Tile still need to be designed on paper
     
     uLCD.BLIT(u, v, 11, 11, &snake_tail[2][0][0]);
}

void draw_snake_tail_W(int u, int v)
{
     //May need to design a snake tail sprite
     //Tile still need to be designed on paper
     
     uLCD.BLIT(u, v, 11, 11, &snake_tail[3][0][0]);
}

void draw_plus_five(int u, int v) {
    uLCD.BLIT(u, v, 11, 11, &plus_five[0][0]);
}


void draw_poison(int u, int v) {
    uLCD.BLIT(u, v, 11, 11, &poison[0][0]);
}

void draw_speed(int u, int v) {
    uLCD.BLIT(u, v, 11, 11, &speed[0][0]);
}

void draw_slow(int u, int v) {
    uLCD.BLIT(u, v, 11, 11, &slow[0][0]);
}

DrawFunc tail(int i) {
    switch (i) {
        case 0:
            return draw_snake_tail_N;
        case 1:
            return draw_snake_tail_E;
        case 2:
            return draw_snake_tail_S;
        default:
            return draw_snake_tail_W;
    }
}

