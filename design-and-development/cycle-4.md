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

Outlines - Every non-player sprite (inside of the dungeon room) won't have a white outline so the user will know where they are.

<figure><img src="../.gitbook/assets/Sprite-0001.png" alt=""><figcaption><p>The Goblin Enemy (shown on the left) and the 'HeartON' UI Sprite (shown on the right)</p></figcaption></figure>

As shown above, the Melee Enemy sprite has no white outline as it is in the dungeon room and the Heart UI sprite has a white outline because it is outside of the room and relevant to the player.

### Pseudocode

{% code title="Normalize Function" %}
```cpp
Vector2D normalize(Vector2D source):
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

The `hit()` function takes a pointer to the Entity which hits the player and maybe later used to destroy enemy bullets.

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

{% code title="Handle Events" %}
```cpp
// Function to handle events in the game
void Game::handleEvents():
    // Poll for SDL events
    SDL_PollEvent(&event)
    
    // Check for mouse motion event
    if Game::event.type == SDL_MOUSEMOTION:
        // Get mouse coordinates
        SDL_GetMouseState(&MouseX, &MouseY)
        // Convert window mouse position to logical mouse position (the position in the game world)
        windowMousePositionToLogicalMousePosition(renderer, window, MouseX, MouseY)
        // Print mouse coordinates
        print MouseX, " :  ", MouseY

    // Check for mouse button down event
    if Game::event.type == SDL_MOUSEBUTTONDOWN:
        // Check if left mouse button is pressed
        if SDL_BUTTON_LEFT == Game::event.button.button:
            // Calculate direction vector from player to mouse
            Vector2D dir{ (float)MouseX - player->GetTransform().position.x, (float)MouseY- player->GetTransform().position.y }
            // Normalize the direction vector
            dir = dir.normalize(dir)
            // Create a new bullet instance
            bullet = new Bullet()
            // Initialize bullet properties
            bullet->CreateBullet(player->GetTransform().position.x, player->GetTransform().position.y, 12, 12, "Assets/FloorTexture2.png", "playerbullet", dir, 3, 1, 400)
            // Add bullet to a group
            bullet->gameObject->addGroup(groupBullets)
```
{% endcode %}

The event handler (found in `Game.cpp`) will get the mouse position in the game scene and then, if the left mouse button is pressed, the player will shoot a bullet in that direction.

<pre class="language-cpp" data-title="Heart Object"><code class="lang-cpp"><strong>// Define a class HeartComponent which inherits from Component
</strong>class HeartComponent extends Component:
    
    // Public section of the class
    public:
        
        // Constructor that takes a PlayerComponent and a position as parameters
        HeartComponent(PlayerComponent *player, int position):
            this->player = player
            this->pos = position

        // Override the update function
        function update():
            // Check if the player's health is less than the current position
            if player->health &#x3C; pos:
                // Set the entity's SpriteComponent texture to "Assets/HeartOFF.png"
                this->entity->getComponent&#x3C;SpriteComponent>().setTex("Assets/HeartOFF.png")
            else:
                // Set the entity's SpriteComponent texture to "Assets/HeartON.png"
                this->entity->getComponent&#x3C;SpriteComponent>().setTex("Assets/HeartON.png")

        // Default constructor (could be left empty or implemented as needed)
        HeartComponent():

    // Private section of the class
    private:
        
        // Pointer to a PlayerComponent object
        PlayerComponent * player
        
        // Position of the heart in the array
        int pos
</code></pre>

The `Heart Component` is attached to an object that displays how much health the player has when paired with more of the same object.

This works as the `pos` variable indicates when the heart should turn off based on its position in the array.

## Development

### Outcome

{% code title="Melee Enemy Class" %}
```cpp
// MeleeEnemy class inherits from the EnemyComponent class and represents a melee-type enemy behavior.

class MeleeEnemy : public EnemyComponent
{
public:
	// Constructor for MeleeEnemy.
	// Parameters:
	// - destination: The TransformComponent pointer represents the destination position.
	// - speed: The movement speed of the enemy.
	// - health: The initial health of the enemy.
	MeleeEnemy(TransformComponent* destination, float speed, int health)
	{
		dest = destination;  // Set the destination position.
		this->health = health;  // Initialize the health of the enemy.
		this->transform = nullptr;  // Initialize transform pointer to nullptr.
		this->speed = speed;  // Set the movement speed of the enemy.
	}

	// Destructor for MeleeEnemy.
	~MeleeEnemy()
	{
		this->entity->destroy();  // Destroy the entity associated with the enemy.
	}

	// Initialization function for the MeleeEnemy component.
	void init() override
	{
		// Check if the entity has a TransformComponent; if not, add one.
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();  // Get a reference to the TransformComponent.

		transform->speed = this->speed;  // Set the movement speed for the TransformComponent.
	}
	
	// Update function for the MeleeEnemy component.
	void update() override
	{
		// Check if the enemy is alive.
		if (!isAlive())
		{
			this->entity->destroy();  // If not alive, destroy the entity.
		}

		Vector2D destpos = dest->position;  // Get the destination position.
		Vector2D dir = dir.normalize(destpos - transform->position);  // Calculate the normalized direction vector.

		transform->velocity = dir;  // Set the velocity of the enemy to move in the calculated direction.
	}
};
```
{% endcode %}

The `MeleeEnemy` component contains everything the game needs to know about the melee-type enemy as well as allowing the enemy to pathfind to the player (as shown in the `update()` function)

{% code title="Game.cpp Extract" %}
```cpp
// Iterate through each enemy in the enemies container.
for (auto& e : enemies)
{
	// Check if the enemy has a ColliderComponent.
	if (e->hasComponent<ColliderComponent>())
	{
		// Get a reference to the ColliderComponent of the player bullet.
		ColliderComponent* cc = cc->getComponent<ColliderComponent>();

		// Check if the tag of the collider is "playerbullet" and if there's a collision with the enemy.
		if (cc->tag == "playerbullet" && Collision::AABB(e->getComponent<ColliderComponent>(), *cc))
		{
			// Call the hit() function on the MeleeEnemy component to handle the enemy being hit.
			e->getComponent<MeleeEnemy>().hit();

			// Destroy the entity associated with the player bullet collider.
			cc->entity->destroy();
		}

		// Check if the tag of the collider is "player" and if there's a collision with the enemy.
		if (cc->tag == "player" && Collision::AABB(e->getComponent<ColliderComponent>(), *cc))
		{
			// Call the hit() function on the PlayerComponent to handle the player being hit by the enemy.
			cc->entity->getComponent<PlayerComponent>().hit(e);
		}
	}
}
```
{% endcode %}

The above code is the detection system to see whether the enemy has been hit or has hit the player. This system works for Melee Enemies but when more types of enemies are added this system will have to change.&#x20;

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%204).

### Challenges

This cycle was quite challenging as it is the first time another moving entity was added to interact with the player. This involves more collision scripts as well as a basic AI to be implemented for the new entity's movement.

A big challenge was also getting the position of the mouse in the game world as I was unaware of the `windowMousePositionToLogicalMousePosition` function provided by the SDL library until I looked into the documentation.

Another challenge was adding the cooldown to the player so the player couldn't be repeatedly hit in a short period of time (depleting their health almost instantly).

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Left Click a Position in the Game World</td><td>A Bullet to Spawn</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Left Click a Position in the Game World</td><td>A Bullet to Spawn and Move towards the Mouse Position</td><td>The bullet was offset due</td><td>Fail</td></tr><tr><td>3</td><td>Left Click a Position in the Game World</td><td>A Bullet to Spawn and Move towards the Mouse Position</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Run the Code</td><td>The new Melee Enemy to move towards the player</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Let the Enemy collide with the Player</td><td>The player to lose 1 health point and have 2 lives left</td><td>The player died</td><td>Fail</td></tr><tr><td>6</td><td>Let the Enemy collide with the Player</td><td>The player to lose 1 health point and have 2 lives left</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Let the Enemy collide with the Player</td><td>The right-most Heart should switch off</td><td>As expected</td><td>Pass</td></tr><tr><td>8</td><td>Shoot a bullet at the enemy</td><td>The enemy to be destroyed </td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/ctZDqX19qA8" %}
The video above shows the fourth cycle of my game ([https://youtu.be/ctZDqX19qA8](https://youtu.be/ctZDqX19qA8))
{% endembed %}

The video above shows a working version of this cycle where the player can shoot bullets around the scene and the enemy moves towards the player at a constant speed.

Something not clearly expressed in the video is the fact that bullets get destroyed on contact with the wall objects (the red borders) but not the trigger objects (the blue borders). This is intentional as I plan to remove the trigger system in upcoming cycles but the wall system will remain the same (hence why I implemented bullet destruction on impact).
