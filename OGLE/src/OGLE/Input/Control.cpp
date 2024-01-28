#include "oglepch.h"
#include "OGLE/Input/Control.h"

namespace OGLE {
	std::unordered_map<ControlID, Control*>* Control::s_Controls;
	std::vector<Control*>* Control::s_BoundControls;
	void Control::InitControl()
	{
		NewControl(this);
		UpdateControlBind();
	}

	void Control::NewControl(Control* ctrl)
	{
		s_Controls->operator[](ctrl->GetControlID()) = ctrl;
	}

	void Control::InitControls()
	{
		s_Controls = new std::unordered_map<ControlID, Control*>();
		s_BoundControls = new std::vector<Control *>();
	}

	void Control::UnbindInput()
	{
		BindInput(nullptr);
	}

	void Control::BindInput(Input* input)
	{
		m_BoundInput = input; 
		UpdateControlBind();
	}

	void Control::BindInput(Control* ctrl, Input* input)
	{
		ctrl->BindInput(input);
	}

	void Control::BindInput(ControlID ctrlID, unsigned int inputID)
	{
		Input* input = Input::GetInput(inputID);
		Control* ctrl = GetControl(ctrlID);
		BindInput(ctrl, input);
	}

	std::vector<Control*>& Control::GetBoundControls()
	{
		return *s_BoundControls;
	}

	OGLE::InputState Control::GetInputState() const
	{
		return m_BoundInput->GetInputState();
	}

	OGLE::ControlType Control::GetControlType() const
	{
		return s_ControlTypes[m_ControlID];
	}

	void Control::UpdateControlBind()
	{
		if (m_BoundInput) {
			s_BoundControls->push_back(this);
		}
		else {
			auto it = std::find(s_BoundControls->begin(), s_BoundControls->end(), this);
			if (it != s_BoundControls->end())
				s_BoundControls->erase(it);
		}
	}

	OGLE::ControlID Control::GetControlID() const
	{
		return m_ControlID;
	}

	Control::Control(ControlID ctrlID, Input* input) : m_ControlID(ctrlID)
	{
		InitControl();
		BindInput(input);
	}

	Control::Control(ControlID ctrlID) : m_ControlID(ctrlID)
	{
		InitControl();
	}

	Control::Control()
	{

	}

	OGLE::Control* Control::GetControl(ControlID ctrlID)
	{
		if (s_Controls->find(ctrlID) == s_Controls->end())
			New(ctrlID);
		return s_Controls->operator[](ctrlID);
	}

	void Control::New(ControlID ctrlID)
	{
		NewControl(new Control(ctrlID));
	}

	void Control::ResetControls(std::unordered_map<ControlID, unsigned int>* initialControls /*= nullptr*/)
	{
		InitControls();
		if (initialControls)
			for (auto& kv : *initialControls)
				BindInput(kv.first, kv.second);
	}

}