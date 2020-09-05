#include "../Header/scene_node.h"
#include "../Header/sprite_node.h"

SpriteNode::SpriteNode(const sf::Texture& texture) : mSprite(texture){
  //
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) : mSprite(texture, textureRect){
  //
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}
