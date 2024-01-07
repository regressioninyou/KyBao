#include "kbpch.h"
#include "Scene.h"
#include <glm/glm.hpp>
namespace KyBao {
	static void DoMath(const glm::mat4& tranform) {

	}
	static void OnTransformConstruct(entt::registry& registry,entt::entity entity) {

	}
	Scene::Scene()
	{
		struct TransformComponent
		{
			glm::mat4 Transform;
			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform) 
				: Transform(transform) {}
			operator glm::mat4&() { return Transform; }
			operator const glm::mat4&() { return Transform; }
		};
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity,glm::mat4(1.0f));
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();
	}
	Scene::~Scene()
	{
	}
}