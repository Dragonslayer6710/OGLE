#pragma once
#include "OGLE/Input/Control.h"
#include "OGLE/Maths/glm.h"

namespace OGLE {

	class Camera {
	public:

		Camera();

		bool IsControlBound();
		void EnablControls();
		void DisableControls();


		void Rotate();

		void MoveForward();

		void MoveBackward();

		void StrafeLeft();

		void StrafeRight();

		void MoveUp();

		void MoveDown();


		glm::mat4 GetWorldToViewMatrix() const;
	private:
		bool m_ControlEnabled = false;
		float m_CameraSensitivity = 0.5f;
		float m_MoveSpeed = 0.1f;

		glm::vec3 m_Pos;
		glm::vec3 m_Orientation;
		glm::vec3 m_Up;
	};
}
