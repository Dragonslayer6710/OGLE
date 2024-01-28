#pragma once
#include "OGLE/Input/Input.h"
namespace OGLE {

	class Camera {
	public:

		Camera(glm::vec2 initMousePos)
			: m_Pos(0.0f, 0.0f, 0.0f), m_Orientation(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f)
		{
		}

		bool GetControlState() { return m_ControlEnabled; }
		void EnablControls() { m_ControlEnabled = true; }
		void DisableControls() { m_ControlEnabled = false; }


		void Rotate(Window& window)
		{

			double x, y;
			glfwGetCursorPos((GLFWwindow*)window.GetNativeWindow(),&x, &y);
			MoveMousePos(glm::vec2(x,y));
			glm::vec3 rotY = glm::cross(m_Orientation, m_Up);
			glm::mat4 rotation =
				glm::rotate(glm::radians(-s_MouseDelta.x * m_CameraSensitivity), m_Up) *
				glm::rotate(glm::radians(-s_MouseDelta.y * m_CameraSensitivity), rotY);
			m_Orientation = glm::mat3(rotation) * m_Orientation;
			s_MouseDelta = glm::vec2(0);
			glfwSetInputMode((GLFWwindow*)window.GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			SetMousePos((GLFWwindow*)window.GetNativeWindow(),glm::vec2(window.GetWidth() / 2, window.GetHeight() / 2));
		}

		void MoveForward()
		{
			m_Pos += m_MoveSpeed * m_Orientation;
		}

		void MoveBackward()
		{
			m_Pos -= m_MoveSpeed * m_Orientation;
		}

		void StrafeLeft()
		{
			m_Pos -= m_MoveSpeed * glm::cross(m_Orientation, m_Up);
		}

		void StrafeRight()
		{
			m_Pos += m_MoveSpeed * glm::cross(m_Orientation, m_Up);
		}

		void MoveUp()
		{
			m_Pos += m_MoveSpeed * m_Up;
		}

		void MoveDown()
		{
			m_Pos -= m_MoveSpeed * m_Up;
		}


		glm::mat4 GetWorldToViewMatrix() const { return glm::lookAt(m_Pos, m_Pos + m_Orientation, m_Up); }
	private:
		bool m_ControlEnabled = false;
		float m_CameraSensitivity = 0.5f;
		float m_MoveSpeed = 0.1f;

		glm::vec3 m_Pos;
		glm::vec3 m_Orientation;
		glm::vec3 m_Up;
	};
}
