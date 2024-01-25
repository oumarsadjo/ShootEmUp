/* Player.hpp
{=========================================================}
{===== Fichier de l'implementation de la class Player ====}
{=========================================================}
*/

#include "Player.hpp"
#include "Global.hpp"
#include <iostream>

Player::Player(float initialX, float initialY) {
    if (!texture.loadFromFile("../Scr/player.png")) {
        std::cerr << "Erreur lors du chargement de la texture du joueur." << std::endl;
    }

    if (!bullet_texture.loadFromFile("../Scr/PlayerBullet.png")) {
        std::cerr << "Erreur lors du chargement de la texture de la balle du joueur." << std::endl;
    }

    playerSprite.setTexture(texture);
    playerSprite.setPosition(initialX, initialY);
    speed = 27.0f;
}

void Player::moveLeft() {
    if (playerSprite.getPosition().x > 0) {
        playerSprite.move(-speed, 0.0f);
    }
}

void Player::moveRight() {
    if (playerSprite.getPosition().x < WIN_LARGEUR - 22) {
        playerSprite.move(speed, 0.0f);
    }
}

const std::vector<sf::RectangleShape>& Player::getBullets() const {
    return bullets;
}

void Player::bulletPlayer() {
    sf::RectangleShape bullet;
    bullet.setSize(sf::Vector2f(50.0f, 50.0f));
    bullet.setTexture(&bullet_texture);

    float playerMidX = playerSprite.getPosition().x + playerSprite.getLocalBounds().width / 2.0f;
    float playerTopY = playerSprite.getPosition().y;
    float offsetY = -20.0f;
    bullet.setPosition(playerMidX - bullet.getLocalBounds().width / 2.0f, playerTopY + offsetY);

    bullets.push_back(bullet);
}

void Player::destroyBullet(std::size_t index) {
    if (index < bullets.size()) {
        bullets.erase(bullets.begin() + index);
    }
}

void Player::update(float deltaTime) {
    for (auto& bullet : bullets) {
        bullet.move(0.0f, -20.0f * speed * deltaTime);
    }
}

sf::Sprite& Player::getSprite() {
    return playerSprite;
}

sf::Vector2f Player::getPosition() const {
    return playerSprite.getPosition();
}

void Player::shoot() {
    bulletPlayer();
}

void Player::reset() {
    playerSprite.setPosition(400, 600 - 25);
}
