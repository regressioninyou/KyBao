
add_executable(
    Editor 
    "${CMAKE_CURRENT_LIST_DIR}/KyBaoEditor.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/EditorLayout.cpp"
)
target_compile_definitions(Editor
PRIVATE
    -DGLFW_INCLUDE_NONL
)
target_sources(
    Editor PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/EditorLayout.h"
)
#target_sources(Editor 
#PUBLIC
# "Editor2D.h" 
#)
target_link_libraries(Editor
PRIVATE 
	KyBao
)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
file(GLOB RESOURCE_FILES ${RESOURCES_DIR}/*)
foreach(RESOURCE ${RESOURCE_FILES})
    file(COPY ${RESOURCE} DESTINATION ${CMAKE_BINARY_DIR}/bin/assets)
endforeach()
target_include_directories(Editor PRIVATE ${CMAKE_BINARY_DIR}/bin/assets)
target_sources(Editor PRIVATE ${RESOURCE_FILES})

target_link_libraries(Editor PRIVATE spdlog)
set_target_properties(Editor PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)