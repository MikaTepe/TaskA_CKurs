#include "PlayerControl.hpp"
#include <SFML/Graphics.hpp>

PlayerControl::PlayerControl(Layer &layer)
    : layer(layer)
{
}

void PlayerControl::update_player(float dt)
{
    // 1) Gravitation anwenden
    velocityY += GRAVITY * dt;

    // 2) Position aktualisieren
    sf::Vector2f pos = player.getPosition();
    pos.y += velocityY * dt;

    // Richtungs-Flag setzen
    if (velocityY < 0)
        player.setVerticalDirection(VerticalDirection::Up);
    else if (velocityY > 0)
        player.setVerticalDirection(VerticalDirection::Down);
    else
        player.setVerticalDirection(VerticalDirection::None);

    // 3) Horizontale Bewegung
    if (player.getHorizontalDirection() == HorizontalDirection::Left)
        pos.x -= 200.f * dt;
    else if (player.getHorizontalDirection() == HorizontalDirection::Right)
        pos.x += 200.f * dt;

    player.setPosition(pos);
}

void PlayerControl::draw_player()
{
    layer.add_to_layer(player.get_sprite());
}

bool PlayerControl::collides_with(const Platform &platform) const
{
    auto bp = player.get_sprite().getGlobalBounds();
    auto pf = platform.get_shape().getGlobalBounds();
    return bp.findIntersection(pf).has_value();
}

void PlayerControl::start_jump()
{
    if (player.getVerticalDirection() == VerticalDirection::None)
    {
        velocityY = -JUMP_SPEED;
        player.setVerticalDirection(VerticalDirection::Up);
    }
}

void PlayerControl::on_key_pressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Key::Left)
        player.setHorizontalDirection(HorizontalDirection::Left);
    else if (key == sf::Keyboard::Key::Right)
        player.setHorizontalDirection(HorizontalDirection::Right);
}

void PlayerControl::on_key_released(sf::Keyboard::Key key)
{
    if ((key == sf::Keyboard::Key::Left && player.getHorizontalDirection() == HorizontalDirection::Left) ||
        (key == sf::Keyboard::Key::Right && player.getHorizontalDirection() == HorizontalDirection::Right))
    {
        player.setHorizontalDirection(HorizontalDirection::None);
    }
}

float PlayerControl::get_height() const
{
    return player.getPosition().y;
}

sf::Vector2f PlayerControl::getPosition() const
{
    return player.getPosition();
}

void PlayerControl::setPosition(const sf::Vector2f &pos)
{
    player.setPosition(pos);
}

sf::FloatRect PlayerControl::getBounds() const
{
    return player.get_sprite().getGlobalBounds();
}

VerticalDirection PlayerControl::getVerticalDirection() const
{
    return player.getVerticalDirection();
}

void PlayerControl::stop_jump()
{
    player.setVerticalDirection(VerticalDirection::None);
    velocityY = 0.f;
}

void PlayerControl::setVelocityY(float v)
{
    velocityY = v;
}