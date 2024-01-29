#include "oglepch.h"
#include "OGLE/Input/Input.h"

namespace OGLE {
	std::unordered_map<unsigned int, Input*>* Input::s_Inputs;
	std::unordered_map<unsigned int, InputState>* Input::s_InputStates;

	void Input::InitInputs()
	{
		s_Inputs = new std::unordered_map<unsigned int, Input*>();
		s_InputStates = new std::unordered_map<unsigned int, InputState>();
	}

	void Input::NewInput(Input* input)
	{
		s_Inputs->operator[](input->GetInputID()) = input;
	}

	Input::Input(unsigned int inputID, InputType inputType) : m_InputID(inputID), m_InputType(inputType)
	{
		if (m_InputType)
			m_KeyCode = m_InputID;
		else
			m_MouseButton = m_InputID;
		SetInputState(INPUT_STATE_RELEASE);
	}

	Input::Input()
	{

	}

	void Input::ResetInputs()
	{
		InitInputs();
	}

	void Input::New(unsigned int inputID)
	{
		if (inputID < 8)
			NewInput(new Input(inputID, INPUT_TYPE_MOUSE));
		else
			NewInput(new Input(inputID, INPUT_TYPE_KEY));
	}

	OGLE::Input* Input::GetInput(unsigned int inputID)
	{
		if (s_Inputs->find(inputID) == s_Inputs->end())
			New(inputID);
		return s_Inputs->operator[](inputID);
	}

	unsigned int Input::GetInputID()
	{
		return m_InputID;
	}

	OGLE::InputState Input::GetInputState()
	{
		return s_InputStates->operator[](m_InputID);
	}

	void Input::SetInputState(InputState state)
	{
		s_InputStates->operator[](m_InputID) = state;
	}

	OGLE::InputType Input::GetInputType()
	{
		return m_InputType;
	}
}