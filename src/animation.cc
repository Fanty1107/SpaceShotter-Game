#include "animation.hpp"


MultiImageAnimation::MultiImageAnimation() {
    currentFrame = 0;
    frameTime = 0.0f;
    durationLeft = 0.0f;
}

MultiImageAnimation::MultiImageAnimation(std::vector<Texture2D> loadedFrames, float timePerFrame) {
    frames = loadedFrames;
    frameTime = timePerFrame;
    durationLeft = frameTime;
    currentFrame = 0;
}

void MultiImageAnimation::animationUpdate(float deltaTime) {
    if (frames.empty()) return;

    durationLeft -= deltaTime;
    if (durationLeft <= 0.0f) {
        durationLeft = frameTime;
        currentFrame++;     
        if (currentFrame >= frames.size()) {
            currentFrame = 0;
        }
    }
}

Texture2D MultiImageAnimation::getCurrentFrame() {
    return frames[currentFrame];
}