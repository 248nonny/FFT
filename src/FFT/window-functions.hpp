
#pragma once
#include <functional>
#include <map>

// below the names and indexes of various windows are defined.
#pragma region

#define WINDOW_COUNT 7

namespace WindowFunction {

    extern const char* names[WINDOW_COUNT];

    extern const short int HANN;
    extern const short int FLAT_TOP;
    extern const short int HAMMING;
    extern const short int BLACKMAN;
    extern const short int BLACKMAN_HARRIS;
    extern const short int BARTLETT;
    extern const short int WELCH;

    void make_window_array(short int window_type, double * array, int array_size);
}

#pragma endregion
