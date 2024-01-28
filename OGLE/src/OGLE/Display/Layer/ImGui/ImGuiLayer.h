#pragma once

#include "OGLE/Display/Layer/ImGui/imgui.h"

#include "OGLE/Display/Layer/Layer.h"

#include "OGLE/Event/ApplicationEvent.h"
#include "OGLE/Event/KeyEvent.h"
#include "OGLE/Event/MouseEvent.h"

namespace OGLE {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
	};

}