#include "include/raylib.h"
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int screenWidth = 1600;
const int screenHeight = 850;

class Game
{
    // We can add boundary class here to show aggregation.
protected:
    Rectangle player;
    char *texture;
    Texture2D textureobject;
    Vector2 playervelocity;
    const float maxSpeed = 26.0f;    // Adjusted maximum speed
    const float acceleration = 3.0f; // Adjusted acceleration
    const float deceleration = 1.0f;
    char *music;
    Sound bgMusic;

public:
    Game(char *texture, char *music) : texture(texture), music(music)
    { // for player
        playervelocity.x = 0.0f;
        playervelocity.y = 0.0f;
        player.x = 0;
        player.y = 0;
        player.width = 40;
        player.height = 40;
        textureobject = LoadTexture(texture);
        bgMusic = LoadSound(music);
    }
    Game(float x, float y, char *texture, char *music) : texture(texture), music(music)
    { // for enemy
        player.x = x;
        player.y = y;
        textureobject = LoadTexture(texture);
        player.height = textureobject.height;
        player.width = textureobject.width;
    }
    ~Game()
    {
        UnloadTexture(textureobject);
        UnloadSound(bgMusic);
    }
    virtual void setpos(float x, float y) = 0;
    float getx() { return player.x; }
    float gety() { return player.y; }
    Rectangle getrect() { return player; }
};

class Player : public Game
{
protected:
    float score;

public:
    Player(char *texture, char *music) : Game(texture, music)
    {
        score = 0;
    }
    void setpos(float x, float y)
    {
        // We can try operator overloading here.
        player.x += x;
        player.y += y;
    }
};

class Enemy : public Game
{
    float speed;

public:
    Enemy(float x, float y, char *texture, char *music) : Game(texture, music)
    {
        speed = GetRandomValue(15, 30) / 10.0f; // Set enemy speed randomly from 1.5 to 3.0
    }
    void setpos(float x, float y)
    {
        player.x += x * speed;
        player.y += y * speed;
    }
};

class DefaultValues
{
private:
public:
    const int screenWidth = 1600;
    const int screenHeight = 850;
    Rectangle player = {0, 0, 40, 40};
    Vector2 playerVelocity = {0.0f, 0.0f};
    const float maxSpeed = 26.0f;    // Adjusted maximum speed
    const float acceleration = 3.0f; // Adjusted acceleration
    const float deceleration = 1.0f;

    const float boundaryLeft = -815.0f;
    const float boundaryRight = 715.0f;
    const float boundaryTop = -429.0f;
    const float boundaryBottom = 332.0f;

    Sound bgMusic = LoadSound("resources/bgmusicwav.wav"); // SUFYAN WALA MUSIC
    Sound sfx4 = LoadSound("resources/StopIt.wav");

    Sound sfx5 = LoadSound("resources/woosh.wav");
    Sound sfx6 = LoadSound("resources/randomsfx1.wav");
    Sound sfx7 = LoadSound("resources/randomsfx2.wav");

    Sound gameover = LoadSound("resources/GameOver.wav");
};

class Bullet
{
private:
    // Attributes
    Vector2 position_;
    int speed_;

public:
    // Attributes
    bool active; // Variable to check if bullet is still within the game window.

    //  Constructors
    Bullet(const Vector2 position, const int speed) : position_(position), speed_(speed) {}

    // Methods

    // Function to update the bullet's position.
    void Update();

    // Function to draw the bullet.
    void Draw();
};