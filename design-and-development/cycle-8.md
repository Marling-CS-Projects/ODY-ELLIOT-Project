# 2.2.8 Cycle 8

## Design

The goal of this cycle is to add more weapon types to the game in order to add some diversity to the user's experience. I also will add an element to the HUD to show the player what weapon they currently are using and whether or not they can use said weapon.

<figure><img src="../.gitbook/assets/Sprite-0001 (3).png" alt=""><figcaption><p>The projectile sprites for each weapon type</p></figcaption></figure>

The red bullet is for the 'Gun' weapon (the original weapon in the game), the blue bullet is for the 'Magic' weapon, and the BONK sprite is for the 'Melee' weapon. The BONK sprite is bigger than the others as the 'Melee' weapon has a bigger area.

The 'Gun' will have low damage, an average cooldown between shots, and an average range.

The 'Magic' weapon will have high damage, a long cooldown between shots, and a long range.

The 'Melee' weapon will have medium damage, a short cooldown between uses, and a short range.

### Objectives

In this cycle, I will:

* [x] Add a Melee Weapon
* [x] Add two Ranged Weapons
* [x] Add a 'Can Shoot' indicator to the HUD
* [x] Choose a Weapon at Random when the Next Level is Generated

### Usability Features

'Can Shoot' Indicator - Allows the user to know when they can shoot so they time their shots effectively.

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

### Challenges

The main challenge&#x20;

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://www.youtube.com/watch?v=G5iw7jgfLf8" %}
The video above shows the eighth cycle of my game ([https://www.youtube.com/watch?v=G5iw7jgfLf8](https://www.youtube.com/watch?v=G5iw7jgfLf8))
{% endembed %}

