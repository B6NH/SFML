#ifndef SCENENODE__H__
#define SCENENODE__H__
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;
  //SceneNode();
  void attachChild(Ptr);
  Ptr detachChild(const SceneNode &);
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const final;
  virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;
  std::vector <Ptr> mChildren;
  SceneNode * mParent;
};

#endif
