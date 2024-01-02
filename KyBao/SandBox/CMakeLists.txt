
add_executable(SandBox "SandBoxApp.cpp")
target_compile_definitions(SandBox
PRIVATE
    -DPLATFORM_WINDOWS
    -DBUILD_DLL
)
target_link_libraries(SandBox
PRIVATE 
	KyBao
)
target_link_libraries(SandBox PRIVATE spdlog)
set_target_properties(SandBox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)