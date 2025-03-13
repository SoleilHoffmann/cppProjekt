#include <SFML/Graphics.hpp>

///Red Circles (enemies)
class RedCircle {
private:
sf::CircleShape circle;
sf::Vector2f direction;
bool type;



public:
RedCircle(float radius, sf::Vector2f& position, sf::Vector2f& direction)
: direction(direction){
circle.setRadius(radius);
circle.setPosition(position);
circle.setOrigin(sf::Vector2f(radius,radius)); 
circle.setFillColor(sf::Color::White);
}


bool collision(sf::CircleShape playerCircle) {
    float dx = playerCircle.getPosition().x - circle.getPosition().x;
    float dy = playerCircle.getPosition().y - circle.getPosition().y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= (playerCircle.getRadius() + circle.getRadius());
}

void move() {
    sf::Vector2f newPosition;
    newPosition = circle.getPosition() + direction;
    circle.setPosition(newPosition);
}

void draw(sf::RenderWindow& window) {
    window.draw(circle);
}

bool isFarAway(sf::RenderWindow& window) const {
    return (circle.getPosition().x > window.getSize().x + 100 || circle.getPosition().x <  - 100 || circle.getPosition().y > window.getSize().y + 100 || circle.getPosition().y <  - 100) ;
}

float getRadius() const {
    return circle.getRadius();
}

sf::Vector2f getPosition() const {
    return circle.getPosition();
}

};

