#pragma once

#include "cairomm/context.h"
#include "cairomm/refptr.h"
#include <gtkmm/drawingarea.h>

#define MAX_MAIN_LINE_COUNT 20
#define MAX_SUB_LINE_COUNT 40

// for pads
#define PAD_TOP 0
#define PAD_RIGHT 1
#define PAD_BOTTOM 2
#define PAD_LEFT 3


struct Grid {
    int width;
    int height;

    int xstart = 20;
    int xstop = 20000;
    int ystart = -125;
    int ystop = 25;

    double main_x_lines[MAX_MAIN_LINE_COUNT]; // main lines determine tick marks, sub lines are for visuals only.
    double sub_x_lines[MAX_SUB_LINE_COUNT];
    double main_y_lines[MAX_MAIN_LINE_COUNT];
    double sub_y_lines[MAX_SUB_LINE_COUNT];

    int pads[4] = {16,35,35,50}; // goes like compass, element 0 is up, 1 is right, 2 is down, 3 is left.
    // int pads[4] = {0,0,0,0};

    std::function<double(double)> trnfrm[2]; // first element is x trnfm, second is y.

    int fontsize = 14;
    float grid_line_rgba[4] = {0.7,0.7,0.7, 0.6};
    int text_offset = 1;
    int text_angle = 30;
    int thick_line_width = 5;
    int thin_line_width = 2;
};



class Graph : public Gtk::DrawingArea {
public:
    Graph();
    virtual ~Graph();

    Grid grid;

protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void get_grid_lines();
    void find_trnfrm();
    void test_trnfrm(const Cairo::RefPtr<Cairo::Context>& cr);
};