#pragma once

#define FRAMES_PER_BUFFER 512
#define AUDIO_BUFFER_SLOTS 10

typedef struct {
    float audio[AUDIO_BUFFER_SLOTS][FRAMES_PER_BUFFER];
    int bufIndex; // ranges from 0 to 9 (for buffer slots).
} StreamData;