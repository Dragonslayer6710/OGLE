#include "oglepch.h"
#include "OGLE/Input/Input.h"

namespace OGLE {
	

	void Input::New(unsigned int inputID)
	{
		if (inputID < 8)
			p_Input::NewInput(new Input(inputID, INPUT_TYPE_MOUSE));
		else
			p_Input::NewInput(new Input(inputID, INPUT_TYPE_KEY));
	}

	Input* Input::Get(unsigned int inputID)
	{
		if (p_Input::s_Inputs->find(inputID) == p_Input::s_Inputs->end())
			New(inputID);
		return p_Input::s_Inputs->operator[](inputID);
	}


	void Input::SetState(unsigned int inputID, InputState state)
	{
		Input::Get(inputID)->SetState(state);
	}

	InputState Input::GetState(unsigned int inputID)
	{
		return Input::Get(inputID)->GetState();
	}


	unsigned int Input::GetID()
	{
		return m_InputID;
	}


	void Input::SetState(InputState state)
	{
		p_Input::s_InputStates->operator[](m_InputID) = state;
	}

	InputState Input::GetState()
	{
		return p_Input::s_InputStates->operator[](m_InputID);
	}


	InputType Input::GetType()
	{
		return m_InputType;
	}


	Input::Input(unsigned int inputID, InputType inputType) : m_InputID(inputID), m_InputType(inputType)
	{
		if (m_InputType)
			m_MouseButton = m_InputID;
		else
			m_KeyCode = m_InputID;

		SetState(INPUT_STATE_RELEASE);
	}
	
	namespace p_Input {
					

		void InitInputs()
		{
			s_Inputs = new std::unordered_map<unsigned int, Input*>();
			s_InputStates = new std::unordered_map<unsigned int, InputState>();
		}

		void ResetInputs()
		{
			InitInputs();
		}

		void NewInput(Input* input)
		{
			s_Inputs->operator[](input->GetID()) = input;
		}

		

	}



}