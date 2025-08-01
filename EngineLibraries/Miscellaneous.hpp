#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Classes.hpp"

Vector2 WindowDynamicVector2Update(SDL_Window* window, Vector2 Vector, int XOffset, int YOffset, const char* type){
    int wx, wy;
    SDL_GetWindowSizeInPixels(window, &wx, &wy);

    if (type == "--"){
        Vector.x = (wx-Vector.w) + XOffset;
        Vector.y = (wy-Vector.h) + YOffset;
    } else if (type == "++")
    {
        Vector.x = (wx+Vector.w) + XOffset;
        Vector.y = (wy+Vector.h) + YOffset;       
    } else if (type == "-+")
    {
        Vector.x = (wx-Vector.w) + XOffset;
        Vector.y = (wy+Vector.h) + YOffset;       
    } else if (type == "+-")
    {
        Vector.x = (wx+Vector.w) + XOffset;
        Vector.y = (wy-Vector.h) + YOffset;       
    }
    
    return Vector;
};

float lerp(float a, float b, float t){
    return a + t * (b - a);
};