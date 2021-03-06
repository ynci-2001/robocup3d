#ifndef _BATS_DRIBBLESIDE_HH_
#define _BATS_DRIBBLESIDE_HH_

#include "behavior.hh"

namespace bats
{
  class DribbleSide : public Behavior
  {
    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);

  public:
    DribbleSide(std::string const &id, std::string const &playerClass);
  };
};

#endif
