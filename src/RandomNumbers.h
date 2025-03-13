#include <random>

///Random numbers///////////////

float randomFloat(float min, float max) {
static std::random_device rd;
static std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(min, max);
return dist(gen);
}


float randomGaussianFloat() {
static std::random_device rd; 
static std::mt19937 gen(rd()); 
std::normal_distribution<float> distribution(0, 10);
return distribution(gen); 
}

