#include "MainWindow.hpp"
#include "gtkmm/enums.h"

MainWindow::MainWindow() 
: main_v_box(Gtk::Orientation::VERTICAL)
{
    set_title("FFT");
    set_default_size(800, 500);

    for (int i = 0; i < BOTTOM_BUTTON_COUNT; i++) {
        bottom_buttons[i].set_label(bottom_button_labels[i]);
        bottom_button_box.append(bottom_buttons[i]);
    }

    bottom_button_box.set_halign(Gtk::Align::CENTER);


    for (int i = 0; i < 3; i ++) {
        graph_frames[i].set_child(graphs[i]);
        graph_frames[i].set_margin(5);
        fft_box.append(graph_frames[i]);
    }

    main_v_box.append(fft_box);
    main_v_box.append(bottom_button_box);
    

    // frame.set_margin_bottom(50);

    set_child(main_v_box);

    // frame.set_child(main_v_box);

}