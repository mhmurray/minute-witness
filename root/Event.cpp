#include "Event.h"
#include <cstdio>

void Event::Print()
{
  printf("Event with fIntMember = %d\n", GetIntMember());
}

Event::Event()
{
  Reset();
  fIntMember=0;
}

Event::Event(int int_member)
{
  Reset();
  fIntMember = int_member;
}

void Event::Reset()
{
  fIntMember=0;
}
