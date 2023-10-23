# 2.2.1b Cycle 1b

{% hint style="danger" %}
Most of the code added in this cycle was created by Let's Make Games on YouTube ([https://www.youtube.com/@CarlBirch](https://www.youtube.com/@CarlBirch)). The tutorials he created helped me learn C++ and SDL2 so I could go on to later create the rest of the game.
{% endhint %}

## Design

In this cycle, I added an Entity Component System (ECS) to my project which will streamline development by handling everything about the entities in the game (such as position). The ECS is the backbone of the game's game engine.

This cycle is a sub-section of[ Cycle 1a](cycle-1a.md).

### Objectives

In this cycle, I will:

* [x] Create an Entity Management System
* [x] Create a Transform Component (to manage an entity's position)
* [x] Create a Sprite Component (to render the entity to the screen)
* [x] An Input Component (for player input)

### Pseudocode

{% code title="Game Implementation" %}
```cpp
// Create a new entity manager
manager = new Manager()

// Create a player entity and add it to the manager
player = manager.AddEntity()

// Game initialization function
function Game.init():
    // Other initialization code here
    
    // Add the necessary components to the player entity
    player.AddComponent(TransformComponent)
    player.AddComponent(SpriteComponent)
    player.AddComponent(InputComponent)

// Game update
function Game.update():
    // Update all entities using the manager
    manager.UpdateAll()

// Game draw
function Game.draw():
    // Render all entities using the manager
    manager.DrawAll()
```
{% endcode %}

The above code does not represent the entire solution but rather the elements related to this cycle.

{% code title="Transform Component" %}
```cpp
class Transform : Component
{
    Vector2D position;
    Vector2D velocity;
    float speed;

    // onUpdate method to update the position based on velocity and speed
    void onUpdate()
    {
        position = position + (velocity * speed);
    }
}
```
{% endcode %}

{% code title="Sprite Component" %}
```cpp
class Sprite : Component
{
    SDL_Texture texture;
    Transform transform;  // Reference to the entity's transform component

    // Initialize the sprite with a texture loaded from a file path
    void init(path)
    {
        texture = LoadTexture(path);  // Load the texture from the provided image file path
    }

    // Render the sprite using the loaded texture at the object's position
    void draw()
    {
        render(texture, transform.position);  // Render the texture at the object's position
    }
}
```
{% endcode %}

{% code title="Input Component" %}
```cpp
class InputController : Component
{
    Transform transform;  // Reference to the object's transform component

    // Constructor to initialize the InputController with the associated Transform component
    InputController(Transform transformReference)
    {
        transform = transformReference;
    }

    // onUpdate method to handle key input and update the Transform component's velocity
    void onUpdate()
    {
        if (KeyDown())
        {
            // Get the key event from the Game class (assume Game::GetEvent() returns the pressed key)
            switch (Game::GetEvent())
            {
            case W:
                transform.velocity.y = -1;  // Move up (negative y velocity)
                break;
            case S:
                transform.velocity.y = 1;  // Move down (positive y velocity)
                break;
            case D:
                transform.velocity.x = 1;  // Move right (positive x velocity)
                break;
            case A:
                transform.velocity.x = -1;  // Move left (negative x velocity)
                break;
            default:
                break;
            }
        }
    }
}
```
{% endcode %}

All these components will inherit a base component class called `Component`.

## Development

### Outcome

{% code title="Game.cpp" %}
```cpp
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"

Manager manager; // Create a manager to handle entities and components
auto& player(manager.addEntity()); // Create the player entity
SDL_Event Game::event; // Declare the SDL event object
SDL_Renderer* Game::renderer = nullptr; // Declare a pointer to the SDL renderer

Game::Game() // Constructor for the Game class
{}

Game::~Game() // Destructor for the Game class
{}

// Initializes the game window and the objects in the game
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    else
    {
        flags = SDL_WINDOW_RESIZABLE;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // Initialize SDL subsystems
    {
        std::cout << "Subsystems Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); // Create the game window

        if (window)
        {
            std::cout << "Window Created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0); // Create the SDL renderer

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set the renderer draw color
            std::cout << "Renderer Created" << std::endl;
        }

        isRunning = true;
        
        /*
        Entity and component initialization
        */
        
        player.addComponent<TransformComponent>(); // Add a transform component to the player entity
        player.addComponent<SpriteComponent>("Assets/Bucket Knight Concept.png"); // Add a sprite component to the player entity
        player.addComponent<KeyboardController>(); // Add a keyboard controller component to the player entity
    }
    else
    {
        isRunning = false; // If SDL initialization fails, set isRunning to false
    }
}

void Game::handleEvents() // Handle SDL events
{
    SDL_PollEvent(&event); // Poll for events from the event queue

    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false; // Quit the game if the window is closed
            break;

        default:
            break;
    }
}

void Game::update() // Update game logic
{
    manager.update(); // Update every entity and their components
}

void Game::render() // Render the game
{
    SDL_RenderClear(renderer); // Clear the renderer
    manager.draw(); // Render every entity's sprite components
    SDL_RenderPresent(renderer); // Present the rendered frame to the screen
}

void Game::clean() // Clean up and exit the game
{
    SDL_DestroyWindow(window); // Destroy the game window
    SDL_DestroyRenderer(renderer); // Destroy the SDL renderer
    SDL_Quit(); // Quit SDL subsystems
    std::cout << "Game Cleaned" << std::endl;
}
```
{% endcode %}

`Game.cpp` handles the implementation of the entities in the game as it creates, adds components, and deletes the entities from the scene.

{% code title="Transform Component" %}
```cpp
#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component // Inherits from the Component class
{
public:
    Vector2D position; // The position of the entity
    Vector2D velocity; // The velocity of the entity

    float speed = 3; // The speed at which the entity can move

    TransformComponent() // Default constructor
    {
        position.x = 0.0f; // Initialize the position's X coordinate to 0.0
        position.y = 0.0f; // Initialize the position's Y coordinate to 0.0
    }

    TransformComponent(float x, float y) // Constructor with initial position
    {
        position.x = x; // Set the position's X coordinate to the provided value
        position.y = y; // Set the position's Y coordinate to the provided value
    }

    void init() override
    {
        velocity.x = velocity.y = 0; // Initialize velocity to 0 in both directions
    }

    void update() override
    {
        // Update the position based on the velocity and speed
        position.x += velocity.x * speed; // Update the X coordinate of the position
        position.y += velocity.y * speed; // Update the Y coordinate of the position
    }
};
```
{% endcode %}

The transform component is the most important component in the game as it handles every entity's position in the scene. It also is required for other components to work (such as the sprite component as it needs a position to get rendered).

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201).

### Challenges

The main challenge when creating an entity component system is making it simple to create entities and add the necessary components to them. It was also difficult to create a function that updates every entity and its components automatically so I could create entities at my leisure without worrying about calling the update function.

### Evidence

Evidence for testing and cycle completion can be found in [Cycle 1a](cycle-1a.md).
