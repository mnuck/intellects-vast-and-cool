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

//Enum for spawning units
enum Dood
{
  WORKER,
  SCOUT,
  TANK
};

enum class Pathing
{
  RANDOMIZED,
  PREDICTABLE
};

struct SpawnRequest
{
  SpawnRequest(Dood dood, Loc spawnLoc): _doodType(dood), _spawnLocation(spawnLoc) {}
  Dood _doodType;
  Loc  _spawnLocation;
};

///The class implementing gameplay logic.
class AI: public BaseAI
{
public:
  friend class Moat;
  friend class Murder;
  friend class Siege;
  friend class Spawn;
  friend class Trench;

  AI(Connection* c);
  virtual const char* username();
  virtual const char* password();
  virtual void init();
  virtual bool run();
  virtual void end();

  std::vector<Loc> bfs(Loc start, Loc end, 
                       Water water, int moveSpeed,
                       Pathing pathing=Pathing::PREDICTABLE) const;
  std::vector<Loc> findMySadPump();
  std::vector<Loc> findIceCaps();
  std::vector<Loc> findMyPumps();
  std::unordered_map<int, Unit*> unitIdIndex;
  void requestSpawn(Dood dood, Loc spawnloc);

  std::map<Loc, Tile*> tileMap;
  std::vector<SpawnRequest> spawnRequests;
};

#endif
