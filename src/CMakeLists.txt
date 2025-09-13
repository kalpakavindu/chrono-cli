file(GLOB SOURCE_FILES *.cpp *.hpp)
file(GLOB HEADER_FILES *.hpp)

add_library(chronocli STATIC ${SOURCE_FILES})

install(FILES ${HEADER_FILES} DESTINATION ${ChronoCLI_INC_DIR})
install(TARGETS chronocli DESTINATION ${ChronoCLI_OUT_DIR})