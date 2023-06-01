# 2.2.1 Cycle 1

## Design

### Objectives

In this cycle I aim to:

* [x] Set up a C++ project in VS 2019
* [x] Incorporate the SDL2 library into the project ([https://www.libsdl.org/](https://www.libsdl.org/))
* [x] Create a black, re-sizable window
* [x] Render a sprite to that window
* [x] Move the sprite around the scene using WASD

### Usability Features

* Controls - Simple controls as it currently will just be movement controls.
* Sprite Contrast - The sprite will have a white outline to contrast with the black background.

### Key Variables

| Variable Name | Use                   |
| ------------- | --------------------- |
| foo           | does something useful |

### Pseudocode

{% code title="Game Loop" %}
```cpp
while game is running
{
    get_inputs()
    update()
    render()
}

clean_memory() // Memory is cleaned to free up the user's RAM

```
{% endcode %}

{% code title="Movement Inputs" fullWidth="false" %}
```cpp
if W is pressed { move(UP) }

else if S is pressed { move(DOWN) }

if A is pressed { move(LEFT) }

else if D is pressed { move(RIGHT) }
```
{% endcode %}

{% code title="Render Sprite" %}
```cpp
texture = load_texture("character.png")
draw_sprite(texture, position)
```
{% endcode %}

## Development

### Outcome

### Challenges

Description of challenges

## Testing

Evidence for testing

### Tests

| Test | Instructions  | What I expect     | What actually happens | Pass/Fail |
| ---- | ------------- | ----------------- | --------------------- | --------- |
| 1    | Run code      | Thing happens     | As expected           | Pass      |
| 2    | Press buttons | Something happens | As expected           | Pass      |

### Evidence

{% file src="../.gitbook/assets/Bucket Knight - Cycle 1.mp4" %}
This video was made using OBS Studio ([https://obsproject.com/](https://obsproject.com/)) and has no sound
{% endfile %}
