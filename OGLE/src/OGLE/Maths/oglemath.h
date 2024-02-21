#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <cmath>
#include<gcem.hpp>

/*constexpr glm::mat4 NewModelMatrix(glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
	{
		return glm::scale(glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(rotation), scale);
	}

	constexpr glm::mat4 NewModelMatrix(glm::vec3 translation = glm::vec3(1.0f), glm::vec3 rotDeg = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
	{
		return NewModelMatrix(translation, glm::quat(glm::radians(rotDeg)), scale);
	}*/

namespace OGLE {
    constexpr double pi = 3.14159265358979323846;

    struct Quaternion {
        constexpr Quaternion(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {}
        float x, y, z, w;
    };

    constexpr Quaternion EulerToQuaternion(const glm::vec3& eulerAngles)
    {
        glm::vec3 eulerRad = glm::radians(eulerAngles);

        // Compute sine and cosine values using GCEM
        float cx = gcem::cos(eulerRad.x * 0.5f);
        float sx = gcem::sin(eulerRad.x * 0.5f);
        float cy = gcem::cos(eulerRad.y * 0.5f);
        float sy = gcem::sin(eulerRad.y * 0.5f);
        float cz = gcem::cos(eulerRad.z * 0.5f);
        float sz = gcem::sin(eulerRad.z * 0.5f);

        return Quaternion(
            sx * cy * cz - cx * sy * sz,
            cx * sy * cz + sx * cy * sz,
            cx * cy * sz - sx * sy * cz,
            cx * cy * cz + sx * sy * sz
        );
    }

    constexpr glm::mat4 ConstModelMatrix(const glm::vec3& translation = glm::vec3(0.0f), const glm::vec3& eulerAngles = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
    {
        Quaternion quaternion = EulerToQuaternion(eulerAngles);

        float x2 = quaternion.x * quaternion.x;
        float y2 = quaternion.y * quaternion.y;
        float z2 = quaternion.z * quaternion.z;
        float xy = quaternion.x * quaternion.y;
        float xz = quaternion.x * quaternion.z;
        float yz = quaternion.y * quaternion.z;
        float wx = quaternion.w * quaternion.x;
        float wy = quaternion.w * quaternion.y;
        float wz = quaternion.w * quaternion.z;

        return glm::mat4(
            scale.x * (1 - 2 * (y2 + z2)), scale.x * (2 * (xy + wz)), scale.x * (2 * (xz - wy)), 0.0f,
            scale.y * (2 * (xy - wz)), scale.y * (1 - 2 * (x2 + z2)), scale.y * (2 * (yz + wx)), 0.0f,
            scale.z * (2 * (xz + wy)), scale.z * (2 * (yz - wx)), scale.z * (1 - 2 * (x2 + y2)), 0.0f,
            translation.x, translation.y, translation.z, 1.0f
        );
    }

    static glm::mat4 NewModelMatrix(const glm::vec3& translation = glm::vec3(0.0f), const glm::vec3& eulerAngles = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
    {
        glm::quat rotationQuat = glm::quat(glm::radians(eulerAngles));

        glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuat);

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }

}

