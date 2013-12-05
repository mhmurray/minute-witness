#include <cstdio>
#include <unistd.h>
#include "Event.h"
#include "TFile.h"
#include "TTree.h"

int main(int argc, const char* argv[])
{
  printf("Hello World!\n");

  TFile* f = new TFile("event_tree.root", "READ");
  TTree* t = (TTree*)f->FindObjectAny("EventTree");

  Event* e = NULL;
  t->SetBranchAddress("EventBranch", &e);
  
  while(true){
    usleep(10);
    for(int i=0; i<t->GetEntries(); i++) {
      t->GetEntry(i);
      e->Print();
    }
  }

  return 0;

}
