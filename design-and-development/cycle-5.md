# 2.2.5 Cycle 5

## Design

In this cycle, I will give the game a more arcade-like feel as I felt it was diverging from the original plan of the game. I will have a score at the top indicating how many rooms the player has cleared as well as the next room spawning automatically, with enemies, when the room has been cleared.

As well as that, I will improve the object creation system as I have identified a simple way to improve it.

### Objectives

In this cycle, I will:

* [x] Overhaul the dungeon progression system
* [x] Spawn enemies randomly when a room is built
* [x] Improve the object creation system

### Usability Features

Enemies Spawning Rules - The enemies will spawn away from the player so the player doesn't get damaged instantaneously.

### Pseudocode

{% code title="If there are no Enemies" %}
```cpp
/* 
Check if there are no remaining enemies in a Level
Part of the update function
*/
if enemies.size() <= 0:
    // Move to the next room in the dungeon generator
    dGen->currentRoom += 1
    // Destroy all bullets
    for each bullet in bullets:
        bullet->destroy()
    // Iterate through enemies
    for each enemy in enemies:
        // Check if enemy is not active (has been killed by the player)
        if !enemy->isActive():
            // Remove the enemy from the enemies group
            enemy->delGroup(groupEnemies)
            // Destroy the enemy
            enemy->destroy()
    // Draw the new room layout
    dGen->DrawCurrentRoom()
    // Reset the player's position
    player->entity->getComponent<TransformComponent>().position = Vector2D(playerX, playerY)
```
{% endcode %}

This code snippet from the `update` function checks to see if there are any enemies left in the room. If there are not, the code deletes all entities in the current room (except the player) and then renders the next room (with new enemies) and the player is teleported to the default position in the level.

This new dungeon system is better than the previous system as you cannot progress unless all enemies are defeated.

## Development

### Outcome

{% code title="Old System" %}
```cpp
auto player = new Player();
player->CreatePlayer(400, 300, 3);
player->gameObject->addGroup(groupForeground);
```
{% endcode %}

{% code title="New System" %}
```cpp
auto player = new Player(400, 300, 3);
player->entity->addGroup(groupForeground);
```
{% endcode %}

The new system results in less code having to be written to create an object by making the class constructor take in arguments and run the object creation function. The old system may still be used in certain circumstances.

As well as that, the `gameObject` variable's name has been changed to `entity` because it represents the value stored inside (which is an Entity pointer).

{% code title="Spawn Enemies Function" %}
```cpp
void Level::SpawnEnemies() // a function in the level class
{
    // Get the player's transformation information
    auto p = player->GetTransform();

    // Loop to spawn the specified number of enemies
    for (int i = 0; i < this->numberOfEnemies; i++)
    {
        // Generate random coordinates within certain ranges for enemy spawn
        int x = (rand() % (568 - 385)) + 385;
        int y = (rand() % (478 - 140)) + 140;

        // Print out the generated coordinates relative to the game world
        std::cout << "X: " + to_string(x) + ", Y: " + to_string(y) << std::endl;

        // Create a new melee enemy instance with the generated coordinates
        auto mE = new EMelee(x, y, 24, 24, "Assets/Goblin.png", "enemy", &p);

        // Add the enemy instance to the 'groupEnemies' entity group
        mE->entity->addGroup(groupEnemies);
    }
}
```
{% endcode %}

The `SpawnEnemies` function runs when a room is built to randomly spawn enemies between the x coordinates of 385 and 568 and the y coordinates of 140 and 478. This will ensure enemies spawn away from the player (who gets teleported to 300, 200) and make each room feel unique.

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%205).

### Challenges

A big challenge was spawning the enemies in the correct positions as it was mainly trial and error until I got values I was happy with. As well as that, there were constant errors as the enemies didn't get references to the player object so the pathfinding didn't function properly.

There were also errors caused by the trigger objects. However, this didn't need to be fixed as I was going to remove them in this cycle anyway.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>One Enemy to spawn inside the level and Pathfind to the Player</td><td>The Enemy spawned outside the level</td><td>Fail</td></tr><tr><td>2</td><td>Run code</td><td>One Enemy to spawn inside the level and Pathfind to the Player</td><td>The Enemy moved towards the game origin rather than the player</td><td>Fail</td></tr><tr><td>3</td><td>Run code</td><td>One Enemy to spawn inside the level</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Run code</td><td>Multiple enemies to spawn inside the level</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Destroy all enemies in the level</td><td>To move on to the next level</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Destroy all enemies in the level</td><td>To move on to the next level and all bullets to be removed from the game</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Generate a new Level by destroying all the enemies</td><td>New enemies to spawn at random</td><td>As expected </td><td>Pass</td></tr></tbody></table>

### Testing Evidence

#### Test 1

<figure><img src="../.gitbook/assets/image (4).png" alt=""><figcaption><p>Screenshot from Bucket Knight</p></figcaption></figure>

The enemy spawned outside of the level (evidenced by the above screenshot). This was a simple fix as I had incorrectly set the enemy spawn boundaries.&#x20;

#### Test 2

<figure><img src="../.gitbook/assets/image (5).png" alt=""><figcaption><p>Screenshot from Bucket Knight</p></figcaption></figure>

Instead of moving towards the player, the Goblin enemy would move towards the origin (0,0). This was found to be a bug where the player's transform was incorrectly referenced so the transform's position would go back to the default of (0,0).

### Evidence

{% embed url="https://youtu.be/8r4hyxzmFZ4" %}
The video above shows the fifth cycle of my game ([https://youtu.be/8r4hyxzmFZ4](https://youtu.be/8r4hyxzmFZ4))
{% endembed %}

The video above shows the new dungeon progression system working as well as enemies spawning at random positions in the level away from the player. The console also logs the position of the newly spawned enemy (shown briefly at the beginning of the video).

In the video, the player reaches the final level and is forced to repeatedly play it. This is because I haven't added a win condition or lose condition as I am going to increase the number of levels in the game to give it more arcade-style gameplay.
