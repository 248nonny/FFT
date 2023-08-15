#pragma once

#include <portaudio.h>
#include "src/FFT/FFTCommander.hpp"
#include "stream-data.hpp"


class AudioHandler {
public:
    AudioHandler();

    //device and suggested latency is taken from device_id
    void set_stream_params(int input_channels = 2, PaSampleFormat sample_format = paFloat32);

    void initialize();

    int frames_per_buffer = 512;
    StreamData stream_data;

    
private:
    PaError err;
    PaStream* stream;

    const PaDeviceInfo* device_info;

    short int device_id = 0;

    PaStreamParameters stream_input_parameters;
    PaStreamParameters stream_output_parameters;
    
    void open_stream();
    void close_stream();
    

    static int audio_callback(
        const void *input,
        void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData
    );

    static int audio_test_callback(
        const void *input,
        void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData
    );
};