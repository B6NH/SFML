#ifndef SPRITE_NODE__H__
#define SPRITE_NODE__H__
#include "scene_node.h"

class SpriteNode : public SceneNode{
private:
  sf::Sprite mSprite;
private:
  virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;
public:
  explicit SpriteNode(const sf::Texture &);
  SpriteNode(const sf::Texture &, const sf::IntRect &);
};

#endif
