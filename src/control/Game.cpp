#include "Game.hpp"
#include <SFML/Window.hpp>   // sf::Event, sf::Keyboard
#include <SFML/Graphics.hpp> // sf::View, sf::Rect, Shapes, Sprites, etc.

Game::Game()
    : window(sf::VideoMode(sf::Vector2u{600u, 600u}), "Spiel mit Plattformen"),
      view(sf::FloatRect({0.f, -600.f}, {600.f, 600.f})),
      game_layer(window),
      player_control(game_layer)
{
    window.setFramerateLimit(60);
    game_layer.set_view(view);

    // Plattformen initialisieren (Koordinaten im invertierten Y-System)
    platforms.emplace_back(sf::Vector2f{100.f, -60.f});
    platforms.emplace_back(sf::Vector2f{250.f, -160.f});
    platforms.emplace_back(sf::Vector2f{400.f, -240.f});
}

void Game::start()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        // Input-Handling
        while (auto eventOpt = window.pollEvent())
        {
            const sf::Event &event = *eventOpt;
            if (event.is<sf::Event::Closed>())
            {
                window.close();
                break;
            }
            if (event.is<sf::Event::KeyPressed>())
            {
                auto kp = event.getIf<sf::Event::KeyPressed>();
                player_control.on_key_pressed(kp->code);
            }
            if (event.is<sf::Event::KeyReleased>())
            {
                auto kr = event.getIf<sf::Event::KeyReleased>();
                player_control.on_key_released(kr->code);
            }
        }

        update(dt);
        draw();
    }
}

void Game::update(float dt)
{
    // 1) Alte Position zwischenspeichern
    sf::Vector2f oldPos = player_control.getPosition();

    // 2) Sprung-Start: nur wenn nicht in der Luft
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
        player_control.getVerticalDirection() == VerticalDirection::None)
    {
        player_control.start_jump();
    }

    // 3) Bewegung & Gravitation
    player_control.update_player(dt);

    // 4) Boden-Kollision (y=0)
    {
        auto pos = player_control.getPosition();
        if (player_control.getVerticalDirection() == VerticalDirection::Down && pos.y > 0.f)
        {
            pos.y = 0.f;
            player_control.setPosition(pos);
            player_control.stop_jump();
            player_control.setVelocityY(0.f);
            return; // Weitere Kollisionsprüfungen überspringen
        }
    }

    // 5) Plattform-Kollision: nur echte Überkreuzung von oben
    for (auto &platform : platforms)
    {
        if (player_control.getVerticalDirection() != VerticalDirection::Down)
            continue;

        // 5.1) Aktuelle Position
        sf::Vector2f pos = player_control.getPosition();

        // 5.2) Roh-Bounds (Offset + Größe)
        auto rawPb = player_control.getBounds();
        float pbLeft = pos.x + rawPb.position.x;
        float pbTop = pos.y + rawPb.position.y;
        float pbRight = pbLeft + rawPb.size.x;
        float pbBottom = pbTop + rawPb.size.y;

        // 5.3) Alte Boden-Koordinate (ebenfalls mit Offset)
        float oldBottom = oldPos.y + rawPb.position.y + rawPb.size.y;

        // 5.4) Plattform-Daten
        auto &shape = platform.get_shape();
        sf::Vector2f pp = shape.getPosition();
        sf::Vector2f ps = shape.getSize();
        float platLeft = pp.x;
        float platRight = pp.x + ps.x;
        float platTop = pp.y;

        // 5.5) Vertikale Prüfung: vorher oberhalb, jetzt unterhalb
        if (oldBottom > platTop)
            continue;
        if (pbBottom < platTop)
            continue;

        // 5.6) Horizontale Überlappung
        if (pbRight <= platLeft ||
            pbLeft >= platRight)
            continue;

        // 5.7) Landung: Y-Position korrigieren
        sf::Vector2f newPos = pos;
        newPos.y = platTop - rawPb.position.y - rawPb.size.y;
        player_control.setPosition(newPos);
        player_control.stop_jump();
        player_control.setVelocityY(0.f);

        break; // nur eine Plattform pro Frame erwischen
    }

    // 6) Kamera folgt der Spielfigur (sanft mit Offset)
    float playerY = player_control.get_height();
    sf::Vector2f center = view.getCenter();
    if (playerY < center.y - 50.f)
    {
        center.y = playerY + 50.f;
        view.setCenter(center);
        game_layer.set_view(view);
    }
}

void Game::draw()
{
    window.clear();
    game_layer.clear();

    // Plattformen zeichnen
    for (auto &platform : platforms)
        game_layer.add_to_layer(platform.get_shape());

    // Spielfigur zeichnen
    player_control.draw_player();

    game_layer.draw();
    window.display();
}