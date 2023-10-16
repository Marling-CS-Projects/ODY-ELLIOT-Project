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

The feature was not included in Bucket Knight as it conflicts with the arcade
