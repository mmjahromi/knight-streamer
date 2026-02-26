cmake_minimum_required(VERSION 3.12)
project(knight_pipe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SUBMODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty)


add_executable(knight_pipe
    src/main.cpp
    src/arguments.cpp
    src/utils/print_helpers.cpp
    src/neuropawn/knight_base.cpp
    src/neuropawn/knight.cpp
    src/neuropawn/knight_imu.cpp
)
target_compile_options(knight_pipe PRIVATE /W4 /WX)
target_precompile_headers(knight_pipe PRIVATE include/pch.hpp)
target_include_directories(knight_pipe PRIVATE include)


add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/liblsl)
target_link_libraries(knight_pipe LINK_PUBLIC lsl)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/CSerialPort)
target_link_libraries(knight_pipe LINK_PUBLIC libcserialport)
target_include_directories(knight_pipe PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/CSerialPort/include)


function(INCLUDE_SUBMODULE MODULE_NAME)
    add_library(${MODULE_NAME} INTERFACE)
    target_include_directories(
        ${MODULE_NAME} INTERFACE "${SUBMODULE_PATH}/${MODULE_NAME}/include"
    )
    target_link_libraries(knight_pipe PRIVATE ${MODULE_NAME})
endfunction()

include_submodule(argparse)