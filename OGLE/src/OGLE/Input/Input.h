#pragma once
#include "OGLE/Core/Base.h"

#include "OGLE/Input/KeyCodes.h"
#include "OGLE/Input/MouseCodes.h"
#include "OGLE/Display/Window.h"
namespace OGLE {

	static enum InputState {
		INPUT_RELEASE,
		INPUT_PRESS
	};

	namespace Key {
		static std::unordered_map<KeyCode, InputState> s_KeyStates = {
				{W, INPUT_RELEASE},
				{A, INPUT_RELEASE},
				{S, INPUT_RELEASE},
				{D, INPUT_RELEASE},
				{Space, INPUT_RELEASE},
				{LeftControl, INPUT_RELEASE}
		};
	}

	namespace Mouse {
		static std::unordered_map<MouseCode, InputState> s_MouseBtnStates = {
						{ButtonLeft, INPUT_RELEASE},
						{ButtonRight, INPUT_RELEASE},
						{ButtonMiddle, INPUT_RELEASE},
						{Button3, INPUT_RELEASE},
						{Button4, INPUT_RELEASE},
						{Button5, INPUT_RELEASE},
						{Button6, INPUT_RELEASE},
						{ButtonLast, INPUT_RELEASE}
		};
	}

	static void SetKeyState(KeyCode key, InputState state) { if (Key::s_KeyStates[key] != state) Key::s_KeyStates[key] = state; }

	static InputState* GetKeyState(KeyCode key) { return &Key::s_KeyStates[key]; }

	static void SetMouseBtnState(MouseCode btn, InputState state) { if (Mouse::s_MouseBtnStates[btn] != state) Mouse::s_MouseBtnStates[btn] = state; }

	static InputState* GetMouseBtnState(MouseCode btn) { return &Mouse::s_MouseBtnStates[btn]; }

	
	static glm::vec2 s_MousePos = glm::vec2(0.0f, 0.0f);
	static glm::vec2 s_MouseDelta = glm::vec2(0.0f, 0.0f);
	static glm::vec2 s_ScrollOffset = glm::vec2(0.0f, 0.0f);


	static void SetMousePos(GLFWwindow* window, glm::vec2 newMousePos) {
		s_MousePos = newMousePos;
		if (window)
			glfwSetCursorPos(window, s_MousePos.x, s_MousePos.y);
	}

	static void MoveMousePos(glm::vec2 newMousePos)
	{
		s_MouseDelta = newMousePos - s_MousePos;
		SetMousePos(nullptr, newMousePos);
	}

	static void ResetScrollOffset() {
		s_ScrollOffset = glm::vec2(0.0f, 0.0f);
	}

	static void SetScrollOffset(glm::vec2 newScrollOffset)
	{
		s_ScrollOffset = newScrollOffset;
	}
}
