#pragma once

#include <gtkmm.h>
#include "Graph.hpp"
#include "src/FFT/FFTCommander.hpp"

#define BOTTOM_BUTTON_COUNT 4

#define GRAPH_COUNT 3

class MainWindow : public Gtk::Window {
public:
    MainWindow();

    FFTCommander fft[GRAPH_COUNT];

    Gtk::Frame graph_frames[GRAPH_COUNT];

    Gtk::Box fft_box;

    Gtk::Box main_v_box;

    // Graph graphs[3];

    Gtk::Button bottom_buttons[BOTTOM_BUTTON_COUNT];
    Glib::ustring bottom_button_labels[BOTTOM_BUTTON_COUNT] = {"1","2","3","4"};
    Gtk::Box bottom_button_box;

    void redraw();
};