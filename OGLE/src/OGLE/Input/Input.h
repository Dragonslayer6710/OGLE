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
		static void New(unsigned int inputID);
		static Input* Get(unsigned int inputID);

		static void SetState(unsigned int inputID, InputState state);
		static InputState GetState(unsigned int inputID);

		unsigned int GetID();

		void SetState(InputState state);
		InputState GetState();

		InputType GetType();

	protected:
		Input(unsigned int inputID, InputType inputType);

		unsigned int m_InputID;
		InputType m_InputType;
		KeyCode m_KeyCode;
		MouseCode m_MouseButton;
	};

	
	namespace p_Input {
		static std::unordered_map<unsigned int, Input*>* s_Inputs;
		static std::unordered_map<unsigned int, InputState>* s_InputStates;	
		void InitInputs();
		void ResetInputs();

		void NewInput(Input* input);


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
