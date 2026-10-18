cmake_minimum_required(VERSION 3.20)

project(pathology_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV 5 REQUIRED COMPONENTS
    core
    imgcodecs
    imgproc
    highgui
)

add_executable(pathology
    src/main.cpp
)

target_link_libraries(pathology PRIVATE
    ${OpenCV_LIBS}
)

target_compile_options(pathology PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
