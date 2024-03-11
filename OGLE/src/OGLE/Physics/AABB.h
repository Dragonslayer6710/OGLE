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

        // Function to calculate the direction of collision
        glm::vec3 calculateCollisionDirection(const AABB& other) const {
            // Calculate the direction from the center of the other AABB to this AABB
            glm::vec3 direction = getCenter() - other.getCenter();
            return glm::normalize(direction);
        }

        // Function to calculate penetration depth
        float calculatePenetrationDepth(const AABB& other, const glm::vec3& collisionDirection) const {
            // Calculate overlap along each axis
            glm::vec3 overlap = glm::vec3(0.0f);
            overlap.x = std::min(m_Max.x - other.m_Min.x, other.m_Max.x - m_Min.x);
            overlap.y = std::min(m_Max.y - other.m_Min.y, other.m_Max.y - m_Min.y);
            overlap.z = std::min(m_Max.z - other.m_Min.z, other.m_Max.z - m_Min.z);

            // Calculate the minimum overlap (penetration) among the three axes
            float penetrationDepth = std::min(std::min(overlap.x, overlap.y), overlap.z);

            // Ensure the penetration depth is non-negative
            penetrationDepth = std::max(0.0f, penetrationDepth);

            return penetrationDepth;
        }
    };
}
