// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define _RED_  0xFF0000
#define GREEN 0x00FF00
#define _BLUE  0x0000FF
#define LGREY 0xBFBFBF
#define DGREY 0x5F5F5F

#define YELLW 0xFFFF00
#define LBLUE 0x00FFFF
#define _PINK 0xFF80FF
#define VIOLT 0x8080FF
#define LGREN 0x80FF00
#define LPECH 0xF78D4C
#define DPECH 0xC96830
#define RPECH 0xF25427


typedef void (*DrawFunc)(int u, int v);
/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions. 
 * These can be used as the MapItem draw functions.
 */
 
void draw_nothing(int u, int v);
void draw_menu();
void draw_plant(int u, int v);
void draw_wall(int u, int v);
void draw_goodie(int u, int v);
void draw_snake_body_H(int u, int v);
void draw_snake_body_V(int u, int v);
void draw_snake_head_N(int u, int v);
void draw_snake_head_E(int u, int v);
void draw_snake_head_S(int u, int v);
void draw_snake_head_W(int u, int v);
void draw_snake_tail_N(int u, int v);
void draw_snake_tail_E(int u, int v);
void draw_snake_tail_S(int u, int v);
void draw_snake_tail_W(int u, int v);
void draw_plus_five(int u, int v);
void draw_poison(int u, int v);
void draw_speed(int u, int v);
void draw_slow(int u, int v);
DrawFunc tail(int i);

#endif // GRAPHICS_H