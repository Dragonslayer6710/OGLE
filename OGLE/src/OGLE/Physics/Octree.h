#pragma once

#include "OGLE/Physics/AABB.h"

#include "OGLE/Core/Base.h"

#include <psapi.h>
#include <chrono>
#include <random>

#include <vector>
#include <memory>

namespace OGLE
{
    template<typename T, int MAX_OBJECTS = 8>
    class Octree {
    private:
        struct Node {
            AABB bounds;
            std::vector<Ref<T>> objects;
            std::array<Scope<Node>, 8> children;

            Node(const AABB& bounds) : bounds(bounds) {}

            // Copy constructor
            Node(const Node& other) : bounds(other.bounds) {
                // Copy objects vector
                for (const auto& obj : other.objects) {
                    objects.push_back(obj);
                }

                // Recursively copy child nodes
                for (int i = 0; i < 8; ++i) {
                    if (other.children[i]) {
                        children[i] = CreateScope<Node>(*other.children[i]);
                    }
                }
            }

            void split() {
                if (!objects.empty() || children[0] != nullptr)
                    return; // Node is already split or contains objects

                glm::vec3 center = bounds.getCenter();
                glm::vec3 min = bounds.min();
                glm::vec3 max = bounds.max();
                glm::vec3 halfExtent = (max - min) / 2.0f;

                for (int i = 0; i < 8; ++i) {
                    glm::vec3 childMin = min;
                    glm::vec3 childMax = max;

                    if (i & 1) childMin.x = center.x;
                    else childMax.x = center.x;

                    if (i & 2) childMin.y = center.y;
                    else childMax.y = center.y;

                    if (i & 4) childMin.z = center.z;
                    else childMax.z = center.z;

                    children[i] = CreateScope<Node>(AABB::FromMinMax(childMin, childMax));
                }
            }
        };

        Scope<Node> root;

        void insert(const Ref<T>& object, Scope<Node>& node) {
            if (!node->bounds.intersects(*object))
                return;

            if (node->children[0] != nullptr) {
                for (int i = 0; i < 8; ++i) {
                    insert(object, node->children[i]);
                }
            }
            else {
                node->objects.push_back(object);
                if (node->objects.size() > MAX_OBJECTS) {
                    node->split();
                    redistributeObjects(node);
                }
            }
        }

        void redistributeObjects(Scope<Node>& node) {
            auto& objects = node->objects;
            // Check if the node has children
            if (node->children[0] == nullptr)
                return;

            for (const auto& child : node->children) {
                for (auto it = objects.begin(); it != objects.end();) {
                    if (child->bounds.intersects(*(*it))) { // Dereference the shared_ptr to access the AABB
                        child->objects.push_back(*it);
                        it = objects.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
        }


        void query(const AABB& queryBounds, const Scope<Node>& node, std::vector<Ref<T>>& result) const {
            if (!node->bounds.intersects(queryBounds))
                return;

            for (const auto& obj : node->objects) {
                if (queryBounds.intersects(*obj)) {
                    result.push_back(obj);
                }
            }

            for (int i = 0; i < 8; ++i) {
                if (node->children[i] != nullptr) {
                    query(queryBounds, node->children[i], result);
                }
            }
        }

        // Recursive function to traverse the octree along the raycast
        void querySingle(const Raycast& raycast, const Scope<Node>& node, Ref<T>& result) const {
            // Check if the node bounds intersect with the raycast
            if (!node->bounds.intersects(raycast)) {
                return;
            }

            // Check intersection with objects in the current node
            for (const auto& obj : node->objects) {
                if (obj->intersects(raycast)) {
                    // Update result if no object has been found yet
                    result = obj;
                }
            }

            // If the node has children, recursively call queryRecursive for each child
            if (node->children[0] != nullptr) {
                for (int i = 0; i < 8; ++i) {
                    querySingle(raycast, node->children[i], result);
                }
            }
        }

    public:
        Octree(const AABB& bounds) : root(CreateScope<Node>(bounds)) {}

        // Copy constructor
        Octree(const Octree& other) : root(CreateScope<Node>(*other.root)) {}

        // Assignment operator (optional)
        Octree& operator=(const Octree& other) {
            if (this != &other) {
                root = CreateScope<Node>(*other.root);
            }
            return *this;
        }

        void insert(const Ref<T>& object) {
            insert(object, root);
        }

        std::vector<Ref<T>> query(const AABB& queryBounds) const {
            std::vector<Ref<T>> result;
            query(queryBounds, root, result);
            return result;
        }

        Ref<T> querySingle(const Raycast& raycast) const {
            // Default of nothing found
            Ref<T> result = nullptr;

            //Call recursive function to traverse octree along raycast
            querySingle(raycast, root, result);

            // Return first result found
            return result;
        }
    };

    // Define BlockTest struct
    struct BlockTest : public AABB {
        BlockTest(int x, int y, int z)
            : AABB(AABB::FromMinMax(glm::vec3(x, y, z), glm::vec3(x + 1, y + 1, z + 1))) {}
    };

    // Define ChunkTest struct with an Octree of BlockTest structs
    struct ChunkTest : public AABB {
        Octree<BlockTest> chunkOctree;
        AABB chunkBounds;

        // Constructor with bounds
        ChunkTest(const AABB& bounds) : 
            AABB(bounds), chunkOctree(bounds), chunkBounds(bounds) {}

        // Copy constructor
        ChunkTest(const ChunkTest& other) :
            AABB(other), chunkOctree(other.chunkOctree), chunkBounds(other.chunkBounds) {}
    };


    // Function to get current memory usage
    inline std::size_t getCurrentMemoryUsage() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return pmc.WorkingSetSize;
        }
        else {
            // Error handling
            return 0;
        }
    }


    // Test function
    inline void testOctree() {
        // Define test parameters
        constexpr int chunkWidth = 10;
        constexpr int chunkHeight = 10;
        constexpr int numChunks = 5;

        // Test memory management
        std::size_t initialMemoryUsage = getCurrentMemoryUsage();

        // Create Octree and perform operations
        Octree<ChunkTest> octree(AABB::FromMinMax(glm::vec3(0.0f), glm::vec3(chunkWidth * numChunks, chunkHeight, chunkWidth)));

        auto startTime = std::chrono::high_resolution_clock::now();

        // Insert chunks and blocks into the octree
        for (int i = 0; i < numChunks; ++i) {
            ChunkTest chunk(AABB::FromMinMax(glm::vec3(i * chunkWidth, 0.0f, 0.0f), glm::vec3((i + 1) * chunkWidth, chunkHeight, chunkWidth)));
            for (float x = i * chunkWidth; x < (i + 1) * chunkWidth; ++x) {
                for (float y = 0; y < chunkHeight; ++y) {
                    for (float z = 0; z < chunkWidth; ++z) {
                        chunk.chunkOctree.insert(CreateRef<BlockTest>(x, y, z));
                    }
                }
            }
            octree.insert(CreateRef<ChunkTest>(chunk));
        }

        auto insertionEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> insertionTime = insertionEndTime - startTime;

        s_TestEnabled = true;

        // Perform collision detection test with queryBounds2
        AABB queryBounds2 = AABB::FromMinMax(glm::vec3(0.0f), glm::vec3(1.0f, 2.0f, 1.0f));
        std::vector<Ref<BlockTest>> collidedBlocks2;
        startTime = std::chrono::high_resolution_clock::now();
        // Query octree for objects within queryBounds2
        for (const Ref<ChunkTest>& chunk : octree.query(queryBounds2)) {
            for (const Ref<BlockTest>& block : chunk->chunkOctree.query(queryBounds2)) {
                collidedBlocks2.emplace_back(block);
                std::cout << "Collided block position (queryBounds2): (" << block->min().x << ", " << block->min().y << ", " << block->min().z << ")" << std::endl;
            }
        }

        auto collisionDetectionEndTime2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> collisionDetectionTime2 = collisionDetectionEndTime2 - startTime;

        // Verify collision detection results
        if (collidedBlocks2.empty()) {
            std::cout << "No collisions detected (queryBounds2)." << std::endl;
        }
        else {
            std::cout << "Collisions detected (queryBounds2): " << collidedBlocks2.size() << " blocks." << std::endl;
        }

        // Output results
        std::cout << "Insertion time: " << insertionTime.count() << " seconds" << std::endl;
        std::cout << "Collision detection time (queryBounds2): " << collisionDetectionTime2.count() << " seconds" << std::endl;

        // Test raycast query
        // Define a raycast
        glm::vec3 rayStart(0.0f, 0.0f, 0.0f);
        glm::vec3 rayDirection(1.0f, 0.0f, 0.0f); // Example direction
        Raycast raycast(rayStart, rayDirection, 100.0f); // Example length

        // Perform raycast query
        auto result = octree.querySingle(raycast);

        // Check the result
        if (result) {
            std::cout << "Raycast intersected object at position: (" << result->min().x << ", " << result->min().y << ", " << result->min().z << ")" << std::endl;
        }
        else {
            std::cout << "Raycast did not intersect any object." << std::endl;
        }

        // Check memory usage after operations
        std::size_t finalMemoryUsage = getCurrentMemoryUsage();
        std::size_t memoryUsageDifference = finalMemoryUsage - initialMemoryUsage;
        std::cout << "Memory usage difference: " << memoryUsageDifference << " bytes" << std::endl;
    }




}
