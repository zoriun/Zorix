#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_dialog.h>
#include <vector>
#include "Classes.hpp"
#include "Miscellaneous.hpp"
#include "RenderQueue.hpp"
#include "Button.hpp"

SDL_Renderer* GlobalRenderer;

void FileOpenContext(void* Userdata, const char* const* File, int File_amount){
    if (File[0] != NULL){
        SDL_Texture* NewTexture = IMG_LoadTexture(GlobalRenderer, File[0]);
        if (NewTexture != NULL){
            Sprite NewSprite(GlobalRenderer, File[0], 0, 0, 200, 200);
            AddToRenderQueue(NewSprite);
        }
    }
};

int CreateNewProjectWindow(){
    SDL_Window* window = SDL_CreateWindow("New Project", 1280, 720, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    GlobalRenderer = renderer;

    Sprite ImportToolSprite(renderer, "Textures/ImportToolUnselected.png",0,0,40,40);
    Sprite MoveToolUnselectedSprite(renderer, "Textures/MoveToolUnselected.png", 0,0,50,50);
    Sprite MoveToolSelectedSprite(renderer, "Textures/MoveToolSelected.png", 0,0,40,40);
    Sprite ToolbarSprite(renderer, "Textures/ToolBar.png", 0,0,375,200);

    ToggleButton ToggleME(renderer, "Textures/MoveToolUnselected.png", "Textures/MoveToolSelected.png", 0,0,40,40);

    std::vector<Sprite> MoveableSprites;

    bool running = true;

    while (running == true)
    {
        SDL_Event event;
        SDL_SetRenderDrawColor(renderer, 60,60,60,255);
        SDL_RenderClear(renderer);

        int wx, wy;
        SDL_GetWindowSizeInPixels(window, &wx, &wy);

        float mx, my;
        SDL_GetMouseState(&mx, &my);

        ImportToolSprite.x = (wx-ImportToolSprite.w)/2;
        ImportToolSprite.y = (wy-ImportToolSprite.h) - (wy-ToolbarSprite.h+130);

        MoveToolUnselectedSprite.x = ((wx-MoveToolUnselectedSprite.w)/2)-100;
        MoveToolUnselectedSprite.y = (wy-MoveToolUnselectedSprite.h) - (wy-MoveToolUnselectedSprite.h)+25;

        ToolbarSprite.x = (wx-ToolbarSprite.w)/2;
        ToolbarSprite.y = (wy-ToolbarSprite.h) -(wy-ToolbarSprite.h+50);

        ToolbarSprite.render(renderer);
        ImportToolSprite.render(renderer);
        MoveToolUnselectedSprite.render(renderer);
        ToggleME.render(renderer);

        RenderCurrentSpriteQueue(renderer); 

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                
                if (mx >= ImportToolSprite.GetVector2().x && mx <= ImportToolSprite.GetVector2().x + ImportToolSprite.GetVector2().w && my >= ImportToolSprite.GetVector2().y && my <= ImportToolSprite.GetVector2().y+ImportToolSprite.GetVector2().h){
                    SDL_ShowOpenFileDialog(FileOpenContext,NULL,window,NULL,0,NULL,false);
                } // check for importing (holy fuck this is unreadable lmaoo, ill make a click detection library for ts later.)

                if (ToggleME.IsMouseHovering() == true) {
                    
                    if (ToggleME.Toggled == false){
                        ToggleME.Toggled = true;
                    } else {
                        ToggleME.Toggled = false;
                    }

                }

            };
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(8);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
};