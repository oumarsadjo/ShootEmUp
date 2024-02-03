/* Enemy.hpp
{=========================================================}
{=== Ce fichier contient methodes/attributs des enemies ==}
{=========================================================}
*/

#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy();
    void update(float deltaTime);
    const sf::Sprite& getSprite() const;
    bool isDestroyed() const;
    void setDestroyed(bool destroyed);

private:
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    float speed;
    bool destroyed;
    /*Pour generer aleatoirement les positions des enemis dans l'ecran */
    void generateRandomPosition();
};
