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
        if(type){
            newRadius = circle.getRadius() - value/1000.f;
        }else{
            newRadius = circle.getRadius() - 0.02;
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





///Red Circles (enemies)//////////////////
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

float getRadius() const {
    return circle.getRadius();
}

sf::Vector2f getPosition() const {
    return circle.getPosition();
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
/////////////////////////////////////////////////




int main() {

//window
auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Circle Game");
window.setFramerateLimit(144);



////////////////////
///define graphics
/////////////////

sf::Font font;
if (!font.openFromFile("Chatkids.ttf")) { 
std::cerr << "Error loading font!" << std::endl;
return -1;
}

sf::Texture gem1Texture;
if (!gem1Texture.loadFromFile("gem.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
}
sf::Sprite gem1(gem1Texture);


sf::Texture redTexture;
if (!redTexture.loadFromFile("sea-urchin.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
}
sf::Sprite red1(redTexture);


sf::Texture healtTexture;
if (!healtTexture.loadFromFile("health.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
}
sf::Sprite heart2(healtTexture);
heart2.setScale(sf::Vector2f(0.2f,0.2f));


sf::Texture heartTexture;
if (!heartTexture.loadFromFile("heart.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
}
sf::Sprite heart1(heartTexture);



sf::CircleShape playerCircle(40.f);
playerCircle.setFillColor(sf::Color::Blue);
playerCircle.setOrigin(sf::Vector2(playerCircle.getRadius(),playerCircle.getRadius()));


sf::Texture frogTexture;
if (!frogTexture.loadFromFile("frog.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
}
sf::Sprite frog(frogTexture);
frog.setScale(sf::Vector2f(0.25f,0.25f));
frog.setOrigin(sf::Vector2f(170.f,170.f));


//text

sf::Text scoreText(font);
scoreText.setCharacterSize(25);
scoreText.setFillColor(sf::Color::White);
scoreText.setPosition(sf::Vector2(10.f, 10.f));


sf::Text greenText(font);
greenText.setFillColor(sf::Color::Black);

sf::Text gameOverText1(font);
gameOverText1.setFillColor(sf::Color::White);
gameOverText1.setString("GAME OVER");
gameOverText1.setPosition(sf::Vector2f(100.f,100.f));
gameOverText1.setCharacterSize(60);

sf::Text gameOverText2(font);
gameOverText2.setFillColor(sf::Color::White);
gameOverText2.setString("blubb"); //"Your score was:  " + std::to_string(score)
gameOverText2.setPosition(sf::Vector2f(100.f,200.f));
gameOverText2.setCharacterSize(40);

sf::Text gameOverText3(font);
gameOverText3.setFillColor(sf::Color::White);
gameOverText3.setString("click anywhere to play again");
gameOverText3.setPosition(sf::Vector2f(100.f,300.f));
gameOverText3.setCharacterSize(30);






////Variables

std::vector<GreenCircle> greenCircles;
std::vector<RedCircle> redCircles;
sf::Clock spawnClockGreen;
sf::Clock spawnClockRed;
int score = 0;
int health = 5;



//////////////////////////////
/////////Game
//////////////////////////


while (window.isOpen()) {
while (const std::optional event = window.pollEvent()) {
if (event->is<sf::Event::Closed>()) {
window.close();
}
}



if(health <= 0){
    window.clear();
    window.draw(gameOverText1);
    gameOverText2.setString("Your score was:  " + std::to_string(score)); //
    window.draw(gameOverText2);
    window.draw(gameOverText3);
    window.display();

    bool waitingForClick = true;
    while (waitingForClick){
        if (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
        window.close();
        return 0;
        }
        if (event->is<sf::Event::MouseButtonPressed>()) {
        waitingForClick=false;
        health=5;
        score=0;
        greenCircles.clear();
        redCircles.clear();
        }
    }
    }
}





if (spawnClockGreen.getElapsedTime().asSeconds() > 0.8f) {
float newRadius = 30.0f;
float x = randomFloat(newRadius, window.getSize().x - newRadius);
float y = randomFloat(newRadius, window.getSize().y - newRadius);

float randomType = randomFloat(0, 100);
if (randomType <= 2){
    greenCircles.emplace_back(newRadius, sf::Vector2f(x, y), 0, true);
}else{
int value = abs(randomGaussianFloat())+1;
greenCircles.emplace_back(newRadius, sf::Vector2f(x, y), value, false);
}
spawnClockGreen.restart();
}


//0.3f
//
if (spawnClockRed.getElapsedTime().asSeconds() > 1.f/(score/500.f+1.f) + 0.15f) {
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

redCircles.emplace_back(newRadius, position, direction);
spawnClockRed.restart();
}



sf::Vector2i mousePos = sf::Mouse::getPosition(window);
sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);
playerCircle.setPosition(mouseWorldPos);
frog.setPosition(mouseWorldPos);


for (auto green = greenCircles.begin(); green != greenCircles.end();) {
if (green->collision(playerCircle)) {
score += green->getValue();
if (green->getType() && health <= 20){
    health +=1;
}
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



////DRAW//////

window.clear();

for (GreenCircle circle : greenCircles) {

    if (circle.getType()){
        circle.draw(window);
        heart1.setScale(sf::Vector2(circle.getRadius()/140,circle.getRadius()/131));
    heart1.setPosition(sf::Vector2(circle.getPosition().x - circle.getRadius(),circle.getPosition().y - circle.getRadius()));
    window.draw(heart1);
    }else{
    gem1.setScale(sf::Vector2(circle.getRadius()/212,circle.getRadius()/212));
    gem1.setPosition(sf::Vector2(circle.getPosition().x - circle.getRadius(),circle.getPosition().y - circle.getRadius()));
    window.draw(gem1);

    greenText.setString(std::to_string(circle.getValue()));
    greenText.setCharacterSize(circle.getRadius());
    greenText.setPosition(sf::Vector2(circle.getPosition().x - greenText.getCharacterSize()/2,circle.getPosition().y - greenText.getCharacterSize()/2));
    window.draw(greenText);
    }

}

for (RedCircle circle : redCircles) {
    red1.setScale(sf::Vector2(circle.getRadius()/190,circle.getRadius()/190));
    red1.setPosition(sf::Vector2(circle.getPosition().x - 66,circle.getPosition().y - 66));
    window.draw(red1);
}


//window.draw(playerCircle);
window.draw(frog);
window.draw(scoreText);

for (int i = 0; i < health; i++) {
    heart2.setPosition(sf::Vector2f( window.getSize().x - i*60 - 100.f, 10.f));
    window.draw(heart2);
}



window.display();


}
return 0;
}



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
//TODO:
// happy frog
// 


