#ifndef AIRCRAFT__H__
#define AIRCRAFT__H__
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "textureholder.h"

class Aircraft : public Entity{
public:
  enum Type{ Eagle, Raptor };
public:
  Aircraft(Type type, const TextureHolder& textures);
  virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
private:
  Type mType;
  sf::Sprite mSprite;
};

#endif
