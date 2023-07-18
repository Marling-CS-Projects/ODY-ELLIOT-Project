# 2.2.3 Cycle 3

## Design

### Objectives

In this cycle I aim to:

* [x] Create a Dungeon Layout Generator
* [x] Create an array of different Rooms for the Dungeon
* [x] Have each room connect to each other
* [x] Dungeon Walls with Collision
* [x] Streamlined Entity Creation System
* [x] Viewport Scaling

### Usability Features

### Key Variables

| Variable Name | Use                   |
| ------------- | --------------------- |
| foo           | does something useful |

### Pseudocode

{% code title="Dungeon Creator" %}
```cpp
Dungeon(int numRooms) // acts as a class constructor
{
    this.numRooms = numRooms
    this.rooms = GetRooms()
    this.currentRoom = 0
}

vector<string> GetRooms()
{
    // returns all the names of the text files the rooms are stored in 
    return vector<string>
    {
        "Room1.txt",
        "Room2.txt",
        "Room3.txt"
    }
}

void GenerateLayout()
void DrawCurrentRoom()

int numRooms
vector<string> rooms{}
vector<Level*> currentLayout
int currentRoom
```
{% endcode %}

## Development

### Outcome

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence



{% embed url="https://youtu.be/dw7ssOx5V9M" %}
The video above shows the third cycle of my game ([https://youtu.be/dw7ssOx5V9M](https://youtu.be/dw7ssOx5V9M))
{% endembed %}
