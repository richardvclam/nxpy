cmake_minimum_required(VERSION 2.8.12)
project(nx)

add_subdirectory(pybind11)
pybind11_add_module(nx src/main.cpp)
