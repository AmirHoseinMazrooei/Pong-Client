// filepath: /c:/Users/mirhi/Documents/GitHub/SDL/SDL2_Template/SDL2_Template/utils.cpp
#include "utils.h"
#include <iostream>

TTF_Font* LoadFont(const std::string& relativePath, int fontSize)
{
    // Get the base path of the executable
    char* basePath = SDL_GetBasePath();
    if (basePath == nullptr)
    {
        std::cerr << "Failed to get base path: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Construct the full path to the font
    std::string fullPath = std::string(basePath) + relativePath;
    SDL_free(basePath); // Free the memory allocated by SDL_GetBasePath

    // Load the font
    TTF_Font* font = TTF_OpenFont(fullPath.c_str(), fontSize);
    if (font == nullptr)
    {
        std::cerr << "Failed to load font '" << fullPath << "': " << TTF_GetError() << std::endl;
    }

    return font;
}



// Function to render text directly onto the renderer
void RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr)
    {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Function to create a texture from text (useful for pre-rendered texts)
SDL_Texture* CreateTextureFromText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface)
    {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}