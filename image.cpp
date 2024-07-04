#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("SDL2 Image Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *imageSurface = IMG_Load("helloworld.png");
    if (!imageSurface)
    {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!texture)
    {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Rect imageRect;
    imageRect.w = 100;                        // Width of the image
    imageRect.h = 100;                        // Height of the image
    imageRect.x = (WIDTH - imageRect.w) / 2;  // Centering the image horizontally
    imageRect.y = (HEIGHT - imageRect.h) / 2; // Centering the image vertically

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &imageRect);
    SDL_RenderPresent(renderer);

    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
            else if (windowEvent.type == SDL_KEYDOWN)
            {
                switch (windowEvent.key.keysym.sym)
                {
                case SDLK_LEFT:
                    imageRect.x -= 10; // Move left
                    break;
                case SDLK_RIGHT:
                    imageRect.x += 10; // Move right
                    break;
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, &imageRect);
                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
