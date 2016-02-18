cmake_minimum_required(VERSION 3.1)

project(filters)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cc flag_manager.cc)

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
