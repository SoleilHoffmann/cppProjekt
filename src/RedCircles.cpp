#include "RedCircles.h"

RedCircle::RedCircle(float radius, sf::Vector2f& position, sf::Vector2f& direction)
    : direction(direction) {
    circle.setRadius(radius);
    circle.setPosition(position);
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setFillColor(sf::Color::White);
    textureLoaded = redTexture.loadFromFile("sea-urchin.png");
}

    bool RedCircle::collision(sf::CircleShape playerCircle) const {
    float dx = playerCircle.getPosition().x - circle.getPosition().x;
    float dy = playerCircle.getPosition().y - circle.getPosition().y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= (playerCircle.getRadius() + circle.getRadius());
}

void RedCircle::move() {
    sf::Vector2f newPosition = circle.getPosition() + direction;
    circle.setPosition(newPosition);
}

void RedCircle::draw(sf::RenderWindow& window) {
    if (textureLoaded) {
        sf::Sprite red1(redTexture);
        red1.setScale(sf::Vector2(circle.getRadius() / 190, circle.getRadius() / 190));
        red1.setPosition(sf::Vector2(circle.getPosition().x - 66, circle.getPosition().y - 66));
        window.draw(red1);
    } else {
        window.draw(circle);    
    }
}

bool RedCircle::isFarAway(sf::RenderWindow& window) const {
    return (circle.getPosition().x > window.getSize().x + 100 || circle.getPosition().x < -100 ||
    circle.getPosition().y > window.getSize().y + 100 || circle.getPosition().y < -100);
}

float RedCircle::getRadius() const {
    return circle.getRadius();
}

sf::Vector2f RedCircle::getPosition() const {
    return circle.getPosition();
}