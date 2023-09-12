# 2.2.7 Cycle 7

## Design

This cycle is focused on better user experience which I will achieve by adding a How-To-Play screen (shown below) as well as implementing music and sound effects.

<figure><img src="../.gitbook/assets/HowToPlayScreen-export.png" alt=""><figcaption><p>The How-To-Play Screen Sprite</p></figcaption></figure>

{% hint style="info" %}
The 'Roll' ability will be added in the next cycle.
{% endhint %}

### Objectives

In this cycle, I will:

* [x] Import the SDL\_Mixer Library to handle Music and SFX
* [x] Create a How-To-Play button
* [x] Create a How-To-Play Screen
* [x] Add a soundtrack that plays on an infinite loop
* [x] Add sound effects that play in response to an event occurring in the game

### Usability Features

How-To-Play - This feature will allow new players to quickly learn the game's controls allowing them to have a more enjoyable experience.

Volume Levels - More important SFX (sound effects) have a greater volume than others (such as the player being hit being louder than the enemies getting hit) which will alert the user to more significant events taking place above other, less significant events.

### Pseudocode

{% code title="How To Play Screen" %}
```cpp
function Game.HowToPlay():
    // Create a back button and add it to the menu group
    backButton = new Trigger(x=24, y=512, width=100, height=27, zIndex=2, image="Assets/Back.png", label="Back Button")
    backButton.entity.addToGroup(menu)

    // Create a how-to-play screen and add it to menu group
    howToPlayScreen = new Trigger(x=0, y=0, width=204, height=156, zIndex=4, image="Assets/HowToPlayScreen.png", label="howtoplay Sprite")
    // The howToPlayScreen has to be a Trigger in order to be added to the menu group
    howToPlayScreen.entity.addToGroup(menu)
```
{% endcode %}

The `HowToPlay` function is a member of the `Game` class and creates the How-To-Play screen, to display the controls for the game, as well as a 'Back' button to return to the Main Menu when pressed.&#x20;

The How-To-Play button (which triggers the `HowToPlay` function) is created and operated similarly to the `Play` button).

## Development

### Outcome

```cpp
// Initialize the SDL_mixer library with MP3 support
Mix_Init(MIX_INIT_MP3);

// Open the audio with the specified parameters: 44100 Hz, default audio format, 2 channels, and a 1024-byte chunk size
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

// Load the music file "Cruising for Goblins.mp3" into the 'music' variable
music = Mix_LoadMUS("Assets/Cruising for Goblins.mp3");

// Check if music loading was successful
if (music == NULL)
{
    std::cout << "Failed to Load Music -> ";
    std::cout << Mix_GetError() << std::endl;
    Mix_ClearError();
}
else
{
    // Output a success message if the music loaded successfully
    std::cout << "Loaded 'Cruising for Goblins.mp3' by Kevin MacLeod" << std::endl;
}

// Start playing the loaded music in an infinite loop (-1 means loop indefinitely)
Mix_PlayMusic(music, -1);

// Set the volume level for the music to 3.5 (adjust as needed)
Mix_VolumeMusic(3.5f);

// Load the sound effect file "shoot.wav" into the 'shoot' variable and set its volume to 3
shoot = Mix_LoadWAV("Assets/shoot.wav");
shoot->volume = 3;

// Load the sound effect file "enemyHit.wav" into the 'enemyHit' variable and set its volume to 3.5
enemyHit = Mix_LoadWAV("Assets/enemyHit.wav");
enemyHit->volume = 3.5f;

// Load the sound effect file "playerHit.wav" into the 'playerHit' variable and set its volume to 4.5
playerHit = Mix_LoadWAV("Assets/playerHit.wav");
playerHit->volume = 4.5f;

// Load the sound effect file "menuClick.wav" into the 'menuClick' variable and set its volume to 3
menuClick = Mix_LoadWAV("Assets/menuClick.wav");
menuClick->volume = 3;

// Load the sound effect file "newLevel.wav" into the 'newLevel' variable and set its volume to 3
newLevel = Mix_LoadWAV("Assets/newLevel.wav");
newLevel->volume = 3;
```

### Challenges

Description of challenges

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>Black Re-sizable Window is opened</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press buttons</td><td>Something happens</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/rmDgmbXZ_yc" %}
