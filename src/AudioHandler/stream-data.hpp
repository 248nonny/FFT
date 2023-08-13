
#pragma once

#include <vector>

// I used float because PortAudio's output is float32, which is same resolution as float. can change if necessary, but I doubt it will be (past self owes you $20 if you have to change it) :P
using AudioBuffer = std::vector<std::vector<std::vector<float>>>;



typedef struct {
    // middle size will be of audio buffer size (per channel?)
    // hmmmm how should I integrate channels? add another layer of nesting >:) not cursed lmao.

    // hierarchy:
    // - main buffer vector (contains channel vectors)
    // --- channel vector (contains chunk vectors)
    // ----- chunk vector (contains double values)
    // ------- raw double value
    //
    // so for example, audio_buffer[0][3][7] is the 8th value of the 4th chunk of the 1st channel.
    AudioBuffer audio_buffer;

    std::vector<short int> chunk_index; // index for each channel, index[0] -> chunks[0]
    // the number of channels is represented by the size of outermost vector
    // similarly, the frames per chunk is reflected in the size of each chunk vector.
    // The audio object should keep the number of values per chunk to a standard probably.
    // I think 512 sounds about right :)

} StreamData;