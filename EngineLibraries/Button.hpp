#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Classes.hpp"

struct ToggleButton
{
    SDL_Texture* ButtonInactiveTexture;
    SDL_Texture* ButtonActiveTexture;
    bool Toggled = false;
    float x,y,h,w;
    ToggleButton(SDL_Renderer* renderer, const char* InactiveTextureLocation, const char* ActiveTextureLocation, float Nx, float Ny, float Nh, float Nw);
    bool IsMouseHovering();
    void render(SDL_Renderer* renderer);
};

ToggleButton::ToggleButton(SDL_Renderer* renderer, const char* InactiveTextureLocation, const char* ActiveTextureLocation, float Nx, float Ny, float Nh, float Nw){
    SDL_Texture* InactiveTexture = IMG_LoadTexture(renderer, InactiveTextureLocation);
    SDL_Texture* ActiveTexture = IMG_LoadTexture(renderer, ActiveTextureLocation);

    if (InactiveTexture != NULL && ActiveTexture != NULL){
        
        ButtonInactiveTexture = InactiveTexture;
        ButtonActiveTexture = ActiveTexture;
        x = Nx; y = Ny; w = Nw; h = Nh;

    }else {
        std::cout << "\nWARNING: TEXTURES DIDNT HAVE A GOOD POKER FACE! (Button.hpp) ♦️🪩\n";
    };
};

void ToggleButton::render(SDL_Renderer* renderer){
    SDL_FRect Rect = {x,y,w,h};

    if (Toggled == false){
        SDL_RenderTexture(renderer, ButtonInactiveTexture, NULL, &Rect);
    } else {
        SDL_RenderTexture(renderer, ButtonActiveTexture, NULL, &Rect);
    };

};

bool ToggleButton::IsMouseHovering(){
    float mx, my;
    SDL_GetMouseState(&mx, &my);

    if (mx >= x && mx <= x+w && my > y && my <= my){
        return true;
    }

    return false;
};