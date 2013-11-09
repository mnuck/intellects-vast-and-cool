#include <vector>
#include <iostream>

#include "AI.h"
#include "util.h"

using std::cout;
using std::endl;

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

//This function is run once, after your last turn.
void AI::end(){}
