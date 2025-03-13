
#ifndef REDCIRCLE_H
#define REDCIRCLE_H

#include <SFML/Graphics.hpp>
#include <cmath>

class RedCircle {
private:
sf::CircleShape circle;
sf::Vector2f direction;
bool type;
sf::Texture redTexture;
bool textureLoaded;

public:
RedCircle(float radius, sf::Vector2f& position, sf::Vector2f& direction);

bool collision(sf::CircleShape playerCircle) const;
void move();
void draw(sf::RenderWindow& window);
bool isFarAway(sf::RenderWindow& window) const;
float getRadius() const;
sf::Vector2f getPosition() const;
};

#endif // REDCIRCLE_H