#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <deque>

#include "AI.h"
#include "util.h"
#include "Murder.h"

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


//Enum for spawning units
enum
{
    WORKER,
    SCOUT,
    TANK,
};

static const std::vector<const char*> NAMES =
{
  "More Dakka",
  "Lemmings with Lazers",
  "BRB Fixing Arena (Again)",
  "PEW PEW",
  "Doctor Manhattan Distance",
  "Not a Smart Man"
};

const char* get_name()
{
    int index = rand() % NAMES.size();
    return NAMES[index];
}


AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return get_name();
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
  tileMap.clear();
  for (int i=0 ; i<tiles.size() ; ++i)
  {
    tileMap[Loc(tiles[i].x(), tiles[i].y())] = &(tiles[i]);
  }

  for (Unit u: units)
  {
    u.touched = false;
  }

  Player me = players[playerID()];
  Player him = players[abs(1 - playerID())];

  vector<Loc> sadPump = findMySadPump();
  vector<Loc> iceCaps = findIceCaps();
  vector<Loc> myPumps = findMyPumps();

  for (Unit u: units)
  {
    if (u.owner() != playerID())
    {
      Murder m(*this, u);
      m.action();
    }
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
    if (manhattanDistance(start, Loc(u)) <= moveSpeed)
    {
      if (Loc(u) != end)
      {
        blockingGrid[Loc(u)] = blocking;
      }
    }
  }

  for (Tile t: tiles)
  {
    if (water == Water::BLOCKS && t.waterAmount() > 0)
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

    Loc north = Loc(current) + Loc( 0, -1);
    Loc south = Loc(current) + Loc( 0,  1);
    Loc west  = Loc(current) + Loc( 1,  0);
    Loc east  = Loc(current) + Loc(-1,  0);

    checkLoc(north);
    checkLoc(south);
    checkLoc(east);
    checkLoc(west);
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
      result.push_back(Loc(t));
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
      result.push_back(Loc(t));
    }
  }
  return result;
}

vector<Loc> AI::findMySadPump()
{
  vector<Loc> result;
  Loc next;


  vector<Loc> isMyPump;
  for (Tile t: tiles)
  {
    if (t.owner() == playerID() && t.pumpID() != -1)
    {
      isMyPump.push_back(Loc(t));
    }
  }


  vector<Loc> adjacent;
  vector<Loc> notAdjacent;

  for (Loc current: isMyPump)
  {
    // north
    if (current.y() > 0)
    {
      next = Loc(current.x(), current.y() - 1);
      if (tileMap[next]->depth() > 1000)
      {
        adjacent.push_back(current);
      }
      else
      {
        notAdjacent.push_back(current);
      }
    }

    // south
    if (current.y() < mapHeight() - 1)
    {
      next = Loc(current.x(), current.y() + 1);
      if (tileMap[next]->depth() > 1000)
      {
        adjacent.push_back(current);
      }
      else
      {
        notAdjacent.push_back(current);
      }
    }

    // east
    if (current.x() > 0)
    {
      next = Loc(current.x() - 1, current.y());
      if (tileMap[next]->depth() > 1000)
      {
        adjacent.push_back(current);
      }
      else
      {
        notAdjacent.push_back(current);
      }
    }

    // west
    if (current.x() < mapWidth() - 1)
    {
      next = Loc(current.x() + 1, current.y());
      if (tileMap[next]->depth() > 1000)
      {
        adjacent.push_back(current);
      }
      else
      {
        notAdjacent.push_back(current);
      }
    }
  }
  return result;
}

//This function is run once, after your last turn.
void AI::end(){}
