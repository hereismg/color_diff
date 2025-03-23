cmake_minimum_required(VERSION 3.30)

project(diff)

set(diff "${CMAKE_CURRENT_LIST_DIR}/diff")

# 启用测试
find_package(GTest REQUIRED)
add_subdirectory(tests)
enable_testing()