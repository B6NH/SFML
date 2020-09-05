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
  void update(sf::Time);
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;
private:
  std::vector<Ptr> mChildren;
  SceneNode * mParent;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const final;
  virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;
  void drawChildren(sf::RenderTarget &, sf::RenderStates) const;

  virtual void updateCurrent(sf::Time);
  void updateChildren(sf::Time);


};

#endif
