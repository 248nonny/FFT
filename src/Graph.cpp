
#include "Graph.hpp"
#include <gtkmm/drawingarea.h>
#include <cmath>

Graph::Graph() {
    set_vexpand(true);
    set_hexpand(true);
    set_margin(0);
    set_size_request(grid.pads[PAD_LEFT] + grid.pads[PAD_RIGHT], grid.pads[PAD_TOP] + grid.pads[PAD_BOTTOM]);
    set_draw_func(sigc::mem_fun(*this, &Graph::on_draw));
}

Graph::~Graph() {
}

void Graph::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    grid.width = width;
    grid.height = height;

    cr->set_line_width(grid.thin_line_width);
    cr->set_source_rgba(grid.grid_line_rgba[0],grid.grid_line_rgba[1],grid.grid_line_rgba[2],grid.grid_line_rgba[3]);
    find_trnfrm();

    // printf("%f\n",grid.trnfrm[1](0));

    // cr->move_to(grid.trnfrm[0](grid.xstart), grid.trnfrm[1](grid.ystart));
    // cr->line_to(grid.trnfrm[0](grid.xstop), grid.trnfrm[0](grid.ystop));
    test_trnfrm(cr);
    cr->stroke();
}

void Graph::find_trnfrm() {
    // for x:
    long double a,b;

    a = (grid.width - grid.pads[PAD_LEFT] - grid.pads[PAD_RIGHT]) / (log10(grid.xstop) - log10(grid.xstart));
    b = grid.pads[PAD_LEFT] - a * log10(grid.xstart);
    grid.trnfrm[0] = [a,b](double xval) {return a * log10(xval) + b;};

    // now for y:
    a = (double)(grid.height - grid.pads[PAD_TOP] - grid.pads[PAD_BOTTOM]) / (double)(grid.ystart - grid.ystop);
    b = grid.pads[PAD_TOP] - a * grid.ystop;
    grid.trnfrm[1] = [a,b](double yval) {return a * yval + b;};
}

void Graph::get_grid_lines() {

}

void Graph::test_trnfrm(const Cairo::RefPtr<Cairo::Context>& cr) {

    float slope = (float)(grid.ystop - grid.ystart) / (float)(grid.xstop - grid.xstart); // y = ax + b
    float b = grid.ystart - slope * grid.xstart;

    cr->move_to(grid.trnfrm[0](grid.xstart), grid.trnfrm[1](grid.ystart));

    for (int i = 0; i < 50; i++) {
        float x = grid.xstart + ((float)(grid.xstop - grid.xstart) / 50) * i;
        float y = slope * x + b;
        cr->line_to(grid.trnfrm[0](x),grid.trnfrm[1](y));
    }

    cr->stroke();

}