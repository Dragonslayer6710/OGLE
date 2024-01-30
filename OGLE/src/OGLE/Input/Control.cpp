#include "oglepch.h"
#include "OGLE/Input/Control.h"

namespace OGLE {

	void Control::New(ControlID ctrlID)
	{
		p_Control::NewControl(new Control(ctrlID));
	}

	Control* Control::Get(ControlID ctrlID)
	{
		if (p_Control::s_Controls->find(ctrlID) == p_Control::s_Controls->end())
			New(ctrlID);
		return p_Control::s_Controls->operator[](ctrlID);
	}


	


	void Control::BindInput(Input* input)
	{
		m_BoundInput = input;
		UpdateControlBind();
	}

	void Control::UnbindInput()
	{
		BindInput(nullptr);
	}


	ControlID Control::GetID() const
	{
		return m_ControlID;
	}

	InputState Control::GetInputState() const
	{
		return m_BoundInput->GetState();
	}

	ControlType Control::GetType() const
	{
		return p_Control::s_ControlTypes[m_ControlID];
	}


	Control::Control(ControlID ctrlID, Input* input)
		: m_ControlID(ctrlID)
	{
		InitControl();
		BindInput(input);
	}

	Control::Control(ControlID ctrlID) : m_ControlID(ctrlID)
	{
		InitControl();
	}

	void Control::InitControl()
	{
		p_Control::NewControl(this);
		UpdateControlBind();
	}

	void Control::UpdateControlBind()
	{
		if (m_BoundInput) {
			p_Control::s_BoundControls->push_back(this);
		}
		else {
			auto it = std::find(p_Control::s_BoundControls->begin(), p_Control::s_BoundControls->end(), this);
			if (it != p_Control::s_BoundControls->end())
				p_Control::s_BoundControls->erase(it);
		}
	}


	



	

	
	

	

	namespace p_Control {
		void InitControls(std::unordered_map<ControlID, unsigned int>* initialControls /*= p_Control::s_InitialControls*/)
		{
			s_Controls = new std::unordered_map<ControlID, Control*>();
			s_BoundControls = new std::vector<Control*>();
			ResetControls(initialControls);
		}
		void ResetControls(std::unordered_map<ControlID, unsigned int>* initialControls /*= nullptr*/)
		{
			p_Input::ResetInputs();
			if (initialControls)
				for (auto& kv : *initialControls)
					BindInput(kv.first, kv.second);
		}

		void NewControl(Control* ctrl)
		{
			s_Controls->operator[](ctrl->GetID()) = ctrl;
		}
	}

	void InitControls(std::unordered_map<ControlID, unsigned int> initialControls)
	{
		p_Control::InitControls(&initialControls);
	}

	

	std::vector<Control*>& GetBoundControls()
	{
		return *p_Control::s_BoundControls;
	}

	void BindInput(Control* ctrl, Input* input)
	{
		ctrl->BindInput(input);
	}

	void BindInput(ControlID ctrlID, unsigned int inputID)
	{
		Input* input = Input::Get(inputID);
		Control* ctrl = Control::Get(ctrlID);
		BindInput(ctrl, input);
	}

}