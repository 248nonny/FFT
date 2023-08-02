#pragma once

#include "cairomm/context.h"
#include "cairomm/refptr.h"
#include <gtkmm/drawingarea.h>

// max params for graphs.
#define MAX_MAIN_LINE_COUNT 20
#define MAX_SUB_LINE_COUNT 40

#define MAX_DATAPOINTS 50

// for pads
#define PAD_TOP 0
#define PAD_RIGHT 1
#define PAD_BOTTOM 2
#define PAD_LEFT 3

#include <vector>

using GraphData = std::vector<std::vector<double>>;
#define DEFAULT_TEST_DATA_SIZE 50

struct Grid {
    bool runbefore = false;

    int prev_width;
    int prev_height;

    int width;
    int height;

    int xstart = 20;
    int xstop = 20000;
    int ystart = -125;
    int ystop = 25;

    double main_x_lines[MAX_MAIN_LINE_COUNT]; // main lines determine tick marks, sub lines are for visuals only.
    int main_x_line_count = 0;

    double sub_x_lines[MAX_SUB_LINE_COUNT];
    int sub_x_line_count = 0;

    double main_y_lines[MAX_MAIN_LINE_COUNT];
    int main_y_line_count = 0;

    double sub_y_lines[MAX_SUB_LINE_COUNT];
    int sub_y_line_count = 0;

    double main_y_line_increment = 25;
    double y_line_subdiv = 5;

    int pads[4] = {16,16,50,50}; // goes like compass, element 0 is up, 1 is right, 2 is bottom, 3 is left.
    // int pads[4] = {0,0,0,0};

    std::function<double(double)> trnfrm[2]; // first element is x trnfm, second is y.

    int fontsize = 12;

    float grid_line_rgba[4] = {0.7,0.7,0.7, 0.6};

    float data_line_width = 2;
    float data_line_rgba[4] = {1,0.27058,0,0.7};

    int text_offset = 10;
    int text_angle = 60;
    int thick_line_width = 4;
    int thin_line_width = 2;
};


class Graph : public Gtk::DrawingArea {
public:
    Graph();
    virtual ~Graph();

    Grid grid;
    GraphData data;
    int data_index;

protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void get_grid_lines();
    void find_trnfrm();
    void test_trnfrm(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_grid_lines(const Cairo::RefPtr<Cairo::Context>& cr);
    
    void draw_v_line(const Cairo::RefPtr<Cairo::Context>& cr, double x);
    void draw_h_line(const Cairo::RefPtr<Cairo::Context>& cr, double x);

    void plot_data(const Cairo::RefPtr<Cairo::Context>& cr);



    void make_random_data();
    void make_sine_data();
    void make_log_data();
    void make_linear_data();

    void reset_data();
    void sort_data_x();
};

