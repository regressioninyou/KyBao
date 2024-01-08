#pragma once 
namespace KyBao {
	class EditorLayout : public Layer
	{
	public:
		EditorLayout();
		virtual ~EditorLayout() = default;

		virtual void OnAttach() override ;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts)  override;
		virtual void OnImGuiRender()  override;
		virtual void OnEvent(Event& event)  override;
	private:
		OrthographicCameraController m_CameraController;
		Ref<VertexArray> m_SquareVA;
		Ref<ShaderLibrary> m_ShaderLibrary;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Texture2D> m_Texture2D;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;

		bool m_ViewportFocus = false;
		bool m_ViewportHovers = false;
		glm::vec2 m_ViewportSize = {0.0f,0.0f};

		glm::vec4 m_SquareColor = { 0.0f,0.1f,0.2f,1.0f };
	};
}