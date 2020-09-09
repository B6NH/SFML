#ifndef RESOURCE_HOLDER__H__
#define RESOURCE_HOLDER__H__

#include <map>
// #include <string>
// #include <memory>
// #include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder{
private:
  std::map<Identifier,std::unique_ptr<Resource>> mResourceMap;
public:
  void load(Identifier, const std::string &);
  template <typename Parameter>
  void load(Identifier, const std::string &, const Parameter &);
  Resource & get(Identifier);
  const Resource & get(Identifier) const;
private:
  void insertResource(Identifier id, std::unique_ptr<Resource> resource);
};

#include "resource_holder.inl"
#endif
