#ifndef AI_H
#define AI_H

#include <unordered_map>
#include <vector>
#include <map>
#include "BaseAI.h"
#include "Loc.h"

enum class Water
{
  BLOCKS,
  PATHABLE
};

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

  std::vector<Loc> bfs(Loc start, Loc end, Water water, int moveSpeed);
  std::vector<Loc> findMySadPump();
  std::vector<Loc> findIceCaps();
  std::vector<Loc> findMyPumps();
  std::map<Loc, Tile*> tileMap;
};

#endif
