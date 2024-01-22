#pragma once

#include "OGLE/Core/Layer.h"

#include "OGLE/Renderer/Renderer.h"


namespace OGLE{

	class HelloLayer : public Layer
	{
	public: 
		HelloLayer(Renderer& renderer);
		virtual ~HelloLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
	private:
		Renderer* m_Renderer;
	};

}

