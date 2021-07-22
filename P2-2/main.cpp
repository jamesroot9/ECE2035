//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "snake.h"

#include <math.h>
#include<stdio.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);

void draw_game(int draw_option);

/**
 * The main game state. Must include snake locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
Snake snake;
#define MENU 0
#define GAME 1
#define PAUSE 2
static int gameState = MENU;
static int invincible = 0;
static int waittime = 100;
// Function prototypes

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 */
#define NO_RESULT 0
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GAME_OVER 7
#define FULL_DRAW 8
#define INVINCIBLE 9
#define DRAW_MENU 10
#define PAUSE_BUTTON 11
#define HARD_MODE 12
#define EASY_MODE 13
#define STANDARD_MODE 14

// Get Actions from User (push buttons & accelerometer)
// Based on push button and accelerometer inputs, determine which action
// needs to be performed (may be no action).
int get_action(GameInputs inputs)
{
    switch(gameState) {
        case MENU:
            if (inputs.b1 == 0 && inputs.b2 == 1 && inputs.b3 == 1) return EASY_MODE;
            if (inputs.b1 == 1 && inputs.b2 == 0 && inputs.b3 == 1) return STANDARD_MODE;
            if (inputs.b1 == 1 && inputs.b2 == 1 && inputs.b3 == 0) return HARD_MODE;
            else return NO_ACTION;
        case GAME:
            if (inputs.b1 == 1 && inputs.b2 == 1 && inputs.b3 == 0) return PAUSE_BUTTON;
            if (inputs.b1 == 1 && inputs.b2 == 0 && inputs.b3 == 1) return INVINCIBLE;
            if (inputs.ax == 0 && inputs.ay == 0) return NO_ACTION; 
            if (fabs(inputs.ax) > fabs(inputs.ay)) {
                if (inputs.ax < 0) {
                    return GO_LEFT;
                } else {
                    return GO_RIGHT;
                }
            }
            if (fabs(inputs.ax) < fabs(inputs.ay)){
                if (inputs.ay < 0) {
                    return GO_DOWN;
                }
                else {
                    return GO_UP;
                }
            }
            return NO_ACTION;
        case PAUSE:
            if (inputs.b1 == 1 && inputs.b2 == 1 && inputs.b3 == 0) return PAUSE_BUTTON;
        default:
            return NO_ACTION;
    }
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the snake position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the snake has not moved.
 */
int update_game(int action) {
    MapItem* next;
    switch (action) {
        case EASY_MODE:
            waittime = 400;
            gameState = GAME;
            return EASY_MODE;
        case STANDARD_MODE:
            waittime = 200;
            gameState = GAME;
            return STANDARD_MODE;
        case HARD_MODE:
            waittime = 100;
            gameState = GAME;
            return HARD_MODE;
        case PAUSE_BUTTON:
            
            if (gameState == PAUSE)
                gameState = GAME;
            else gameState = PAUSE;
            return NO_ACTION;
                
        case INVINCIBLE : 
            invincible = !invincible;
        case GO_LEFT:
            if (gameState == MENU || gameState == PAUSE)
                return NO_ACTION;
            next = get_west(snake.head_x, snake.head_y);
            if (next->walkable) {
                switch (next->type) {
                    case GOODIE:
                        snake.length += 2;
                        snake.score += 2;
                        break;
                    case PLUS_5:
                        snake.score = snake.score + 5;
                        draw_game(0);
                        break;
                    case POISON:
                        snake.score -= 10;
                        if (snake.score <= 0) {
                            return GAME_OVER;
                        }
                        break;
                    case SPEED:
                        waittime /= 2;
                        break;
                    case SLOW:
                        waittime *= 2;
                        break;
                    default:
                        break;
                }
                return GO_LEFT;
            }
            return GAME_OVER;
        case GO_RIGHT:
            if (gameState == MENU || gameState == PAUSE)
                return NO_ACTION;
            next = get_east(snake.head_x, snake.head_y);
            if (next->walkable) {
                switch (next->type) {
                    case GOODIE:
                        snake.length += 2;
                        snake.score += 2;
                        break;
                    case PLUS_5:
                        snake.score += 5;
                        break;
                    case POISON:
                        snake.score -= 10;
                        if (snake.score <= 0) {
                            return GAME_OVER;
                        }
                        break;
                    case SPEED:
                        waittime /= 2;
                        break;
                    case SLOW:
                        waittime *= 2;
                        break;
                    default:
                        break;
                }
                return GO_RIGHT;
            }
            return GAME_OVER;
        case GO_UP:
            if (gameState == MENU || gameState == PAUSE)
                return NO_ACTION;
            next = get_north(snake.head_x, snake.head_y);
            if (next->walkable) {
                switch (next->type) {
                    case GOODIE:
                        snake.length += 2;
                        snake.score += 2;
                        break;
                    case PLUS_5:
                        snake.score += 5;
                        break;
                    case POISON:
                        snake.score -= 10;
                        if (snake.score <= 0) {
                            return GAME_OVER;
                        }
                        break;
                    case SPEED:
                        waittime /= 2;
                        break;
                    case SLOW:
                        waittime *= 2;
                        break;
                    default:
                        break;
                }
                return GO_UP;
            }
            return GAME_OVER;
        case GO_DOWN:
            if (gameState == MENU || gameState == PAUSE)
                return NO_ACTION;
            next = get_south(snake.head_x, snake.head_y);
            if (next->walkable) {
                switch (next->type) {
                    case GOODIE:
                        snake.length += 2;
                        snake.score += 2;
                        break;
                    case PLUS_5:
                        snake.score += 5;
                        break;
                    case POISON:
                        snake.score -= 10;
                        if (snake.score <= 0) {
                            return GAME_OVER;
                        }
                        break;
                    case SPEED:
                        waittime /= 2;
                        break;
                    case SLOW:
                        waittime *= 2;
                        break;
                    default:
                        break;
                }
                return GO_DOWN;
            }
            return GAME_OVER; 
        default:
            return NO_ACTION;
    }
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int draw_option)
{
    
    uLCD.locate(0,0);
    uLCD.printf("Pos:%i,%i Score:%i ", snake.head_x, snake.head_y, snake.score);
    // Draw game border first
    if(draw_option == FULL_DRAW) 
    {
        draw_border();
        int u = 58;
        int v = 56;
        draw_snake_head_E(u, v);
        draw_snake_body_H(u-11, v);
        draw_snake_tail_E(u-22, v);
        return;
    }
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + snake.head_x;
            int y = j + snake.head_y;

            // Compute the previous map (px, py) of this tile
            int px = i + snake.head_px;
            int py = j + snake.head_py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }
            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map_Easy()
{
    srand(time(NULL));
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39) {
        add_goodie(i % map_width(), i / map_width());
    }
    
    //generate 64 random goodies
    for (int i = 0; i < 64; i++) {
        int r = rand() % map_area();
        add_goodie(r % map_width(), r / map_width());
    }
    pc.printf("plants\r\n");

    //generate randomly positioned speed objects
    for (int i = 0; i < 6; i++) {
        int r = rand() % map_area();
        add_speed(r % map_width(), r / map_width());
    }
    pc.printf("speed\r\n");
    
    //generate randomly positioned slow objects
    for (int i = 0; i < 6; i++) {
        int r = rand() % map_area();
        add_slow(r % map_width(), r / map_width());
    }
    pc.printf("slow\r\n");
    
    //generate randomly positioned poison objects
    for (int i = 0; i < 6; i++) {
        int r = rand() % map_area();
        add_poison(r % map_width(), r / map_width());
    }
    pc.printf("poison\r\n");
    
    //generate randomly positioned plus 5 objects
    for (int i = 0; i < 6; i++) {
        int r = rand() % map_area();
        add_plus_5(r % map_width(), r / map_width());
    }
    pc.printf("plus5\r\n");

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    //add_snake_head_E(snake.locations[0].x, snake.locations[0].y);
    //add_snake_body_H(snake.locations[1].x, snake.locations[1].y);
    //add_snake_tail_E(snake.locations[2].x, snake.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    pc.printf("Added!\r\n");


    // Add stairs to chamber (map 1)
    //add_stairs(15, 5, 1, 5, 5);

//    profile_hashtable();
    print_map();
}

void init_main_map_standard()
{
    srand(time(NULL));
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39) {
        add_goodie(i % map_width(), i / map_width());
    }
    
    //generate 64 random goodies
    for (int i = 0; i < 64; i++) {
        int r = rand() % map_area();
        add_goodie(r % map_width(), r / map_width());
    }
    pc.printf("plants\r\n");

    //generate randomly positioned speed objects
    for (int i = 0; i < 18; i++) {
        int r = rand() % map_area();
        add_speed(r % map_width(), r / map_width());
    }
    pc.printf("speed\r\n");
    
    //generate randomly positioned slow objects
    for (int i = 0; i < 6; i++) {
        int r = rand() % map_area();
        add_slow(r % map_width(), r / map_width());
    }
    pc.printf("slow\r\n");
    
    //generate randomly positioned poison objects
    for (int i = 0; i < 12; i++) {
        int r = rand() % map_area();
        add_poison(r % map_width(), r / map_width());
    }
    pc.printf("poison\r\n");
    
    //generate randomly positioned plus 5 objects
    for (int i = 0; i < 9; i++) {
        int r = rand() % map_area();
        add_plus_5(r % map_width(), r / map_width());
    }
    pc.printf("plus5\r\n");

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    add_snake_head_E(snake.locations[0].x, snake.locations[0].y);
    add_snake_body_H(snake.locations[1].x, snake.locations[1].y);
    add_snake_tail_E(snake.locations[2].x, snake.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    pc.printf("Added!\r\n");


    // Add stairs to chamber (map 1)
    //add_stairs(15, 5, 1, 5, 5);

//    profile_hashtable();
    print_map();
}

void init_main_map_hard()
{
    srand(time(NULL));
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39) {
        add_goodie(i % map_width(), i / map_width());
    }
    
    //generate 64 random goodies
    for (int i = 0; i < 64; i++) {
        int r = rand() % map_area();
        add_goodie(r % map_width(), r / map_width());
    }
    pc.printf("plants\r\n");

    //generate randomly positioned speed objects
    for (int i = 0; i < 30; i++) {
        int r = rand() % map_area();
        add_speed(r % map_width(), r / map_width());
    }
    pc.printf("speed\r\n");
    
    //generate randomly positioned slow objects
    for (int i = 0; i < 3; i++) {
        int r = rand() % map_area();
        add_slow(r % map_width(), r / map_width());
    }
    pc.printf("slow\r\n");
    
    //generate randomly positioned poison objects
    for (int i = 0; i < 18; i++) {
        int r = rand() % map_area();
        add_poison(r % map_width(), r / map_width());
    }
    pc.printf("poison\r\n");
    
    //generate randomly positioned plus 5 objects
    for (int i = 0; i < 12; i++) {
        int r = rand() % map_area();
        add_plus_5(r % map_width(), r / map_width());
    }
    pc.printf("plus5\r\n");

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    //add_snake_head_E(snake.locations[0].x, snake.locations[0].y);
    //add_snake_body_H(snake.locations[1].x, snake.locations[1].y);
    //add_snake_tail_E(snake.locations[2].x, snake.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    pc.printf("Added!\r\n");


    // Add stairs to chamber (map 1)
    //add_stairs(15, 5, 1, 5, 5);

//    profile_hashtable();
    print_map();
}

/**
 * Program entry point! This is where it all begins.
 * This function or all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    // 0. Initialize the maps -- implement this function:
    maps_init();
    
    while(1) {
        switch (gameState) {
            case MENU:
                //draw_menu();
                uLCD.cls();
                uLCD.printf("\n\n\n       SNAKE\n\n\n\n\n\n\n");
                uLCD.printf(" 1 - Easy \n 2 - Standard\n 3 - Hard");
                int result = NO_ACTION;
                while (result == NO_ACTION) {
                    GameInputs inputs = read_inputs();
                    int action = get_action(inputs);
                    int result = update_game(action);
                    if (result == EASY_MODE) {
                        init_main_map_Easy();
                        set_active_map(0);
                        break;
                    }
                    if (result == STANDARD_MODE) {
                        init_main_map_standard();
                        set_active_map(0);
                        break;
                    }
                    if (result == HARD_MODE) {
                        init_main_map_hard();
                        set_active_map(0);
                        break;
                    }    
                }
                uLCD.cls();
                wait(.5);
                gameState = GAME;
            case GAME:
                snake_init(&snake);
                // Initial drawing
                draw_game(FULL_DRAW);
                // Main game loop
                while (1) {   
                    int over = 0; 
                    // Timer to measure game update speed
                    Timer t;
                    t.start();
                    // 1. Read inputs -- implement this function:
                    GameInputs inputs = read_inputs();
            
                    // 2. Determine action (move, act, menu, etc.) -- implement this function:
                    int action = get_action(inputs);
            
                    // 3. Update game -- implement this function:
                    int result = update_game(action);
            
                    // 3b. Check for game over based on result
                    // and if so, handle game over -- implement this.
                    int typ;
                    switch (result) {
                        case GO_LEFT:
                            //remove tail
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = CLEAR;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = draw_nothing;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->walkable = 1; 
                            snake.head_px = snake.head_x;
                            snake.head_py = snake.head_y;
                            snake.head_x = snake.head_x - 1;
                            add_snake_body_H(snake.head_px, snake.head_py);
                            add_snake_head_W(snake.head_x, snake.head_y);
                            for (int i = snake.length - 1; i > 0; i--) {
                                snake.locations[i].x = snake.locations[i - 1].x;
                                snake.locations[i].y = snake.locations[i - 1].y;
                                snake.locations[i].dir = snake.locations[i - 1].dir;
                            }
                            typ = TAIL_N + snake.locations[snake.length - 1].dir;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = typ;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = tail(snake.locations[snake.length - 1].dir);
                            snake.locations[0].x = snake.head_x;
                            snake.locations[0].y = snake.head_y;
                            snake.locations[0].dir = 3;
                            break;
                        case GO_RIGHT:
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = CLEAR;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = draw_nothing;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->walkable = 1; 
                            snake.head_px = snake.head_x;
                            snake.head_py = snake.head_y;
                            snake.head_x = snake.head_x + 1;
                            add_snake_body_H(snake.head_px, snake.head_py);
                            add_snake_head_E(snake.head_x, snake.head_y);
                            for (int i = snake.length - 1; i > 0; i--) {
                                snake.locations[i].x = snake.locations[i - 1].x;
                                snake.locations[i].y = snake.locations[i - 1].y;
                                snake.locations[i].dir = snake.locations[i - 1].dir;
                            }
                            typ = TAIL_N + snake.locations[snake.length - 1].dir;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = typ;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = tail(snake.locations[snake.length - 1].dir);
                            snake.locations[0].x = snake.head_x;
                            snake.locations[0].y = snake.head_y;
                            snake.locations[0].dir = 1;
                            break;
                        case GO_DOWN:
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = CLEAR;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = draw_nothing;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->walkable = 1; 
                            snake.head_px = snake.head_x;
                            snake.head_py = snake.head_y;
                            snake.head_y = snake.head_y + 1;
                            add_snake_body_V(snake.head_px, snake.head_py);
                            add_snake_head_S(snake.head_x, snake.head_y);
                            for (int i = snake.length - 1; i > 0; i--) {
                                snake.locations[i].x = snake.locations[i - 1].x;
                                snake.locations[i].y = snake.locations[i - 1].y;
                                snake.locations[i].dir = snake.locations[i - 1].dir;
                            }
                            typ = TAIL_N + snake.locations[snake.length - 1].dir;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = typ;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = tail(snake.locations[snake.length - 1].dir);
                            snake.locations[0].x = snake.head_x;
                            snake.locations[0].y = snake.head_y;
                            snake.locations[0].dir = 2;
                            break;
                        case GO_UP:
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = CLEAR;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = draw_nothing;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->walkable = 1; 
                            snake.head_px = snake.head_x;
                            snake.head_py = snake.head_y;
                            snake.head_y = snake.head_y - 1;
                            add_snake_body_V(snake.head_px, snake.head_py);
                            add_snake_head_N(snake.head_x, snake.head_y);
                            for (int i = snake.length - 1; i > 0; i--) {
                                snake.locations[i].x = snake.locations[i - 1].x;
                                snake.locations[i].y = snake.locations[i - 1].y;
                                snake.locations[i].dir = snake.locations[i - 1].dir;
                            }
                            typ = TAIL_N + snake.locations[snake.length - 1].dir;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->type = typ;
                            get_here(snake.locations[snake.length-1].x, snake.locations[snake.length-1].y)->draw = tail(snake.locations[snake.length - 1].dir);
                            snake.locations[0].x = snake.head_x;
                            snake.locations[0].y = snake.head_y;
                            snake.locations[0].dir = 0;
                            break;
                        case GAME_OVER:
                            if (!invincible) {
                                uLCD.cls();
                                uLCD.printf("\n\n\n\n\n     GAME OVER");
                                while (1) {
                                    wait(1);
                                }
                                //gameState = MENU;
                                //over = 1;
                            }
                        default:
                            break;
                    }
                    
                    if (over) break;
                    // 4. Draw screen -- provided:]
                    draw_border();
                    draw_game(result);
            
                    // Compute update time
                    t.stop();
                    int dt = t.read_ms();
        
                    // Display and wait
                    // NOTE: Text is 8 pixels tall
                    if (dt < waittime) wait_ms(waittime - dt);
                }
                break;
            case PAUSE:
                uLCD.locate(0,119);
                uLCD.printf("PAUSED         ");
                while (1) {
                    if (!button3.read()) {
                        break;
                    }
                }
                draw_game(0);
                gameState = GAME;
                break;
            default:
                break;
        }
    }
}

// Plays a wavfile
void playSound(char* wav)
{
    FILE* sound = fopen(wav, "r");
    waver.play(sound);
    fclose(sound);\
}