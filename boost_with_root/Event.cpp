#include "Event.h"
#include <cstdio>

const double Event::kTest = 0.1;

void Event::Print(Option_t*) const
{
  printf("Event with fIntMember = %d\n", GetIntMember());
  printf("  And vector of size %d :", fObjects.size());
  for(int i=0; i<fObjects.size(); i++) {
    printf(" %03d", fObjects[i]->GetUniqueID());
  }
  printf("\n");
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
  for(int i=0; i<fObjects.size(); i++) {
    if(fObjects[i]) delete fObjects[i];
    fObjects[i] = NULL;
  }
  fObjects.clear();
}
