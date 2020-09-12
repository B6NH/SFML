
#ifndef BUTTON__H__
#define BUTTON__H__

#include "component.h"
#include "resource_identifiers.h"
#include "resource_holder.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI{

class Button : public Component{
public:
  typedef std::shared_ptr<Button> Ptr;
  typedef std::function<void()> Callback;
public:
  Button(const FontHolder &, const TextureHolder &);
  void setCallback(Callback);
  void setText(const std::string &);
  void setToggle(bool flag);
  virtual bool isSelectable() const;
  virtual void select();
  virtual void deselect();
  virtual void activate();
  virtual void deactivate();
  virtual void handleEvent(const sf::Event &);
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
private:
  Callback mCallback;
  const sf::Texture & mNormalTexture;
  const sf::Texture & mSelectedTexture;
  const sf::Texture & mPressedTexture;
  sf::Sprite mSprite;
  sf::Text mText;
  bool mIsToggle;
};

}

#endif
