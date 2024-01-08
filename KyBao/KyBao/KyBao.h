#pragma once
#define GLFW_INCLUDE_NONE  // 防止GLFW包含OpenGL头文件
#include "imgui.h"
#include "KyBao/Core/Application.h"
#include "KyBao/Core/Layer.h"
#include "KyBao/Core/Log.h"

#include "KyBao/Core/Timestep.h"

#include "KyBao/Core/Input.h"
#include "KyBao/Core/KeyCodes.h"
#include "KyBao/Events/KeyEvent.h"
#include "KyBao/Core/MouseCodes.h"
#include "KyBao/Camera/OrthographicCameraController.h"

#include "KyBao/ImGui/ImGuiLayer.h"


#include "KyBao/Scene/Scene.h"
#include "KyBao/Scene/Entity.h"
#include "KyBao/Scene/Components.h"
//-------Renderer----------------------
#include "KyBao/Render/Renderer.h"
#include "KyBao/Render/Renderer2D.h"
#include "KyBao/Render/RendererCommand.h"

#include "KyBao/Render/Buffer.h"
#include "KyBao/Render/Shader.h"
#include "KyBao/Render/Framebuffer.h"
#include "KyBao/Render/Texture.h"
#include "KyBao/Render/VertexArray.h"

#include "KyBao/Camera/OrthographicCamera.h"

#include "KyBao/Core/EntryPoint.h"