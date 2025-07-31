#pragma once
#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Classes.hpp"

std::vector<Sprite> RenderSpriteQueue;

void AddToRenderQueue(Sprite RenderSprite){
    RenderSpriteQueue.push_back(RenderSprite);
};

std::vector<Sprite> RetrieveRenderQueue(){
    return RenderSpriteQueue;
};

void RenderCurrentSpriteQueue(SDL_Renderer* renderer){
    if (RenderSpriteQueue.size() > 0){
        for (int i = 0; i < RenderSpriteQueue.size(); i++){
            RenderSpriteQueue[i].render(renderer);
        };
    };
};