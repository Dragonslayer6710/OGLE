#pragma once
#include "OGLE/Input/Control.h"
#include "OGLE/Physics/Raycast.h"

namespace OGLE {

	class Camera {
	public:

		static Scope<Camera> Create(Ref<glm::vec3> position = CreateRef<glm::vec3>(0.0f))
		{ 
			return CreateScope<Camera>(position);
		}

		static Scope<Camera> Create(glm::vec3 position = glm::vec3(0.0f))
		{
			return Camera::Create(CreateRef<glm::vec3>(position));
		}

		Camera(Ref<glm::vec3> position = CreateRef<glm::vec3>(0.0f));

		void Rotate();

		Ref<glm::vec3> GetPosition();
		Ref<glm::vec3> GetOrientation();
		Ref<glm::vec3> GetUp();

		glm::mat4 GetViewMatrix() const;

		Raycast GetRaycast(float distance);
	private:
		float m_CameraSensitivity = 0.5f;

		Ref<glm::vec3> m_Position;
		Ref<glm::vec3> m_Orientation;
		Ref<glm::vec3> m_Up;
	};
}
