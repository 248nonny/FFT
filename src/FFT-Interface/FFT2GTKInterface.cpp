#include "FFT2GTKInterface.hpp"
#include "src/FFT/FFTCommander.hpp"
#include <glog/logging.h>


namespace FFT {

FFT2GTKInterface::FFT2GTKInterface() 
: FFT::FFTInterface()
{
    DLOG(INFO) << "creating drop-down window function things.";
    window_menu_list = Gtk::ListStore::create(window_menu_cols);
    window_function_menu.set_model(window_menu_list);
    auto iter = window_menu_list->append();
    auto row = *iter;

    window_menu_list->clear();

    for (int i = 0; i < WINDOW_COUNT; i++) {
        row = *window_menu_list->append();
        row[window_menu_cols.window_id] = i;
        row[window_menu_cols.window_name] = WindowFunction::names[i];
    }

    DLOG(INFO) << "setting window function drop-down properties.";

    // window_function_menu.pack_start(window_menu_cols.window_id);
    window_function_menu.pack_start(window_menu_cols.window_name);

    window_function_menu.set_hexpand(false);
    window_function_menu.set_vexpand(false);
    window_function_menu.set_halign(Gtk::Align::CENTER);

    window_function_menu.set_active(WindowFunction::HANN);


    DLOG(INFO) << "connecting window function drop-down menu callback function.";
    window_function_menu.signal_changed().connect(sigc::mem_fun(*this, &FFT2GTKInterface::set_window_function_from_menu));
}

void FFT2GTKInterface::write_fft_data(std::vector<std::vector<double>> data) {
    graph.write_data(data, 0);
}

void FFT2GTKInterface::set_window_function_from_menu() {
    const auto iter = window_function_menu.get_active();

    if (iter) {
        const auto row = *iter;
        if (row) {
            fft.window_type = row[window_menu_cols.window_id];
        }
    }
    fft.test_window_function(99);
}

}