#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color
{
    WHITE,
    GREY,
    BLACK,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    PURPLE,
    CYAN
};

void draw_circle(double x_pos, double y_pos, double radius, Color color, bool filled = false, double thickness = 3.0);
static void set_color(Color color);

#endif
