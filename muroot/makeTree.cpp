#include "TFile.h"
#include "TTree.h"
#include "TObject.h"
#include "TTPCMiniPulse.h"
#include "TMusunEvent.h"
#include <vector>

void makeTree() {
  TFile* f = TFile::Open("event_tree.root","RECREATE");
  TTree* t = new TTree("EventTree", "Tree of events", 99);

  TMusunEvent* e = new TMusunEvent();

  t->Branch("EventBranch", &e);

  for(int i=0; i<10; i++) {
    for(int j=0; j<i; j++) {
      TTPCGenericPulse* p = new TTPCMiniPulse();
      e->AddTPCPulse(p);
    }
    t->Fill();
    e->Clear();
  }

  t->Write();
  f->Close();
}
