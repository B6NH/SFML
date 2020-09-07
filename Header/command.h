#ifndef COMMAND__H__
#define COMMAND__H__
#include <functional>
#include <SFML/System/Time.hpp>

class SceneNode;

struct Command{
  Command();
  std::function<void(SceneNode&,sf::Time)> action;
  unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn){
	return [=] (SceneNode& node, sf::Time dt){
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif
