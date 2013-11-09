#ifndef AI_H
#define AI_H

#include <unordered_map>
#include "BaseAI.h"
#include "Murder.h"
#include "Trench.h"
#include "Defend.h"
#include "Seige.h"

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

  std::unordered_map<int, Unit> unitMap;
};

#endif
