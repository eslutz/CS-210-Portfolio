cmake_minimum_required(VERSION 3.22)
project(Project_3)

set(CMAKE_CXX_STANDARD 23)

find_package(PythonLibs REQUIRED)

add_executable(Project_3 main.cpp PythonCode.py Utilities.cpp Utilities.h InventoryItem.cpp InventoryItem.h)

include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(Project_3 ${PYTHON_LIBRARIES})


