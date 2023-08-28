# 2.2.5 Cycle 5

## Design

In this cycle, I will make the game have a more arcade-like feel. I will have a score at the top indicating how many rooms the player has cleared as well as the next room spawning automatically, with enemies, when the room has been cleared.

As well as that, I will improve the object creation system as I have identified a simple way to improve it.

### Objectives

In this cycle, I will:

* [x] Overhaul the dungeon progression system
* [x] Spawn enemies randomly when a room is built
* [x] Improve the object creation system

### Pseudocode

```
procedure do_something
    
end procedure
```

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

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/8r4hyxzmFZ4" %}
The video above shows the fourth cycle of my game ([https://youtu.be/8r4hyxzmFZ4](https://youtu.be/8r4hyxzmFZ4))
{% endembed %}
