# 2.2.8 Cycle 8

## Design

The goal of this cycle is to add more weapon types to the game in order to add some diversity to the user's experience. I also will add an element to the HUD to show the player what weapon they currently are using and whether or not they can use said weapon.

<figure><img src="../.gitbook/assets/Sprite-0001 (3).png" alt=""><figcaption><p>The projectile sprites for each weapon type</p></figcaption></figure>

The red bullet is for the 'Gun' weapon (the original weapon in the game), the blue bullet is for the 'Magic' weapon, and the BONK sprite is for the 'Melee' weapon. The BONK sprite is bigger than the others as the 'Melee' weapon has a bigger area.

The 'Gun' will have low damage, an average cooldown between shots, and an average range.

The 'Magic' weapon will have high damage, a long cooldown between shots, and a long range.

The 'Melee' weapon will have medium damage, a short cooldown between uses, and a short range.

I also will add a roll ability with appropriate UI to indicate when it can be used.

### Objectives

In this cycle, I will:

* [x] Add a Melee Weapon
* [x] Add two Ranged Weapons
* [x] Add a 'Can Shoot' indicator to the HUD
* [x] Choose a Weapon at Random when the Next Level is Generated
* [x] Add a roll ability for the player to use
* [x] Add some UI to indicate when the roll ability can be used

### Usability Features

'Can Shoot' and 'Roll' Indicator - Allows the user to know when they can shoot and roll so they time their resources effectively

### Pseudocode

{% code title="Attack Function" %}
```cpp
function Game.Attack():
    // Check if the player can currently attack (based on canShoot icon)
    if (canShoot.entity.getComponent<CanShootIcon>().on):
        // Determine the current weapon and perform the corresponding attack
        if (weapon == "Gun"):
            AttackGun()
            frameToWaitFor = gameRef.GetFrames() + gunCooldown
        elif (weapon == "Magic"):
            AttackMagic()
            frameToWaitFor = gameRef.GetFrames() + magicCooldown
        else:
            AttackMelee()
            frameToWaitFor = gameRef.GetFrames() + meleeCooldown

        // Set canShoot icon to off (attack used)
        canShoot.entity.getComponent<CanShootIcon>().on = false
    else:
        // Display an error message when the attack is on cooldown
        Print("Attack on Cooldown")
```
{% endcode %}

This attack function is triggered when the player presses the left click. It selects the attack the player currently has and activates it (provided the player can attack). The player can attack if the `CanShootIcon` is `on`.

{% code title="Switch Weapon Function" %}
```cpp
function Game.SwitchWeapon(newWeapon: String):
    // Check if the entity associated with canShoot has a SpriteComponent
    if (canShoot.entity.hasComponent<SpriteComponent>()):
        // Check if the provided weapon name is not empty
        if (newWeapon != ""):
            // Update the SpriteComponent's texture with the new weapon
            canShoot.entity.getComponent<SpriteComponent>().setTexture(s)
            
            // Update the current weapon
            weapon = newWeapon
            
            // Add or update the CanShootIcon component with the new weapon
            canShoot.entity.addComponent<CanShootIcon>(weapon)
```
{% endcode %}

After each level, this function is called in order to change the weapon the player is using based on the input `newWeapon`.

## Development

### Outcome

{% code title="Gun Weapon Function" %}
```cpp
// Member function for the Game class to handle player attacks with a gun
void Game::AttackGun()
{
    // Calculate the direction from the player to the mouse pointer
    Vector2D dir{ (float)MouseX - player->GetTransform().position.x - 12, (float)MouseY - player->GetTransform().position.y - 12 };
    
    // Normalize the direction vector to make it a unit vector
    dir = dir.normalize(dir);

    // Create a new bullet instance
    auto bullet = new Bullet();

    // Initialize the bullet with position, size, texture path, tag, direction, damage, and speed
    bullet->CreateBullet(
        player->GetTransform().position.x + 12,
        player->GetTransform().position.y + 12,
        12, 12, "Assets/Bullet.png", "playerbullet", dir, 3, 1, 200);

    // Add the bullet entity to the 'groupBullets' group
    bullet->entity->addGroup(groupBullets);

    // Play the 'shoot' sound effect using a free audio channel (-1), and no repetitions (0)
    Mix_PlayChannel(-1, shoot, 0);
}
```
{% endcode %}

{% code title="Magic Weapon Function" %}
```cpp
// Member function for the Game class to handle player attacks with magic
void Game::AttackMagic()
{
    // Calculate the direction from the player to the mouse pointer
    Vector2D dir{ (float)MouseX - player->GetTransform().position.x - 12, (float)MouseY - player->GetTransform().position.y - 12 };
    
    // Normalize the direction vector to make it a unit vector
    dir = dir.normalize(dir);

    // Create a new bullet (magic projectile) instance
    auto bullet = new Bullet();

    // Initialize the magic bullet with position, size, texture path, tag, direction, damage, and speed
    bullet->CreateBullet(
        player->GetTransform().position.x + 12,
        player->GetTransform().position.y + 12,
        12, 12, "Assets/Magic.png", "playerbullet", dir, 3, 3, 300);

    // Add the magic bullet entity to the 'groupBullets' group
    bullet->entity->addGroup(groupBullets);

    // Play the 'magic' sound effect using a free audio channel (-1), and no repetitions (0)
    Mix_PlayChannel(-1, magic, 0);
}
```
{% endcode %}

The Gun and Magic weapons are similar so their functions contain similar code.

{% code title="Melee Weapon Function" %}
```cpp
// Member function for the Game class to handle player melee attacks
void Game::AttackMelee()
{
    // Calculate the direction from the player to the mouse pointer
    Vector2D dir{ (float)MouseX - player->GetTransform().position.x - 12, (float)MouseY - player->GetTransform().position.y - 12 };
    
    // Normalize the direction vector to make it a unit vector
    dir = dir.normalize(dir);

    // Create a new melee attack (e.g., sword swing) instance
    auto bullet = new Bullet();

    // Initialize the melee attack with position, size, texture path, tag, direction, damage, and speed
    bullet->CreateBullet(
        player->GetTransform().position.x + 12 + (dir.x * 48),
        player->GetTransform().position.y + 12 + (dir.y * 48),
        48, 48, "Assets/BONK.png", "playerbullet", dir, 0.2, 2, 3);

    // Add the melee attack entity to the 'groupBullets' group
    bullet->entity->addGroup(groupBullets);

    // Play the 'melee' sound effect using a free audio channel (-1), and no repetitions (0)
    Mix_PlayChannel(-1, melee, 0);
}
```
{% endcode %}

The Melee weapon basically is a bullet with a short range and travels slowly. This gives an illusion of being a Melee weapon when it is actually a projectile.&#x20;

{% code title="Roll Ability" %}
```cpp
void roll(Mix_Chunk* r)
{
    // Check if the player is not already rolling, and if the roll can be used again based on frames
    if (!rolling && RolUseAgainFrame <= frames && (entity->getComponent<TransformComponent>().velocity.x != 0 || entity->getComponent<TransformComponent>().velocity.y != 0))
    {
        // Set the frame when the roll ability will end
        RolFrame = frames + RolAbilityTime;

        // Set the frame when the roll can be used again after a cooldown
        RolUseAgainFrame = RolFrame + RolCooldown;

        // Output a message to indicate that the player rolled
        std::cout << "Player Rolled" << std::endl;

        // Play the roll sound effect
        Mix_PlayChannel(-1, r, 0);

        // Set the rolling flag to true to indicate that the player is rolling
        rolling = true;
    }
}
```
{% endcode %}

The roll ability function takes in a sound effect from `Game` and triggers two cooldowns to start (if the player can roll). The cooldowns are for how long the player can roll and how long until the player can roll again.

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%208).

### Challenges

The main challenge was keeping track of weapons that were being used to properly display that information to the player.

Other than that, this cycle went smoothly as I had already built strong foundations for my solution.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Use the magic weapon</td><td>A blue bullet to be spawned and one-shot the enemy</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Use the melee weapon</td><td>The BONK sprite to appear and two-shot the enemy</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Use the gun weapon</td><td>A red bullet to be spawned and three-shot the enemy</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Complete levels</td><td>Different weapons to be used</td><td>As expected</td><td>Pass</td></tr><tr><td>5</td><td>Complete levels</td><td>The UI to update based on what weapon is being used</td><td>As expected</td><td>Pass</td></tr><tr><td>6</td><td>Use the weapons</td><td>The UI to update based on whether the player can attack or not</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Use the roll ability</td><td>The player should move faster around the map for a short bit of time</td><td>As expected</td><td>Pass</td></tr><tr><td>8</td><td>Use the roll ability when the roll icon is on</td><td>The player should roll and the icon should turn off</td><td>As expected</td><td>Pass</td></tr><tr><td>9</td><td>Use the roll ability when the roll icon is off</td><td>The player shouldn't roll</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://www.youtube.com/watch?v=G5iw7jgfLf8" %}
The video above shows the eighth cycle of my game ([https://www.youtube.com/watch?v=G5iw7jgfLf8](https://www.youtube.com/watch?v=G5iw7jgfLf8))
{% endembed %}

In the video, every time the player completes a level, the icon in the bottom left is updated to match the weapon type the player is currently using. As well as that, the icon turns grey if the player cannot attack due to the weapon being on cooldown. The roll ability and roll icon also function correctly.

Each weapon functions how it is expected to and I have given them custom sound effects to give each weapon some personality in order to differentiate them from their counterparts. I also gave a sound effect to the roll ability so the player can hear when it is triggered.
