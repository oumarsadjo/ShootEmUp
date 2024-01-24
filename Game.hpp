// Game.hpp

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

    sf::Font font;  // Nouvelle fonte pour le texte du score
    sf::Text scoreText;  // Nouveau texte pour afficher le score

    int score;  // Nouvelle variable pour stocker le score

    void initializeEnemies();  // Nouvelle fonction pour initialiser les ennemis

    void processEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void destroyCollidedBullets(const std::vector<bool>& collisions);
};
