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

### Key Variables

| Variable Name | Use                   |
| ------------- | --------------------- |
| foo           | does something useful |

### Pseudocode

{% code title="Normalize Function" %}
```cpp
Vector2D normalize(Vector2D source)
{
    float length = SquareRoot((source.x * source.x) + (source.y * source.y));
    Vector2D direction = source.x / length, source.y / length;

    return direction;
}
```
{% endcode %}

The `normalize` function returns a new vector with a length of 1 while preserving the vector's direction, using Pythagoras (`a² + b² = c²`).

<pre class="language-cpp" data-title="Player Component"><code class="lang-cpp"><strong>#pragma once
</strong>#include "Components.h"

class PlayerComponent : public Component
{

public:

PlayerComponent(int health, int cooldownTime) // Constructor
	{
		this->health = health;
		this->cooldown = cooldownTime;
	}

	void update() override
	{
		if (health &#x3C; 1)
		{
			player.destroy()
		}
		else if (CooldownFinished())
		{
			canBeHit = true; // makes the cooldown work
		}
	}

	void hit(Entity* enemy) 
	{
		if (canBeHit)
		{
			health -= 1;
			canBeHit = false;
			StartCooldown();
		}
	}

	bool canBeHit;
	bool onCooldown;
	int health;
};
</code></pre>

The `Player Component` is attached to the Player and tracks the player's health and if the player can be hit.

The `hit()` function takes a pointer to the Entity which hits the player and may be later used to destroy enemy bullets.

{% code title="Enemy Component" %}
```cpp
#pragma once
#include "Components.h"

class EnemyComponent : public Component
{
public:
	EnemyComponent()
	{
		this->destination = nullptr;
		this->transform = nullptr;
		this->health = 0;
	}
	~EnemyComponent()
	{
		this->entity->destroy();
	}

	bool isAlive()
	{
		if (health > 0)
		{
			return true;
		}

		return false;
	}

	virtual void hit()
	{
		health -= 1;
	}

	TransformComponent* destination;
	TransformComponent* transform;
	int health;
	float speed;
};

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
{% endcode %}



## Development

### Outcome

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
