// Game.cpp

#include "Game.hpp"
#include "Global.hpp"
#include "Player.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(WIN_LARGEUR, WIN_HAUTEUR), "Fond avec Personnage SFML"),
               player(400, 600 - 25),
               enemies(NUM_ENEMIES),
               enemiesDestroyed(false),
               score(0)
{
    if (!backgroundTexture.loadFromFile("../Photos/Background.png")) {
        std::cout << "Erreur lors du chargement de la texture du fond." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    initializeEnemies();  // Appel de la fonction pour initialiser les ennemis

    // Initialiser la police et le texte du score
    if (!font.loadFromFile("../Photos/score.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(WIN_LARGEUR - 120, 10);  // Position en haut à droite

    // Le son pour la collision
        if (!collisionSoundBuffer.loadFromFile("../Photos/collision.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio." << std::endl;
    }
    collisionSound.setBuffer(collisionSoundBuffer);

    if (!gameOverSoundBuffer.loadFromFile("../Photos/gameOver.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio de game over." << std::endl;
    }
    gameOverSound.setBuffer(gameOverSoundBuffer);

    if (!congratsSoundBuffer.loadFromFile("../Photos/congratulations.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio de félicitations." << std::endl;
    }
    congratsSound.setBuffer(congratsSoundBuffer);
}

void Game::initializeEnemies() {
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        enemies.push_back(Enemy());
    }
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                player.moveLeft();
            } else if (event.key.code == sf::Keyboard::Right) {
                player.moveRight();
            } else if (event.key.code == sf::Keyboard::S) {
                player.shoot();
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (!gameOverFlag) {
        player.update(deltaTime);

        for (auto& enemy : enemies) {
            enemy.update(deltaTime);

            // Vérifier si un ennemi atteint le bas de l'écran
            if (enemy.getSprite().getPosition().y > WIN_HAUTEUR) {
                gameOver();
                return;  // Sortir de la fonction dès que le "GAME OVER" est affiché
            }
        }

        checkCollisions();

        // Vérifier si tous les ennemis sont détruits
        if (std::all_of(enemies.begin(), enemies.end(), [](const Enemy& e) { return e.isDestroyed(); })) {
            congratulations();
            return;  // Sortir de la fonction dès que "FÉLICITATIONS" est affiché
        }

        if (enemiesDestroyed) {
            score += 1;
            enemiesDestroyed = false;
        }

        scoreText.setString("Score:" + std::to_string(score));
    }
}

void Game::gameOver() {
    // Faire jouer le son
    gameOverSound.play();

    // Afficher "GAME OVER" et fermer la fenêtre du jeu
    sf::Text gameOverText("GAME OVER", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(WIN_LARGEUR / 2 - 150, WIN_HAUTEUR / 2 - 25);

    window.clear();
    window.draw(gameOverText);
    window.display();

    // Attente pour afficher "GAME OVER" pendant quelques secondes
    sf::sleep(sf::seconds(3));

    // Nouvelle attente pour laisser le texte affiché avant de fermer la fenêtre
    sf::sleep(sf::seconds(1));

    window.close();
    gameOverFlag = true;
}


void Game::congratulations() {
    // Son pour les félicitations
    congratsSound.play();

    // Afficher "FÉLICITATIONS" et attendre 3 secondes
    sf::Text congratsText("**** CONGRATULATIONS ****", font, 50);
    congratsText.setFillColor(sf::Color::Green);

    // Calculate the position to center the text
    sf::FloatRect textBounds = congratsText.getGlobalBounds();
    float xPos = (WIN_LARGEUR - textBounds.width) / 2;
    float yPos = (WIN_HAUTEUR - textBounds.height) / 2;

    congratsText.setPosition(xPos, yPos);


    sf::Clock clock;

    while (clock.getElapsedTime().asSeconds() < 3) {
        processEvents();  // Process events to keep the window responsive

        window.clear();
        window.draw(backgroundSprite);
        window.draw(player.getSprite());

        for (const auto& enemy : enemies) {
            if (!enemy.isDestroyed()) {
                window.draw(enemy.getSprite());
            }
        }

        // Dessiner le texte du score
        window.draw(scoreText);

        window.draw(congratsText);
        window.display();
    }

    window.close();
    gameOverFlag = true;
}




void Game::checkCollisions() {
    const std::vector<sf::RectangleShape>& playerBullets = player.getBullets();

    for (std::size_t i = 0; i < playerBullets.size(); ++i) {
        const sf::RectangleShape& bullet = playerBullets[i];

        for (auto& enemy : enemies) {
            if (!enemy.isDestroyed()) {
                sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();
                sf::FloatRect bulletBounds = bullet.getGlobalBounds();

                if (bulletBounds.intersects(enemyBounds)) {
                    enemy.setDestroyed(true);
                    score += 1;  // Mettez à jour le score ici
                    player.destroyBullet(i);

                    // Play the collision sound
                    collisionSound.play();

                    return;  // Sortez de la fonction dès qu'une collision est détectée
                }
            }
        }
    }
}



void Game::destroyCollidedBullets(const std::vector<bool>& collisions) {
    auto& playerBullets = player.getBullets();

    for (std::size_t i = 0; i < collisions.size(); ++i) {
        if (collisions[i]) {
            player.destroyBullet(i);
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
    window.draw(player.getSprite());

    for (const auto& enemy : enemies) {
        if (!enemy.isDestroyed()) {
            window.draw(enemy.getSprite());
        }
    }

    // Dessiner le texte du score
    window.draw(scoreText);

    const std::vector<sf::RectangleShape>& playerBullets = player.getBullets();
    for (const auto& bullet : playerBullets) {
        window.draw(bullet);
    }
    window.display();
}
