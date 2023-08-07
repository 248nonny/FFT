#include "FFTCommander.hpp"
#include "src/FFT/stream-data.hpp"
#include "src/gtk/Graph.hpp"
#include <atomic>
#include <cmath>
#include <fftw3.h>


#define SIN_TEST_FREQ_COUNT 3

FFTCommander::FFTCommander()
: agent(512)
{
    create_sin_data();
}

void FFTCommander::create_sin_data() {
    double period = FRAMES_PER_BUFFER * (1.000/sample_rate);
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

    GraphData output;
    allocate_GraphData(agent.transform_size/2 + 1, true, output);

    for (int i = 0; i < agent.transform_size/2 + 1; i++) {
        double &x = output.data[i][0] = (double)i * sample_rate / FRAMES_PER_BUFFER;
        double &y = output.data[i][1] = 20 * log10(sqrt(pow(agent.out[i][0],2) + pow(agent.out[i][1],2)) / FRAMES_PER_BUFFER);
        // printf("x: %f, y: %f\n",x,y);
    }

    graph.write_data(output);
}