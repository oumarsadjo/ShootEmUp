/* Player.hpp
{=========================================================}
{==== Ce fichier contient methodes/attributs du Joueur ===}
{=========================================================}
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
public:
    const std::vector<sf::RectangleShape>& getBullets() const;
    Player(float initialX, float initialY);

    void bulletPlayer();
    void moveLeft();
    void moveRight();
    
    /*Pour faire disparaitre les balles*/
    void destroyBullet(std::size_t index);

    void update(float deltaTime);
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void shoot();
    void reset();

private:
    sf::Texture texture;
    sf::Texture bullet_texture;
    sf::Sprite bulletSprite;
    sf::Sprite playerSprite;
    float speed;

    std::vector<sf::RectangleShape> bullets;
};
