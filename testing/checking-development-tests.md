# 3.3 Checking Development Tests

This part of testing will include every previous test I completed across my 12 cycles of development.

## [Cycle 1](../design-and-development/cycle-1a.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>The player moved double the speed than was intended due to the entity being updated twice. This problem was displayed in the video below but has been fixed in the GitHub files for cycle 1 which you can find <a href="https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%201">here</a>.</td><td>Fail</td></tr><tr><td>3</td><td>Press buttons WASD</td><td>W makes the player move UP, A moves LEFT, S moves DOWN, and D moves RIGHT</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Close the game</td><td>The memory to be cleaned</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/wLS_OUcNmBI" %}
The video above shows the first cycle of my game ([https://youtu.be/wLS\_OUcNmBI](https://youtu.be/wLS\_OUcNmBI))
{% endembed %}

## [Cycle 2](../design-and-development/cycle-2.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Tiles are in the shape of a smiley face.</td><td>All tiles were jumbled.</td><td>Fail</td></tr><tr><td>2</td><td>Run code</td><td>Tiles are in the shape of a smiley face.</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Move the player into the wall</td><td>A console log stating there has been a collision between the player and the wall.</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/-B1UMLdatTE" %}
The video above shows the second cycle of my game ([https://youtu.be/-B1UMLdatTE](https://youtu.be/-B1UMLdatTE))
{% endembed %}

## [Cycle 3](../design-and-development/cycle-3.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Player touches frontTigger</td><td>The next room appears</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Player touches backTigger</td><td>The previous room appears</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Player walks into the wall</td><td>The player doesn't pass through the wall</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Player touches frontTigger while in the final room</td><td>The player stays in the final room</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Player touches backTigger</td><td>The player stays in the first room</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/dw7ssOx5V9M" %}
The video above shows the third cycle of my game ([https://youtu.be/dw7ssOx5V9M](https://youtu.be/dw7ssOx5V9M))
{% endembed %}

## [Cycle 4](../design-and-development/cycle-4.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Left Click a Position in the Game World</td><td>A Bullet to Spawn</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Left Click a Position in the Game World</td><td>A Bullet to Spawn and Move towards the Mouse Position</td><td>The bullet was offset due</td><td>Fail</td></tr><tr><td>3</td><td>Left Click a Position in the Game World</td><td>A Bullet to Spawn and Move towards the Mouse Position</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Run the Code</td><td>The new Melee Enemy to move towards the player</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Let the Enemy collide with the Player</td><td>The player to lose 1 health point and have 2 lives left</td><td>The player died</td><td>Fail</td></tr><tr><td>6</td><td>Let the Enemy collide with the Player</td><td>The player to lose 1 health point and have 2 lives left</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Let the Enemy collide with the Player</td><td>The right-most Heart should switch off</td><td>As expected</td><td>Pass</td></tr><tr><td>8</td><td>Shoot a bullet at the enemy</td><td>The enemy to be destroyed </td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/ctZDqX19qA8" %}
The video above shows the fourth cycle of my game ([https://youtu.be/ctZDqX19qA8](https://youtu.be/ctZDqX19qA8))
{% endembed %}

## [Cycle 5](../design-and-development/cycle-5.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>One Enemy to spawn inside the level and Pathfind to the Player</td><td>The Enemy spawned outside the level</td><td>Fail</td></tr><tr><td>2</td><td>Run code</td><td>One Enemy to spawn inside the level and Pathfind to the Player</td><td>The Enemy moved towarss the game origin rather than the player</td><td>Fail</td></tr><tr><td>3</td><td>Run code</td><td>One Enemy to spawn inside the level</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Run code</td><td>Multiple enemies to spawn inside the level</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Destroy all enemies in the level</td><td>To move on to the next level</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Destroy all enemies in the level</td><td>To move on to the next level and all bullets to be removed from the game</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Generate a new Level by destroying all the enemies</td><td>New enemies to spawn at random</td><td>As expected </td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/8r4hyxzmFZ4" %}
The video above shows the fifth cycle of my game ([https://youtu.be/8r4hyxzmFZ4](https://youtu.be/8r4hyxzmFZ4))
{% endembed %}

## [Cycle 6](../design-and-development/cycle-6.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>The Main Menu Appears</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press the Play Button</td><td>The Game starts</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Press the Play Button and let the Player die</td><td>The Game reverts back to the Main Menu</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Press the Play Button and let the Player die then attempt to start the Game again</td><td>The Game starts</td><td>A read access violation occurs as the pointer points to a memory location that no longer exists</td><td>Fail</td></tr><tr><td>5</td><td>Press the Play Button and let the Player die then attempt to start the Game again</td><td>The Game starts</td><td>Write access violation as the pointer cannot access the correct memory location to write the new data onto</td><td>Fail</td></tr><tr><td>6</td><td>Press the Play Button and let the Player die then attempt to start the Game again</td><td>The Game starts</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Go through the Dungeon by defeating the enemies in each room</td><td>The Score should increment correctly</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/VF2-2tVXJ2I" %}
The video above shows the sixth cycle of my game ([https://youtu.be/VF2-2tVXJ2I](https://youtu.be/VF2-2tVXJ2I))
{% endembed %}

## [Cycle 7](../design-and-development/cycle-7.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Music to be playing</td><td>No music played and an error was printed out to the console reading "Failed to Load Music -> Unrecognised File Format"</td><td>Fail</td></tr><tr><td>2</td><td>Run code</td><td>Music to be playing</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Press the How-To-Play button</td><td>The scene to switch to the How-To-Play screen</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Press the Back Button </td><td>The scene to revert back to the Main Menu</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Click the Menu buttons</td><td>The menuClick sound to play</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Recieve damage from an enemy</td><td>The playerHit sound to play</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Deal damage to an enemy</td><td>The enemyHit sound to play</td><td>As expected</td><td>Pass</td></tr><tr><td>8</td><td>Destroy all enemies in a level</td><td>The level to change so the newLevel sound plays</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/rmDgmbXZ_yc" %}
The video above shows the seventh cycle of my game ([https://youtu.be/rmDgmbXZ\_yc](https://youtu.be/rmDgmbXZ\_yc))
{% endembed %}

## [Cycle 8](../design-and-development/cycle-8.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Use the magic weapon</td><td>A blue bullet to be spawned and one-shot the enemy</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Use the melee weapon</td><td>The BONK sprite to appear and two-shot the enemy</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Use the gun weapon</td><td>A red bullet to be spawned and three-shot the enemy</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Complete levels</td><td>Different weapons to be used</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Complete levels</td><td>The UI to update based on what weapon is being used</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Use the weapons</td><td>The UI to update based on whether the player can attack or not</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://www.youtube.com/watch?v=G5iw7jgfLf8" %}
The video above shows the eighth cycle of my game ([https://www.youtube.com/watch?v=G5iw7jgfLf8](https://www.youtube.com/watch?v=G5iw7jgfLf8))
{% endembed %}

## [Cycle 9](../design-and-development/cycle-9.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Go through the levels</td><td>Enemies to spawn in the sequence 1,1,2,2,3,3,... (excluding the first level)</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Go through the levels</td><td>Different enemy types spawn</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Get shot by Wizard enemy</td><td>The player to take damage</td><td>The player dies instantly</td><td>Fail (as the player should still be alive after being hit)</td></tr><tr><td>4</td><td>Get shot by Wizard enemy</td><td>The player to take damage</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Spawn a Furball enemy</td><td>The enemy should move towards the player and shoot</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Get shot by a Furball enemy</td><td>The player to take damage</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>See if all the enemy types contain variation</td><td>The enemies to have slightly different stats to their counterparts</td><td>As expected</td><td>Pass</td></tr><tr><td>8</td><td>Shoot the Wizard enemy once with the Gun weapon</td><td>The enemy to die as the Gun weapon deals 1HP and the Wizard has 1HP</td><td>As expected</td><td>Pass</td></tr><tr><td>9</td><td>Shoot the Furball enemy twice with the Gun weapon</td><td>The enemy to die after the second shot as the Gun weapon deals 1HP and the Furball has 2HP</td><td>As expected</td><td>Pass</td></tr><tr><td>10</td><td>Kill the enemies using the other weapons</td><td>The enemies to be destroyed correctly (based on the weapon's damage and health)</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://www.youtube.com/watch?t=2s&v=Z4aXRpog_YY" %}
The video above shows the ninth cycle of my game ([https://www.youtube.com/watch?v=Z4aXRpog\_YY](https://www.youtube.com/watch?v=Z4aXRpog\_YY))
{% endembed %}

## [Cycle 10](../design-and-development/cycle-10.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Install the Application</td><td>The game to run as normal</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/Zcm7wGaESJo" %}
The video above shows the tenth cycle of my game ([https://www.youtube.com/watch?v=Zcm7wGaESJo](https://www.youtube.com/watch?v=Zcm7wGaESJo))
{% endembed %}

## [Cycle 11](../design-and-development/cycle-11.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Collide with the wall and defeat all the enemies</td><td>The player to teleport to the default position</td><td>The player remained at the same position</td><td>Fail</td></tr><tr><td>2</td><td>Collide with the wall and defeat all the enemies</td><td>The player to teleport to the default position</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Reach later levels in the game</td><td>Everything to function as normal (i.e. no lag and no random projectiles)</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/a-GtOMCnsjA" %}
The video above depicts the elevnth cycle of my game ([https://youtu.be/a-GtOMCnsjA](https://youtu.be/a-GtOMCnsjA))
{% endembed %}

## [Cycle 12](../design-and-development/cycle-12.md)

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Press 'P' after the game has started</td><td>The pause menu appears on screen</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press 'P' after the game has started</td><td>The pause menu appears on screen and all entities stop updating</td><td>Enemies stop moving but still shoot bullets</td><td>Fail</td></tr><tr><td>3</td><td>Press 'P' after the game has started</td><td>The pause menu appears on screen and all entities stop updating</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Let the player die</td><td>The game-over screen should be displayer</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Test out all the weapons</td><td>The stats should be changed</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Test for input lag</td><td>No input lag should occur</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://www.youtube.com/watch?v=XrXzbDvoiRU" %}
The video above depicts the twelfth cycle of my game ([https://www.youtube.com/watch?v=XrXzbDvoiRU](https://www.youtube.com/watch?v=XrXzbDvoiRU))
{% endembed %}
