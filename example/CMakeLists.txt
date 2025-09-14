add_executable(example main.cpp)

target_link_libraries(example PRIVATE chronocli)

target_include_directories(example PRIVATE ${PROJECT_SOURCE_DIR}/src)

install(TARGETS example RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin)