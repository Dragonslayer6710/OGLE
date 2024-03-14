#pragma once

#include "OGLE/Display/Layer/Layer.h"

#include "OGLE/Display/Renderer/Renderer.h"

#include "OGLE/Core/Application.h"

namespace OGLE {

	class GameWorldLayer : public Layer
	{
	public:
		GameWorldLayer(Renderer& renderer);
		virtual ~GameWorldLayer() = default;

		virtual void OnAttach() override;

		virtual void OnEvent(Event& event) override;

		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void OnUpdate(double deltaTime) override;
	private:
		Renderer* m_Renderer;
	};

}

