#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <deque>

#include "AI.h"
#include "util.h"

using std::cout;
using std::endl;
using std::vector;

int manhattanDistance(Loc start, Loc end)
{
  return abs(start.x() - end.x()) + abs(start.y() - end.y());
}

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
    "Code Smell",
    "Simpleton Pattern",
    "Death by Ungabunga",
    "Feature Creep",
    "Jebediah Kerman",
    "Sunk Cost Fallacy",
    "Voodoo Debugging",
    "Law of Demeter",
    "Dunning-Kruger Effect",
    "Peter Principle",
    "Last Argument of Kings",
    "Intellects Vast and Cool",
    "Mineshaft Gap",
    "Flouridated Water",
    "Mezzanine Chump",
    "Leaf on the Wind",
    "Big Damn Heroes",
    "Moral Event Horizon",
    "Man of Wealth and Taste",
    "RMS's Left Sword",
    "35 Minutes Ago",
    "Need a Montage",
    "Bigger Hammer",
    "Kansas City Shuffle",
    "Why a Spoon?",
    "Han Shot First",
    "Robe and Wizard Hat",
    "For the Articles",
    "Play the Player",
    "The Real Slim Shady",
    "Monty Haul Problem",
    "Bizzaro Gordan Freeman",
    "Snowdens of Yesteryear",
    "P == NP",
    "P != NP",
    "Godwin's Law",
    "Mittani Sends His Regards",
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
  Player me = players[playerID()];
  Player him = players[abs(1 - playerID())];
  for (Unit u: units)
  {
    if (u.owner() == playerID())
    {
      int x = u.x();
      int y = u.y();
      int choice = rand() % 4;
      switch (choice)
      {
        case 0:
          u.move(x+1, y);
          break;
        case 1:
          u.move(x-1, y);
          break;
        case 2:
          u.move(x, y+1);
          break;
        case 3:
          u.move(x, y-1);
          break;
        default:
          break;
      }
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
          cout << "SPAWNIN A DOOD" << endl;
          t.spawn(WORKER);
        }
      }
    }
  }
  return true;
}



vector<Loc> AI::bfs(Loc start, Loc end, bool blockingWater, int moveSpeed)
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
        blockingGrid[Loc(x, y)] = available; // not blocking
      }
    }

    // units only count as blocking for the first moveSpeed tiles
    for (Unit u: units)
    {
      if (manhattanDistance(start, Loc(u.x(), u.y())) <= moveSpeed)
      {
        blockingGrid[Loc(u.x(), u.y())] = blocking; // blocking
      }
    }

    for (Tile t: tiles)
    {
      if (blockingWater && t.waterAmount() > 0)
      {
        blockingGrid[Loc(t.x(), t.y())] = blocking; // blocking
      }
      if (t.owner() == 3) // ice
      {
        blockingGrid[Loc(t.x(), t.y())] = blocking; // blocking
      }
      if (t.owner() != playerID() && t.pumpID() == -1)
      {
        blockingGrid[Loc(t.x(), t.y())] = blocking; // blocking
      }
    }

    frontier.push_back(Loc(start.x(), start.y()));

    while (!frontier.empty())
    {
      current = frontier.front();
      frontier.pop_front();

      if (current == end)
      {
        while (current != start)
        {
          result.push_back(current);
          current = blockingGrid[current];
        }
        break;
      }

      // north
      if (current.y() > 0)
      {
        next = Loc(current.x(), current.y() - 1);
        if (blockingGrid[next] == available)
        {
          blockingGrid[next] = current;
          frontier.push_back(next);
        }
      }

      // south
      if (current.y() < mapHeight() - 1)
      {
        next = Loc(current.x(), current.y() + 1);
        if (blockingGrid[next] == available)
        {
          blockingGrid[next] = current;
          frontier.push_back(next);
        }
      }

      // east
      if (current.x() > 0)
      {
        next = Loc(current.x() - 1, current.y());
        if (blockingGrid[next] == available)
        {
          blockingGrid[next] = current;
          frontier.push_back(next);
        }
      }

      // west
      if (current.x() < mapWidth() - 1)
      {
        next = Loc(current.x() + 1, current.y());
        if (blockingGrid[next] == available)
        {
          blockingGrid[next] = current;
          frontier.push_back(next);
        }
      }
    }

    return result;
}


/*

start = get_start()
frontier = [start]
while frontier
  current = frontier.pop
  if is_goal_state(current)
    break
  neighbors = get_neighbors(current)
  frontier.extend(neighbors)

*/


//This function is run once, after your last turn.
void AI::end(){}
