{
  TFile* f = TFile::Open("event_tree.root", "READ");
  TTree* t = (TTree*)f->FindObjectAny("EventTree");

  t->Print();
  printf("Scanning first 10 entries...\n");
  t->Scan("Print()","","",10);

  exit(0);
}
