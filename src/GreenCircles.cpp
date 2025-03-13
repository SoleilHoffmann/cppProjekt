#include "GreenCircles.h"

GreenCircle::GreenCircle(float radius, const sf::Vector2f& position, int value, bool type)
    : value(value), type(type) {
        circle.setRadius(radius);
        circle.setPosition(position);
        circle.setOrigin(sf::Vector2f(radius,radius));
        gemTextureLoaded = gem1Texture.loadFromFile("gem.png");
        heartTextureLoaded = heartTexture.loadFromFile("heart.png");
}

float GreenCircle::getRadius() const {
    return circle.getRadius();
}

sf::Vector2f GreenCircle::getPosition() const {
    return circle.getPosition();
}

int GreenCircle::getValue() const {
    return value;
}

bool GreenCircle::getType() const {
    return type;
}

bool GreenCircle::collision(sf::CircleShape playerCircle) const {
    float dx = playerCircle.getPosition().x - circle.getPosition().x;
    float dy = playerCircle.getPosition().y - circle.getPosition().y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance <= (playerCircle.getRadius() + circle.getRadius());
}

void GreenCircle::draw(sf::RenderWindow& window, sf::Font font) {
    if(type == true){
        if(heartTextureLoaded){
            sf::Sprite heart1(heartTexture);
            heart1.setScale(sf::Vector2(circle.getRadius()/140, circle.getRadius()/131));
            heart1.setPosition(sf::Vector2(circle.getPosition().x - circle.getRadius(), circle.getPosition().y - circle.getRadius()));
            window.draw(heart1);
        } else {
            window.draw(circle);
        }
    } else {
        if(gemTextureLoaded){
            sf::Sprite gem1(gem1Texture);

            sf::Text greenText(font);
            greenText.setFillColor(sf::Color::Black);

            gem1.setScale(sf::Vector2(circle.getRadius()/212, circle.getRadius()/212));
            gem1.setPosition(sf::Vector2(circle.getPosition().x - circle.getRadius(), circle.getPosition().y - circle.getRadius()));
            window.draw(gem1);

            greenText.setString(std::to_string(value));
            greenText.setCharacterSize(circle.getRadius());
            greenText.setPosition(sf::Vector2(circle.getPosition().x - greenText.getCharacterSize()/2, circle.getPosition().y - greenText.getCharacterSize()/2));
            window.draw(greenText);
        } else {
            window.draw(circle);
        }
    }
}

void GreenCircle::shrink() {
    float newRadius;
    if(circle.getRadius() > 0){
        if(type == true){
            newRadius = circle.getRadius() - 0.05f;
        } else {
            newRadius = circle.getRadius() - value/1000.f;
        }
    } else {
        newRadius = 0;
    }
    circle.setRadius(newRadius);
    circle.setOrigin(sf::Vector2f(newRadius, newRadius));
}

bool GreenCircle::isExpired() const {
    return circle.getRadius() <= 0;
}