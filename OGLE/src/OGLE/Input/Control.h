#pragma once
#include "OGLE/Input/Input.h"

namespace OGLE {
	enum ControlID {
		CTRL_MOVE_FORWARD,
		CTRL_MOVE_LEFT,
		CTRL_MOVE_BACKWARD,
		CTRL_MOVE_RIGHT,
		CTRL_MOVE_UP,
		CTRL_MOVE_DOWN,
		
		CTRL_CFG_CAMERA_CONTROL_TOGGLE,
	};

	enum ControlBindState {
		CTRL_STATE_UNBOUND,
		CTRL_STATE_BOUND
	};

	enum ControlType {
		CTRL_TYPE_MOVEMENT,
		CTRL_TYPE_CAMERA,
		CTRL_TYPE_CONFIG,
	};	

	static std::unordered_map<ControlID, ControlType> s_ControlTypes = {
		{CTRL_MOVE_FORWARD, CTRL_TYPE_MOVEMENT},
		{CTRL_MOVE_LEFT, CTRL_TYPE_MOVEMENT},
		{CTRL_MOVE_BACKWARD, CTRL_TYPE_MOVEMENT},
		{CTRL_MOVE_RIGHT, CTRL_TYPE_MOVEMENT},
		{CTRL_MOVE_UP, CTRL_TYPE_MOVEMENT},
		{CTRL_MOVE_DOWN, CTRL_TYPE_MOVEMENT},

		{CTRL_CFG_CAMERA_CONTROL_TOGGLE, CTRL_TYPE_CONFIG}
	};

	
	static std::unordered_map<ControlID, unsigned int> s_InitialControls =
	{
		{CTRL_MOVE_FORWARD, Key::W},
		{CTRL_MOVE_LEFT, Key::A},
		{CTRL_MOVE_BACKWARD, Key::S},
		{CTRL_MOVE_RIGHT, Key::D},
		{CTRL_MOVE_UP, Key::Space},
		{CTRL_MOVE_DOWN, Key::LeftControl},

		{CTRL_CFG_CAMERA_CONTROL_TOGGLE, Mouse::ButtonLeft}
	};


	class Control {
	public:		
		static std::vector<Control*>& GetBoundControls();

		static void ResetControls(std::unordered_map<ControlID, unsigned int>* initialControls = nullptr);

		static void BindInput(ControlID ctrlID, unsigned int inputID);

		static void New(ControlID ctrlID);

		static Control* GetControl(ControlID ctrlID);

		Control();

		Control(ControlID ctrlID);

		Control(ControlID ctrlID, Input* input);

		ControlID GetControlID() const;

		void UpdateControlBind();

		ControlType GetControlType() const;

		InputState GetInputState() const;


	private:

		static void BindInput(Control* ctrl, Input* input);

		void BindInput(Input* input);
		void UnbindInput();

		static void InitControls();

		static void NewControl(Control* ctrl);

		void InitControl();

	private:
		static std::unordered_map<ControlID, Control*>* s_Controls;
		static std::vector<Control*>* s_BoundControls;

		ControlID m_ControlID;
		Input* m_BoundInput = nullptr;
	};

	static void InitControls(std::unordered_map<ControlID, unsigned int> initialControls = s_InitialControls) {
		Input::ResetInputs();
		Control::ResetControls(&initialControls);
	}
}

