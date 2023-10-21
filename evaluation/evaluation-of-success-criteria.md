# 4.1 Evaluation of Success Criteria

## Player Evaluation

### Criteria

| Ref. No. | Criterion                                                                                                                      | Included     | Reference                                                                       |
| :------: | ------------------------------------------------------------------------------------------------------------------------------ | ------------ | ------------------------------------------------------------------------------- |
|     1    | The player should be able to move using the WASD keys.                                                                         | Included     | [Movement](../analysis/features-of-the-proposed-solution.md#movement)           |
|     2    | The player should be able to collide with the dungeon's walls.                                                                 | Included     | [Collisions](../analysis/features-of-the-proposed-solution.md#collisions)       |
|     3    | The player should have a camera attached to them.                                                                              | Not Included | [Camera](../analysis/features-of-the-proposed-solution.md#camera)               |
|     4    | The player should be able to use a variety of weapons.                                                                         | Included     | [Weapons](../analysis/features-of-the-proposed-solution.md#weapons)             |
|     5    | The player should have a roll ability which they can to dodge attacks.                                                         | Included     | [Movement](../analysis/features-of-the-proposed-solution.md#movement)           |
|     6    | When the player dies (health <= 0) a game over screen should be presented and then the user will be directed to the main menu. | Included     | [HP and Damage](../analysis/features-of-the-proposed-solution.md#hp-and-damage) |

### Criterion 1

This feature was added in [Cycle 1](../design-and-development/cycle-1a.md) and allows the player to move in eight directions. This is a core mechanic of the game as the player has to move around the enemies to avoid being hit.

### Criterion 2

Added in [Cycle 3](../design-and-development/cycle-3.md), the collisions with walls are a vital feature of the game as they prevent the player from going out of bounds which would allow them to leave the game scene.

### Criterion 3

The movable camera attached to the player was never implemented. This is because there wasn't any need to add one due to the game taking a more arcade-like approach after [Cycle 5](../design-and-development/cycle-5.md).

### Criterion 4

The weapons were created in [Cycle 8](../design-and-development/cycle-8.md) using the foundations built in [Cycle 4](../design-and-development/cycle-4.md). The weapons are important to the game as they provide some variety so users are entertained for longer.

### Criterion 5

The roll ability was added in [Cycle 8](../design-and-development/cycle-8.md) and it was later patched (in [Cycle 12](../design-and-development/cycle-12.md)) so the player is invincible while the roll is active. The roll is essential to the game as it provides some variety to the player's movement which will keep the player engaged for longer. It also provides a 'Get out of Jail Free Card' when the player is stuck in sticky situations (such as being boxed into the corner by enemies).

### Criterion 6

This feature was added in [Cycle 4](../design-and-development/cycle-4.md) and is a vital feature of the game as it allows the player to lose. Without this, the user will face no challenge which will make the game not enjoyable as it won't be in the 'Goldilocks Zone'.

## Enemies Evaluation

### Criteria

| Ref. No. | Criterion                                                                                                   | Included           | Reference                                                                       |
| :------: | ----------------------------------------------------------------------------------------------------------- | ------------------ | ------------------------------------------------------------------------------- |
|     7    | There needs to be a multiple classes of enemies.                                                            | Included           | [Enemies](../analysis/features-of-the-proposed-solution.md#enemies)             |
|     8    | The enemies should be able to move towards and around the player.                                           | Partially Included | [Enemies](../analysis/features-of-the-proposed-solution.md#enemies)             |
|     9    | Each enemy should be assigned a rarity on creation and better rarities will be more common in later levels. | Not Included       | [Progression](../analysis/features-of-the-proposed-solution.md#progression)     |
|    10    | There should be at least 1 unique enemy in each class.                                                      | Partailly Included | [Enemies](../analysis/features-of-the-proposed-solution.md#enemies)             |
|    11    | The boss needs to appear on the last level and be the most difficult opponent of the game.                  | Not Included       | [Enemies](../analysis/features-of-the-proposed-solution.md#enemies)             |
|    12    | When an enemy's health <=0, destroy the enemy.                                                              | Included           | [HP and Damage](../analysis/features-of-the-proposed-solution.md#hp-and-damage) |

### Criterion 7

There are currently three classes of enemies implemented in the game which were added in [Cycle 9](../design-and-development/cycle-9.md) (except for the melee enemy which was added in [Cycle 4](../design-and-development/cycle-4.md)). This adds variety to the game which will keep the player's attention for longer as well as add more depth to the challenge the game provides.

### Criterion 8

As mentioned in [Criterion 7](evaluation-of-success-criteria.md#criterion-7), the different classes of enemies have been implemented in the game. The majority of the classes move towards the player to provide a sense of urgency to present a challenge to the player. However, there is one enemy that doesn't move towards the player (that being the Wizard added in [Cycle 8](../design-and-development/cycle-8.md)). This was to add more variety to the enemy types as well as prevent players from luring all enemies to a corner and then dashing away (a common behaviour I found while testing [Cycle 8](../design-and-development/cycle-8.md)).

### Criterion 9

The feature was not included in Bucket Knight as it made the game more confusing as the same enemy could have varied health and damage. Instead, I opted to increase the number of enemies each level provides (added in [Cycle 9](../design-and-development/cycle-9.md)) to present the player with a challenge which is perceived to be more difficult than enemy rarities without confusing them.

### Criterion 10 & 11

There is a unique enemy in all classes except for the Boss class (evidenced in [Cycle 8](../design-and-development/cycle-8.md)). The Boss was omitted as there is no last level that the player can get to,**\*** due to the arcade-style gameplay introduced in [Cycle 5](../design-and-development/cycle-5.md).

**\***Theoretically the player can reach level 255 before the game starts to loop. This was added as an Easter Egg to represent the old arcade games, such as Pac-Man, having this level cap as they used 8-bit integers to store the score value. Most players will never go this far into the game so there would be no reason to add a special enemy type to this level.

### Criterion 12

When an enemy reaches zero health it is essential to the game that the enemy is destroyed. Without this feature, levels would never progress (as all enemies need to be killed to progress through the game) so the user will get bored of the game extremely quickly. This feature was added in [Cycle 4](../design-and-development/cycle-4.md).

## Dungeon Generation

### Criteria

| Ref. No. | Criterion                                                    | Included           | Reference                                                                                                                                                                 |
| :------: | ------------------------------------------------------------ | ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|    13    | There needs to be an easy way to build rooms.                | Included           | [Procedural ](../analysis/features-of-the-proposed-solution.md#procedural-generation)[Generation](../analysis/features-of-the-proposed-solution.md#procedural-generation) |
|    14    | The dungeon generation algorithm.                            | Partially Included | [Procedural ](../analysis/features-of-the-proposed-solution.md#procedural-generation)[Generation](../analysis/features-of-the-proposed-solution.md#procedural-generation) |
|    15    | Each room generated needs to have a chance to spawn a chest. | Not Included       | [Procedural ](../analysis/features-of-the-proposed-solution.md#procedural-generation)[Generation](../analysis/features-of-the-proposed-solution.md#procedural-generation) |
|    16    | The end room needs to generate.                              | Included           | [Procedural ](../analysis/features-of-the-proposed-solution.md#procedural-generation)[Generation](../analysis/features-of-the-proposed-solution.md#procedural-generation) |

### Criterion 13

Tilemaps were added in [Cycle 2](../design-and-development/cycle-2.md) and allowed me to quickly build rooms via external text files which made it easy to create a variety of pre-made rooms.

### Criterion 14

I labelled this feature as partially included as it generates the level order the player will play through but doesn't create entire dungeons which it was originally intended to do. The reason for this is the lack of a camera for the player and the new arcade-style approach to the game ([Cycle 5](../design-and-development/cycle-5.md)). This feature was added in [Cycle 3](../design-and-development/cycle-3.md) and later developed to be more arcade-like in [Cycle 5](../design-and-development/cycle-5.md).

### Criterion 15

Chests weren't included in the game due to the new weapon-switching mechanic taking priority (which was added in [Cycle 8](../design-and-development/cycle-8.md)). I believe this was a good change as chests slow down the gameplay because the player needs to interact with them separately whereas weapon-switching allows the player to keep the game at the same pace which I believe is ideal for an arcade game.

### Criterion 16

As mentioned in [Criterion 10 & 11](evaluation-of-success-criteria.md#criterion-10-and-11), the end room spawns at score 255 which is mostly impossible to reach. However, I did make a custom room for this to reward players who reach this far into the game with a level that looks like a smiley-face made from smiley-face tiles.

## Weapons

### Criteria

| Ref. No. | Criterion                                                                                                                                      | Included     | Reference                                                                                                                                                                           |
| :------: | ---------------------------------------------------------------------------------------------------------------------------------------------- | ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|    17    | There needs to be 3 classes of weapon.                                                                                                         | Included     | [Weapons](../analysis/features-of-the-proposed-solution.md#weapons)                                                                                                                 |
|    18    | There needs to be different rarities of weapons.                                                                                               | Not Included | <p><a href="../analysis/features-of-the-proposed-solution.md#weapons">Weapons</a><br><br><a href="../analysis/features-of-the-proposed-solution.md#limitations">Limitations</a></p> |
|    19    | Weapons need to be more effective against enemies with the opposing class and be less effective against enemies with the more effective class. | Not Included | [Weapons](../analysis/features-of-the-proposed-solution.md#weapons)                                                                                                                 |

### Criterion 17

The three weapon types were added in [Cycle 8](../design-and-development/cycle-8.md) and were representative of the originally planned weapons. The magic weapon (blue weapon) is the new version of the ranger class as it has a large cooldown but high damage output. The gun weapon (red weapon) represents the mage class as it has a short cooldown and low damage output per shot. The melee weapon (the BONK weapon) has stayed the same.

### Criterion 18

This feature wasn't included for similar reasons to [Criterion 9](evaluation-of-success-criteria.md#criterion-9): it overcomplicated the game. Instead of adding rarities, the weapon switches after each level which makes up for the lack of weapons as it forces the player to keep adapting to different playstyles which keeps them engaged. Weapon switching was added in [Cycle 8](../design-and-development/cycle-8.md).

### Criterion 19

This feature wasn't included as it makes the game more complicated, in my opinion. A complicated arcade game may cause players to stop playing faster (due to a lack of understanding) which goes against my goals of making an entertaining game.
