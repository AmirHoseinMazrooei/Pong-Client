// filepath: /c:/Users/mirhi/Documents/GitHub/SDL/SDL2_Template/SDL2_Template/utils.h
#pragma once
#include <SDL.h>

#include <SDL_ttf.h>

#include <string>

// Function Declarations
TTF_Font* LoadFont(const std::string& relativePath, int fontSize);


// Function to render text directly onto the renderer
void RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);

