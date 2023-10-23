# 2.2.1a Cycle 1a

{% hint style="danger" %}
Most of the code added in this cycle was created by Let's Make Games on YouTube ([https://www.youtube.com/@CarlBirch](https://www.youtube.com/@CarlBirch)). The tutorials he created helped me learn C++ and SDL2 so I could go on to later create the rest of the game.
{% endhint %}

## Design

This is the first cycle of my game 'Bucket Knight' so the primary goal is to set-up the project by incorporating the SDL2 library into the solution and creating a basic player.

### Objectives

In this cycle, I aim to:

* [x] Set up a C++ project in VS 2019
* [x] Incorporate the SDL2 library into the project ([https://www.libsdl.org/](https://www.libsdl.org/))
* [x] Create a Game Loop
* [x] Create a black, re-sizable window
* [x] Render a sprite to that window
* [x] Move the sprite around the scene using WASD

### Usability Features

Controls - Simple controls as they currently will just be movement controls.

Sprite Contrast - The sprite will have a white outline to contrast with the black background.

### Pseudocode

{% code title="Game Loop" %}
```cpp
game = new Game();  // Create a new instance of the Game class
game->initialize_game(title, size);  // Initialize the game with specified title and screen size

// Main game loop
while (game is running)
{
    game->get_inputs();  // Get user inputs
    game->update();  // Update the game
    game->render();  // Render the game's sprites to the screen
}

game->clean_memory();  // Clean up memory to free RAM before exiting
```
{% endcode %}

Creates the game loop so the game while the game is running everything is updated and rendered, the game gets the inputs, and the memory is cleaned when the game is closed.

{% code title="Movement Inputs" fullWidth="false" %}
```cpp
// Check if the 'W' key is pressed
if W is pressed:
    // If 'W' is pressed, move the character UP at a specified speed
    move(UP, speed)

// Else check if the 'S' key is pressed
else if S is pressed:
    // If 'S' is pressed, move the character DOWN at a specified speed
    move(DOWN, speed)

// Check if the 'A' key is pressed
if A is pressed:
    // If 'A' is pressed, move the character LEFT at a specified speed
    move(LEFT, speed)

// Else check if the 'D' key is pressed
else if D is pressed:
    // If 'D' is pressed, move the character RIGHT at a specified speed
    move(RIGHT, speed)
```
{% endcode %}

Gets the player's inputs (part of the InputComponent in [Cycle 1b](cycle-1b.md))

{% code title="Render Sprite" %}
```cpp
// Load the character texture from a file
texture = load_texture("character.png");

// Draw the sprite using the loaded texture at a specified position
draw_sprite(texture, position);
```
{% endcode %}

Renders a sprite to the window (part of the SpriteComponent in [Cycle 1b](cycle-1b.md))

## Development

### Outcome

{% code title="main.cpp" %}
```cpp
#include "Game.h"

Game* game = nullptr; // Pointer to the Game instance

int main(int argc, char *arg[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game(); // Create a new Game instance

    game->init("Bucket Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false); // Initialize the game

    while (game->running()) // Main game loop
    {
        frameStart = SDL_GetTicks(); // Record the starting time of the frame

        game->handleEvents(); // Handle input events
        game->update(); // Update game logic
        game->render(); // Render the game

        frameTime = SDL_GetTicks() - frameStart; // Calculate the time taken for the frame

        // Delay to maintain a constant frame rate
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean(); // Clean up and free resources when the game ends

    return 0;
}
```
{% endcode %}

`main.cpp` Is the first script to be run when the program is started. It instances a new object `game` which inherits from the `Game class` and creates a resizable window.&#x20;

As well as that, `main.cpp` sets the frame rate to 60FPS in order to make the game the same for all devices.

{% hint style="info" %}
When the game is run without the frame rate set to 60FPS, the game will run at the maximum possible frame rate resulting in faster computers calling the update function more frequently than slower computers. By setting the frame rate, all users will experience the game as intended and won't use all of their computer's resources.
{% endhint %}

{% code title="Player Input Controller" %}
```cpp
#include "Game.h"
#include "Components.h"

class KeyboardController : public Component // Inherits from the base Component class
{
public:
    TransformComponent* transform; // Pointer to the TransformComponent of the entity

    void init() override
    {
        // Initialize the pointer to the transform component
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        // Check for key presses
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w: // W key is held down
                transform->velocity.y = -1; // Move upward (negative Y velocity)
                break;
            case SDLK_s: // S key is held down
                transform->velocity.y = 1; // Move downward (positive Y velocity)
                break;
            case SDLK_d: // D key is held down
                transform->velocity.x = 1; // Move rightward (positive X velocity)
                break;
            case SDLK_a: // A key is held down
                transform->velocity.x = -1; // Move leftward (negative X velocity)
                break;
            default:
                break;
            }
        }

        // Check for key releases
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
            case SDLK_s:
                transform->velocity.y = 0; // Stop the vertical movement when the 'W' or 'S' key is released
                break;
            case SDLK_d:
            case SDLK_a:
                transform->velocity.x = 0; // Stop the horizontal movement when the 'D' or 'A' key is released
                break;
            default:
                break;
            }
        }
    }
};
```
{% endcode %}

In `InputComponent.h` the entities transform component's velocity (which should have been direction due to it creating a direction vector) is updated using the player's inputs (which are handled by the SDL library). The keyboard controller class inherits from the component class which is defined in the `ECS.h` file. Components are gone into more detail in [Cycle 1b](cycle-1b.md) (which is a sub-section of this cycle).

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201).

### Challenges

The main challenges of this cycle were the initial struggle of importing the SDL library, in order to render the game and creating components to allow the player to have a sprite and the ability to move.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>The player moved double the speed than was intended due to the entity being updated twice. This problem was displayed in the video below but has been fixed in the GitHub files for cycle 1 which you can find <a href="https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201">here</a>.</td><td>Fail</td></tr><tr><td>3</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Close the game</td><td>The memory to be cleaned</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/wLS_OUcNmBI" %}
The video above shows the first cycle of my game ([https://youtu.be/wLS\_OUcNmBI](https://youtu.be/wLS\_OUcNmBI))
{% endembed %}

{% hint style="warning" %}
In the video above, the player has double the intended speed due to the player being updated twice every frame. This has been fixed in the GitHub files for cycle 1 which you can find [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201).
{% endhint %}

In the video above a black, resizable screen is created as well as a player in the top left. This player has a rendered sprite attached to it and can move around the window using the WASD keys.

<figure><img src="../.gitbook/assets/image (5) (2).png" alt=""><figcaption><p>This is a screenshot from the video above</p></figcaption></figure>

The console logs the current position of the player as well as when the game is initialized, when the window is created, and when the game is cleaned (the game cleaned output message isn't shown in the video).
