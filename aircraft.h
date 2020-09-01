#ifndef AIRCRAFT__H__
#define AIRCRAFT__H__
#include "entity.h"

class Aircraft : public Entity{
public:
  enum Type{ Eagle, Raptor };
public:
  explicit Aircraft(Type type) : mType(type) {}
private:
  Type mType;
};

#endif
