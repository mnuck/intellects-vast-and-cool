#ifndef AI_H
#define AI_H

#include <unordered_map>
#include <vector>
#include "BaseAI.h"
#include "Loc.h"

///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();

  std::vector<Loc> bfs(Loc start, Loc end, bool blockingWater, int moveSpeed);
};

#endif
