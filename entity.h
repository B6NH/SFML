#ifndef ENTITY__H__
#define ENTITY__H__

class Entity{
private:
  sf::Vector2f mVelocity;
public:
  void setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }
  void setVelocity(float vx, float vy) { mVelocity.x = vx; mVelocity.y = vy; }
  sf::Vector2f getVelocity() const { return mVelocity; }
};

#endif
