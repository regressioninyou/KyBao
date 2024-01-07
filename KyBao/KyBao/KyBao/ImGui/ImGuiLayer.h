#pragma once
#include "KyBao/Core/Layer.h"

namespace KyBao {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach()override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void SetBlockFocosEvents(bool block) { m_BlockFocos = block; };
		bool GetBlockEvents() { return m_BlockFocos; };
	private:
		bool m_BlockFocos = true;
		float m_Time = 0.0f;
	};
}