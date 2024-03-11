#pragma once

#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric> 

namespace OGLE {

    class Timer {

    public:

        Timer(int targetFPS = 144, double minDeltaTime = 0.001) {
            SetTargetFPS(targetFPS);
            this->minDeltaTime = minDeltaTime;
            lastTime = std::chrono::steady_clock::now();
        }

        void SetTargetFPS(int targetFPS) {
            targetFrameDuration = std::chrono::duration<double>(1.0 / targetFPS);
            // Adjust sample size based on target FPS
            int sampleSize = std::max(1, targetFPS / 10); // Use 1/10th of target FPS as sample size
            SetSampleSize(sampleSize);
        }

        void SetSampleSize(int sampleSize) {
            deltaTimeSamples.clear();
            deltaTimeSamples.resize(sampleSize, targetFrameDuration.count());
        }

        double GetDeltaTime() {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<double> frameDuration = currentTime - lastTime;

            // Cap the frame duration to avoid very large deltaTime values
            frameDuration = std::min(frameDuration, maxFrameDuration);

            // Ensure delta time is non-negative
            if (frameDuration.count() < 0) {
                std::cerr << "Negative frame duration detected!" << std::endl;
                return 0.0; // Return 0 to avoid negative delta time
            }

            lastTime = currentTime;

            // Store the frame duration in the circular buffer
            deltaTimeSamples[circularIndex] = frameDuration.count();

            // Update circularIndex
            circularIndex = (circularIndex + 1) % deltaTimeSamples.size();

            // Calculate the average delta time
            double avgDeltaTime = std::accumulate(deltaTimeSamples.begin(), deltaTimeSamples.end(), 0.0) / deltaTimeSamples.size();

            return std::max(avgDeltaTime, minDeltaTime); // Use minimum delta time
        }

    private:
        std::chrono::duration<double> targetFrameDuration;
        std::chrono::time_point<std::chrono::steady_clock> lastTime;
        const std::chrono::duration<double> maxFrameDuration = std::chrono::milliseconds(100); // Cap at 100 ms

        std::vector<double> deltaTimeSamples;
        size_t circularIndex = 0;
        double minDeltaTime;
    };

} // namespace OGLE
