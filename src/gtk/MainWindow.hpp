#pragma once

#include <gtkmm.h>
#include "Graph.hpp"
#include "src/AudioHandler/AudioHandler.hpp"
#include "src/FFT/FFTCommander.hpp"
#include <portaudio.h>
#include <vector>


#define BOTTOM_BUTTON_COUNT 4

#define GRAPH_COUNT 3

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    std::vector<const PaDeviceInfo*> device_info;
    int device_count;
private:
    FFTCommander fft[GRAPH_COUNT];

    AudioHandler audio_handler;

    Gtk::Frame graph_frames[GRAPH_COUNT];

    Gtk::Box fft_box;
    Gtk::Box graph_pkg_box[GRAPH_COUNT];

    Gtk::Box main_v_box;

    // Graph graphs[3];

    Gtk::Button bottom_buttons[BOTTOM_BUTTON_COUNT];
    Glib::ustring bottom_button_labels[BOTTOM_BUTTON_COUNT] = {"1","2","3","4"};
    Gtk::Box bottom_button_box;

    void get_pa_device_info();
    void print_device_info();

    void redraw();
};