#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

struct Vector2
{
    float x,y,w,h;
    Vector2(float newX, float newY, float newW, float newH);
};

struct Sprite
{
    SDL_Texture* SpriteTexture;
    float x,y,w,h;
    
    Sprite(SDL_Renderer* renderer, const char* SpriteLocation, int Nx, int Ny, int Nw, int Nh);
    void render(SDL_Renderer* renderer);
    void editTransform(float Nx, float Ny, float Nw, float Nh);
    void editTransformWithVector2(Vector2 vector);
    Vector2 GetVector2();
};

Vector2::Vector2(float newX, float newY, float newW, float newH){
    x = newX;
    y = newY;
    w = newW;
    h = newH;
};

Sprite::Sprite(SDL_Renderer* renderer, const char* SpriteLocation, int Nx, int Ny, int Nw, int Nh){
    SpriteTexture = IMG_LoadTexture(renderer, SpriteLocation);
    x = Nx; y = Ny; w = Nw; h = Nh;
}; 

void Sprite::editTransform(float Nx, float Ny, float Nw, float Nh){
    x = Nx; y = Ny; w = Nw; h = Nh;
};
void Sprite::editTransformWithVector2(Vector2 vector){
    x = vector.x; y = vector.y; w = vector.w; h = vector.h;
};

Vector2 Sprite::GetVector2(){
    return Vector2(x,y,w,h);
};

void Sprite::render(SDL_Renderer* renderer) {
    SDL_FRect SpriteRect = {x, y, w, h};
    SDL_RenderTexture(renderer, SpriteTexture, NULL, &SpriteRect);
};