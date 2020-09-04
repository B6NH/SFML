#ifndef SCENE_NODE__H__
#define SCENE_NODE__H__
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;
public:
  SceneNode();
  void attachChild(Ptr);
  Ptr detachChild(const SceneNode &);
private:
  std::vector<Ptr> mChildren;
  SceneNode * mParent;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const final;
  virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;
  void drawChildren(sf::RenderTarget &, sf::RenderStates) const;
};

#endif
