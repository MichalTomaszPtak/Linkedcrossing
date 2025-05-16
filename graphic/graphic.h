#ifndef GRAPHIC_H
#define GRAPHIC_H

typedef struct {
	double r;
	double g;
	double b;
} color_t;

constexpr color_t WHITE		= {1.0,  1.0,  1.0};
constexpr color_t GREY		= {0.5,  0.5,  0.5};
constexpr color_t BLACK		= {0.0,  0.0,  0.0};
constexpr color_t RED		= {1.0,  0.0,  0.0};
constexpr color_t GREEN		= {0.0,  0.65, 0.0};
constexpr color_t BLUE		= {0.65, 0.65, 1.0};
constexpr color_t ORANGE	= {1.0,	 0.65, 0.0};
constexpr color_t PURPLE	= {0.65, 0.0,  0.65};
constexpr color_t CYAN		= {0.0,	 1.0,  1.0};

void draw_circle(double x,
				 double y,
				 double radius,
				 color_t stroke_color = BLACK,
				 double thickness = 1.0,
				 bool filled = false,
				 color_t fill_color = BLACK);
void draw_rect(double x,
			   double y,
			   double width,
			   double height,
			   color_t color = BLACK,
			   bool filled = false,
			   double thickness = 1.0);
void draw_segment(double baseX,
				  double baseY,
				  double endX,
				  double endY,
				  color_t color = BLACK,
				  double thickness = 1.0);

#endif
