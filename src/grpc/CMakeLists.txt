file(GLOB GRPC_SOURCES *.cpp *.pb.cc *.grpc.pb.cc)
add_library(grpc_services STATIC ${GRPC_SOURCES})
target_include_directories(grpc_services PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(grpc_services PUBLIC grpc++ grpc)
