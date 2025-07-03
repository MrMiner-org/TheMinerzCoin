file(GLOB ZMQ_SOURCES *.cpp)
add_library(zmq_lib STATIC ${ZMQ_SOURCES})
target_include_directories(zmq_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
