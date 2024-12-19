#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "Level.h"
#include "GameMenu.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void initMenu();
    void handleMenuSelection();
    void startLevel();

    sf::RenderWindow window_;
    std::unique_ptr<b2World> world_;
    std::unique_ptr<Level> level_;
    std::unique_ptr<game::GameMenu> menu_;
    Player player_;
    
    // Game states
    enum class GameState {
        Menu,
        Playing,
        Paused,
        GameOver
    };
    GameState currentState_;

    // Menu resources
    sf::Font font_;
    sf::Text titleText_;
    sf::RectangleShape menuBackground_;
    sf::Texture menuBackgroundTexture_;

    // Game resources
    sf::View gameView_;
    float timeStep_;
    int velocityIterations_;
    int positionIterations_;
};
