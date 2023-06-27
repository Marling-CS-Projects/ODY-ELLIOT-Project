# 2.2.1b Cycle 1b

This cycle is part of cycle 1 but I have split the cycle up to better explain it.

## Design

### Objectives

In this cycle I will:

* [x] Create an Entity Management System
* [x] Create a Transform Component (to manage an entities position)
* [x] Create a Sprite Component (to render the entity to the screen)
* [x] An Input Component (for player input)

### Usability Features

### Key Variables

| Variable Name | Use                                                                                                                   |
| ------------- | --------------------------------------------------------------------------------------------------------------------- |
| player        | Stores the reference to the player entity.                                                                            |
| manager       | Stores a reference to the manager class.                                                                              |
| position      | Stores an object's position.                                                                                          |
| velocity      | <p>Stores the direction the object is moving.<br>(In hindsight, velocity should of actually been named direction)</p> |
| speed         | Stores the speed the object will travel at.                                                                           |
| texture       | Stores the sprite's SDL\_Texture so it can be rendered to the screen.                                                 |

### Pseudocode

{% code title="Game Implementation" %}
```cpp
manager = new Manager()
player = manager.AddEntity()

void Game::init()
{
    // there will be other pieces of code here
        
    player.AddComponent(TransformComponent)
    player.AddComponent(SpriteComponent)
    player.AddComponent(InputComponent)
}

void Game::update()
{
    manager.UpdateAll(); // updates all entities
}

void Game::draw()
{
    manager.DrawALL(); // renders all entities
}
```
{% endcode %}

The above code does not represent the entire solution but rather the elements related to this cycle.

{% code title="Transform Component" %}
```cpp
class Transform : Component
{
    Vector2D position 
    Vector2D velocity
    // Vector2D is a custom class
    float speed
    
    void onUpdate()
    {
        position = velocity * speed
    }
}
```
{% endcode %}

{% code title="Sprite Component" %}
```cpp
class Sprite : Component
{
    SDL_Texture texture
    Transform transform // reference to the object's transform component
    
    void init(path)
    {
        texture = LoadTexture(path) // path will be the path to the image file
    }
    
    void draw()
    {
        render(texture, transform.position)
    }
}
```
{% endcode %}

{% code title="Input Component" %}
```cpp
class Input : Component
{
    Transform transform // reference to the object's transform component
    
    void onUpdate()
    {
	if (KeyDown())
	{
		switch (Game::GetEvent()) // done in the Game class
		{
		case W:
			transform->velocity.y = -1;
			break;
		case S:
			transform->velocity.y = 1;
			break;
		case D:
			transform->velocity.x = 1;
			break;
		case A:
			transform->velocity.x = -1;
			break;
		default:
			break;
		}
	}
}
```
{% endcode %}

## Development

### Outcome

```cpp

#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"

Manager manager;
auto& player(manager.addEntity()); // creates an entity
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// Adds components to the player
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("Assets/Bucket Knight Concept.png");
	player.addComponent<KeyboardController>();
}

	else
	{
		isRunning = false;
	}

}

void Game::handleEvents()
{
	// Handles all inputs made by the player
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	manager.update(); // updates all the entities components
}

void Game::render()
{
	SDL_RenderClear(renderer);
	manager.draw(); // Draws the sprite components, in the game, to the screen
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl; // Debug Statemanet
}

```

{% hint style="info" %}
Most uneccasry code for this cycle has been deleted from the solution above.
{% endhint %}

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence
