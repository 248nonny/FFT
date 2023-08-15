#pragma once

#include <fftw3.h>
#include <functional>
#include "src/AudioHandler/stream-data.hpp"

namespace FFT {

class FFTAgent {
public:
    FFTAgent(int transform_size);
    double *in = NULL;
    fftw_complex *out = NULL;
    void execute_fft();

    fftw_plan p;
    void write_func_data(std::function<double(double)> *func, int func_arr_size);
    int transform_size;

private:
};

}