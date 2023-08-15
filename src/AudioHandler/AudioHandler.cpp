
#include "AudioHandler.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <portaudio.h>




static void checkErr(PaError err) {
    if (err != paNoError) {
        printf("PortAudio Error: %s\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
}

AudioHandler::AudioHandler() {
}

void AudioHandler::initialize() {
    // portaudio should be initialized before calling this.
    // PaError err = Pa_Initialize();
    checkErr(err);

    // set amog values to output parameters. is this really necessary? who knows :P
    memset(&stream_output_parameters, 0, sizeof(stream_output_parameters));
    stream_output_parameters.channelCount = Pa_GetDeviceInfo(device_id)->maxOutputChannels;
    stream_output_parameters.device = device_id;
    stream_output_parameters.hostApiSpecificStreamInfo = NULL;
    stream_output_parameters.sampleFormat = paFloat32;
    stream_output_parameters.suggestedLatency = Pa_GetDeviceInfo(device_id)->defaultLowInputLatency;


    set_stream_params();
    open_stream();

}

void AudioHandler::open_stream() {
    device_info = Pa_GetDeviceInfo(device_id);


    err = Pa_OpenStream(
        &stream,
        &stream_input_parameters,
        &stream_output_parameters,
        device_info->defaultSampleRate,
        frames_per_buffer,
        paNoFlag,
        this->audio_callback,
        &stream_data
    );
    checkErr(err);

    err =Pa_StartStream(stream);
    checkErr(err);
    printf("stream is open!");
}

void AudioHandler::close_stream() {
    err =Pa_StopStream(stream);
    checkErr(err);

    err =Pa_CloseStream(stream);
    checkErr(err);
}


void AudioHandler::set_stream_params(int input_channels, PaSampleFormat sample_format) {
    memset(&stream_input_parameters, 0, sizeof(stream_input_parameters));
    stream_input_parameters.channelCount = input_channels;
    stream_input_parameters.device = device_id;
    stream_input_parameters.hostApiSpecificStreamInfo = NULL;
    stream_input_parameters.sampleFormat = sample_format;
    stream_input_parameters.suggestedLatency = Pa_GetDeviceInfo(device_id)->defaultLowInputLatency;
}


int AudioHandler::audio_callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData
) {
    double* in = (double*) input;
    (void)output;

    StreamData *data = (StreamData*)userData;
    // code and stuff here.

    return 0;
}



static inline float max(float a, float b) {
    return a > b ? a : b;
};

int AudioHandler::audio_test_callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData
) {


    float* in = (float*)input;
    (void)output;


    int dispSize = 100;
    printf("\r");

    float vol_r = 0;
    float vol_l = 0;

    for (unsigned long i = 0; i < frameCount * 2; i+=2) {
        vol_l = max(vol_l, std::abs(in[i]));
        vol_r = max(vol_r, std::abs(in[i+1]));
    }

    for (int i = 0; i < dispSize; i++) {
        float barProp = i / (float)dispSize;

        if (barProp <= vol_l && barProp <= vol_r) {
            printf("█");
        } else if (barProp <= vol_l) {
            printf("▀");
        } else if (barProp <= vol_r) {
            printf("▄");
        } else {
            printf(" ");
        }
    }

    fflush(stdout);
    return 0;
}