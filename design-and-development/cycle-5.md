# 2.2.5 Cycle 5

## Design

This cycle will be an optimisation cycle where I will clean up code to make it easier to continue development.

As well as that, I will give the dungeon a more arcade-like system where the next room will spawn when all the enemies are defeated.

### Objectives

In this cycle, I will:

* [ ] Overhaul the dungeon progression system
* [ ] Improve the object creation system

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

The new system results in less code having to be written to create an object by making the class constructor take in arguments and run the object creation function.

As well as that, the `gameObject` variable's name has been changed to `entity` because it represents the valued stored inside (which is an Entity pointer).

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence
