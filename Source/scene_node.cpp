#include <algorithm>
#include <cassert>
#include "../Header/category.h"
#include "../Header/command.h"
#include "../Header/scene_node.h"
#include "../Header/utility.h"


#include "../Header/aircraft.h"
#include <iostream>

SceneNode::SceneNode(Category::Type category) :
  mChildren(),
  mParent(nullptr),
  mDefaultCategory(category){
  //
}

void SceneNode::attachChild(Ptr child){
  child->mParent = this;
  mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode & node){
  auto found =
    std::find_if(mChildren.begin(),
                 mChildren.end(),
                 [&] (Ptr & p) -> bool { return p.get() == &node; });
  assert(found != mChildren.end());
  Ptr result = std::move(*found);
  result->mParent = nullptr;
  mChildren.erase(found);
  return result;
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const{
  states.transform *= getTransform();
  drawCurrent(target,states);
  drawChildren(target,states);
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const{
  //
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const{
  for(const Ptr & child : mChildren){
    child->draw(target,states);
  }
}

void SceneNode::update(sf::Time dt, CommandQueue& commands){
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time, CommandQueue&){
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands){
	for(Ptr& child : mChildren){
    child->update(dt, commands);
  }
}

sf::Transform SceneNode::getWorldTransform() const{
  sf::Transform transform = sf::Transform::Identity;

  for(const SceneNode * node = this; node != nullptr; node = node->mParent){
    transform = node->getTransform() * transform;
  }

  return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const{
  return getWorldTransform() * sf::Vector2f();
}

void SceneNode::onCommand(const Command& command, sf::Time dt){

	if (command.category & getCategory()){
    command.action(*this, dt);
  }

	for(Ptr & child : mChildren){
    child->onCommand(command, dt);
  }

}

unsigned int SceneNode::getCategory() const{
  return mDefaultCategory;
}

sf::FloatRect SceneNode::getBoundingRect() const{
	return sf::FloatRect();
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs){
	checkNodeCollision(sceneGraph, collisionPairs);

	for(Ptr& child : sceneGraph.mChildren){
    checkSceneCollision(*child, collisionPairs);
  }

}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs){
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	for(Ptr & child : mChildren){
    child->checkNodeCollision(node, collisionPairs);
  }

}

bool SceneNode::isDestroyed() const{
	// By default, scene node needn't be removed
	return false;
}

float distance(const SceneNode& lhs, const SceneNode& rhs){
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

bool collision(const SceneNode& lhs, const SceneNode& rhs){
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}
