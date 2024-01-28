#pragma once

#include "OGLE/Display/Layer/Layer.h"

#include "OGLE/Display/Renderer/Renderer.h"


namespace OGLE{

	class HelloLayer : public Layer
	{
	public: 
		HelloLayer(Renderer& renderer);
		virtual ~HelloLayer() = default;

		virtual void OnAttach() override;

		virtual void OnEvent(Event& event) override;

		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void OnUpdate(Timestep ts) override;
	private:
		Renderer* m_Renderer;
		Camera* m_Camera;
	};

}

