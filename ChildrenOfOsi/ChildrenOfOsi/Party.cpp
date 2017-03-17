#include "stdafx.h"

#include "Party.h"

/**
 * Creates a new party with no alliegances, no leader, and no members.
 */
Party::Party(): faction(nullptr), leader(nullptr), target(nullptr), mode(Party::MODE_IDLE) {}

/**
 * Creates a new party with alliegance to the given faction, but no members nor
 * any leader.
 */
Party::Party(Alliance *a): faction(a), leader(nullptr), target(nullptr), mode(Party::MODE_IDLE) {}

/**
 * Creates a new party with the given leader, as a part of no faction.
 */
Party::Party(Soldier *leader): faction(nullptr), leader(leader), target(nullptr)
{
  this->addToParty(leader, true);
  this->setMode(Party::MODE_IDLE);
}

/**
 * Creates a new party as a part of the specified alliance and with the given
 * leader. The leader will be the only initial member of this party.
 */
Party::Party(Alliance *a, Soldier *leader) : faction(a), leader(leader), target(nullptr)
{
  this->addToParty(leader, true);
  this->setMode(Party::MODE_IDLE);
}

/**
 * Creates a new party as a part of the specified alliance and with the given
 * leader and additional members. Note that if the vector of additional members
 * contains the leader, they will be added twice.
 */
Party::Party(Alliance *a, Soldier *leader, const vector<Soldier *>& members): faction(a), leader(leader), target(nullptr)
{
  this->addToParty(leader, true);
  this->setMode(Party::MODE_IDLE);
  for(auto& member : members) {
    this->addToParty(member, false);
  }
}

/**
 * Returns whether the given soldier is an ally of this party.
 */
bool Party::isAllyOf(Soldier *s)
{
  return this->faction == s->getParty()->getAlliance();
}

/**
 * Returns whether the given party is an ally of this one.
 */
bool Party::isAllyOf(Party *p)
{
  return this->faction == p->faction;
}

/**
 * Returns whether the given soldier is an enemy of this party.
 */
bool Party::isEnemyOf(Soldier *s)
{
  return this->faction != s->getParty()->getAlliance();
}

/**
 * Returns whether the given party is an eney of this one.
 */
bool Party::isEnemyOf(Party *p)
{
  return this->faction != p->faction;
}

/**
 * Adds the given solider to this party, and sets them as the new leader if
 * specified, or if there are no other members in the party.
 */
void Party::addToParty(Soldier* s, bool isLeader)
{
  if(s != nullptr) {
    this->members.push_back(s);
    s->setParty(this);
    if(isLeader || members.size() == 1)
      this->leader = s;
  }
}

/**
 * Removes the specified soldier from this party. If, for some reason, the
 * soldier has duplicate references in this party, all such duplicates will be
 * removed as well.
 */
void Party::removeSoldier(Soldier* s)
{
  for(auto& i = this->members.begin(); i != this->members.end(); ++i) {
    if(*i == s) {
      this->members.erase(i);
      s->setParty(nullptr);
      if(leader == s) {
        leader = *members.begin();
      }
    }
  }
}

/**
 * Clears this party of all members, also leaving it leaderless.
 */
void Party::clear()
{
  this->members.clear();
  this->leader = nullptr;
}

/**
 * Sets this party's leader to the specified member, provided that the soldier
 * specified is already a member of this party. If they are not, returns without
 * making any changes.
 */
void Party::setLeader(Soldier* s)
{
  for(auto i = members.begin(); i != members.end(); ++i) {
    if(*i == s) {
      leader = s;
      break;
    }
  }
}

/**
 * Changes the combat mode of all members of this party to the one specified,
 * given it is valid. If the mode is not recognized, returns without making any
 * changes. Accepted combat modes are Party::MODE_IDLE, Party::MODE_ATTACK,
 * Party::MODE_DEFEND, Party::MODE_PATROL, and Party::MODE_FLEE.
 */
void Party::setMode(int m)
{
  this->mode = m;
  if(mode == Party::MODE_IDLE) {
    for(auto& member : this->members) {
      member->setInCombat(false);
      member->setEvade(false);
      member->setHold(false);
    }
  }
  else if(mode == Party::MODE_ATTACK) {
    for(auto& member : this->members) {
      member->setInCombat(true);
      member->setEvade(false);
      member->setHold(false);
    }
  }
  else if(mode == Party::MODE_DEFEND) {
    for(auto& member : this->members) {
      member->setInCombat(true);
      member->setHold(true);
      member->setEvade(false);
    }
  }
  else if(mode == Party::MODE_PATROL) {
    for(auto& member : this->members) {
      member->setInCombat(false);
      member->setHold(false);
      member->setEvade(false);
    }
  }
  else if(mode == Party::MODE_FLEE) {
    for(auto& member : this->members) {
      member->setInCombat(false);
      member->setHold(false);
      member->setEvade(true);
    }
  }
}

void Party::findEnemy()
{

}

void Party::update()
{

}
