cmake_minimum_required(VERSION 3.26.1)

project(FFT)

set(USER_EXECUTABLES src/GTK/MainWindow.cpp src/GTK/Graph.cpp src/FFT/FFTAgent.cpp src/FFT/FFTCommander.cpp src/FFT/window-functions.cpp src/AudioHandler/AudioHandler.cpp)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-4.0)
pkg_check_modules(GLIBMM glibmm-2.68)
pkg_check_modules(PORTAUDIO portaudiocpp)
pkg_check_modules(FFTW3 fftw3)
pkg_check_modules(GLOG libglog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# add_definitions(-DNDEBUG) # if this line exists, DLOG calls from glog will not be compiled.

include_directories(${GTKMM_INCLUDE_DIRS} ${GLIBMM_INCLUDE_DIRS} ${PORTAUDIO_INCLUDE_DIRS} ${FFTW3_INCLUDE_DIRS} ${GLOG_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS} ${FFTW3_LIBRARY_DIRS} ) # ${GLOG_LIBRARY_DIRS}

add_executable(${PROJECT_NAME} main.cpp ${USER_EXECUTABLES})

target_include_directories(${PROJECT_NAME} PRIVATE .)

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${GLIBMM_LIBRARIES} ${FFTW3_LIBRARIES} ${PORTAUDIO_LIBRARIES} ${GLOG_LIBRARIES} gflags)  # add later: ${GTKMM_LIBRARIES} ${GLIBMM_LIBRARIES} ${PORTAUDIO_LIBRARIES} ${FFTW3_LIBRARIES}




