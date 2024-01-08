# CMakeList.txt: KyBao 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。


add_library(KyBao 
        "${CMAKE_CURRENT_LIST_DIR}/kbpch.cpp" 
        "${CMAKE_CURRENT_LIST_DIR}/Platform/load/stb_image/stb_image.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLContext.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLBuffer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLVertexArray.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLRendererAPI.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLShader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLTexture.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLFramebuffer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Window/WindowsWindow.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Window/WindowsInput.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Layer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/LayerStack.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Log.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Application.cpp" 

        "${CMAKE_CURRENT_LIST_DIR}/KyBao/ImGui/ImGuiLayer.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Shader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Buffer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Renderer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Renderer2D.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/RendererAPI.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/VertexArray.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/RendererCommand.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Framebuffer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Texture.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Camera/OrthographicCamera.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Camera/OrthographicCameraController.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Scene/Scene.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Scene/Entity.cpp"
        "${IMGUI_SOURCE}"
)
target_compile_definitions(KyBao
PRIVATE
    -DPLATFORM_WINDOWS_S
    -DBUILD_DLL
    -DGLFW_INCLUDE_NONL
    -DIMGUI_IMPL_OPENGL_LOADER_GLAD
)
target_precompile_headers(KyBao PRIVATE "kbpch.h")
# 或者对于多个头文件：
# target_precompile_headers(MyLibrary PRIVATE "path/to/header1.h" "path/to/header2.h")
target_sources(KyBao
PRIVATE 
PUBLIC  "${CMAKE_CURRENT_LIST_DIR}/KyBao.h" 
        "${CMAKE_CURRENT_LIST_DIR}/kbpch.h"
        
        "${CMAKE_CURRENT_LIST_DIR}/Platform/load/stb_image/stb_image.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/load/entt/entt.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLContext.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLBuffer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLVertexArray.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLRendererAPI.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLShader.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLTexture.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OpenGL/OpenGLFramebuffer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Window/WindowsWindow.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Window/WindowsInput.h"
        
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Input.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/KeyCodes.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/MouseCodes.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Layer.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/LayerStack.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Log.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Application.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Core/Timestep.h"

        "${CMAKE_CURRENT_LIST_DIR}/KyBao/ImGui/ImGuiLayer.h"

        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Events/ApplicationEvent.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Events/Event.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Events/KeyEvent.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Events/MouseEvent.h"

        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/GraphicsContext.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Shader.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Buffer.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Renderer.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Renderer2D.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/RendererAPI.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/VertexArray.h" 
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/RendererCommand.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Framebuffer.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Render/Texture.h" 
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Camera/OrthographicCamera.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Camera/OrthographicCameraController.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Camera/Camera.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Scene/Scene.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Scene/Entity.h"
        "${CMAKE_CURRENT_LIST_DIR}/KyBao/Scene/Components.h"
)

target_include_directories(KyBao
PUBLIC
"${CMAKE_CURRENT}"
"${INCLUDE_DIR}"
"${INCLUDE_DIR_IMGUI}"
"${CMAKE_SOURCE_DIR}/external/glm"
)
#message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(KyBao PRIVATE glm)
target_link_libraries(KyBao PRIVATE spdlog)
target_link_libraries(KyBao PRIVATE glad) 
target_link_libraries(KyBao PRIVATE glfw) 
set_target_properties(KyBao PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)