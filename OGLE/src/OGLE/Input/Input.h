#pragma once
#include "OGLE/Core/Base.h"

#include "OGLE/Input/KeyCodes.h"
#include "OGLE/Input/MouseCodes.h"
#include "OGLE/Display/Window.h"
namespace OGLE {

	enum InputState {
		INPUT_STATE_RELEASE,
		INPUT_STATE_PRESS
	};

	enum InputType {
		INPUT_TYPE_KEY,
		INPUT_TYPE_MOUSE
	};

	class Input {
	public:
		Input();
		static void ResetInputs();

		static void New(unsigned int inputID);

		static Input* GetInput(unsigned int inputID);

		unsigned int GetInputID();

		InputState GetInputState();
		void SetInputState(InputState state);

		InputType GetInputType();

	protected:

		static void InitInputs();

		static void NewInput(Input* input);

		Input(unsigned int inputID, InputType inputType);

	private:
		static std::unordered_map<unsigned int, Input*>* s_Inputs;
		static std::unordered_map<unsigned int, InputState>* s_InputStates;

		unsigned int m_InputID;
		InputType m_InputType;
		KeyCode m_KeyCode;
		MouseCode m_MouseButton;
	};

	static void SetInputState(unsigned int inputID, InputState state) {
		Input::GetInput(inputID)->SetInputState(state);
	}

	inline glm::vec2 s_MousePos = glm::vec2(0.0f, 0.0f);
	inline glm::vec2 s_MouseDelta = glm::vec2(0.0f, 0.0f);
	inline glm::vec2 s_ScrollOffset = glm::vec2(0.0f, 0.0f);

	static void SetMousePos(glm::vec2 newMousePos) {
		s_MousePos = newMousePos;
	}

	static void MoveMousePos(glm::vec2 newMousePos)
	{
		s_MouseDelta = newMousePos - s_MousePos;
		SetMousePos(newMousePos);
	}

	static void ResetScrollOffset() {
		s_ScrollOffset = glm::vec2(0.0f, 0.0f);
	}

	static void SetScrollOffset(glm::vec2 newScrollOffset)
	{
		s_ScrollOffset = newScrollOffset;
	}
}
