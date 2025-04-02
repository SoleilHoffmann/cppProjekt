#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include "RedCircles.hpp"
#include "GreenCircles.hpp"
#include "RandomNumbers.hpp"


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


    sf::Texture healtTexture;
    if (!healtTexture.loadFromFile("./assets/health.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
    }
    sf::Sprite heart2(healtTexture);
    heart2.setScale(sf::Vector2f(0.2f,0.2f));



    sf::CircleShape playerCircle(40.f);
    playerCircle.setFillColor(sf::Color::Blue);
    playerCircle.setOrigin(sf::Vector2(playerCircle.getRadius(),playerCircle.getRadius()));


    sf::Texture frogTexture;
    if (!frogTexture.loadFromFile("./assets/frog.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
    }
    sf::Sprite frog(frogTexture);
    frog.setScale(sf::Vector2f(0.25f,0.25f));
    frog.setOrigin(sf::Vector2f(170.f,170.f));


    sf::Texture frogTexture2;
    if (!frogTexture2.loadFromFile("./assets/frog-eating.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
    }

    sf::Texture frogTexture3;
    if (!frogTexture3.loadFromFile("./assets/frog-glowing.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
    }

    sf::Texture frogTexture4;
    if (!frogTexture4.loadFromFile("./assets/frog-sad.png")) {
        std::cout << "Could not load texture" << std::endl;
        return 0;
    }


    //Define Texts

    sf::Text scoreText(font);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2(10.f, 10.f));

    sf::Text gameOverText1(font);
    gameOverText1.setFillColor(sf::Color::White);
    gameOverText1.setString("GAME OVER");
    gameOverText1.setPosition(sf::Vector2f(100.f,100.f));
    gameOverText1.setCharacterSize(60);

    sf::Text gameOverText2(font);
    gameOverText2.setFillColor(sf::Color::White);
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
    sf::Clock resetFrog;
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


        //Game Over Screen
        if(health <= 0){
            window.clear();
            window.draw(gameOverText1);
            gameOverText2.setString("Your score was:  " + std::to_string(score)); 
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




        //Spawn new Circles 
        if (spawnClockGreen.getElapsedTime().asSeconds() > 0.8f) {
            float newRadius = 30.0f;
            float x = randomFloat(newRadius, window.getSize().x - newRadius);
            float y = randomFloat(newRadius, window.getSize().y - newRadius);

            float randomType = randomFloat(0, 100);
            if (randomType <= 3){
                greenCircles.emplace_back(newRadius, sf::Vector2f(x, y), 0, true);
            }else{
                int value = abs(randomGaussianFloat())+1;
                greenCircles.emplace_back(newRadius, sf::Vector2f(x, y), value, false);
            }
            spawnClockGreen.restart();
        }


        if (spawnClockRed.getElapsedTime().asSeconds() > 1.f/(score/300.f+1.f) + 0.15f) {
            float newRadius = 50.0f;
            float x;
            float y;
            float xdir;
            float ydir;

            float maxSpeed = 10.f - (8.f/(score/3000.f + 1.f));
            float side = randomFloat(0.f,4.f);
            if (side <= 1) {
                x = -50.f;
                y = randomFloat(newRadius, window.getSize().y - newRadius);
                xdir = randomFloat(0.2f,maxSpeed);
                ydir = randomFloat(-maxSpeed,maxSpeed);
            } else if (side <= 2) {
                x = randomFloat(newRadius, window.getSize().x - newRadius);
                y = -50.f;
                xdir = randomFloat(-maxSpeed,maxSpeed);
                ydir = randomFloat(0.2f,maxSpeed);
            } else if (side <= 3) {
                x = window.getSize().x + 50.f;
                y = randomFloat(newRadius, window.getSize().y - newRadius);
                xdir = randomFloat(-maxSpeed,-0.2f);
                ydir = randomFloat(maxSpeed,maxSpeed);
            } else {
                x = randomFloat(newRadius, window.getSize().x - newRadius);
                y = window.getSize().y + 50.f;
                xdir = randomFloat(-maxSpeed,maxSpeed);
                ydir = randomFloat(-maxSpeed,-0.2f);
            }

            sf::Vector2f position(x, y);
            sf::Vector2f direction(xdir, ydir);

            redCircles.emplace_back(newRadius, position, direction);
            spawnClockRed.restart();
        }


        //Move Player
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);
        playerCircle.setPosition(mouseWorldPos);
        frog.setPosition(mouseWorldPos);


        //Test for collisions and remove expired circles
        for (auto green = greenCircles.begin(); green != greenCircles.end();) {
            if (green->collision(playerCircle)) {
                score += green->getValue();
                if (green->getType() && health <= 20){
                    health +=1;
                    frog.setTexture(frogTexture3);
                    resetFrog.restart();
                }
                if (!green->getType()){
                    frog.setTexture(frogTexture2);
                    resetFrog.restart();
                }
                green = greenCircles.erase(green); 
            } else {
                if (green->isExpired()) {
                    green = greenCircles.erase(green); 
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
                frog.setTexture(frogTexture4);
                resetFrog.restart();
            }else if (red->isFarAway(window)) {
                red = redCircles.erase(red);
            } else {
                red->move();
                ++red;
            }
        }

        scoreText.setString(std::to_string(score));

        if (resetFrog.getElapsedTime().asSeconds() > 0.2f) {
            frog.setTexture(frogTexture);
        }



        ////DRAW//////

        window.clear();

        for (GreenCircle circle : greenCircles) {
            circle.draw(window, font);
        }

        for (RedCircle circle : redCircles) {
            circle.draw(window);
        }


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

