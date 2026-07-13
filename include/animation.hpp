#pragma once
#include "raylib.h"
#include <vector>

class MultiImageAnimation {
public:
    std::vector<Texture2D> frames;
    int currentFrame;
    float frameTime;
    float durationLeft;
    
    MultiImageAnimation();
    MultiImageAnimation(std::vector<Texture2D> loadedFrames, float timePerFrame);
    
    void animationUpdate(float deltaTime);
    Texture2D getCurrentFrame();
};