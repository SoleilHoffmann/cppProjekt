
#ifndef GREENCIRCLE_H
#define GREENCIRCLE_H

#include <SFML/Graphics.hpp>
#include <cmath>

class GreenCircle {
private:
sf::CircleShape circle;
int value;
bool type; // true means it's a heart

sf::Texture gem1Texture;
sf::Texture heartTexture;

bool gemTextureLoaded;
bool heartTextureLoaded;

public:
GreenCircle(float radius, const sf::Vector2f& position, int value, bool type);

float getRadius() const;
sf::Vector2f getPosition() const;
int getValue() const;
bool getType() const;
bool collision(sf::CircleShape playerCircle) const;
void draw(sf::RenderWindow& window, sf::Font font);
void shrink();
bool isExpired() const;
};

#endif // GREENCIRCLE_H