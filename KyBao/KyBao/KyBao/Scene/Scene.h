#pragma once 
#include "Platform/load/entt/entt.hpp"
#include <KyBao/Core/Timestep.h>
#include <string>
namespace KyBao {
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}