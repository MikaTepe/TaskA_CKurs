#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

// Enum-Klassen für Bewegungsrichtungen
// None = keine Bewegung, Left/Up = negative Richtung, Right/Down = positive Richtung
enum class HorizontalDirection
{
    None = 0,
    Left = -1,
    Right = 1
};

enum class VerticalDirection
{
    None = 0,
    Up = -1,
    Down = 1
};

// Modellklasse für die Spielfigur
class Player
{
public:
    Player(); // Konstruktor

    // Positions-Methoden
    void setPosition(const sf::Vector2f &pos);
    sf::Vector2f getPosition() const;

    // Richtungs-Methoden
    void setHorizontalDirection(HorizontalDirection dir);
    HorizontalDirection getHorizontalDirection() const;
    void setVerticalDirection(VerticalDirection dir);
    VerticalDirection getVerticalDirection() const;

    // Sprite-Zugriff
    const sf::Sprite &get_sprite() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    HorizontalDirection horizontalDirection = HorizontalDirection::None;
    VerticalDirection verticalDirection = VerticalDirection::None;
};

#endif // PLAYER_H