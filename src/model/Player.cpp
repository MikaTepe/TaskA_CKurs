#include "Player.hpp"
#include <stdexcept>

// Konstruktor: Textur laden, Sprite konfigurieren, Startposition setzen
Player::Player()
    : texture(), sprite(texture), position(300.f, 0.f), horizontalDirection(HorizontalDirection::None), verticalDirection(VerticalDirection::None)
{
    if (!texture.loadFromFile("assets/images/spritesheet_bread.png"))
        throw std::invalid_argument("Spritesheet nicht gefunden");

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {100, 100}));
    sprite.setOrigin({50, 100});
    sprite.setPosition(position);
}

// Setzt neue Position und aktualisiert das Sprite
void Player::setPosition(const sf::Vector2f &pos)
{
    position = pos;
    sprite.setPosition(pos);
}
// Gibt die aktuelle Position zurück
sf::Vector2f Player::getPosition() const
{
    return position;
}

// Setzt horizontale Bewegungsrichtung
void Player::setHorizontalDirection(HorizontalDirection dir)
{
    horizontalDirection = dir;
}
// Liefert horizontale Bewegungsrichtung
HorizontalDirection Player::getHorizontalDirection() const
{
    return horizontalDirection;
}

// Setzt vertikale Bewegungsrichtung
void Player::setVerticalDirection(VerticalDirection dir)
{
    verticalDirection = dir;
}
// Liefert vertikale Bewegungsrichtung
VerticalDirection Player::getVerticalDirection() const
{
    return verticalDirection;
}

// Gibt das Sprite für das Rendering zurück
const sf::Sprite &Player::get_sprite() const
{
    return sprite;
}
