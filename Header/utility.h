#ifndef UTILITY__H__
#define UTILITY__H__

#include <sstream>

namespace sf{
	class Sprite;
	class Text;
}

template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#include "utility.inl"
#endif
