
add_executable(SandBox 
"SandBoxApp.cpp" 
#"SandBoxAppRender.cpp"
 #"SandBox2D.cpp"
)
target_compile_definitions(SandBox
PRIVATE
    -DPLATFORM_WINDOWS
    -DGLFW_INCLUDE_NONL
)
#target_sources(SandBox 
#PUBLIC
# "SandBox2D.h"
#)
target_link_libraries(SandBox
PRIVATE 
	KyBao
)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
file(GLOB RESOURCE_FILES ${RESOURCES_DIR}/*)
foreach(RESOURCE ${RESOURCE_FILES})
    file(COPY ${RESOURCE} DESTINATION ${CMAKE_BINARY_DIR}/bin/assets)
endforeach()
target_include_directories(SandBox PRIVATE ${CMAKE_BINARY_DIR}/bin/assets)
target_sources(SandBox PRIVATE ${RESOURCE_FILES})

target_link_libraries(SandBox PRIVATE spdlog)
set_target_properties(SandBox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)