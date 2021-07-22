// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "snake.h"

void snake_init (Snake * s)
{
    s->head_x = 5;
    s->head_y = 4;
    s->head_px = 4;
    s->head_py = 4;
    s->length = 3;
    s->score = 3;
}
