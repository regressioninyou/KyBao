#include <KyBao.h>
#include <imgui.h>
class RendererLayer :public KyBao::Layer
{
public:

    RendererLayer() :Layer("RendererLayer") {

    };

     void OnAttach() {

         KyBao::FramebufferSpecification fbsf;
         fbsf.Width = 1280;
         fbsf.Height = 720;
         m_Framerbuffer = KyBao::Framebuffer::Create(fbsf);
     }
     void OnDetach() {}
     void OnUpdate(KyBao::Timestep ts) {}
     void OnImGuiRender() {
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
         ImGui::Begin("Settings");

         ImGui::End();
     };
     void OnEvent(KyBao::Event& event) {}

private:
    KyBao::Ref<KyBao::Framebuffer> m_Framerbuffer;
};
class Sandbox :public KyBao::Application
{
public:
    Sandbox() {
        PushLayer(new RendererLayer());
    };
    ~Sandbox() {};

private:

};

KyBao::Application* KyBao::CreateApplication() {
    return new Sandbox();
}
