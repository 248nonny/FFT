#include <gtkmm.h>
#include <stdio.h>

#include "src/gtk/MainWindow.hpp"



int main(int argc, char *argv[]) {
    printf("Hello, World!\n");

    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<MainWindow>(argc,argv);
}