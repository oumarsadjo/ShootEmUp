/* Game.hpp
{=========================================================}
{===== Ce fichier contient methodes/attributs du Jeux ====}
{=========================================================}
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Global.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Game {
public:
    Game();
    void run();
    void gameOver();
    void congratulations();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Player player;
    std::vector<Enemy> enemies;
    bool enemiesDestroyed;
    bool gameOverFlag ;
    sf::SoundBuffer collisionSoundBuffer;
    sf::Sound collisionSound;

    sf::SoundBuffer gameOverSoundBuffer;
    sf::Sound gameOverSound;

    sf::SoundBuffer congratsSoundBuffer;
    sf::Sound congratsSound;
    sf::Music backgroundMusic;

    sf::Font font;
    sf::Font font_game_over;
    sf::Font font_congratulations;
    sf::Font font_restart;   
    sf::Text scoreText;  

    int score; 

    void initializeEnemies();  

    void processEvents();
    void update(float deltaTime);
    void render();  /*Pour dessiner les objets a l'ecran*/
    void restartGame();
    void checkCollisions();
    void restartIfRequested();
    void destroyCollidedBullets(const std::vector<bool>& collisions);
};
