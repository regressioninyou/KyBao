#include <KyBao.h>
class ExampleLayer :public KyBao::Layer 
{
public:
	ExampleLayer():
		Layer("Example"),
		m_Camera(1280.0f /720.0f )
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
		m_VertexArray.reset(KyBao::VertexArray::Create());
		KyBao::Ref<KyBao::VertexBuffer> vb;
		KyBao::Ref<KyBao::IndexBuffer> ib;
		vb.reset(KyBao::VertexBuffer::Create(&vertices.at(0), sizeof(float) * vertices.size()));
		{
			KyBao::BufferLayout layout = {
				{KyBao::ShaderDataType::Float3,"aPosition"},
				{KyBao::ShaderDataType::Float4,"aTExcoord"}
			};
			vb->SetLayout(layout);
		}
		ib.reset(KyBao::IndexBuffer::Create(&indices.at(0), indices.size()));
		m_VertexArray->AddVertexBuffer(vb);
		m_VertexArray->SetIndexBuffer(ib);

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
		//m_Shader = KyBao::Shader::Create(TvsSrc, TfsSrc);

		std::string vsSrc2 = R"(
#version 330 core
layout(location = 0) in vec3 aPosition;
uniform mat4 uViewProjection;
void main (){
	gl_Position =  uViewProjection * vec4( aPosition + 0.5 ,1.0f); 
}
		)";
		std::string fsSrc2 = R"( 
#version 330 core
layout(location = 0) out vec4 color;
void main(){
color = vec4(0.0,0.0,1.0,1.0);
}
)";
		m_ShaderLibrary->Add(KyBao::Shader::Create("./assets/shaders/Texture_vs.glsl", "./assets/shaders/Texture_fs.glsl"));
		m_ShaderLibrary->Add("Blue", KyBao::Shader::Create(TvsSrc, TfsSrc));
		m_Texture = KyBao::Texture2D::Create("./assets/textures/Checkerboard.png");
		m_Texture->Bind();
		m_ShaderLibrary->Get("Blue")->SetInt("uTexture", 0);
	};
	void OnUpdate(KyBao::Timestep ts) override {

		m_Camera.OnUpdate(ts);
		KyBao::RenderCommand::SetClearColor({ 0.1, 0.1, 0.15, 1 });
		KyBao::RenderCommand::Clear();

		KyBao::Renderer::BeginScene(m_Camera.GetCamera());
		//KyBao::Renderer::Submit(m_VertexArray, m_Shader);
		KyBao::Renderer::Submit(m_SquareVA, m_ShaderLibrary->Get("Blue"));
		KyBao::Renderer::EndScene();

	}
	virtual void OnImGuiRender() override {
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

		ImGui::End();
	}
	void OnEvent(KyBao::Event& event)override {
		m_Camera.OnEvent(event);
		
	}
	bool OnKeyPressedEvent(KyBao::KeyPressedEvent& e) {
		return false;
	}
private:
	KyBao::Ref<KyBao::ShaderLibrary> m_ShaderLibrary;
	KyBao::Ref<KyBao::VertexArray> m_VertexArray;

	KyBao::Ref<KyBao::VertexArray> m_SquareVA;

	KyBao::Ref<KyBao::Texture2D> m_Texture;

	KyBao::OrthographicCameraController m_Camera;
};
class Sandbox :public KyBao::Application
{
public:
	Sandbox():Application("Sandbox") {
		//PushLayer(new ExampleLayer());
		PushLayer(new ExampleLayer());
	};
	~Sandbox() {};

private:

};

KyBao::Application* KyBao::CreateApplication() {
	return new Sandbox();
}