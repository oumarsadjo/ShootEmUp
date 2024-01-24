// Player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
public:
    const std::vector<sf::RectangleShape>& getBullets() const;
    Player(float initialX, float initialY);

    void bulletPlayer();
    void moveLeft();
    void moveRight();
    void destroyBullet(std::size_t index);

    void update(float deltaTime);
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void shoot();

private:
    sf::Texture texture;
    sf::Texture bullet_texture;
    sf::Sprite bulletSprite;
    sf::Sprite playerSprite;
    float speed;

    std::vector<sf::RectangleShape> bullets;
};

#endif // PLAYER_HPP
