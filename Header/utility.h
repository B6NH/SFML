#ifndef UTILITY__H__
#define UTILITY__H__

#include <sstream>
#include <SFML/System/Vector2.hpp>

namespace sf{
	class Sprite;
	class Text;
}

template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float toDegree(float radian);
float toRadian(float degree);
int randomInt(int exclusiveMax);
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

#include "utility.inl"
#endif
