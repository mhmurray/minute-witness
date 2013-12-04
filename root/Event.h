#ifndef Event_h
#define Event_h

#include "TObject.h"

class Event : public TObject {
  public:
  Event();
  explicit Event(int int_member);

  int GetIntMember() { return fIntMember; }
  void SetIntMember(int i) { fIntMember=i; }

  void Reset();
  void Print();

  private:
  int fIntMember;

  ClassDef(Event,1)
};

#endif
