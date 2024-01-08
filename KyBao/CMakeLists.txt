# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.12)

project ("KyBaoProject")
# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS ON)
endif()

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://gitee.com/mirrors/glm.git
)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

#FetchContent_Declare(
#    entt
#    GIT_REPOSITORY https://github.com/skypjack/entt.git
#)
#FetchContent_GetProperties(entt)
#if(NOT entt_POPULATED)
#    FetchContent_Populate(entt)
#    add_subdirectory(${entt_SOURCE_DIR} ${entt_BINARY_DIR})
#endif()

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://gitee.com/hanzhongyi/glfw.git
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
endif() 

#FetchContent_Declare(
#    spdlog
#    GIT_REPOSITORY https://github.com/gabime/spdlog.git
#)
#FetchContent_GetProperties(spdlog)
#if(NOT spdlog_POPULATED)
#    FetchContent_Populate(spdlog)
#    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
#endif()
add_definitions(-DGLFW_INCLUDE_NONL)

list(APPEND INCLUDE_DIR ${GLAD_DIR}/include)
set(GLFW_DIR ${CMAKE_CURRENT_LIST_DIR}/external/glfw) # Set this to point to an up-to-date GLFW repo
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} glfw_binary EXCLUDE_FROM_ALL)
list(APPEND INCLUDE_DIR ${GLFW_DIR}/include)
list(APPEND INCLUDE_DIR ${GLFW_DIR}/deps)

set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR}/Dependencis/imgui)
list(APPEND INCLUDE_DIR_IMGUI ${IMGUI_DIR} ${IMGUI_DIR}/backends)
list(
    APPEND 
    IMGUI_SOURCE 
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
)
# 添加 glad 源代码路径
#add_subdirectory("Dependencis/imgui")
add_subdirectory("external/glad")
add_subdirectory("external/spdlog")
# 包含子项目。
add_subdirectory ("KyBao")
add_subdirectory ("KyBao-Editor")
add_subdirectory ("SandBox")
