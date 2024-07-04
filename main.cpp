#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hello SDL WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 244, 244, 244, 255);

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 150;
    rect.h = 150;
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    SDL_Event windowEvent;

    Uint32 lastTime = SDL_GetTicks(), currentTime;
    const Uint32 moveInterval = 2000; // 2000 milliseconds (2 seconds)
    while (true)
    {
        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + moveInterval)
        {
            // Move the rectangle to the right every 2 seconds
            rect.x += 10;
            rect.x = std::min(rect.x, WIDTH - rect.w); // Keep it within bounds
            lastTime = currentTime;

            // Clear the renderer with the background color
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Set the draw color for the rectangle
            SDL_SetRenderDrawColor(renderer, 244, 244, 244, 255);

            // Draw the rectangle in the new position
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderDrawRect(renderer, &rect);

            // Update the screen
            SDL_RenderPresent(renderer);
        }

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
                case SDLK_UP:
                    rect.y -= 10;
                    break;
                case SDLK_DOWN:
                    rect.y += 10;
                    break;
                case SDLK_RIGHT:
                    rect.x += 10;
                    break;
                case SDLK_LEFT:
                    rect.x -= 10;
                    break;
                }

                rect.x = std::min(rect.x, WIDTH - rect.w);  // Right edge
                rect.x = std::max(rect.x, 0);               // Left edge
                rect.y = std::min(rect.y, HEIGHT - rect.h); // Bottom edge
                rect.y = std::max(rect.y, 0);               // Top edge

                // Clear the renderer with the background color
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                // Set the draw color for the rectangle
                SDL_SetRenderDrawColor(renderer, 244, 244, 244, 255);

                // Draw the rectangle in the new position
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderDrawRect(renderer, &rect);

                // Update the screen
                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}