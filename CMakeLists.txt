cmake_minimum_required(VERSION 3.00)
project(cbz-downscaler)
add_link_options(-lzip)
add_executable(main main.cpp)
