# 2.2.11 Cycle 11

## Design

After realising my game, players mentioned bugs that were occurring in the game (shown in the video below posted by my friend).

{% embed url="https://www.youtube.com/watch?v=9LzeccIsdXM" %}
A video depicting Bucket Knight's glitches ([https://www.youtube.com/watch?v=9LzeccIsdXM](https://www.youtube.com/watch?v=9LzeccIsdXM))
{% endembed %}

### Objectives

In this cycle, I will:

* [x] Fix the bugs mentioned in the video
* [x] Release the new version
* [x] Add the patch notes to the itch.io page

### Key Variables

<table><thead><tr><th width="303">Variable Name</th><th>Use</th></tr></thead><tbody><tr><td>background, enemies, foreground, bullets, players, score, oldtiles, menu</td><td>stores a reference to all of their respective entities in their groups</td></tr></tbody></table>

## Development

### Outcome

{% code title="Bug Solution" %}
```cpp
// Clear and destroy objects in the 'background' collection
for (auto b : background)
{
    b->destroy();
}

background.clear();

// Clear and destroy objects in the 'enemies' collection
for (auto e : enemies)
{
    e->destroy();
}

enemies.clear();

// Clear and destroy objects in the 'foreground' collection
for (auto f : foreground)
{
    f->destroy();
}

foreground.clear();

// Clear and destroy objects in the 'bullets' collection
for (auto b : bullets)
{
    b->destroy();
}

bullets.clear();

// Clear and destroy objects in the 'players' collection
for (auto p : players)
{
    p->destroy();
}

players.clear();

// Clear and destroy objects in the 'score' collection
for (auto s : score)
{
    s->destroy();
}

score.clear();

// Clear and destroy objects in the 'oldtiles' collection
for (auto o : oldtiles)
{
    o->destroy();
}

oldtiles.clear();

// Clear and destroy objects in the 'menu' collection
for (auto m : menu)
{
    m->destroy();
}

menu.clear();
```
{% endcode %}

The majority of bugs found were caused by not destroying entities correctly. This would mean 'phantom' enemies would still exist evidenced by the random bullets spawning and the major performance issues in later levels. This was solved via the code above (which is a code snippet from the `EndGame` function).

The player not being teleported to the correct position bug was caused by the previous position being loaded immediately after being moved due to the collision with the wall. This was solved by teleporting the player after the previous position had been set as the desired position.

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%2011).

### Challenges

The main challenge was identifying the cause of the bugs that occurred in the game as they were relatively easy to fix once identified.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Collide with the wall and defeat all the enemies</td><td>The player to teleport to the default position</td><td>The player remained at the same position</td><td>Fail</td></tr><tr><td>2</td><td>Collide with the wall and defeat all the enemies</td><td>The player to teleport to the default position</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Reach later levels in the game</td><td>Everything to function as normal (i.e. no lag and no random projectiles)</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Testing Evidence

#### Test 1

The problem arose from the player being set to their previous position when colliding with walls so this was fixed by setting both the previous position and the player's current position to the level starting position the player was meant to be at.&#x20;

### Evidence

{% embed url="https://youtu.be/a-GtOMCnsjA" %}
The video above depicts the elevnth cycle of my game ([https://youtu.be/a-GtOMCnsjA](https://youtu.be/a-GtOMCnsjA))
{% endembed %}

In the video above, I have added the version 1.1 patch notes to the store page as a development log. I have also updated the installer to v1.1 so the player can play the most recent version of the game.
