#include "../include/Game.h"
#include <iostream>

#include "Player.h"

Game::Game() 
    : currentState_(GameState::Menu)
    , timeStep_(1.0f/60.0f)
    , velocityIterations_(8)
    , positionIterations_(3)
{
    // Create the window
    window_.create(sf::VideoMode::getDesktopMode(), "Game", sf::Style::Fullscreen);
    window_.setMouseCursorVisible(false);

    // Initialize Box2D world
    b2Vec2 gravity(0.0f, 9.81f);
    world_ = std::make_unique<b2World>(gravity);

    player_.createBody(*world_, *player_.getBodyDef());
    world_->CreateBody(player_.getBodyDef().get());
    // Initialize game view
    gameView_.reset(sf::FloatRect(0, 0, window_.getSize().x, window_.getSize().y));

    initMenu();
}

Game::~Game() = default;

void Game::initMenu() {
    // Load font
    if (!font_.loadFromFile("Font/troika.otf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Setup title text
    titleText_.setFont(font_);
    titleText_.setString(L"Апокалипсис");
    titleText_.setCharacterSize(150);
    titleText_.setFillColor(sf::Color(237, 147, 0));
    titleText_.setOutlineThickness(3);
    titleText_.setPosition(480, 50);

    // Setup menu background
    menuBackground_.setSize(sf::Vector2f(window_.getSize()));
    if (!menuBackgroundTexture_.loadFromFile("Image/destroyed_city.jpg")) {
        throw std::runtime_error("Failed to load menu background");
    }
    menuBackground_.setTexture(&menuBackgroundTexture_);

    // Setup menu
    std::vector<sf::String> menuItems = {
        L"Играть",
        L"Продолжить",
        L"О игре",
        L"Выход"
    };
    menu_ = std::make_unique<game::GameMenu>(window_, 950, 350, menuItems, 100, 120);
    menu_->set_color_text_menu(sf::Color(237,147,0), sf::Color::Red, sf::Color::Black);
    menu_->Allign_menu(2);
}

void Game::run() {
    sf::Clock clock;
    
    while (window_.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (currentState_ == GameState::Playing) {
                    currentState_ = GameState::Menu;
                } else {
                    window_.close();
                }
            }

            if (currentState_ == GameState::Menu) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    menu_->move_up();
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    menu_->move_down();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    handleMenuSelection();
                }
            }
        }
    }
}

void Game::handleMenuSelection() {
    switch (menu_->get_select_menu_number()) {
        case 0: // Play
            startLevel();
            currentState_ = GameState::Playing;
            break;
        case 1: // Continue
            if (level_) {
                currentState_ = GameState::Playing;
            }
            break;
        case 2: // About
            // Implement about screen
            break;
        case 3: // Exit
            window_.close();
            break;
    }
}

void Game::startLevel() {
    level_ = std::make_unique<Level>();
    if (!level_->loadFromFile("Image/level1.xml", *world_)) {
        throw std::runtime_error("Failed to load level");
    }
}

void Game::update(float deltaTime) {
    if (currentState_ == GameState::Playing) {
        world_->Step(timeStep_, velocityIterations_, positionIterations_);
        player_.update(deltaTime);
        // Update game logic here
    }
}

void Game::render() {
    window_.clear();

    if (currentState_ == GameState::Menu) {
        window_.draw(menuBackground_);
        window_.draw(titleText_);
        menu_->draw();
    }
    else if (currentState_ == GameState::Playing && level_) {
        level_->render(window_);
        player_.render(window_); // Рендеринг игрока
    }

    window_.display();
}
