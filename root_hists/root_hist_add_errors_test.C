/* This example shows that the TH1::Add() function for ROOT histograms
 * will not treat the bin errors as if the sum of random uncorrelated
 * variables has been performed. Instead, the bin errors on a
 * difference histogram are the Sqrt(|N|), where N is the difference
 * in counts (notice the absolute value is taken).
 */
void root_hist_add_errors_test()
{
  // Sumw2 not called on these
  TH1* h1 = new TH1D("h1","h1", 10,0,10);
  TH1* h2 = new TH1D("h2","h2", 10,0,10);
  TH1* hDiff12 = NULL;

  // Sumw2 is called on these
  TH1* h3 = new TH1D("h3","h3", 10,0,10);
  TH1* h4 = new TH1D("h4","h4", 10,0,10);
  TH1* hDiff34 = NULL;


  for(int i=0; i<10; i++) {
    for(int j=0; j<-2+i; j++) {
      h1->Fill(i);
      h3->Fill(i);
    }

    for(int j=0; j<2; j++) {
      h2->Fill(i);
      h4->Fill(i);
    }
  }
  h3->Sumw2();
  h4->Sumw2();

  hDiff12 = (TH1*)h1->Clone("hDiff12");
  hDiff12->SetTitle("hDiff12");
  hDiff12->Add(h2,-1);

  hDiff34 = (TH1*)h3->Clone("hDiff34");
  hDiff34->SetTitle("hDiff34");
  hDiff34->Add(h4,-1);

  TCanvas* c12 = new TCanvas();
  c12->Divide(1,3);

  c12->cd(1);
  h1->Draw("pe");
  c12->cd(2);
  h2->Draw("pe");
  c12->cd(3);
  hDiff12->Draw("pe");

  printf("%5s | %11s | %11s | %11s\n", "Bin", "h1", "h2", "hDiff12");
  for(int i=1; i<=10; i++) {
    printf("%5d | %4.1f (%4.2f) | %4.1f (%4.2f) | %4.1f (%4.2f)\n",
        i, h1->GetBinContent(i), h1->GetBinError(i),
        h2->GetBinContent(i), h2->GetBinError(i),
        hDiff12->GetBinContent(i), hDiff12->GetBinError(i));
  }
  printf("%5s | %11s | %11s | %11s\n", "Bin", "h3", "h4", "hDiff34");
  for(int i=1; i<=10; i++) {
    printf("%5d | %4.1f (%4.2f) | %4.1f (%4.2f) | %4.1f (%4.2f)\n",
        i, h3->GetBinContent(i), h3->GetBinError(i),
        h4->GetBinContent(i), h4->GetBinError(i),
        hDiff34->GetBinContent(i), hDiff34->GetBinError(i));
  }

  TCanvas* c34 = new TCanvas();
  c34->Divide(1,3);

  c34->cd(1);
  h3->Draw("pe");
  c34->cd(2);
  h4->Draw("pe");
  c34->cd(3);
  hDiff34->Draw("pe");
    
}
