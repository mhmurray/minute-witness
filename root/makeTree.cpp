{
  // Make old 
  TFile* f = TFile::Open("event_tree.root","RECREATE");
  TTree* t = new TTree("EventTree", "Tree of events", 99);

  Event* e = new Event();

  t->Branch("EventBranch", &e);

  for(int i=0; i<10; i++) {
    e->SetIntMember(i+4);
    t->Fill();
  }

  t->Write();
  f->Close();
}
