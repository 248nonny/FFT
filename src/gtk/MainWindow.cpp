#include "MainWindow.hpp"
#include "gtkmm/enums.h"
#include "sigc++/functors/mem_fun.h"


MainWindow::MainWindow() 
: main_v_box(Gtk::Orientation::VERTICAL)
{
    set_title("FFT");
    set_default_size(800, 500);

    for (int i = 0; i < BOTTOM_BUTTON_COUNT; i++) {
        bottom_buttons[i].set_label(bottom_button_labels[i]);
        bottom_button_box.append(bottom_buttons[i]);
    }

    bottom_buttons[0].set_label("Redraw");

    bottom_buttons[0].signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::redraw));

    bottom_button_box.set_halign(Gtk::Align::CENTER);


    for (int i = 0; i < GRAPH_COUNT; i ++) {
        graph_frames[i].set_child(fft[i].graph);
        graph_frames[i].set_margin(5);
        fft_box.append(graph_frames[i]);
    }

    main_v_box.append(fft_box);
    main_v_box.append(bottom_button_box);
    

    // frame.set_margin_bottom(50);

    set_child(main_v_box);

    // frame.set_child(main_v_box);

}

void MainWindow::redraw() {
    for (int i = 0; i < GRAPH_COUNT; i++) {
        fft[i].graph.queue_draw();
    }
}