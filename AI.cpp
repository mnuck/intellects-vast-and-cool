#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <deque>

#include "AI.h"
#include "util.h"
#include "Loc.h"
#include "Murder.h"
#include "Spawn.h"

using std::cout;
using std::endl;
using std::vector;


namespace std {
  template <> struct hash<Loc>
  {
    size_t operator()(const Loc & rhs) const
    {
      return rhs.y() * 40 + rhs.x();
    }
  };
}

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Red Rocket";
}

const char* AI::password()
{
  return "password";
}

//This function is run once, before your first turn.
void AI::init(){}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  spawnRequests.clear();
  tileMap.clear();
  for (int i=0 ; i<tiles.size() ; ++i)
  {
    tileMap[tiles[i]] = &(tiles[i]);
  }

  for (Unit u: units)
  {
    u.touched = false;
  }

  Player me = players[playerID()];
  vector<Loc> iceCaps = findIceCaps();
  vector<Loc> myPumps = findMyPumps();

  for (Unit u: units)
  {
    if (u.owner() != playerID())
    {
      Murder(*this, u, Dood::WORKER).activate();
    }
  }

  for (SpawnRequest req: spawnRequests)
  {
    Spawn(*this, req).activate();
  }

  for (Tile t: tiles)
  {
    if (t.owner() == playerID())
    {
      if (!t.isSpawning())
      {
        if (me.oxygen() >= unitTypes[WORKER].cost())
        {
          t.spawn(WORKER);
        }
      }
    }
  }
  return true;
}

vector<Loc> AI::bfs(Loc start, Loc end, Water water, int moveSpeed) const
{
  vector<Loc> result;
  std::unordered_map<Loc, Loc> blockingGrid;
  Loc current;
  Loc next;
  Loc blocking(-2, -2);
  Loc available(-1, -1);

  std::deque<Loc> frontier;

  for (int x = 0 ; x < mapWidth() ; ++x)
  {
    for (int y = 0 ; y < mapHeight() ; ++y)
    {
      blockingGrid[Loc(x, y)] = available;
    }
  }

  // units only count as blocking for the first moveSpeed tiles
  for (Unit u: units)
  {
    if (manhattanDistance(start, u) <= moveSpeed)
    {
      if (Loc(u) != end)
      {
        blockingGrid[Loc(u)] = blocking;
      }
    }
  }

  for (Tile t: tiles)
  {
    if (water == Water::BLOCKS && t.waterAmount() > 0) // water
    {
      blockingGrid[Loc(t)] = blocking;
    }
    if (t.owner() == 3) // ice
    {
      blockingGrid[Loc(t)] = blocking;
    }
    if (t.owner() == (1 - playerID()) && t.pumpID() == -1) // his spawn point
    {
      if (Loc(t) != end)
      {
        blockingGrid[Loc(t)] = blocking;
      }
    }
  }

  frontier.push_back(start);

  while (!frontier.empty())
  {
    current = frontier.front();
    frontier.pop_front();

    if (current == end)
    {
      while (current != start)
      {
        result.insert(result.begin(), current);
        current = blockingGrid[current];
      }
      break;
    }

    auto checkLoc = [&] (Loc next) -> void
    {
      if (blockingGrid[next] == available)
      {
        blockingGrid[next] = current;
        frontier.push_back(next);
      }
    };

    checkLoc(current + Loc( 0, -1));  // north
    checkLoc(current + Loc( 0,  1));  // south
    checkLoc(current + Loc(-1,  0));  // east
    checkLoc(current + Loc( 1,  0));  // west
  }
  return result;
}

vector<Loc> AI::findIceCaps()
{
  vector<Loc> result;
  for (Tile t: tiles)
  {
    if (t.owner() == 3)
    {
      result.push_back(t);
    }
  }
  return result;
}

vector<Loc> AI::findMyPumps()
{
  vector<Loc> result;
  for (Tile t: tiles)
  {
    if (t.owner() == playerID() && t.pumpID() != -1)
    {
      result.push_back(t);
    }
  }
  return result;
}


void AI::requestSpawn(Dood dood, Loc spawnLoc)
{
  spawnRequests.push_back(SpawnRequest(dood, spawnLoc));
}

//This function is run once, after your last turn.
void AI::end(){}
