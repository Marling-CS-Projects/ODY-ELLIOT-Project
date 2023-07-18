# 2.2.1a Cycle 1a

## Design

This is the first cycle of my game 'Bucket Knight' so the primary goal is to set-up the project by incorporating the SDL2 library into the solution and creating a basic player.

### Objectives

In this cycle I aim to:

* [x] Set up a C++ project in VS 2019
* [x] Incorporate the SDL2 library into the project ([https://www.libsdl.org/](https://www.libsdl.org/))
* [x] Create a Game Loop
* [x] Create a black, re-sizable window
* [x] Render a sprite to that window
* [x] Move the sprite around the scene using WASD

### Usability Features

* Controls - Simple controls as it currently will just be movement controls.
* Sprite Contrast - The sprite will have a white outline to contrast with the black background.

### Key Variables

| Variable Name | Use                                                                           |
| ------------- | ----------------------------------------------------------------------------- |
| speed         | determines how fast the character moves in the scene                          |
| texture       | stores the SDL\_Texture used to render a sprite to the screen                 |
| is\_running   | tells the game loop whether to run the game when true                         |
| game          | an object (an instance of the game class) used to initialize and run the game |

### Pseudocode

<pre class="language-cpp" data-title="Game Loop"><code class="lang-cpp">game = new Game
game->initialize_game(title, size)

while game is_running
{
    game->get_inputs()
    game->update()
    game->render()
}

<strong>game->clean_memory() // Memory is cleaned to free up the user's RAM
</strong></code></pre>

Creates the game loop so the game while the game is running everything is updated and rendered, the game gets the inputs, and the memory is cleaned when the game is closed.

<pre class="language-cpp" data-title="Movement Inputs" data-full-width="false"><code class="lang-cpp"><strong>if W is pressed { move(UP, speed) }
</strong>
else if S is pressed { move(DOWN, speed) }

if A is pressed { move(LEFT, speed) }

else if D is pressed { move(RIGHT, speed) }
</code></pre>

Gets the players inputs (part of the InputComponent in [Cycle 1b](cycle-1b.md))

{% code title="Render Sprite" %}
```cpp
texture = load_texture("character.png")
draw_sprite(texture, position)
```
{% endcode %}

Renders a sprite to the window (part of the SpriteComponent in [Cycle 1b](cycle-1b.md))

## Development

### Outcome

{% code title="main.cpp" %}
```cpp
#include "Game.h"

Game* game = nullptr;

int main(int argc, char *arg[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Bucket Knight", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}

```
{% endcode %}

`main.cpp` Is the first script to be run when the program is started. It instances a new object `game` which inherits from the `Game class` and creates a resizable window.&#x20;

As well as that, `main.cpp` sets the frame rate to 60FPS in order to make the game the same for all devices.

{% hint style="info" %}
When the game is run without the frame rate set to 60FPS, the game will run at the maximum possible frame rate resulting in faster computers calling the update function more frequently than slower computers. By setting the frame rate, all users will experience the game as intended.
{% endhint %}

{% code title="InputController.h" %}
```cpp
#pragma once

#include "Game.h"
#include "Components.h"

class KeyboardController : public Component // inherits from the base component class
{
public:
	TransformComponent* transform; // a pointer to the transform component

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;

			default:
				break;
			}
		}
	}
};
```
{% endcode %}

In `InputComponent.h` the entities transform component's velocity (which should have been direction due to it creating a direction vector) is updated using the player's inputs (which is handled by the SDL library). The keyboard controller class inherits from the component class which is defined in the `ECS.h` file. Components are gone into more detail in [Cycle 1b](cycle-1b.md) (which is a sub-section of this cycle).

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201).

### Challenges

The main challenges of this cycle was the initial struggle of importing the SDL library, in order to render the game, as well as creating components to allow the player to have a sprite and the ability to move.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>The player moved double the speed than was intended due to the entity being updated twice. This problem was displayed in the video below but has been fixed in the GitHub files for cycle 1 which you can find <a href="https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201">here</a>.</td><td>Fail</td></tr><tr><td>3</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Close the game</td><td>The memory to be cleaned</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/wLS_OUcNmBI" %}
The video above shows the first cycle of my game ([https://youtu.be/wLS\_OUcNmBI](https://youtu.be/wLS\_OUcNmBI))
{% endembed %}

{% hint style="warning" %}
In the video above, the player has double the intended speed due to the player being updated twice every frame. This has been fixed in the GitHub files for cycle 1 which you can find [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201).
{% endhint %}

In the video above a black, resizable screen is created as well as a player in the top left. This player has a rendered sprite attatched to it and can move around the window using the WASD keys.

<figure><img src="../.gitbook/assets/image (5).png" alt=""><figcaption><p>This is a screenshot from the video above</p></figcaption></figure>

The console logs the current position of the player as well as when the game is initialized, when the window is created, and when the game is cleaned (the game cleaned output message isn't shown in the video).
