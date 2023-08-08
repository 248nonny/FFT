#include <gtkmm.h>
#include <stdio.h>
#include <portaudio.h>
#include <signal.h>

#include "src/gtk/MainWindow.hpp"

void terminate_handler(int signum) {
    int err = Pa_Terminate();
    printf("\n byeeee!\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    printf("Hello, World!\n");


    signal(SIGINT, terminate_handler);

    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    int to_return = app->make_window_and_run<MainWindow>(argc,argv);
    terminate_handler(0);
    
}