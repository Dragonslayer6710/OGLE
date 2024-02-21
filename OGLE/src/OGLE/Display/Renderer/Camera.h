#pragma once
#include "OGLE/Input/Control.h"

namespace OGLE {

	class Camera {
	public:

		Camera();

		void Rotate();

		void MoveForward();

		void MoveBackward();

		void StrafeLeft();

		void StrafeRight();

		void MoveUp();

		void MoveDown();


		glm::mat4 GetViewMatrix() const;
	private:
		float m_CameraSensitivity = 0.5f;
		float m_MoveSpeed = 0.1f;

		glm::vec3 m_Pos;
		glm::vec3 m_Orientation;
		glm::vec3 m_Up;
	};
}
