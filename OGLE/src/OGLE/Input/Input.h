#pragma once
#include "OGLE/Core/Base.h"

#include "OGLE/Input/KeyCodes.h"
#include "OGLE/Input/MouseCodes.h"

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

	
	inline double s_MousePosX;
	inline double s_MousePosY;
	inline double s_NextMousePosX;
	inline double s_NextMousePosY;
	inline double s_MouseDeltaX;
	inline double s_MouseDeltaY;
	inline double s_ScrollOffsetX;
	inline double s_ScrollOffsetY;
}
