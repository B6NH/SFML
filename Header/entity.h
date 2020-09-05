#ifndef ENTITY__H__
#define ENTITY__H__
#include <SFML/Graphics.hpp>
#include "scene_node.h"

class Entity : public SceneNode{
private:
  sf::Vector2f mVelocity;
public:
  void setVelocity(sf::Vector2f);
  void setVelocity(float, float);
  sf::Vector2f getVelocity() const;
private:
  virtual void updateCurrent(sf::Time);
};

#endif
