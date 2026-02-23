cmake_minimum_required(VERSION 3.20)

project(420J12 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(420J12
        src/main.cpp
        src/entity.cpp
        src/component.h
        src/render_component.h
        src/render_component.cpp
)

# 只用 SDL3 核心
find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(420J12 PRIVATE SDL3::SDL3)