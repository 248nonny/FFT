
#include "Graph.hpp"
#include <gtkmm/drawingarea.h>
#include <cmath>
#include <string>

Graph::Graph() {

    reset_data();

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

    if (!grid.runbefore) {
        find_trnfrm();
        get_grid_lines();

        cr->set_line_cap(Cairo::Context::LineCap::ROUND);
        make_log_data();
        // make_linear_data();
        sort_data_x();
    }



    if (grid.prev_height != height || grid.prev_width !=width) {

        find_trnfrm();

        // printf("%f\n",grid.trnfrm[1](0));

        // cr->move_to(grid.trnfrm[0](grid.xstart), grid.trnfrm[1](grid.ystart));
        // cr->line_to(grid.trnfrm[0](grid.xstop), grid.trnfrm[0](grid.ystop));
        // test_trnfrm(cr);
        get_grid_lines();
    }
    draw_grid_lines(cr);
    cr->stroke();

    // reset_data();
    // make_random_data();
    plot_data(cr);
    cr->stroke();

    if (!grid.runbefore) {
        grid.runbefore = true;
    }
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

    grid.prev_height = grid.height;
    grid.prev_width = grid.width;

    // find main log x lines.
    float logdiff = log10((double)grid.xstop / (double)grid.xstart);

    grid.main_x_line_count = ceil(logdiff);

    for (int i = 0; i < grid.main_x_line_count; i++) {
        grid.main_x_lines[i] = pow(10, ceil(log10(grid.xstart))) * pow(10, i);
        // printf("BL: %d\n",(int)grid.main_x_lines[i]);
    }

    // find sub x lines.
    grid.sub_x_line_count = 0;

    short int firstPow = ceil(log10(grid.xstart));
    short int lastPow = floor(log10(grid.xstop));

    // first we loop thru and find the leftmost lines (to the left of the first big line):
    for (int i = 0; i < 10; i++) {
        double val = pow(10,firstPow) - (i + 1) * pow(10, firstPow - 1);

        if (val >= grid.xstart) {
            grid.sub_x_lines[i] = val;
            // printf("val: %f\n",val);
        } else {
            grid.sub_x_line_count = i;
            break;
        }
    }

    // now we add 8 multiples (of sub lines) for each main x line (except the last):
    for (int i = 0; i < grid.main_x_line_count - 1; i++) {
        double &mVal = grid.main_x_lines[i];


        // why did I write this? great question. am re-reading it now, and no clue tbh :P
        // I guess I'll just leave it here lol
        if (mVal == 0) {
            break;
        }

        for (int i = 0; i < 8; i++) {
            grid.sub_x_lines[grid.sub_x_line_count] = mVal * (i + 2);
            grid.sub_x_line_count++;
        }
    }

    // now we get the values after the last big line:
    for (int i = 0; i < 10; i++) {
        double val = pow(10,lastPow) + (i + 1) * pow(10,lastPow);

        if (val <= grid.xstop) {
            grid.sub_x_lines[grid.sub_x_line_count] = val;
            grid.sub_x_line_count++;
        } else {
            break;
        }
    }



    // now for the y lines :o
    int ydiff = grid.ystop - grid.ystart;
    grid.main_y_line_count = (((int)(ydiff*1000) % (int)(grid.main_y_line_increment*1000)) == 0 && (int)(grid.ystart*1000)%(int)(grid.main_y_line_increment*1000) == 0) ? floor((float)ydiff/(float)grid.main_y_line_increment) + 1 : floor((float)ydiff/(float)grid.main_y_line_increment);

    //main y lines:
    for (int i = 0; i < grid.main_y_line_count; i++) {
        grid.main_y_lines[i] = grid.ystart + i * grid.main_y_line_increment;
    }


    // sub y lines:
    for (int i = 0; i < grid.main_y_line_count * grid.y_line_subdiv; i++) {
        double val = grid.ystart + i * ((float)grid.main_y_line_increment/(float)grid.y_line_subdiv);
        if ((int)(val*1000)%(int)(grid.main_y_line_increment * 1000) == 0 && val <= grid.ystop) {
            grid.sub_y_lines[i] = val;
        } else {
            grid.sub_y_line_count = i;
            break;
        }
    }
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

void Graph::draw_grid_lines(const Cairo::RefPtr<Cairo::Context>& cr) {

    cr->set_source_rgba(grid.grid_line_rgba[0],grid.grid_line_rgba[1],grid.grid_line_rgba[2],grid.grid_line_rgba[3]);
    cr->set_font_size(grid.fontsize);

    // draw main x lines
    for (int i = 0; i < grid.main_x_line_count; i++) {
        double &x = grid.main_x_lines[i];
        draw_v_line(cr, x);
        
        cr->move_to(grid.trnfrm[0](x) - 6, grid.trnfrm[1](grid.ystart) + grid.text_offset);
        cr->rotate_degrees(grid.text_angle);
        cr->show_text(std::to_string((int)x));
        cr->rotate_degrees(-grid.text_angle);
    }

    // draw main y lines
    for (int i = 0; i < grid.main_y_line_count; i++) {
        double y = grid.main_y_lines[i];
        draw_h_line(cr, y);
        cr->move_to(grid.xstart - grid.text_offset,grid.trnfrm[1](y) + 0.3 * grid.fontsize);
        cr->show_text(std::to_string((int)y));

    }

    cr->set_line_width(grid.thick_line_width);
    cr->stroke();

    //draw sub x lines
    for (int i = 0; i < grid.sub_x_line_count; i++) {
        draw_v_line(cr, grid.sub_x_lines[i]);
    }

    // draw sub y lines
    for (int i = 0; i < grid.sub_y_line_count; i++) {
        draw_h_line(cr, grid.sub_y_lines[i]);
    }

    cr->set_line_width(grid.thin_line_width);
    cr->stroke();
}

void Graph::draw_v_line(const Cairo::RefPtr<Cairo::Context>& cr, double x) {
    cr->move_to(grid.trnfrm[0](x), grid.trnfrm[1](grid.ystart));
    cr->line_to(grid.trnfrm[0](x), grid.trnfrm[1](grid.ystop));
}

void Graph::draw_h_line(const Cairo::RefPtr<Cairo::Context>& cr, double y) {
    cr->move_to(grid.trnfrm[0](grid.xstart), grid.trnfrm[1](y));
    cr->line_to(grid.trnfrm[0](grid.xstop), grid.trnfrm[1](y));
}


void Graph::plot_data(const Cairo::RefPtr<Cairo::Context>& cr) {
    
    cr->set_line_width(grid.data_line_width);
    cr->set_source_rgba(grid.data_line_rgba[0],grid.data_line_rgba[1],grid.data_line_rgba[2],grid.data_line_rgba[3]);

    // cr->move_to(0, 0);
    cr->move_to(grid.trnfrm[0](data[0][0]),grid.trnfrm[1](data[0][1]));

    for (int i = 0; i < data.size(); i++) {
        
        double x = grid.trnfrm[0](data[i][0]);
        double y = grid.trnfrm[1](data[i][1]);
        cr->line_to(x, y);
    }
    

    cr->stroke();
}

void Graph::make_random_data() {
    


    for (int i = 0; i < data.size(); i++) {
        
        data[i][0] = rand() % (int)(grid.xstop - grid.xstart) + grid.xstart;
        data[i][1] = rand() % (int)(grid.ystop - grid.ystart) + grid.ystart;
    }
    
}

void Graph::make_log_data() {

    double a = (double)(grid.ystop - grid.ystart) / log10(grid.xstop/grid.xstart);
    double b = grid.ystart - a * log10(grid.xstart);

    double c = (double)(grid.xstop - grid.xstart) / (pow(10,data.size()));
    double d = grid.xstart - c;

    for (int i = 0; i < data.size(); i++) {
        double &x = data[i][0] = c * pow(10,i + 1) + d;
        data[i][1] = a * log10(x) + b;
    }
}

void Graph::make_linear_data() {
    double a = (double)(grid.ystop-grid.ystart)/(grid.xstop - grid.xstart);
    double b = grid.ystart - a * grid.xstart;

    double c = (double)(grid.xstop - grid.xstart) / (pow(10,data.size()));
    double d = grid.xstart - c;    

    for (int i = 0; i < data.size(); i++) {
        double &x = data[i][0] = c * pow(10,i + 1) + d;
        data[i][1] = a * x + b;
    }
}

void Graph::reset_data() {
    
    data.clear();
    data.resize(DEFAULT_TEST_DATA_SIZE);
    for (int i = 0; i < data.size(); i++) {
        data[i] = {0,0};
    }
    
}

void Graph::sort_data_x() {
    GraphData tempData;
    tempData.resize(data.size());

    for (int i = 0; i < data.size(); i++) {
        tempData[i].resize(data[i].size());
        for (int j = 0; j < data[0].size(); j++) {
            tempData[i][j] = data[i][j];
        }
    }

    reset_data();
    
    for (int i = 0; i < tempData.size(); i ++) {
    	
        if (i == 0) {
        	data[i][0] = tempData[i][0];
        	data[i][1] = tempData[i][1];
            
        } else {
        	for (int ii = i; ii >= 0; ii --) {
            	
                
              	if (ii == 0) {
                	data[ii][0] = tempData[i][0];
                    data[ii][1] = tempData[i][1];
                } else if (data[ii - 1][0] > tempData[i][0]) {
                	data[ii][0] = data[ii - 1][0];
                    data[ii][1] = data[ii - 1][1];
                } else {
                	data[ii][0] = tempData[i][0];
                    data[ii][1] = tempData[i][1];
                    break;
                }

            }
        }
        
    }
}