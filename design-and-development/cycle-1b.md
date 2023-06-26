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

| Variable Name | Use                                        |
| ------------- | ------------------------------------------ |
| player        | Stores the reference to the player entity. |
| manager       | Stores a reference to the manager class.   |

### Pseudocode

{% code title="Game.cpp" %}
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

## Development

### Outcome

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence
