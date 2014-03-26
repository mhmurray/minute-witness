void root_hist_test()
{
  // Project3D uses overflows?
  TH3* h3D = new TH3D("h3D", "h3D", 2,0,2, 2,0,2, 2,0,2);
  for(int i=0; i<=h3D->GetNbinsX()+1; i++) {
    for(int j=0; j<=h3D->GetNbinsY()+1; j++) {
      for(int k=0; k<=h3D->GetNbinsZ()+1; k++) {
        h3D->SetBinContent(i,j,k, 1);
      }
    }
  }

  printf("h3D integral = %d\tentries = %d\n", h3D->Integral(), h3D->GetEntries());

  h3D->GetZaxis()->SetRange(3,3);
  TH2* hYX = (TH2*) h3D->Project3D("yx");

  printf("hYX integral = %d\tentries = %d\n", hYX->Integral(), hYX->GetEntries());
  hYX->Draw("colz");
}
