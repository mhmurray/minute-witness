#include "TFile.h"
#include "TTree.h"
#include "TObject.h"
#include "TTPCMiniPulse.h"
#include "Event.h"
#include <vector>

void makeTree() {
  TFile* f = TFile::Open("event_tree.root","RECREATE");
  TTree* t = new TTree("EventTree", "Tree of events", 99);

  Event* e = new Event();

  t->Branch("EventBranch", &e);

  for(int i=0; i<10; i++) {
    e->SetIntMember(10*i);
    std::vector<TObject*> v;
    for(int j=0; j<i; j++) {
      //TObject* o = new TH1D();
      TObject* o = new TTPCMiniPulse();
      o->SetUniqueID(e->GetIntMember()+j);
      v.push_back(o);
    }
    e->SetObjects(v);
    t->Fill();
  }

  t->Write();
  f->Close();
}
