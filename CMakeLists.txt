cmake_minimum_required(VERSION 3.1)

project(filters)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
    src/main.cc
    src/flag_manager.cc
    src/base_filter.cc
    src/grayscale_filter.cc
    src/green_filter.cc
    src/blue_filter.cc
    src/red_filter.cc
    src/meanshift_filter.cc
    src/negative_filter.cc
    src/emboss_filter.cc
    src/gaussianblur_filter.cc
    src/sharp_filter.cc
    src/dot_filter.cc
    src/simple_filter.cc
    src/affine_filter.cc)

set(gflags_SHARED FALSE)
set(gflags_NOTHREADS FALSE)

find_package(gflags REQUIRED)

add_executable(filters ${SOURCE_FILES})

if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
  target_link_libraries(filters ${OpenCV_LIBS})
endif(OpenCV_FOUND)

if (gflags_FOUND)
  include_directories(${gflags_INCLUDE_DIR})
  target_link_libraries(filters gflags)
endif(gflags_FOUND)
