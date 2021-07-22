// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

#define NUM_MAPS 1
static Map maps[NUM_MAPS];
static int active_map;

static const MapItem CLEAR_SENTINEL = {
    .type = CLEAR,
    .draw = draw_nothing,
    .walkable = 1
};

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
     // TODO: Fix me!
     return X * 50 + Y;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // TODO: Fix me!
    return key % 50;
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    // Set width & height
    maps[active_map].w = 50;
    maps[active_map].h = 50;
    maps[active_map].items = createHashTable(map_hash, 50);
}

Map* get_active_map()
{
    return &maps[active_map];
}

Map* set_active_map(int m)
{
    active_map = m;
    return &maps[active_map];
}

void print_map()
{
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++)
    {
        for (int i = 0; i < map->w; i++)
        {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    return maps[active_map].w;
}

int map_height()
{
    return maps[active_map].h;
}

int map_area()
{
    return maps[active_map].w * maps[active_map].h;
}
MapItem* get_current(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y));
}
MapItem* get_north(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y - 1));  
}
MapItem* get_south(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y + 1));
}

MapItem* get_east(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x + 1, y));   
}

MapItem* get_west(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x - 1, y));
}

MapItem* get_here(int x, int y)
{
    return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y));
}

void map_erase(int x, int y)
{
    deleteItem(get_active_map()->items, XY_KEY(x, y));
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_goodie(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GOODIE;
    w1->draw = draw_goodie;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void remove_goodie(int x, int y) // I'm lazy so overwrite it with a plant
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_body_H(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BODY_H;
    w1->draw = draw_snake_body_H;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_body_V(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BODY_H;
    w1->draw = draw_snake_body_V;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_head_N(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = HEAD_N;
    w1->draw = draw_snake_head_N;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_head_E(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = HEAD_E;
    w1->draw = draw_snake_head_E;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_head_S(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = HEAD_S;
    w1->draw = draw_snake_head_S;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_head_W(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = HEAD_W;
    w1->draw = draw_snake_head_W;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_tail_N(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TAIL_N;
    w1->draw = draw_snake_tail_N;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_tail_S(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TAIL_S;
    w1->draw = draw_snake_tail_S;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_tail_E(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TAIL_E;
    w1->draw = draw_snake_tail_E;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_tail_W(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TAIL_W;
    w1->draw = draw_snake_tail_W;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_speed(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SPEED;
    w1->draw = draw_speed;
    w1->walkable = 1;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_slow(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SLOW;
    w1->draw = draw_slow;
    w1->walkable = 1;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_plus_5(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLUS_5;
    w1->draw = draw_plus_five;
    w1->walkable = 1;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_poison(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = POISON;
    w1->draw = draw_poison;
    w1->walkable = 1;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

