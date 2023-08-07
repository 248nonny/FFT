
#pragma once
#include <functional>
#include <map>

// below the names and indexes of various windows are defined.
#pragma region
#define WINDOW_COUNT 7

#define HANN 0
#define FLAT_TOP 1
#define HAMMING 2
#define BLACKMAN 3
#define BLACKMAN_HARRIS 4
#define BARTLETT 5
#define WELCH 6

#pragma endregion

void make_window_array(short int window_type, double * array, int array_size);