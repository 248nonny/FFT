#include "FFTCommander.hpp"
#include "src/AudioHandler/stream-data.hpp"
#include "src/FFT-Interface/FFTInterface.hpp"
#include "src/FFT/window-functions.hpp"
#include <atomic>
#include <cmath>
#include <fftw3.h>
#include <gtkmm.h>
#include <glog/logging.h>


#define SIN_TEST_FREQ_COUNT 3

namespace FFT {


FFTCommander::FFTCommander(FFTInterface *interface)
: agent(512)
{
    DLOG(INFO) << "constructing FFT Commander.";
    this->interface = interface;

    window_type = WindowFunction::HANN;


    // create_sin_data();
    DLOG(INFO) << "testing window function...";
    test_window_function(100);
}

void FFTCommander::create_sin_data() {
    double period = frames_per_buffer * (1.000/sample_rate);
    // printf("sample period: %f\n",period);
    double minfreq = (double)1/period;
    // printf("min f: %f\n",minfreq);
    double maxfreq = ((double)sample_rate) / 10;
    // printf("max f: %f\n",maxfreq);

    double f[SIN_TEST_FREQ_COUNT];
    double a[SIN_TEST_FREQ_COUNT];
    std::function<double(double)> sinwave[SIN_TEST_FREQ_COUNT];

    if ((int)(maxfreq*1000) == 0) {
        printf("error with the sine freq. generation in fftcommander (maxfreq was too small).\n");
    } else {

        printf("\nmaking test freqs for graph...\n");
        for (int i = 0; i < SIN_TEST_FREQ_COUNT; i++) {
            double &ff = f[i] = (double)(rand() % (int)(maxfreq * 1000)) / 1000 + minfreq;

            //amplitudes will be between 0.01 (-40dB) to 1000 (60dB)
            double &aa = a[i] = (double)(rand() % (int)1000*1000)/1000 + 0.01;
            printf("f%d(Hz):%f, a%d(dB):%f\n",i,f[i],i,20 * log10(a[i]));

            sinwave[i] = [ff,aa, &smplrt = this->sample_rate](double x) {return aa * sin((x * (double)1/smplrt) * ff * 2 * M_PI);};
        }
    }


    agent.write_func_data(sinwave, SIN_TEST_FREQ_COUNT);

    agent.execute_fft();

    Output output;

    for (int i = 0; i < agent.transform_size/2 + 1; i++) {
        double &x = output[i][0] = (double)i * sample_rate / frames_per_buffer;
        double &y = output[i][1] = 20 * log10(sqrt(pow(agent.out[i][0],2) + pow(agent.out[i][1],2)) / frames_per_buffer);
        // printf("x: %f, y: %f\n",x,y);
    }

    write_data(output);
}

void FFTCommander::test_window_function(int array_size) {
    DLOG(INFO) << "testing window function of size " << array_size << ".";
    Output output;
    output.reserve(array_size);
    

    double y[array_size];
    WindowFunction::make_window_array(window_type, y, array_size);
    DLOG(INFO) << "writing test window values to output GraphDataSet.";
    for (int i = 0; i < array_size; i ++) {
        output.push_back({i * (1.00/ array_size), y[i] * 100});
        // double &xval = output[i][0] = i * (1.00/ array_size);
        // double &yval = output[i][1] = y[i] * 100;
        // printf("{x: %f, y:%f}\n",xval,yval);
    }
    write_data(output);
    // DLOG(INFO) << "queuing graph redraw";
    // graph.queue_draw();
}

void FFTCommander::write_data(Output data) {
    interface->write_fft_data(data);
}

}