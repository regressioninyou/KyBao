#pragma once 
#include "KyBao/Render/RendererCommand.h"
#include "KyBao/Camera/OrthographicCamera.h"
#include "Shader.h"
namespace KyBao {
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width,uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArry,const std::shared_ptr<Shader>& shader);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}