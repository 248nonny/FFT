#include "MainWindow.hpp"
#include "gtkmm/enums.h"
#include "sigc++/functors/mem_fun.h"
#include "src/AudioHandler/AudioHandler.hpp"
#include <portaudio.h>

static void checkErr(PaError err) {
    if (err != paNoError) {
        printf("PortAudio Error: %s\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
}

MainWindow::MainWindow() 
: main_v_box(Gtk::Orientation::VERTICAL)
{
    Pa_Initialize();
    // get portaudio device names; we'll store them here and feed to audio handlers individually.
    get_pa_device_info();
    print_device_info();

    audio_handler = new AudioHandler;





    set_title("FFT");
    set_default_size(800, 500);

    for (int i = 0; i < BOTTOM_BUTTON_COUNT; i++) {
        bottom_buttons[i].set_label(bottom_button_labels[i]);
        bottom_button_box.append(bottom_buttons[i]);
    }

    bottom_buttons[0].set_label("Redraw");

    bottom_buttons[0].signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::redraw));

    bottom_button_box.set_halign(Gtk::Align::CENTER);


    for (int i = 0; i < GRAPH_COUNT; i ++) {
        graph_frames[i].set_child(fft[i].graph);
        graph_frames[i].set_margin(5);
        graph_pkg_box[i].append(graph_frames[i]);
        graph_pkg_box[i].append(fft[i].window_function_menu);
        graph_pkg_box[i].set_orientation(Gtk::Orientation::VERTICAL);
        fft_box.append(graph_pkg_box[i]);
    }

    main_v_box.append(fft_box);
    main_v_box.append(bottom_button_box);
    

    // frame.set_margin_bottom(50);

    set_child(main_v_box);

    // frame.set_child(main_v_box);

}

void MainWindow::redraw() {
    for (int i = 0; i < GRAPH_COUNT; i++) {
        fft[i].graph.queue_draw();
    }
}

void MainWindow::get_pa_device_info() {
    device_count = Pa_GetDeviceCount();
    printf("%d devices detected by portaudio.\n",device_count);

    if (device_count < 0) {
        printf("Error getting device count.\n");
        exit(EXIT_FAILURE);
    } else if (device_count == 0) {
        printf("There are no available audio devices on this machine.");
        Pa_Terminate();
        exit(EXIT_SUCCESS);
    }

    device_info.resize(device_count);

    for (int i = 0; i < device_count; i++) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if (deviceInfo != nullptr) {
            device_info[i] = deviceInfo;
        }
    }
}

void MainWindow::print_device_info() {
    for (int i = 0; i < device_info.size(); i++) {
        printf("Device: %d\n",i);
        printf("   Name: %s\n",device_info[i]->name);
        printf("   max input channels: %d\n",device_info[i]->maxInputChannels);
        printf("   max output channels: %d\n",device_info[i]->maxOutputChannels);
        printf("   default sample rate: %f\n", device_info[i]->defaultSampleRate);
    }
}