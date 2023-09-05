# 2.2.6 Cycle 6

## Design

In this cycle, I will add a main menu which the player is sent to when they lose and an arcade-style scoring system so the player knows how far they have progressed.

As well as that, I will add a few new assets to improve the game's look.

### Objectives

In this cycle, I will:

* [x] Create a main menu with a Play Button
* [x] When a player loses, the scene will revert to the main menu
* [x] Create an arcade-style scoring system
* [x] Add some improved assets

### Usability Features

Game Loop - The player can now play the game multiple times without restarting the application which will reduce downtime leading to the player being engaged for longer.

### Pseudocode

{% code title="Start Game Function" %}
```cpp
function Game.StartGame():
    // Create a new player and add it to the player group
    player = new Player()
    player.CreatePlayer(x=400, y=300, lives=3)
    player.entity.addToGroup(player)

    // Create player hearts and add them to foreground group
    heart1 = new PlayerHeart(x=12, y=12, playerComponent=player.entity.getComponent<PlayerComponent>(), heartNumber=1)
    heart1.entity.addToGroup(foreground)

    heart2 = new PlayerHeart(x=60, y=12, playerComponent=player.entity.getComponent<PlayerComponent>(), heartNumber=2)
    heart2.entity.addToGroup(foreground)

    heart3 = new PlayerHeart(x=108, y=12, playerComponent=player.entity.getComponent<PlayerComponent>(), heartNumber=3)
    heart3.entity.addToGroup(foreground)

    // Create walls and add them to foreground group
    wall1 = new Wall(x=204, y=120, width=432, height=24, texture="Assets/WallTexture.png")
    wall1.entity.addToGroup(foreground)

    wall2 = new Wall(x=204, y=528, width=432, height=24, texture="Assets/WallTexture.png")
    wall2.entity.addToGroup(foreground)

    wall3 = new Wall(x=612, y=120, width=24, height=432, texture="Assets/WallTexture.png")
    wall3.entity.addToGroup(foreground)

    wall4 = new Wall(x=204, y=120, width=24, height=432, texture="Assets/WallTexture.png")
    wall4.entity.addToGroup(foreground)

    // Create objects for tens and ones digit scores
    tens = new Object()
    tens.CreateObject()
    tens.entity.addComponent<TransformComponent>(x=359, y=12, width=24, height=24, zIndex=2)
    tens.entity.addComponent<SpriteComponent>("Assets/0.png")
    tens.entity.addComponent<ScoreComponent>("tens")
    tens.entity.addToGroup(score)

    ones = new Object()
    ones.CreateObject()
    ones.entity.addComponent<TransformComponent>(x=409, y=12, width=24, height=24, zIndex=2)
    ones.entity.addComponent<SpriteComponent>("Assets/0.png")
    ones.entity.addComponent<ScoreComponent>("ones")
    ones.entity.addToGroup(score)

    // Create a dungeon and generate its layout
    dGen = new Dungeon(maxRooms=20)
    dGen.GenerateLayout()
    dGen.DrawCurrentRoom()
```
{% endcode %}

The `StartGame()` function initialises everything needed for the game to run (replacing part of the `init()` function) and is called when the Play Button is pressed.

{% code title="End Game Function" %}
```cpp
function Game.EndGame():

    // Clears all the game's groups
    background.clear()
    enemies.clear()
    foreground.clear()
    bullets.clear()
    menu.clear()
    players.clear()
    score.clear()

    // Create a new Play Button and add it to the menu group
    playButton = new Trigger(x=152, y=240, width=256, height=48, zIndex=2, image="Assets/PlayButton.png", label="Play Button")
    playButton.entity.addToGroup(menu)
```
{% endcode %}

The `EndGame()` function removes all current Entities from the scene by clearing the game's groups and then the function creates the Main Menu.

This function is run at the start of the game (by the `init()` function) and when the player dies.

## Development

### Outcome

{% code title="Extract of the update function" %}
```cpp
// Iterate over each 'm' object in the 'menu' group
for (auto& m : menu)
{
    // Check if the Left Click event occurred, and if 'm' is a "Play Button" and the mouse is over it
    // Also, ensure that the game has not already started
    if (Game::event.type == SDL_MOUSEBUTTONDOWN &&
        m->getComponent<ColliderComponent>().tag == "Play Button" &&
        Collision::AABB(m->getComponent<ColliderComponent>().collider, SDL_Rect { MouseX, MouseY, 1, 1 }) &&
        !gameStarted)
    {
        // Activate the 'm' object which ensures the object is active to reduce the chance of pointer failure
        m->activate();

        // Call teh StartGame() Method to initialise the Entities required for the game to run
        StartGame();

        // Set the 'gameStarted' flag to true to prevent multiple game starts
        gameStarted = true;

        // Output a message to the console indicating that the game has started
        std::cout << "Game Started" << std::endl;

        // Destroy the Play Button
        m->destroy();
    }
}
```
{% endcode %}

This code checks whether the Play Button has been pressed and then Starts the game if it was pressed.

{% code title="Score Component" %}
```cpp
// Define a class called ScoreComponent that inherits from the Component class
class ScoreComponent : public Component
{
public:
    // Constructor for ScoreComponent, takes a 'column' parameter ('tens' or 'ones')
    ScoreComponent(string column)
    {
        this->score = 0; // Initialize the score to 0
        this->column = column; // Store the provided 'column' value
    }

    // Get the current score
    int GetScore()
    {
        return this->score;
    }

    // Increment the score by 1
    void IncrementScore()
    {
        score += 1;
    }
    
    // Update the displayed score based on the 'column' value
    void DisplayScore()
    {
        if (column == "tens")
        {
            // Calculate the 'tens' digit of the score
            int i = (score - (score % 10)) / 10;
            
            // Generate the path to the sprite based on the tens digit
            string s = "Assets/" + to_string(i) + ".png";
            
            // Convert the path to a C-style string and set it as the texture
            const char* c = s.c_str();
            sprite->setTex(c);
        }
        else if (column == "ones")
        {
            // Calculate the 'ones' digit of the score
            int i = score % 10;
            
            // Generate the path to the sprite based on the ones digit
            string s = "Assets/" + to_string(i) + ".png";
            
            // Convert the path to a C-style string and set it as the texture
            const char* c = s.c_str();
            sprite->setTex(c);
        }
    }
    
    // Initialization function, overridden from the base Component class
    void init() override
    {
        if (entity->hasComponent<SpriteComponent>())
        {
            this->sprite = &entity->getComponent<SpriteComponent>();
        }
        else
        {
            // Displays an error message as this component relies heavily on the Sprite Component
            std::cout << "Error: No Sprite Component attached to the Score Entity" << std::endl;
        }
    }

private:
    int score = 0; // Store the score value
    string column; // Store the column value ('tens' or 'ones')
    SpriteComponent* sprite; // Pointer to the associated SpriteComponent
};
```
{% endcode %}

The `ScoreComponent` tells the scoreboard what number to display based on the column the entity represents.

You can find the rest of the solution [here](https://github.com/Marling-CS-Projects/ODY-ELLIOT-Project/tree/cycles/Bucket%20Knight%20-%20Cycle%206).

### Challenges

This cycle had many bugs arising from attempting to reset the game scene. The main issue was pointer errors as destroyed objects wouldn't be removed from groups and were still attempting to be referenced. This issue was solved by clearing the groups when the game ended.

## Testing

<table><thead><tr><th width="90">Test</th><th width="141">Instructions</th><th>What I expect</th><th width="163">What actually happens</th><th>Pass/Fail</th></tr></thead><tbody><tr><td>1</td><td>Run code</td><td>The Main Menu Appears</td><td>As expected</td><td>Pass</td></tr><tr><td>2</td><td>Press the Play Button</td><td>The Game starts</td><td>As expected</td><td>Pass</td></tr><tr><td>3</td><td>Press the Play Button and let the Player die</td><td>The Game reverts back to the Main Menu</td><td>As expected</td><td>Pass</td></tr><tr><td>4</td><td>Press the Play Button and let the Player die then attempt to start the Game again</td><td>The Game starts</td><td>A read access violation occurs as the pointer points to a memory location that no longer exists</td><td>Fail</td></tr><tr><td>5</td><td>Press the Play Button and let the Player die then attempt to start the Game again</td><td>The Game starts</td><td>Write access violation as the pointer cannot access the correct memory location to write the new data onto</td><td>Fail</td></tr><tr><td>6</td><td>Press the Play Button and let the Player die then attempt to start the Game again</td><td>The Game starts</td><td>As expected</td><td>Pass</td></tr><tr><td>7</td><td>Go through the Dungeon by defeating the enemies in each room</td><td>The Score should increment correctly</td><td>As expected</td><td>Pass</td></tr></tbody></table>

### Evidence

{% embed url="https://youtu.be/VF2-2tVXJ2I" %}
The video above shows the sixth cycle of my game ([https://youtu.be/VF2-2tVXJ2I](https://youtu.be/VF2-2tVXJ2I))
{% endembed %}

The video&#x20;
