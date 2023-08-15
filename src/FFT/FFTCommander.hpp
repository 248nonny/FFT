#pragma once
#include "src/GTK/Graph.hpp"
#include <gtkmm.h>
#include <vector>
#include "FFTAgent.hpp"
#include "window-functions.hpp"
// #include "src/FFT-Interface/FFTInterface.hpp"

namespace FFT {


using Output = std::vector<std::vector<double>>;

class FFTInterface;

class FFTCommander {
public:
    FFTCommander(FFTInterface *interface);
    FFTInterface *interface;

    // std::vector<FFTAgent> agents; // next step.
    FFTAgent agent;
    int window_type;

    int frames_per_buffer = 512;
    void test_window_function(int array_size);
private:
    int sample_rate = 44000; // Hz

    // writes random sine data to FFT, processes, and sends to graph.
    void create_sin_data();

    // writes a window function with 'array_zize' number of datapoints to graph.
    void write_data(std::vector<std::vector<double>> data);

};

}