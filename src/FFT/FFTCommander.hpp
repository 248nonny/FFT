#pragma once
#include "../gtk/Graph.hpp"
#include <gtkmm.h>
#include "FFTAgent.hpp"
#include "window-functions.hpp"

class WindowFunctionMenuCols : public Gtk::TreeModel::ColumnRecord
{
public:
    WindowFunctionMenuCols()
    {add(window_id); add(window_name);};

    Gtk::TreeModelColumn<int> window_id;
    Gtk::TreeModelColumn<Glib::ustring> window_name;
};

class FFTCommander {
public:
    FFTCommander();


    WindowFunctionMenuCols window_menu_cols;
    Graph graph;
    Gtk::ComboBox window_function_menu;
    Glib::RefPtr<Gtk::ListStore> window_menu_list;

    FFTAgent agent;
    int window_type;

private:
    int sample_rate = 44000; // Hz

    // writes random sine data to FFT, processes, and sends to graph.
    void create_sin_data();

    // writes a window function with 'array_zize' number of datapoints to graph.
    void test_window_function(int array_size);

    // used in dropdown menu, should not be called otherwise.
    void set_window_function_from_menu();

};