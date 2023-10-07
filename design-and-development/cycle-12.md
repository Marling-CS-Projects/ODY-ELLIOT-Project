# 2.2.12 Cycle 12

## Design

This cycle was to add features in response to player requests I received from the [Bucket Knight Response Form](https://docs.google.com/forms/d/e/1FAIpQLSewdKSRPxViHy7iZwTl3iMBZkAM8XL76dQIEQXJQ5ZiwxuIdg/viewform). Most requests were to improve the balance of the weapons in the game, but there were some highly requested features I had to implement (such as a game-over screen).

<figure><img src="../.gitbook/assets/image.png" alt=""><figcaption><p>Requests for a Game Over screen and a Pause Menu</p></figcaption></figure>

### Objectives

In this cycle, I will:

* [x] Increase attack speed
* [x] Make the melee weapon centred&#x20;
* [x] Buff the melee weapon
* [x] Nerf the magic weapon
* [x] Add a pause menu
* [x] Add a game-over screen
* [x] Create a better movement input system

### Usability Features

Pause Menu - Allowing the player to pause will let them stop playing without losing progress in their current run.

Game Over Screen - This adds a delay between the player dying and the main menu to prevent accidental button presses.

### Pseudocode

{% code title="New Input Controller" %}
```cpp
class InputController : public Component
{
public:
    bool w, a, s, d = false;  // Boolean flags to track key states (pressed or not)

    TransformComponent* transform;  // Reference to the entity's transform component

    void init() override
    {
        // Initialize the transform component reference
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        // Check if a key was pressed
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                w = true;  // Set 'w' flag to true when 'W' key is pressed (move up)
                break;
            case SDLK_s:
                s = true;  // Set 's' flag to true when 'S' key is pressed (move down)
                break;
            case SDLK_d:
                d = true;  // Set 'd' flag to true when 'D' key is pressed (move right)
                break;
            case SDLK_a:
                a = true;  // Set 'a' flag to true when 'A' key is pressed (move left)
                break;

            default:
                break;
            }
        }

        // Check if a key was released
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                w = false;  // Set 'w' flag to false when 'W' key is released
                break;
            case SDLK_s:
                s = false;  // Set 's' flag to false when 'S' key is released
                break;
            case SDLK_d:
                d = false;  // Set 'd' flag to false when 'D' key is released
                break;
            case SDLK_a:
                a = false;  // Set 'a' flag to false when 'A' key is released
                break;

            default:
                break;
            }
        }

        Vector2D dir;  // Create a 2D vector to represent movement direction

        // Determine the movement direction based on key states
        if (a && d)
        {
            dir.x = 0;  // No horizontal movement if both 'a' and 'd' are pressed
        }
        else if (a)
        {
            dir.x = -1;  // Move left (negative horizontal direction) if 'a' is pressed
        }
        else if (d)
        {
            dir.x = 1;  // Move right (positive horizontal direction) if 'd' is pressed
        }
        else
        {
            dir.x = 0;  // No horizontal movement if neither 'a' nor 'd' are pressed
        }

        if (w && s)
        {
            dir.y = 0;  // No vertical movement if both 'w' and 's' are pressed
        }
        else if (w)
        {
            dir.y = -1;  // Move up (negative vertical direction) if 'w' is pressed
        }
        else if (s)
        {
            dir.y = 1;  // Move down (positive vertical direction) if 's' is pressed
        }
        else
        {
            dir.y = 0;  // No vertical movement if neither 'w' nor 's' are pressed
        }

        transform->velocity = dir;  // Update the entity's velocity based on the calculated direction
    }
};
```
{% endcode %}

Although lengthier than my previous solution, this solution should solve issues such as input delay by processing each scenario the user could input.

## Development

### Outcome

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/XrXzbDvoiRU" %}
The video above depicts the elevnth cycle of my game ([https://youtu.be/XrXzbDvoiRU](https://youtu.be/XrXzbDvoiRU))
{% endembed %}
