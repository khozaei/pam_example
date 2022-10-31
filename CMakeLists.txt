cmake_minimum_required(VERSION 3.5)

project(pam_example)

add_executable(pam_example main.c)

target_link_libraries(pam_example pam)
