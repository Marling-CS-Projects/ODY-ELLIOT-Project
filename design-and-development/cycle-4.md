# 2.2.4 Cycle 4

## Design

This cycle will focus on the basic Melee Enemy type in my game, while also allowing the Player to shoot bullets and take damage.

In this cycle, I aim to:

* [x] Create a health system for the Player with UI
* [x] Add a basic ranged weapon for the Player to use
* [x] Create an Enemy
* [x] Make the Enemy move toward the Player
* [x] Make the Enemy be Destroyed when Shot
* [x] Have the enemy reduce the Player's health on Impact

### Usability Features

Outlines - Every non-player sprite won't have a white outline so the user will know where they are.

### Key Variables

| Variable Name | Use                   |
| ------------- | --------------------- |
| foo           | does something useful |

### Pseudocode

{% code title="Normalize Function" %}
```cpp
VVector2D normalize(Vector2D source):
    length = SquareRoot((source.x * source.x) + (source.y * source.y))
    direction = Vector2D(source.x / length, source.y / length)

    return direction
```
{% endcode %}

The `normalize` function returns a new vector with a length of 1 while preserving the vector's direction, using Pythagoras (`a² + b² = c²`).

{% code title="Player Component" %}
```cpp
Include "Components.h"

class PlayerComponent extends Component:
    // Constructor
    PlayerComponent(health, cooldownTime):
        health = health
        cooldown = cooldownTime

    // Override update function
    function update():
        if health < 1:
            player.destroy()
        else if CooldownFinished():
            canBeHit = true

    // Function to handle the player being hit by an enemy
    function hit(enemy):
        if canBeHit:
            health = health - 1
            canBeHit = false
            StartCooldown()

    boolean canBeHit
    boolean onCooldown
    int health
```
{% endcode %}

The `Player Component` is attached to the Player and tracks the player's health and if the player can be hit.

The `hit()` function takes a pointer to the Entity which hits the player and may be later used to destroy enemy bullets.

{% code title="Enemy Component" %}
```cpp
Include "Components.h"

class EnemyComponent extends Component:
    // Constructor
    EnemyComponent():
        destination = null
        transform = null
        health = 0
        speed = 0.0

    // Destructor
    ~EnemyComponent():
        entity.destroy()

    // Function to check if the enemy is alive
    function isAlive():
        if health > 0:
            return true
        else:
            return false

    // Function to simulate the enemy being hit
    function hit():
        health = health - 1

    TransformComponent destination
    TransformComponent transform
    int health
    float speed
```
{% endcode %}

The `Enemy Component` will be the base for every enemy as it contains basic functions that every enemy will use (such as `hit()`).

## Development

### Outcome

```cpp
class MeleeEnemy : public EnemyComponent
{
public:
	MeleeEnemy(TransformComponent* destination, float speed, int health)
	{
		dest = destination;
		this->health = health;
		this->transform = nullptr;
		this->speed = speed;
	}

	~MeleeEnemy()
	{
		this->entity->destroy();
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		transform->speed = this->speed;
	}
	
	void update() override
	{
		if (!isAlive())
		{
			this->entity->destroy();
		}

		Vector2D destpos = dest->position;
		Vector2D dir = dir.normalize(destpos - transform->position);
		
		transform->velocity = dir;
	}
};
```

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/ctZDqX19qA8" %}
The video above shows the third cycle of my game ([https://youtu.be/ctZDqX19qA8](https://youtu.be/ctZDqX19qA8))
{% endembed %}
