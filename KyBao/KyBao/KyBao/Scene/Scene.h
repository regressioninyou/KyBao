#pragma once 
#include "Platform/load/entt/entt.hpp"
namespace KyBao {
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;
	};
}