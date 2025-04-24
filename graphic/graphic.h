#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color {
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

void draw_circle(double x,
				 double y,
				 double radius,
				 Color color = BLACK,
				 bool filled = false,
				 double thickness = 1.0);
void draw_rect(double x,
			   double y,
			   double width,
			   double height,
			   Color color = BLACK,
			   bool filled = false,
			   double thickness = 1.0);
void draw_segment(double baseX,
				  double baseY,
				  double endX,
				  double endY,
				  Color color = BLACK,
				  double thickness = 1.0);
static void set_color(Color color);

#endif
