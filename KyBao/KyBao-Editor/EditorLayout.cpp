#include <KyBao.h>
#include "EditorLayout.h"
namespace KyBao {
	EditorLayout::EditorLayout()
		:Layer("Editor"), m_CameraController(1280.0f / 720.0f), m_ViewportSize(1280.0f, 720.0f)
	{
		m_ShaderLibrary = KyBao::CreateRef<KyBao::ShaderLibrary>();
		std::vector<float> vertices = {
			-0.5f,  0.5f, 0.0f, 0.0f,1.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f,1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f,0.0f,
		};
		std::vector<unsigned int>  indices = {
			0, 1, 2, 2, 1, 3
		};
		m_SquareVA.reset(KyBao::VertexArray::Create());
		KyBao::Ref<KyBao::VertexBuffer> squareVB;
		squareVB.reset(KyBao::VertexBuffer::Create(&vertices.at(0), sizeof(float) * vertices.size()));
		{
			KyBao::BufferLayout layout = {
			{KyBao::ShaderDataType::Float3,"aPosition"},
			{KyBao::ShaderDataType::Float2,"aTexcoord"},
			};
			squareVB->SetLayout(layout);
		}
		KyBao::Ref<KyBao::IndexBuffer> squareIB;
		squareIB.reset(KyBao::IndexBuffer::Create(&indices.at(0), indices.size()));
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);
		std::string TvsSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexcoord;

uniform mat4 uViewProjection;
out vec2 vTexcoord;
void main (){
	vTexcoord = aTexcoord;
	gl_Position =   uViewProjection * vec4( aPosition,1.0f); 
}
		)";
		std::string TfsSrc = R"(
#version 330 core
layout(location = 0) out vec4 color;
uniform sampler2D uTexture;
in vec2 vTexcoord;
void main(){
color = texture(uTexture,vTexcoord);
}
)";
		m_ShaderLibrary->Add("Blue", KyBao::Shader::Create(TvsSrc, TfsSrc));
	}

	void EditorLayout::OnAttach()
	{
		m_Texture2D = KyBao::Texture2D::Create("./assets/textures/Checkerboard.png");
		FramebufferSpecification fbsf;
		fbsf.Width = 1280;
		fbsf.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbsf);
	}

	void EditorLayout::OnDetach()
	{
	}

	void EditorLayout::OnUpdate(Timestep ts)
	{
		if (m_ViewportFocus)
			m_CameraController.OnUpdate(ts);
		m_Framebuffer->Bind();
		KyBao::RenderCommand::SetClearColor({ 0.1, 0.1, 0.2, 1 });
		KyBao::RenderCommand::Clear();

		KyBao::Renderer::BeginScene(m_CameraController.GetCamera());
		//KyBao::Renderer::Submit(m_VertexArray, m_Shader);
		m_ShaderLibrary->Get("Blue")->Bind();
		m_Texture2D->Bind();
		m_ShaderLibrary->Get("Blue")->SetInt("uTexture", 0);
		KyBao::Renderer::Submit(m_SquareVA, m_ShaderLibrary->Get("Blue"));
		KyBao::Renderer::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayout::OnImGuiRender()
	{
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static bool p_open = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				if (ImGui::MenuItem("Exit"))
					KyBao::Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Begin("Setting");
		ImGui::Text("Setting");
		float color[4] = { 1.0f, 1.0f, 1.0f,1.0f };
		ImGui::ColorEdit4("color", color);
		ImGui::End();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Render");
		m_ViewportFocus = ImGui::IsWindowFocused();
		m_ViewportHovers = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockFocosEvents(!m_ViewportFocus || !m_ViewportHovers);
		uint32_t renderID = m_Framebuffer->GetColorAttachmentRendererID();
		ImVec2 avail = ImGui::GetContentRegionAvail();
		ImGui::Image((void*)renderID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2{ 0,1 }, ImVec2{ 1,0 });
		if (m_ViewportSize != *((glm::vec2*)&avail) && avail.x > 0 && avail.y > 0)
		{
			m_Framebuffer->Resize((uint32_t)avail.x, (uint32_t)avail.y);
			m_ViewportSize = { avail.x,avail.y };
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}
		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void EditorLayout::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}

}