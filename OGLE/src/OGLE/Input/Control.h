#pragma once
#include "OGLE/Input/Input.h"

namespace OGLE {
	static enum ControlID {
		CTRL_MOVE_FORWARD,
		CTRL_MOVE_LEFT,
		CTRL_MOVE_BACKWARD,
		CTRL_MOVE_RIGHT,
		CTRL_MOVE_UP,
		CTRL_MOVE_DOWN,
		
		CTRL_ENABLE_ROTATE,
	};

	static enum ControlState {
		CTRL_STATE_UNBOUND,
		CTRL_STATE_BOUND
	};

	static enum ControlType {
		CTRL_NONE,
		CTRL_TYPE_KEY,
		CTRL_TYPE_MBTN
	};	

	std::unordered_map<ControlID, ControlState*>* s_ControlStates;

	void SetControlState(ControlID id, ControlState state) {

		(*s_ControlStates)[id] = &state;
	}

	ControlState* GetControlState(ControlID id)
	{
		return (*s_ControlStates)[id];
	}


	class ControlBind {
	public:
		static ControlBind* New(ControlID id) {
			return new ControlBind(id, nullptr);
		}	

	public:
		ControlID GetID() { return ID; }
		ControlType GetType() { return Type; }
		void SetType(ControlType type) { Type = type; }
		InputState GetState() { return *InpState; }
	protected:
		ControlID ID;
		ControlType Type;
		ControlState* CtrlState;
		InputState* InpState;
		ControlBind(ControlID id, InputState* inpState, ControlType type=CTRL_NONE)
			:ID(id), Type(type) , InpState(inpState)
		{
			OGLE_CORE_ASSERT(s_ControlStates->find(ID) == s_ControlStates->end(), std::string("Control Bind ID ({0}) already exists!",ID));
			UpdateControlBind();
		}

		void UpdateControlBind()
		{
			if (Type != CTRL_NONE)
				SetControlState(ID, CTRL_STATE_UNBOUND);
			else
				SetControlState(ID, CTRL_STATE_BOUND);
			CtrlState = GetControlState(ID);
		}
	};

	class KeyBind : ControlBind {
	public:
		static ControlBind* New(ControlID id, KeyCode key) {
			return new KeyBind(id, key);

		}
		void SetKey(KeyCode key)
		{
			Key = key;
			InpState = GetKeyState(key);
			UpdateControlBind();
		}
	protected:
		KeyCode Key;
		KeyBind(ControlID id, KeyCode key)
			: ControlBind(id, GetKeyState(key), CTRL_TYPE_KEY), Key(key) {}
	};

	class MouseBtnBind : ControlBind {
	public:
		static ControlBind* New(ControlID id, MouseCode btn) {
			return new MouseBtnBind(id, btn);
		}
		void SetMouseButton(MouseCode btn)
		{
			Button = btn;
			InpState = GetMouseBtnState(btn);
			UpdateControlBind();
		}
	protected:
		MouseCode Button;
		MouseBtnBind(ControlID id, MouseCode btn)
			: ControlBind(id, GetMouseBtnState(btn), CTRL_TYPE_MBTN), Button(btn) {}
	};


	static std::unordered_map<ControlID,ControlBind*> ControlBinds;


	void NewControlBind(ControlID ctrlID) {
		ControlBinds[ctrlID] = ControlBind::New(ctrlID);
	}

	void NewKeyBind(ControlID ctrlID, KeyCode key) {
		ControlBinds[ctrlID] = KeyBind::New(ctrlID, key);
	}

	void NewMouseButtonBind(ControlID ctrlID, MouseCode btn) {
		ControlBinds[ctrlID] = MouseBtnBind::New(ctrlID, btn);
	}

	void NewControlBind(ControlBind* ctrlBind) {
		ControlBinds[ctrlBind->GetID()] = ctrlBind;
	}

	void BindKey(ControlID ctrlID, KeyCode key)
	{
		if (ControlBinds[ctrlID]->GetType() == CTRL_NONE)
			ControlBinds[ctrlID]->SetType(CTRL_TYPE_KEY);
		((KeyBind*)ControlBinds[ctrlID])->SetKey(key);
	}

	void BindMouseButton(ControlID ctrlID, MouseCode btn)
	{
		if (ControlBinds[ctrlID]->GetType() == CTRL_NONE)
			ControlBinds[ctrlID]->SetType(CTRL_TYPE_MBTN);
		((MouseBtnBind*)ControlBinds[ctrlID])->SetMouseButton(btn);
	}

}

