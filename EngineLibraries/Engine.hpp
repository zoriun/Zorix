#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
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
            Sprite NewSprite(GlobalRenderer, File[0], 0, 0, NewTexture->w, NewTexture->h);
            AddToRenderQueue(NewSprite);
        }
    }
};

int CreateNewProjectWindow(){
    SDL_Window* window = SDL_CreateWindow("New Project", 1280, 720, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    GlobalRenderer = renderer;

    Sprite ImportToolSprite(renderer, "Textures/ImportToolUnselected.png",0,0,40,40);
    Sprite ToolbarSprite(renderer, "Textures/ToolBar.png", 0,0,375,200);

    ToggleButton MoveToolButton(renderer, "Textures/MoveToolUnselected.png", "Textures/MoveToolSelected.png", 0,0,45,45);

    Sprite* SelectedSprite;

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

        MoveToolButton.x = ((wx-MoveToolButton.w)/2)-150;
        MoveToolButton.y = (wy-MoveToolButton.h) - (wy-MoveToolButton.h)+27;

        ToolbarSprite.x = (wx-ToolbarSprite.w)/2;
        ToolbarSprite.y = (wy-ToolbarSprite.h) -(wy-ToolbarSprite.h+50);

        RenderCurrentSpriteQueue(renderer);

        ToolbarSprite.render(renderer);
        ImportToolSprite.render(renderer);
        MoveToolButton.render(renderer);

        if (MoveToolButton.Toggled == true && SelectedSprite != NULL){
            SelectedSprite->x = lerp(SelectedSprite->x, mx-(SelectedSprite->w/2), .1);
            SelectedSprite->y = lerp(SelectedSprite->y, my-(SelectedSprite->h/2), .1);
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                
                if (mx >= ImportToolSprite.GetVector2().x && mx <= ImportToolSprite.GetVector2().x + ImportToolSprite.GetVector2().w && my >= ImportToolSprite.GetVector2().y && my <= ImportToolSprite.GetVector2().y+ImportToolSprite.GetVector2().h){
                    SDL_ShowOpenFileDialog(FileOpenContext,NULL,window,NULL,0,NULL,false);
                } // check for importing (holy fuck this is unreadable lmaoo, ill make a click detection library for ts later.)

                if (MoveToolButton.IsMouseHovering() == true) {
                    
                    if (MoveToolButton.Toggled == false){
                        MoveToolButton.Toggled = true;
                    } else {
                        MoveToolButton.Toggled = false;
                    }
                    
                }

                if (MoveToolButton.Toggled == true){

                    if (RenderQueueCheckMouseOverlap() == SelectedSprite){
                        SelectedSprite = NULL;
                    } else {
                        SelectedSprite = RenderQueueCheckMouseOverlap();
                    }

                }

            };
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(8);
    }
    
    CleanUpRenderQueue();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
};