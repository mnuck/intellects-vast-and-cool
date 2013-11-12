//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::mapWidth() const
{
  return getMapWidth(c);
}
int BaseAI::mapHeight() const
{
  return getMapHeight(c);
}
int BaseAI::waterDamage() const
{
  return getWaterDamage(c);
}
int BaseAI::turnNumber() const
{
  return getTurnNumber(c);
}
int BaseAI::maxUnits() const
{
  return getMaxUnits(c);
}
int BaseAI::playerID() const
{
  return getPlayerID(c);
}
int BaseAI::gameNumber() const
{
  return getGameNumber(c);
}
int BaseAI::maxSiege() const
{
  return getMaxSiege(c);
}
float BaseAI::oxygenRate() const
{
  return getOxygenRate(c);
}
int BaseAI::depositionRate() const
{
  return getDepositionRate(c);
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getPlayerCount(c);
  players.clear();
  players.resize(count);
  for(int i = 0; i < count; i++)
  {
    players[i] = Player(getPlayer(c, i));
  }

  count = getMappableCount(c);
  mappables.clear();
  mappables.resize(count);
  for(int i = 0; i < count; i++)
  {
    mappables[i] = Mappable(getMappable(c, i));
  }

  count = getPumpStationCount(c);
  pumpStations.clear();
  pumpStations.resize(count);
  for(int i = 0; i < count; i++)
  {
    pumpStations[i] = PumpStation(getPumpStation(c, i));
  }

  count = getUnitCount(c);
  units.clear();
  units.resize(count);
  for(int i = 0; i < count; i++)
  {
    units[i] = Unit(getUnit(c, i));
  }

  count = getTileCount(c);
  tiles.clear();
  tiles.resize(count);
  for(int i = 0; i < count; i++)
  {
    tiles[i] = Tile(getTile(c, i));
  }

  count = getUnitTypeCount(c);
  unitTypes.clear();
  unitTypes.resize(count);
  for(int i = 0; i < count; i++)
  {
    unitTypes[i] = UnitType(getUnitType(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}
