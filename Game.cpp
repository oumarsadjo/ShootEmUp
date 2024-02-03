/* Game.hpp
{=========================================================}
{===== Fichier de l'implementation de la class Game ======}
{=========================================================}
*/

#include "Game.hpp"
#include "Global.hpp"
#include "Player.hpp"
#include <iostream>

/* 1.Le constructeur de la class Game
{=========================================================}
{= Il initialise:la fenêtre, le joueur, les ennemis, les =}
{= ressources en créant l'environnement du jeu ShootEmUp =}
{=========================================================}
*/

Game::Game() : window(sf::VideoMode(WIN_LARGEUR, WIN_HAUTEUR), "ShootEmUp 2D - POO Project"),
               player(400, 600 - 35),
               enemies(NUM_ENEMIES),
               enemiesDestroyed(false),
               score(0)
{
    if (!backgroundTexture.loadFromFile("../Scr/background_2d.jpg")) {
        std::cout << "Erreur lors du chargement de la texture du fond." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    initializeEnemies();

    if (!font.loadFromFile("../Scr/score.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }

    if (!font_game_over.loadFromFile("../Scr/game_over.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }

        if (!font_congratulations.loadFromFile("../Scr/congratulations.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }
        if (!font_restart.loadFromFile("../Scr/restart_fonct.ttf")) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(WIN_LARGEUR - 120, 10);

        if (!collisionSoundBuffer.loadFromFile("../Scr/collision.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio." << std::endl;
    }
    collisionSound.setBuffer(collisionSoundBuffer);

    if (!gameOverSoundBuffer.loadFromFile("../Scr/gameOver.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio de game over." << std::endl;
    }
    gameOverSound.setBuffer(gameOverSoundBuffer);

    if (!congratsSoundBuffer.loadFromFile("../Scr/congratulations.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio de félicitations." << std::endl;
    }
    congratsSound.setBuffer(congratsSoundBuffer);


    if (!backgroundMusic.openFromFile("../Scr/music.ogg")) {
        std::cout << "Erreur lors du chargement du fichier audio de fond." << std::endl;
    }
    backgroundMusic.setLoop(true);  
    backgroundMusic.play();
}

/* 2.La methode initializeEnemies() de la class Game
{=========================================================}
{= Elle initialise les ennemis, en fonction du nombre des=}
{=enemis souhaites, modifiable dans le fichier Global.hpp=}
{=========================================================}
*/

void Game::initializeEnemies() {
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        enemies.push_back(Enemy());
    }
}

/* 3.La methode run() de la class Game
{=========================================================}
{= Elle permet de faire tourner les differentes methodes =}
{= responsables des evenements et le dessigner les objets=}
{=========================================================}
*/

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

/* 4.La methode processEvents() de la class Game
{=========================================================}
{= Elle est responsables des evenements du jeux ShootEmUp=}
{=========================================================}
*/

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

/* 5.La methode restartGame() de la class Game
{=========================================================}
{======= Elle est responsable reinitialiser le jeux ======}
{=========================================================}
*/

void Game::restartGame() {
    // Réinitialiser les variables du jeu
    gameOverFlag = false;
    score = 0;

    player.reset();

    initializeEnemies();
}

/* 6.La methode update(float deltaTime) de la class Game
{=========================================================}
{======= Elle est responsable la mise-a-jour du jeux =====}
{=========================================================}
*/

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

/* 7.La methode gameOver() de la class Game
{==========================================================}
{Arreter le jeux si les enemis arrivenet au fond de l'ecran}
{==========================================================}
*/

void Game::gameOver() {
    // Faire jouer le son du GameOver
    gameOverSound.play();

    // Afficher "GAME OVER" 
    sf::Text gameOverText("GAME OVER", font_game_over, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(WIN_LARGEUR / 2 - 150, WIN_HAUTEUR / 2 - 25);

    window.clear();
    window.draw(gameOverText);
    window.display();

    sf::sleep(sf::seconds(3));

    sf::sleep(sf::seconds(1));
    
    sf::Text restartText("Appuyez sur R pour rejouer, ou sur X pour quitter", font_restart, 20);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(WIN_LARGEUR / 2 - 250, WIN_HAUTEUR / 2 + 50);
    window.draw(restartText);
    window.display();

    // Attendre les touches R ou X pour relancer ou arreter le jeu
    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                initializeEnemies();
                restartGame();
                return;
            } else if (event.key.code == sf::Keyboard::X) {
                window.close();
                return;
            }
        }
    }
}

/* 8.La methode congratulations() de la class Game
{==========================================================}
{Verifier si tous les enemis sont detruis et arreter le jeu}
{==========================================================}
*/

void Game::congratulations() {
    // Son pour les félicitations
    congratsSound.play();

    // Afficher "FÉLICITATIONS" et attendre 3 secondes
    sf::Text congratsText("***** CONGRATULATIONS *****", font_congratulations, 50);
    congratsText.setFillColor(sf::Color::Green);

    // Gestion de la position du Texte
    sf::FloatRect textBounds = congratsText.getGlobalBounds();
    float xPos = (WIN_LARGEUR - textBounds.width) / 2;
    float yPos = (WIN_HAUTEUR - textBounds.height) / 2;
    congratsText.setPosition(xPos, yPos);

    sf::Clock clock;

    while (clock.getElapsedTime().asSeconds() < 3) {
        processEvents();
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

    sf::Text restartText("Appuyez sur R pour rejouer, ou sur X pour quitter", font_restart, 20);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(WIN_LARGEUR / 2 - 250, WIN_HAUTEUR / 2 + 50);
    window.draw(restartText);
    window.display();

    // Attendre les touches R ou X pour relancer ou arreter le jeu
    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                restartGame();
                return;
            } else if (event.key.code == sf::Keyboard::X) {
                window.close();
                return;
            }
        }
    }
}

/* 9.La methode checkCollisions() de la class Game
{==========================================================}
{== Verifier si les balles et les enemis se sont touches ==}
{==========================================================}
*/

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
                    score += 1;  // Mettre à jour le score ici
                    player.destroyBullet(i);

                    // Faire joueur le son du collision a chaque collision
                    collisionSound.play();

                    return;
                }
            }
        }
    }
}

/* 10.La methode destroyCollidedBullets(const std::vector<bool>& collisions)
{==========================================================}
{==Pour faire disparaitre les balles apres une collision ==}
{==========================================================}
*/

void Game::destroyCollidedBullets(const std::vector<bool>& collisions) {
    auto& playerBullets = player.getBullets();

    for (std::size_t i = 0; i < collisions.size(); ++i) {
        if (collisions[i]) {
            player.destroyBullet(i);
        }
    }
}

/* 11.La methode render() de la class Game
{==========================================================}
{== Pour dessiner les differents objets --> rendu du design}
{==========================================================}
*/

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
    window.draw(player.getSprite());

    for (const auto& enemy : enemies) {
        if (!enemy.isDestroyed()) {
            window.draw(enemy.getSprite());
        }
    }

    /* Dessiner le texte du score */
    window.draw(scoreText);

    const std::vector<sf::RectangleShape>& playerBullets = player.getBullets();
    for (const auto& bullet : playerBullets) {
        window.draw(bullet);
    }
    window.display();
}