#include <SFML/Graphics.hpp>


//Green Circles (Gems)
class GreenCircle {
private:
sf::CircleShape circle;
int value;
bool type; //true heißt es ist ein herz


public:
GreenCircle(float radius, const sf::Vector2f& position, int value, bool type)
: value(value), type(type) {
circle.setRadius(radius);
circle.setPosition(position);
circle.setOrigin(sf::Vector2f(radius,radius)); 
}


float getRadius() const {
    return circle.getRadius();
}

sf::Vector2f getPosition() const {
    return circle.getPosition();
}

int getValue() const {
    return value;
}

bool getType() const {
    return type;   
}


bool collision(sf::CircleShape playerCircle) {
    float dx = playerCircle.getPosition().x - circle.getPosition().x;
    float dy = playerCircle.getPosition().y - circle.getPosition().y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= (playerCircle.getRadius() + circle.getRadius());
}

void draw(sf::RenderWindow& window) {
    window.draw(circle);
}

void shrink() {
    float newRadius;
    if(circle.getRadius() > 0){
        if(type==true){
            newRadius = circle.getRadius() - 0.05f;
        }else{
            newRadius = circle.getRadius() - value/1000.f;
        }
        
    } else {
        newRadius=0;
    }
    circle.setRadius(newRadius);
    circle.setOrigin(sf::Vector2f(newRadius, newRadius));
}

bool isExpired() const {
return circle.getRadius() <= 0;
}
};
