#pragma once
#include "OGLE/Input/Input.h"

namespace OGLE {
	enum ControlID {
		CTRL_MOVE_FORWARD,
		CTRL_MOVE_LEFT,
		CTRL_MOVE_BACKWARD,
		CTRL_MOVE_RIGHT,
		CTRL_JUMP,
		CTRL_CROUCH,

		CTRL_CFG_SPRINT,		
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

	class Control {
	public:		
		static void New(ControlID ctrlID);
		static Control* Get(ControlID ctrlID);

		void BindInput(Input* input);
		void UnbindInput();

		ControlID GetID() const;
		ControlType GetType() const;
		InputState GetInputState() const;

	private:
		Control(ControlID ctrlID);
		Control(ControlID ctrlID, Input* input);
		void InitControl();
		void UpdateControlBind();

	private:
		ControlID m_ControlID;
		Input* m_BoundInput = nullptr;
	};

	namespace p_Control {
		static std::unordered_map<ControlID, Control*>* s_Controls;
		static std::vector<Control*>* s_BoundControls;

		static std::unordered_map<ControlID, ControlType> s_ControlTypes = {
			{CTRL_MOVE_FORWARD, CTRL_TYPE_MOVEMENT},
			{CTRL_MOVE_LEFT, CTRL_TYPE_MOVEMENT},
			{CTRL_MOVE_BACKWARD, CTRL_TYPE_MOVEMENT},
			{CTRL_MOVE_RIGHT, CTRL_TYPE_MOVEMENT},
			{CTRL_JUMP, CTRL_TYPE_MOVEMENT},
			{CTRL_CROUCH, CTRL_TYPE_MOVEMENT},

			{CTRL_CFG_SPRINT, CTRL_TYPE_CONFIG},
			{CTRL_CFG_CAMERA_CONTROL_TOGGLE, CTRL_TYPE_CONFIG}
		};

		static void InitControls(std::unordered_map<ControlID, unsigned int>* initialControls = nullptr);
		static void ResetControls(std::unordered_map<ControlID, unsigned int>* initialControls = nullptr);
		
		static void NewControl(Control* ctrl);

	}

	static std::unordered_map<ControlID, unsigned int> s_InitialControls =
	{
		{CTRL_MOVE_FORWARD, Key::W},
		{CTRL_MOVE_LEFT, Key::A},
		{CTRL_MOVE_BACKWARD, Key::S},
		{CTRL_MOVE_RIGHT, Key::D},
		{CTRL_JUMP, Key::Space},
		{CTRL_CROUCH, Key::LeftControl},

		{CTRL_CFG_SPRINT, Key::LeftShift},
		{ CTRL_CFG_CAMERA_CONTROL_TOGGLE, Mouse::ButtonLeft }
	};

	void InitControls(std::unordered_map<ControlID, unsigned int> initialControls = s_InitialControls);

	std::vector<Control*>& GetBoundControls();

	void BindInput(ControlID ctrlID, unsigned int inputID);
	void BindInput(Control* ctrl, Input* input);
}

