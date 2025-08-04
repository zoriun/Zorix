#include <iostream>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_dialog.h>
#include "EngineLibraries/Engine.hpp"
#include "EngineLibraries/Miscellaneous.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("Zorix Engine ⚡️", 1280, 720, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture* NewProjectButton = IMG_LoadTexture(renderer, "Textures/ProjectButton.png");
    SDL_FRect NewProjectButtonRect = {450, 250, 400, 200};

    bool running = true;
    bool AnimateButton = false;
    float Frame = 0;
    bool OpenNewProjectWindow = false;

    while (running == true)
    {
        SDL_Event event;

        int wx, wy;
        SDL_GetWindowSizeInPixels(window, &wx, &wy);

        NewProjectButtonRect.x = (wx-NewProjectButtonRect.w)/2;
        NewProjectButtonRect.y = (wy-NewProjectButtonRect.h)-50;

        float mx, my;
        SDL_GetMouseState(&mx, &my);

        SDL_SetRenderDrawColor(renderer, 80,80,80,255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, NewProjectButton, NULL, &NewProjectButtonRect);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                if (mx >= NewProjectButtonRect.x && mx <= NewProjectButtonRect.x + NewProjectButtonRect.w && my >= NewProjectButtonRect.y && my <= NewProjectButtonRect.y + NewProjectButtonRect.h && AnimateButton == false){
                    AnimateButton = true;
                    Frame = 0;
                };
            }
        }

        //TODO: Create an Animation module that does this crap in a clean manner lmao
        if (AnimateButton == true) {
            if (Frame >= 0.90f){
                AnimateButton = false;
                Frame = 0;
                OpenNewProjectWindow = true;
            }
            Frame+=.01;
            NewProjectButtonRect.w = lerp(NewProjectButtonRect.w, NewProjectButtonRect.w/2, easein(Frame));
            NewProjectButtonRect.h = lerp(NewProjectButtonRect.h, NewProjectButtonRect.h/2, easein(Frame));
            NewProjectButtonRect.x = lerp(NewProjectButtonRect.x, NewProjectButtonRect.x-NewProjectButtonRect.w, easein(Frame));
            NewProjectButtonRect.y = lerp(NewProjectButtonRect.y, NewProjectButtonRect.y-NewProjectButtonRect.h, easein(Frame));
        };

        if (OpenNewProjectWindow == true) {
            running = false;
        };

        SDL_RenderPresent(renderer);
        SDL_Delay(8);
    }
    
    SDL_DestroyTexture(NewProjectButton);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    if (OpenNewProjectWindow == true){
        OpenNewProjectWindow = false;
        CreateNewProjectWindow();
    };
    return 0;
};