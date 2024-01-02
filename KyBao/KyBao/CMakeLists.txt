# CMakeList.txt: KyBao 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。


add_library(KyBao "")
file(GLOB_RECURSE KYBAO_EVENTS_H "KyBao/Events/*.h")
file(GLOB_RECURSE KYBAO_KyBao_H "KyBao/*.h")
file(GLOB_RECURSE KYBAO_KyBao_SOURCES "KyBao/*.cpp")

target_precompile_headers(KyBao PRIVATE "kbpch.h")

# 或者对于多个头文件：
# target_precompile_headers(MyLibrary PRIVATE "path/to/header1.h" "path/to/header2.h")
target_sources(KyBao
PRIVATE 
        "${KYBAO_KyBao_H}"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Window/WindowsWindow.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Window/WindowsWindow.cpp"
        "${KYBAO_EVENTS_H}"
        "${KYBAO_KyBao_SOURCES}"
        "kbpch.cpp"
PUBLIC "${CMAKE_CURRENT_LIST_DIR}/KyBao.h" 
        "${CMAKE_CURRENT_LIST_DIR}/kbpch.h")

target_include_directories(KyBao
PUBLIC
${CMAKE_CURRENT_LIST_DIR}
)
#message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(KyBao PRIVATE glm)
target_link_libraries(KyBao PRIVATE spdlog)
target_link_libraries(KyBao PRIVATE glfw)
target_link_libraries(KyBao PRIVATE glew)
# 如果是 Windows 平台，还需要链接额外的库
if(WIN32)
    target_link_libraries(KyBao PRIVATE opengl32.lib)
endif()
set_target_properties(KyBao PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)