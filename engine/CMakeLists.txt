cmake_minimum_required(VERSION 3.8)

add_executable(geosketchpad entry.cc)

target_link_libraries(geosketchpad PUBLIC glm fmt)