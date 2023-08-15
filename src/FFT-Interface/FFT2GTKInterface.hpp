#pragma once

#include "src/AudioHandler/stream-data.hpp"
#include "src/FFT/FFTCommander.hpp"
#include "src/GTK/Graph.hpp"
#include "src/FFT-Interface/FFTInterface.hpp"


class WindowFunctionMenuCols : public Gtk::TreeModel::ColumnRecord
{
public:
    WindowFunctionMenuCols()
    {add(window_id); add(window_name);};

    Gtk::TreeModelColumn<int> window_id;
    Gtk::TreeModelColumn<Glib::ustring> window_name;
};

namespace FFT {


class FFT2GTKInterface : public FFT::FFTInterface{
public:

    FFT2GTKInterface();

    // window function menu tings
    WindowFunctionMenuCols window_menu_cols;
    Gtk::ComboBox window_function_menu;
    Glib::RefPtr<Gtk::ListStore> window_menu_list;


    Graph graph;

    void write_fft_data(std::vector<std::vector<double>> data) override;
    
private:

    // used in dropdown menu, should not be called otherwise.
    void set_window_function_from_menu();

};

}