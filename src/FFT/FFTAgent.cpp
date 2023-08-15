#include "FFTAgent.hpp"
#include <fftw3.h>

namespace FFT {

FFTAgent::FFTAgent(int transform_size) {
    this->transform_size = transform_size;
    in = (double*) fftw_malloc(sizeof(double) * transform_size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (transform_size/2 + 1));

    // in = new fftw_complex[transform_size];this->transform_size = transform_size;
    in = (double*) fftw_malloc(sizeof(double) * transform_size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (transform_size/2 + 1));

    // in = new fftw_complex[transform_size];
    // out = new fftw_complex[transform_size];
    p = fftw_plan_dft_r2c_1d(transform_size, in, out, FFTW_ESTIMATE);
}

void FFTAgent::execute_fft() {
    fftw_execute(p);
}

void FFTAgent::write_func_data(std::function<double(double)> *func, int func_arr_size) {

    for (int i = 0; i < transform_size; i++) {
        in[i] = 0;
        for (int ii = 0; ii < func_arr_size; ii++) {
            in[i] += func[ii](i);
            // printf("i: %d, val: %f\n",i,in[i]);
        }
    }
}

}