#pragma once
static bool s_TestEnabled = false;
namespace OGLE 
{
    class AABB {
    protected:
        glm::vec3 m_Min, m_Max;

        AABB(const glm::vec3& min, const glm::vec3& max)
            : m_Min(min), m_Max(max) {}

    public:
        AABB() {}
        static AABB FromMinMax(const glm::vec3& min, const glm::vec3& max)
        {
            return AABB(min, max);
        }
       
        static AABB FromPos(const glm::vec3& position, const glm::vec3& size = glm::vec3(1.0f))
        {
            return AABB(position - size / 2.0f, position + size / 2.0f);
        }  

        inline glm::vec3 min() const { return m_Min; }
        inline glm::vec3 max() const { return m_Max; }
        bool AABB::intersects(const AABB& other) const {

            // Check if there is overlap on each axis
            bool overlapX = (other.m_Min.x <= m_Max.x) && (other.m_Max.x >= m_Min.x);
            bool overlapY = (other.m_Min.y <= m_Max.y) && (other.m_Max.y >= m_Min.y);
            bool overlapZ = (other.m_Min.z <= m_Max.z) && (other.m_Max.z >= m_Min.z);

            // No intersection if there is no overlap on any axis
            if (!overlapX || !overlapY || !overlapZ) {
                return false;
            }

            return true;

        }
        glm::vec3 getCenter() const {
            return (m_Min + m_Max) / 2.0f;
        }

        float getRadius() const {
            glm::vec3 extent = m_Max - m_Min;
            return glm::compMax(extent) / 2.0f;
        }

        glm::vec3 calculateCollisionCorrection(const AABB& other) const {
            glm::vec3 otherToThis = m_Max - other.m_Min;
            glm::vec3 thisToOther = other.m_Max - m_Min;

            glm::vec3 minOverlap = glm::vec3(0.0f);

            // Calculate overlap on each axis
            for (int i = 0; i < 3; i++) {
                if (abs(otherToThis[i]) < abs(thisToOther[i])) {
                    minOverlap[i] = otherToThis[i];
                }
                else {
                    minOverlap[i] = thisToOther[i];                   
                }
            }
            return minOverlap;
            // Find the axis with the least overlap
            if (std::abs(minOverlap.x) < std::abs(minOverlap.y) && std::abs(minOverlap.x) < std::abs(minOverlap.z)) {
                if (!minOverlap.x)
                    if (minOverlap.x == abs(otherToThis.x))
                        minOverlap.x = -1.0f;
                    else
                        minOverlap.x = 1.0f;
                return glm::vec3(minOverlap.x, 0.0f, 0.0f);
            }
            else if (std::abs(minOverlap.y) < std::abs(minOverlap.z)) {
                if (!minOverlap.y)
                    if (minOverlap.y == abs(otherToThis.y))
                        minOverlap.y = -1.0f;
                    else
                        minOverlap.y = 1.0f;
                return glm::vec3(0.0f, minOverlap.y, 0.0f);
            }
            else {
                if (!minOverlap.z)
                    if (minOverlap.z == abs(otherToThis.z))
                        minOverlap.z = -1.0f;
                    else
                        minOverlap.z = 1.0f;
                return glm::vec3(0.0f, 0.0f, minOverlap.z);
            }
        }


        // Function to calculate penetration depth
        glm::vec3 calculateCorrectionDirection (const AABB& other, const glm::vec3& correction) const {
            glm::vec3 otherToThis = m_Max - other.m_Min;
            glm::vec3 thisToOther = other.m_Max - m_Min;

            glm::vec3 collisionDirection(0.0f);

            if (std::abs(correction.x) < std::abs(correction.y) && std::abs(correction.x) < std::abs(correction.z)) {
                if (correction.x == otherToThis.x && correction.x > 0)
                    collisionDirection.x = -correction.x;
                else
                    collisionDirection.x = correction.x;
                if (!correction.x)
                    if (correction.x == abs(otherToThis.x))
                        collisionDirection.x = -1.0f;
                    else
                        collisionDirection.x = 1.0f;
            }
            else if (std::abs(correction.y) < std::abs(correction.z)) {
                if (correction.y == otherToThis.y && correction.y > 0)
                    collisionDirection.y = -correction.y;
                else
                    collisionDirection.y = correction.y;
                if (!correction.y)
                    if (correction.y == abs(otherToThis.y))
                        collisionDirection.y = -1.0f;
                    else
                        collisionDirection.y = 1.0f;
            }
            else {
                if (correction.z == otherToThis.z && correction.z > 0)
                    collisionDirection.z = -correction.z;
                else
                    collisionDirection.z = correction.z;
                if (!correction.z)
                    if (correction.z == abs(otherToThis.z))
                        collisionDirection.z = -1.0f;
                    else
                        collisionDirection.z = 1.0f;
            }
            return glm::normalize(collisionDirection);
        }
    };
}
