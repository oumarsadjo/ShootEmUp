// Enemy.cpp

#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy() {
    if (!enemyTexture.loadFromFile("../Photos/Enemy2.png")) {
        std::cerr << "Erreur lors du chargement de la texture de l'ennemi." << std::endl;
    } else {
        std::cout << "Texture de l'ennemi chargée avec succès." << std::endl;
    }

    enemySprite.setTexture(enemyTexture);
    generateRandomPosition();
    speed = 20.0f;
    destroyed = false;
}



void Enemy::update(float deltaTime) {
    if (!destroyed) {
        enemySprite.setTexture(enemyTexture);
        enemySprite.move(0.0f, speed * deltaTime);
    }
}

void Enemy::generateRandomPosition() {
    float randomX = static_cast<float>(rand() % 700);
    float randomY = static_cast<float>(rand() % 200);
    enemySprite.setPosition(randomX, randomY);
}

const sf::Sprite& Enemy::getSprite() const {
    return enemySprite;
}

bool Enemy::isDestroyed() const {
    return destroyed;
}

void Enemy::setDestroyed(bool destroyed) {
    this->destroyed = destroyed;
}
