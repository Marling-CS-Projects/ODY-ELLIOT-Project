# 2.2.1 Cycle 1

## Design

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

| Variable Name | Use                                                                                  |
| ------------- | ------------------------------------------------------------------------------------ |
| speed         | determines how fast the character moves in the scene                                 |
| texture       | stores the SDL\_Texture used to render a sprite to the screen                        |
| is running    | tells the game loop whether to run the game when true                                |
| player        | stores everything about the player and its components (such as the sprite component) |
| game          | an object (an instance of the game class) used to initialize and run the game        |

### Pseudocode

<pre class="language-cpp" data-title="Game Loop"><code class="lang-cpp">game = new Game
game->initialize_game(title, size)

while game is running
{
    game->get_inputs()
    game->update()
    game->render()
}

<strong>game->clean_memory() // Memory is cleaned to free up the user's RAM
</strong>
</code></pre>

<pre class="language-cpp" data-title="Movement Inputs" data-full-width="false"><code class="lang-cpp"><strong>if W is pressed { move(UP, speed) }
</strong>
else if S is pressed { move(DOWN, speed) }

if A is pressed { move(LEFT, speed) }

else if D is pressed { move(RIGHT, speed) }
</code></pre>

{% code title="Render Sprite" %}
```cpp
texture = load_texture("character.png")
draw_sprite(texture, position)
```
{% endcode %}

{% code title="Player" %}
```cpp
initialize()
{
    player = create_entity()
    player->add_sprite(texture)
}

update() // The update method is called every frame. The game's frame rate is 60FPS
{
    player->handle_inputs()
    player->draw()
}
```
{% endcode %}

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

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201).

### Challenges

The main challenges of this cycle was the initial struggle of importing the SDL2 library, in order to render the game, as well as creating components to allow the player to have a sprite and the ability to move.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Close the game</td><td>The memory to be cleaned</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% file src="../.gitbook/assets/2023-06-01_18-07-04.mp4" %}
This video was made using OBS Studio ([https://obsproject.com/](https://obsproject.com/)) and has no sound
{% endfile %}

In the video above a black, resizable screen is created as well as a player in the top left. This player has a rendered sprite attatched to it and can move around the window using the WASD keys.

<figure><img src="../.gitbook/assets/image (5).png" alt=""><figcaption><p>This is a screenshot from the video above</p></figcaption></figure>

The console logs the current position of the player as well as when the game is initialized, when the window is created, and when the game is cleaned (the game cleaned output message isn't shown in the video).
