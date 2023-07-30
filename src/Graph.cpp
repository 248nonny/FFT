
#include "Graph.hpp"
#include <gtkmm/drawingarea.h>


Graph::Graph() {
    set_vexpand(TRUE);
    set_hexpand(TRUE);
    set_margin(0);
    set_size_request(grid.pads[PAD_LEFT] + grid.pads[PAD_RIGHT], grid.pads[PAD_TOP] + grid.pads[PAD_BOTTOM]);
    set_draw_func(sigc::mem_fun(*this, &Graph::on_draw));
}

Graph::~Graph() {
}

void Graph::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    grid.width = width;
    grid.height = height;

    cr->move_to(0, 0);
    cr->line_to(width, height);
    cr->stroke();
}