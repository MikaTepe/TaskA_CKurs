#include "Game.hpp"
#include <SFML/Window/Keyboard.hpp>

Game::Game()
    : window(sf::VideoMode({600u, 600u}), "Spiel mit Plattformen"),
      view(sf::FloatRect(sf::Vector2f({0, -600}), sf::Vector2f({600, 600}))),
      game_layer(window),
      player_control(game_layer)
{
    window.setFramerateLimit(60);
    game_layer.set_view(view);

    // Plattformen initialisieren (Positionen anpassen nach Spielwelt)
    platforms.emplace_back(sf::Vector2f(100.f, -100.f));
    platforms.emplace_back(sf::Vector2f(250.f, -200.f));
    platforms.emplace_back(sf::Vector2f(400.f, -300.f));
}

void Game::start()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        if (!input())
        {
            update(elapsed.asSeconds());
            draw();
        }
    }
}

bool Game::input()
{
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
            return true;
        }
        // TODO: Weitere Eingaben (Tasten, Maus) verarbeiten
    }
    return false;
}

void Game::update(float dt)
{
    // TODO: Kollision mit Plattformen prüfen und Sprung-Logik
    player_control.update_player(dt);
}

void Game::draw()
{
    window.clear();
    game_layer.clear();

    // Plattformen zeichnen
    for (auto &platform : platforms)
    {
        game_layer.draw(platform.get_shape());
    }

    // Spielfigur zeichnen
    player_control.draw_player();

    // Alle Objekte auf die Leinwand bringen
    game_layer.draw();
    window.display();
}
