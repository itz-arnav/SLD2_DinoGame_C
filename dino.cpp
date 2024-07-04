#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>

const int WIDTH = 600, HEIGHT = 400;
const int OBSTACLE_WIDTH = 30, OBSTACLE_HEIGHT = 30;
const int DINO_HEIGHT = 100, DINO_WIDTH = 100;
const int GROUND_Y = HEIGHT - 50;          // Y coordinate of the ground
const int DINO_Y = GROUND_Y - DINO_HEIGHT; // Y coordinate of the dino
const int SPAWN_INTERVAL = 2000;          // Milliseconds between obstacle spawns

struct Obstacle
{
    int x;
    int y = GROUND_Y - OBSTACLE_HEIGHT;
    int w = OBSTACLE_WIDTH;
    int h = OBSTACLE_HEIGHT;
};

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect dino = {100, DINO_Y, DINO_WIDTH, DINO_HEIGHT};
    std::vector<Obstacle> obstacles;

    Uint32 lastSpawnTime = SDL_GetTicks();
    Uint32 lastSpeedTime = SDL_GetTicks();

    SDL_Event windowEvent;
    while (true)
    {
        Uint32 currentTime = SDL_GetTicks();

        // Spawn a new obstacle at regular intervals
        if (currentTime > lastSpawnTime + SPAWN_INTERVAL)
        {
            obstacles.push_back({WIDTH, GROUND_Y - OBSTACLE_HEIGHT, OBSTACLE_WIDTH, OBSTACLE_HEIGHT});
            lastSpawnTime = currentTime;
        }

        if(currentTime > lastSpeedTime + 200){
            lastSpeedTime = currentTime;
            // Move existing obstacles
            for (auto &obstacle : obstacles)
            {
                obstacle.x -= 5;
            }

            // Remove obstacles that have moved off screen
            obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle &obstacle)
                                           { return obstacle.x < 0; }),
                            obstacles.end());
        }

        // Event handling
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
            // Additional event handling can go here (e.g., jump logic)
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the dino
        SDL_SetRenderDrawColor(renderer, 244, 244, 244, 255);
        SDL_RenderFillRect(renderer, &dino);
        SDL_RenderDrawRect(renderer, &dino);

        // Draw obstacles
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (const auto &obstacle : obstacles)
        {
            SDL_Rect sdlRect = {obstacle.x, obstacle.y, obstacle.w, obstacle.h};
            SDL_RenderFillRect(renderer, &sdlRect);
            SDL_RenderDrawRect(renderer, &sdlRect);
        }

        // Draw the ground
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, GROUND_Y, WIDTH, GROUND_Y);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
