#pragma once
#include "../gtk/Graph.hpp"
#include <portaudio.h>
#include "src/FFT/FFTAgent.hpp"
#include "stream-data.hpp"

class FFTCommander {
public:
    FFTCommander();
    Graph graph;
    FFTAgent agent;

private:
    PaStream *stream;
    StreamData stream_data;
    int sample_rate = 44000; // Hz
    void create_sin_data();

};