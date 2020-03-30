cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

enable_language(CXX)

find_package(Threads REQUIRED)
if(CMAKE_USE_PTHREADS_INIT)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
endif()

project(hw1_timer)


include_directories(${PROJECT_SOURCE_DIR})
add_executable(timer ITimer.h Timer.h Timer.cpp Test_main.cpp) #add here other cpp file 

target_link_libraries(timer ${CMAKE_THREAD_LIBS_INIT})
