#ifndef Event_h
#define Event_h

#include "TObject.h"
#include <vector>

class Event : public TObject {
  public:
  Event();
  explicit Event(int int_member);

  int GetIntMember() const { return fIntMember; }
  void SetIntMember(int i) { fIntMember = i; }

  std::vector<TObject*>* GetObjects() { return &fObjects; }
  void SetObjects(std::vector<TObject*> v) { fObjects = v; }

  void Reset();
  void Print(Option_t* = "") const;

  private:
  int fIntMember;
  std::vector<TObject*> fObjects;

  ClassDef(Event,1)
};

#endif
