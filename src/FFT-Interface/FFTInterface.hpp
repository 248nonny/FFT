#pragma once

#include "src/FFT-Interface/FFTInterface.hpp"
#include "src/FFT/FFTCommander.hpp"
#include <vector>

namespace FFT {

class FFTInterface {
public:
    FFTInterface(): fft(this){};
    
    FFTCommander fft;
    virtual void write_fft_data(std::vector<std::vector<double>> data) {};
    // virtual void write_audio_data();
};

}