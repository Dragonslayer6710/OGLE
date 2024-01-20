#pragma once

#include "OGLE/Core/Layer.h"

namespace OGLE{

	class HelloLayer : public Layer
	{
	public: 
		HelloLayer();
		virtual ~HelloLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;

	};

}

