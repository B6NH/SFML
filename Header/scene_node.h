#ifndef SCENE_NODE__H__
#define SCENE_NODE__H__
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <set>
#include "category.h"
#include "command_queue.h"


struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;
  typedef std::pair<SceneNode*, SceneNode*> Pair;
public:
  explicit SceneNode(Category::Type category = Category::None);
  void attachChild(Ptr);
  Ptr detachChild(const SceneNode &);
  void update(sf::Time dt, CommandQueue& commands);
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;

  void onCommand(const Command& command, sf::Time dt);
  virtual unsigned int getCategory() const;

  virtual sf::FloatRect	getBoundingRect() const;

  void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
  void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);

  virtual bool isMarkedForRemoval() const;
  virtual bool isDestroyed() const;

  void removeWrecks();

private:
  std::vector<Ptr> mChildren;
  SceneNode * mParent;
  Category::Type mDefaultCategory;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const final;
  virtual void drawCurrent(sf::RenderTarget &, sf::RenderStates) const;
  void drawChildren(sf::RenderTarget &, sf::RenderStates) const;

  virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
  void updateChildren(sf::Time dt, CommandQueue& commands);

};

bool	collision(const SceneNode& lhs, const SceneNode& rhs);
float	distance(const SceneNode& lhs, const SceneNode& rhs);

#endif
