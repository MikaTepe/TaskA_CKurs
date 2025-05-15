#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


// model class for player character
class Player {

public:
    // constructor, initializes sprite
    Player();
   
    // TODO declaration of additional methods

    // returns the sprite depicting the character
    const sf::Sprite &get_sprite() const;

private:

    sf::Texture texture;

    sf::Sprite sprite;
};

#endif