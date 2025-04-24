#include <cmath>
#include <iostream>
#include "graphic_gui.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context> *ptcr(nullptr);

// local prototypes
static void set_color(color_t color);
// graphic_gui.h

void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr) {
    ptcr = &cr;
}

void draw_circle(double x,
				 double y,
				 double radius,
				 color_t color,
				 bool filled,
				 double thickness) {
    (*ptcr)->set_line_width(thickness);
    set_color(color);
    (*ptcr)->arc(x, y, radius, 0, 2 * M_PI);
    if (filled) (*ptcr)->fill();
    else 		(*ptcr)->stroke();
	return;
};

void draw_rect(double x,
			   double y,
			   double width,
			   double height,
			   color_t color,
			   bool filled,
			   double thickness) {
    (*ptcr)->set_line_width(thickness);
    set_color(color);
	(*ptcr)->rectangle(x, y, width, height);
    if (filled) (*ptcr)->fill();
    else 		(*ptcr)->stroke();
	return;
}

void draw_segment(double baseX,
				  double baseY,
				  double endX,
				  double endY,
				  color_t color,
				  double thickness) {
    (*ptcr)->set_line_width(thickness);
    set_color(color);
    (*ptcr)->move_to(baseX, baseY);
    (*ptcr)->line_to(endX, endY);
    (*ptcr)->stroke();
}
// à compléter pour effectuer des dessins élémentaires: trait, cercle, ...


// local function
static void set_color(color_t color) {
    (*ptcr)->set_source_rgb(color.r, color.g, color.b);
}
