#ifndef PLAYERCONTROL_HPP
#define PLAYERCONTROL_HPP

#include <SFML/Window.hpp>   // sf::Keyboard::Key
#include <SFML/System.hpp>   // sf::Vector2f
#include <SFML/Graphics.hpp> // sf::FloatRect
#include "../model/Player.hpp"
#include "../view/Layer.hpp"
#include "../model/Platform.hpp"

/// Steuerungsklasse für die Spielfigur
class PlayerControl
{
public:
    PlayerControl(Layer &layer);

    void update_player(float elapsed_time);
    void draw_player();
    bool collides_with(const Platform &platform) const;
    void start_jump();
    void on_key_pressed(sf::Keyboard::Key key);
    void on_key_released(sf::Keyboard::Key key);
    float get_height() const;

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &pos);
    sf::FloatRect getBounds() const;
    VerticalDirection getVerticalDirection() const;
    void stop_jump();

    // Direktes Setzen der vertikalen Geschwindigkeit
    void setVelocityY(float v);

private:
    Player player;       ///< Modell der Spielfigur
    Layer &layer;        ///< Zeichen-Ebene
    float velocityY = 0; ///< Aktuelle vertikale Geschwindigkeit

    static constexpr float GRAVITY = 1000.f;
    static constexpr float JUMP_SPEED = 400.f;
};

#endif // PLAYERCONTROL_HPP#