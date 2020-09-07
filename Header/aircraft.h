#ifndef AIRCRAFT__H__
#define AIRCRAFT__H__
#include "entity.h"
#include "texture_holder.h"

class Aircraft : public Entity{
public:
  enum Type{
    Eagle, Raptor
  };
public:
  explicit Aircraft(Type, const TextureHolder &);
  virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;
  virtual unsigned int getCategory() const;
private:
  Type mType;
  sf::Sprite mSprite;
};

#endif
