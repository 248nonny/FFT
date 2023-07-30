#pragma once

#include <gtkmm.h>

#define BOTTOM_BUTTON_COUNT 4

class MainWindow : public Gtk::Window {
public:
    MainWindow();

    Gtk::Frame frame;

    Gtk::Box main_v_box;

    Gtk::Button bottom_buttons[BOTTOM_BUTTON_COUNT];
    Glib::ustring bottom_button_labels[BOTTOM_BUTTON_COUNT] = {"1","2","3","4"};
    Gtk::Box bottom_button_box;
};