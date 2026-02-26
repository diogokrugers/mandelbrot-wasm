cmake_minimum_required(VERSION 3.0)
project(mandelbrot)

set(CMAKE_CXX_STANDARD 17)

add_executable(mandelbrot mandelbrot.cpp)

set_target_properties(mandelbrot PROPERTIES
    SUFFIX ".js"
    LINK_FLAGS "-s WASM=1 \
                -s EXPORTED_FUNCTIONS=['_allocate_buffer','_generate_mandelbrot'] \
                -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','HEAPU8'] \
                -s ALLOW_MEMORY_GROWTH=1 \
                -s MODULARIZE=1 \
                -s EXPORT_NAME='createModule'"
)