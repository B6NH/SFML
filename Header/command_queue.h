#ifndef COMMAND_QUEUE__H__
#define COMMAND_QUEUE__H__
#include <queue>
#include "command.h"

class CommandQueue{
public:
  void push(const Command & command);
  Command pop();
  bool isEmpty() const;
private:
  std::queue<Command>mQueue;
};

#endif
