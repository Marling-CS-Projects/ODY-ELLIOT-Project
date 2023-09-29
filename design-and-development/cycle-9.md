# 2.2.9 Cycle 9

## Design

In this cycle, I will add more enemies to the game as well as add a progression system so each level gets harder and harder.

<figure><img src="../.gitbook/assets/Sprite-0001.png" alt=""><figcaption><p>The game's enemy sprites</p></figcaption></figure>

The 'Goblin' enemy was the first enemy added to the game is shown on the left. It will have 3 health points (HP) and will move towards the player in order to deal damage. The 'Wizard' (shown on the right) has 1 HP and will stay still and damage the player via magic projectiles. The 'Furball' (shown in the middle) is a combination of the 'Goblin' and the 'Wizard' and has 2 HP. He moves towards the player slowly and fires projectiles.

### Objectives

In this cycle, I will:

* [x] Create the 'Wizard' enemy
* [x] Create the 'Furball' enemy
* [x] Create a suitable progression system

### Usability Features

Number of Enemies - the number of enemies are capped so the player doesn't feel like levels past a certain point are unplayable.

### Pseudocode

{% code title="Number of Enemies" %}
```cpp
// Loop through a range of values from 0 to (numRooms - 2)
for i from 0 to (numRooms - 2):
    // case if i < 1
    if (i < 1):
        enemyNumber = 1
    elif (i % 2 == 0):
        enemyNumber = i / 2
    else:
        enemyNumber = (i + 1) / 2

    // Ensure that number of enemies does not exceed 10
    if (enemyNumber > 10):
        enemyNumber = 10
```
{% endcode %}

This code snippet determines the number of enemies each level should have based on their number in the sequence (denoted by `i`).&#x20;

Using the function `f(i) = i / 2` when `i` is even and `f(i) = (i + 1) / 2` when `x` is odd, we can get the sequence of 1, 1, 2, 2, 3, 3, ...

This goes on as `i` increases so I have capped the number of enemies to 10 so the levels don't become impossible.

The first level will always have 1 enemy and the last level will always have 11 enemies as they are initialized separately to the rest of the levels.

## Development

### Outcome

{% code title="Magic Enemy Component" %}
```cpp
// Define a class called MagicEnemy that inherits from EnemyComponent
class MagicEnemy : public EnemyComponent
{
public:
    // Constructor for MagicEnemy
    MagicEnemy(TransformComponent* destination, int health, Game* game, int cooldown)
    {
        this->dest = destination; // Store the destination transform component
        this->health = health; // Set the initial health
        this->transform = nullptr; // Initialize transform as nullptr
        this->game = game; // Store a pointer to the game object
        this->cooldown = cooldown; // Store the cooldown for shooting

        // Calculate the frame to wait for before shooting again
        this->frameToWaitFor = game->GetFrames() + this->cooldown;
    }

    // Destructor for MagicEnemy
    ~MagicEnemy()
    {
        // Destroy the entity associated with this MagicEnemy
        this->entity->destroy();
    }

    // Initialization function, overridden from the base EnemyComponent class
    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        // Set the speed of the transform to 0
        transform->speed = 0;
    }

    // Update function, overridden from the base EnemyComponent class
    void update() override
    {
        // Check if the enemy is alive; if not, destroy the entity
        if (!isAlive())
        {
            this->entity->destroy();
        }

        // Calculate the destination position
        Vector2D destpos{ dest->position.x - 12, dest->position.y - 12 };

        // Calculate the direction towards the destination
        Vector2D dir = dir.normalize(destpos - transform->position);

        // Check if it's time to shoot based on the frame counter
        if (frameToWaitFor <= game->GetFrames())
        {
            // Create an enemy bullet with the specified parameters
            game->CreateEnemyBullet(transform->position.x + 12, transform->position.y + 12, 12, 12, "Assets/EnemyMagic.png", "enemybullet", dir, 2, 1, 800, "Magic");

            // Update the frame to wait for the next shot
            frameToWaitFor = game->GetFrames() + cooldown;
        }
    }

    int cooldown; // Cooldown time between shots
    int frameToWaitFor; // Frame to wait for before shooting again
    Game* game; // Pointer to the game object
};
```
{% endcode %}

The `MagicEnemy` is the component for the Wizard and will cause the enemy to shoot bullets at the player.

{% code title="Gun Enemy Component" %}
```cpp
// Define a class called GunEnemy that inherits from EnemyComponent
class GunEnemy : public EnemyComponent
{
public:
    // Constructor for GunEnemy
    GunEnemy(TransformComponent* destination, float speed, int health, Game* game, int cooldown)
    {
        this->dest = destination; // Store the destination transform component
        this->health = health; // Set the initial health
        this->transform = nullptr; // Initialize transform as nullptr
        this->game = game; // Store a pointer to the game object
        this->cooldown = cooldown; // Store the cooldown for shooting
        this->speed = speed; // Store the movement speed

        // Calculate the frame to wait for before shooting again
        this->frameToWaitFor = game->GetFrames() + this->cooldown;
    }

    // Destructor for GunEnemy
    ~GunEnemy()
    {
        // Destroy the entity associated with this GunEnemy
        this->entity->destroy();
    }

    // Initialization function, overridden from the base EnemyComponent class
    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        // Set the speed of the transform to the specified speed
        transform->speed = this->speed;
    }

    // Update function, overridden from the base EnemyComponent class
    void update() override
    {
        // Check if the enemy is alive; if not, destroy the entity
        if (!isAlive())
        {
            this->entity->destroy();
        }

        // Calculate the destination position
        Vector2D destpos{ dest->position.x - 12, dest->position.y - 12 };

        // Calculate the direction towards the destination
        Vector2D dir = dir.normalize(destpos - transform->position);

        // Check if it's time to shoot based on the frame counter
        if (frameToWaitFor <= game->GetFrames())
        {
            // Create an enemy bullet with the specified parameters
            game->CreateEnemyBullet(transform->position.x + 12, transform->position.y + 12, 12, 12, "Assets/Hairball.png", "enemybullet", dir, 2, 1, 200, "hair");
            
            // Update the frame to wait for the next shot
            frameToWaitFor = game->GetFrames() + cooldown;
        }

        // Set the velocity of the transform to the calculated direction
        transform->velocity = dir;
    }

    int cooldown; // Cooldown time between shots
    int frameToWaitFor; // Frame to wait for before shooting again
    float speed; // Movement speed of the enemy
    Game* game; // Pointer to the game object
};
```
{% endcode %}

The `GunEnemy` is the component for the Wizard and will cause the enemy to shoot bullets at the player as well as move towards the player.

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%209).

### Challenges

There were a lot of bugs when spawning enemy bullets such as them spawning in the corner for a single frame before being teleported to the correct position.

Another feature I added was to make each enemy unique by randomizing their stats slightly. For example, the Wizard enemy could have a cooldown of 200 plus or minus 10.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Go through the levels</td><td>Enemies to spawn in the sequence 1,1,2,2,3,3,... (excluding the first level)</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Go through the levels</td><td>Different enemy types spawn</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Get shot by Wizard enemy</td><td>The player to take damage</td><td>The player dies instantly</td><td>Fail (as the player should still be alive after being hit)</td></tr><tr><td>4</td><td>Get shot by Wizard enemy</td><td>The player to take damage</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Spawn a Furball enemy</td><td>The enemy should move towards the player and shoot</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Get shot by a Furball enemy</td><td>The player to take damage</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>See if all the enemy types contain variation</td><td>The enemies to have slightly different stats to their counterparts</td><td>As expected</td><td>Pass</td></tr><tr><td>8</td><td>Shoot the Wizard enemy once with the Gun weapon</td><td>The enemy to die as the Gun weapon deals 1HP and the Wizard has 1HP</td><td>As expected</td><td>Pass</td></tr><tr><td>9</td><td>Shoot the Furball enemy twice with the Gun weapon</td><td>The enemy to die after the second shot as the Gun weapon deals 1HP and the Furball has 2HP</td><td>As expected</td><td>Pass</td></tr><tr><td>10</td><td>Kill the enemies using the other weapons</td><td>The enemies to be destroyed correctly (based on the weapon's damage and health)</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://www.youtube.com/watch?t=2s&v=Z4aXRpog_YY" %}
The video above shows the ninth cycle of my game ([https://www.youtube.com/watch?v=Z4aXRpog\_YY](https://www.youtube.com/watch?v=Z4aXRpog\_YY))
{% endembed %}

The video above shows enemies spawning in the sequence 1,1,2,2,3,3,... (excluding the first level) as well as the different enemies and their behaviours.
