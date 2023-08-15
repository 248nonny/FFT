#include <gtkmm.h>
#include <stdio.h>
#include <portaudio.h>
#include <signal.h>

#include "src/GTK/MainWindow.hpp"
#include <glog/logging.h>
#include <gflags/gflags.h>

void terminate_handler(int signum) {
    int err = Pa_Terminate();
    printf("\n byeeee!\n");
    exit(0);
}

int main(int argc, char *argv[]) {

    // glog setup stuff
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc,&argv,true);
    FLAGS_logtostderr = 1;

    // printf("Hello, World!\n");
    DLOG(INFO) << "this is a debug log test.";

    // this allows PortAudio to terminate gracefully when program is cut of with ^C.
    DLOG(INFO) << "setting PA terminate handler.";
    signal(SIGINT, terminate_handler);

    // Gtk run app.
    DLOG(INFO) << "making Gtk app.";
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    DLOG(INFO) << "running Gtk app.";
    int to_return = app->make_window_and_run<MainWindow>(argc,argv);

    // stop app
    DLOG(INFO) << "Stopping app.";
    terminate_handler(0);
}