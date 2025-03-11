#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>

//Circles///////////////////////////////////////////////////////////////////////////


//Green Circles////////////////
class GreenCircle {
private:
sf::CircleShape circle;
int value;
bool type;


public:
GreenCircle(float radius, const sf::Vector2f& position, int value, bool type)
: value(value), type(type) {
circle.setRadius(radius);
circle.setPosition(position);
circle.setOrigin(sf::Vector2f(radius,radius)); // Set origin to the center for better positioning
}


// Getters
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

// Draw function
void draw(sf::RenderWindow& window) {
    window.draw(circle);
}

void shrink() {
    float newRadius;
    if(circle.getRadius() > 0){
        newRadius = circle.getRadius()-value/1000.f;
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





///Red Circles (enemies)//////////////////
class RedCircle {
private:
sf::CircleShape circle;
sf::Vector2f direction;
bool type;



public:
RedCircle(float radius, sf::Vector2f& position, sf::Vector2f& direction, bool type)
: type(type), direction(direction){
circle.setRadius(radius);
circle.setPosition(position);
circle.setOrigin(sf::Vector2f(radius,radius)); // Set origin to the center for better positioning
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

};


///Random numbers///////////////

float randomFloat(float min, float max) {
static std::random_device rd;
static std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(min, max);
return dist(gen);
}


float randomGaussianFloat() {
static std::random_device rd; // Obtain a random number from hardware
static std::mt19937 gen(rd()); // Seed the generator
std::normal_distribution<float> distribution(0, 10);
return distribution(gen); // Generate a normally distributed float
}


/////////////////////////////////////////////////
/////////////////////////////////////////////////

int main() {
auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Circle Game");
window.setFramerateLimit(144);

sf::Vector2f t1(500,200);
sf::Vector2f t2(2,4);
RedCircle testRed(10.f, t1, t2, false);

sf::Font font;
if (!font.openFromFile("Chatkids.ttf")) { 
std::cerr << "Error loading font!" << std::endl;
return -1;
}

sf::Texture texture;
if (!texture.loadFromFile("gem.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
}
sf::Sprite gem1(texture);


sf::Text scoreText(font);
scoreText.setCharacterSize(25);
scoreText.setFillColor(sf::Color::White);
scoreText.setPosition(sf::Vector2(10.f, 10.f));



sf::Text greenText(font);
greenText.setFillColor(sf::Color::Black);


sf::CircleShape playerCircle(25.f);
playerCircle.setFillColor(sf::Color::Blue);
playerCircle.setOrigin(sf::Vector2(playerCircle.getRadius(),playerCircle.getRadius()));


std::vector<GreenCircle> greenCircles;
std::vector<RedCircle> redCircles;
sf::Clock spawnClockGreen;
sf::Clock spawnClockRed;
int score = 0;
int health = 5;

while (window.isOpen()) {
while (const std::optional event = window.pollEvent()) {
if (event->is<sf::Event::Closed>()) {
window.close();
}
}



if (spawnClockGreen.getElapsedTime().asSeconds() > 0.8f) {
float newRadius = 30.0f;
float x = randomFloat(newRadius, window.getSize().x - newRadius);
float y = randomFloat(newRadius, window.getSize().y - newRadius);

int value =  abs(randomGaussianFloat())+1;
greenCircles.emplace_back(newRadius, sf::Vector2f(x, y), value, false);
spawnClockGreen.restart();
}


if (spawnClockRed.getElapsedTime().asSeconds() > 0.3f) {
float newRadius = 50.0f;
float x;
float y;
float xdir;
float ydir;

float side = randomFloat(0.f,4.f);
if (side <= 1) {
    x = -50.f;
    y = randomFloat(newRadius, window.getSize().y - newRadius);
    xdir = randomFloat(0.2f,4.f);
    ydir = randomFloat(-4.f,4.f);
} else if (side <= 2) {
    x = randomFloat(newRadius, window.getSize().x - newRadius);
    y = -50.f;
    xdir = randomFloat(-4.f,4.f);
    ydir = randomFloat(0.2f,4.f);
} else if (side <= 3) {
    x = window.getSize().x + 50.f;
    y = randomFloat(newRadius, window.getSize().y - newRadius);
    xdir = randomFloat(-4.f,-0.2f);
    ydir = randomFloat(4.f,4.f);
} else {
    x = randomFloat(newRadius, window.getSize().x - newRadius);
    y = window.getSize().y + 50.f;
    xdir = randomFloat(-4.f,4.f);
    ydir = randomFloat(-4.f,-0.2f);
}

sf::Vector2f position(x, y);
sf::Vector2f direction(xdir, ydir);

redCircles.emplace_back(newRadius, position, direction, false);
spawnClockRed.restart();
}



sf::Vector2i mousePos = sf::Mouse::getPosition(window);
sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);
playerCircle.setPosition(mouseWorldPos);


for (auto green = greenCircles.begin(); green != greenCircles.end();) {
if (green->collision(playerCircle)) {
score += green->getValue();
green = greenCircles.erase(green); // Remove circle upon collision
} else {
if (green->isExpired()) {
green = greenCircles.erase(green); // Remove if expired
} else {
green->shrink();
++green;
}
}
}

for (auto red = redCircles.begin(); red != redCircles.end();) {
    if (red->collision(playerCircle)) {
        health -= 1;
        red = redCircles.erase(red);
    }else if (red->isFarAway(window)) {
        red = redCircles.erase(red); // Remove if expired
    } else {
    red->move();
    ++red;
    }
}

scoreText.setString(std::to_string(score));


testRed.move();


// for (RedCircle& circle : redCircles) {
// circle.move();
// }

////DRAW//////

window.clear();

for (GreenCircle circle : greenCircles) {
    //circle.draw(window);

    gem1.setScale(sf::Vector2(circle.getRadius()/212,circle.getRadius()/212));
    //gem1.setOrigin(sf::Vector2(circle.getRadius(),circle.getRadius()));
    //gem1.setPosition(circle.getPosition());
    gem1.setPosition(sf::Vector2(circle.getPosition().x - circle.getRadius(),circle.getPosition().y - circle.getRadius()));
    window.draw(gem1);

    greenText.setString(std::to_string(circle.getValue()));
    greenText.setCharacterSize(circle.getRadius());
    greenText.setPosition(sf::Vector2(circle.getPosition().x - greenText.getCharacterSize()/2,circle.getPosition().y - greenText.getCharacterSize()/2));
    window.draw(greenText);

}

for (RedCircle circle : redCircles) {
    circle.draw(window);
}

testRed.draw(window);


window.draw(scoreText);

window.draw(playerCircle);


window.display();


}
return 0;
}



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////



