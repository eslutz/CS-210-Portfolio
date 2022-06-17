cmake_minimum_required(VERSION 3.22)
project(Project_3)

set(CMAKE_CXX_STANDARD 23)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_executable(${PROJECT_NAME} main.cpp Utilities.cpp Utilities.h InventoryItem.cpp InventoryItem.h)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
                ${Python3_INCLUDE_DIRS}
)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
                ${Python3_LIBRARIES}
        )

# Copy python_modules to dist folder.
add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/python_modules/ ${OUTPUT_DIR}/python_modules
)

# Cope files to dist folder.
add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/files/ ${OUTPUT_DIR}/files
)

# Copies Python dll file to dist folder if running in Windows.
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${Python3_RUNTIME_LIBRARY_DIRS}/python/${Python3-VERSION_MAJOR}.$PYTHON3_VERSION_MINOR}.dll ${OUTPUT_DIR}/files
)
endif()

