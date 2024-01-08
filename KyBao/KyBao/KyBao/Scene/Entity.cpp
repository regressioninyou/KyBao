#include "kbpch.h"
#include "Entity.h"

namespace KyBao {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}