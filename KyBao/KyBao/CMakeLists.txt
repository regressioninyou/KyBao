# CMakeList.txt: KyBao 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
add_library(KyBao "")

target_sources(KyBao
PRIVATE "KyBao/Application.cpp"
PUBLIC "${CMAKE_CURRENT_LIST_DIR}/KyBao.h")

target_include_directories(KyBao
PUBLIC
${CMAKE_CURRENT_LIST_DIR}
)
#message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")


set_target_properties(KyBao PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)