//////////////////////////////////////////////////////////////////////////////
//
//+  Tutorial illustrating use and precision of the Double32_t data type
//
// You must run this tutorial with ACLIC
//    root > .x double32.C+
//
// The following cases are supported for streaming a Double32_t type
// depending on the range declaration in the comment field of the data member:
//  A-    Double32_t     fNormal;
//  B-    Double32_t     fTemperature; //[0,100]
//  C-    Double32_t     fCharge;      //[-1,1,2]
//  D-    Double32_t     fVertex[3];   //[-30,30,10]
//  E-    Double32_t     fChi2;        //[0,0,6]
//  F-    Int_t          fNsp;
//        Double32_t*    fPointValue;   //[fNsp][0,3]
//
// In case A fNormal is converted from a Double_t to a Float_t
// In case B fTemperature is converted to a 32 bit unsigned integer
// In case C fCharge is converted to a 2 bits unsigned integer
// In case D the array elements of fVertex are converted to an unsigned 10 bits integer
// In case E fChi2 is converted to a Float_t with truncated precision at 6 bits
// In case F the fNsp elements of array fPointvalue are converted to an unsigned 32 bit integer
//           Note that the range specifier must follow the dimension specifier.
// the case B has more precision (9 to 10 significative digits than case A (6 to 7 digits).
//
// The range specifier has the general format: [xmin,xmax] or [xmin,xmax,nbits]
//  [0,1]
//  [-10,100];
//  [-pi,pi], [-pi/2,pi/4],[-2pi,2*pi]
//  [-10,100,16]
//  [0,0,8]
// if nbits is not specified, or nbits <2 or nbits>32 it is set to 32
// if (xmin==0 and xmax==0 and nbits <=14) the double word will be converted
// to a float and its mantissa truncated to nbits significative bits.
//
// IMPORTANT NOTE
// --------------
// Lets assume an original variable double x:
// When using the format [0,0,8] (ie range not specified) you get the best
// relative precision when storing and reading back the truncated x, say xt.
// The variance of (x-xt)/x will be better than when specifying a range
// for the same number of bits. However the precision relative to the 
// range (x-xt)/(xmax-xmin) will be worst, and vice-versa.
// The format [0,0,8] is also interesting when the range of x is infinite
// or unknown.
//
//Author: Rene Brun
//
///////////////////////////////////////////////////////////////////////////

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include <vector>
using std::vector;
   
class DemoDouble32  {
private:
   vector<Double_t> fVD64;      //reference member with full double precision
   vector<Double32_t> fVF32;    //saved as a 32 bit Float_t
   vector<Double32_t> fVI32;    //[-pi,pi]    saved as a 32 bit unsigned int
   vector<Double32_t> fVI16;    //[-pi,pi,16]    saved as a 16 bit unsigned int
   vector<Double32_t> fVI8;    //[-pi,pi,8]    saved as a 8 bit unsigned int
   vector<Double32_t> fVI4;    //[-pi,pi,4]    saved as a 4 bit unsigned int
   vector<Int_t> fVI;

   static const int kNVectorEntries=100; //!


public:
   DemoDouble32() {;}
   void Set(vector<Double_t>& ref);

   ClassDef(DemoDouble32,1)
};

#if !defined(__CINT__)
ClassImp(DemoDouble32);
#endif

void DemoDouble32::Set(vector<Double_t>& ref) {
   fVD64.clear();
   for(int i=0; i<ref.size(); i++) { fVD64.push_back(ref[i]); }

   fVI.clear();
   for(int i=0; i<ref.size(); i++) { fVI.push_back(int(ref[i])); }

   vector<Double32_t> vectors[] = {fVF32, fVI32, fVI16, fVI8, fVI4};
   int n_vectors = sizeof(vectors)/sizeof(vector<Double32_t>);

   for(int j=0; j<n_vectors; j++){
     vectors[j].clear();
     for(int i=0; i<ref.size(); i++) { vectors[j].push_back(ref[i]); }
   }
}
      
void double32() {
   // show the use and precision of the Double32_t data type
   
   DemoDouble32 *d = new DemoDouble32();
   
   //create a Tree with 40000 objects DemoDouble32
   TFile::Open("DemoDouble32.root","recreate");
   TTree *T = new TTree("T","DemoDouble32");
   TBranch *bd = T->Branch("d","DemoDouble32",&d,4000);
   TRandom3 r;
   Double_t xmax = TMath::Pi();
   Double_t xmin = -xmax;
   Int_t i, n = 40000;
   for (i=0;i<n;i++) {
      vector<Double_t> vDoubles;
      for(int j=0; j<d->kNVectorEntries; j++) {
        vDoubles.push_back(r.Uniform(xmin,xmax));
      }
      d->Set(vDoubles);
      T->Fill();
   }
   T->Write();
   
   //Create the frame histogram and the graphs
   TObjArray *branches = bd->GetListOfBranches();
   Int_t nb = branches->GetEntries();
   TBranch *br = (TBranch*)branches->At(0);
   Long64_t zip64 = br->GetZipBytes();
   Double_t cx = 1;
   Double_t drange = 15;
   Double_t dval = 15;
   TCanvas *c1 = new TCanvas("c1","c1",800,600);
   c1->SetGrid();
   c1->SetHighLightColor(0);
   c1->SetFillColor(17);
   c1->SetFrameFillColor(20);
   c1->SetFrameBorderSize(10);
   TH1F *h = new TH1F("h","",nb,0,nb);
   h->SetMaximum(16);
   h->SetStats(0);
   h->Draw();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   TGraph *gcx = new TGraph(nb); gcx->SetName("gcx");
   gcx->SetMarkerStyle(21);
   gcx->SetMarkerColor(kBlue);
   TGraph *gdrange = new TGraph(nb); gdrange->SetName("gdrange");
   gdrange->SetMarkerStyle(20);
   gdrange->SetMarkerColor(kRed);
   TGraph *gdval = new TGraph(nb); gdval->SetName("gdval");
   gdval->SetMarkerStyle(20);
   gdval->SetMarkerColor(kBlack);
   TPaveLabel *title = new TPaveLabel(.15,.92,.85,.97,"Double32_t compression and precision","brNDC");   
   title->Draw();
   
   //loop on branches to get the precision and compression factors
   for (i=0;i<nb;i++) {
      br = (TBranch*)branches->At(i);
      h->GetXaxis()->SetBinLabel(i+1,br->GetName());
      cx = Double_t(zip64)/Double_t(br->GetZipBytes());
      gcx->SetPoint(i,i+0.5,cx);
      if (i > 0) {
         T->Draw(Form("(fVD64-%s)/(%g)",br->GetName(),xmax-xmin),"","goff");
         Double_t rms = TMath::RMS(n,T->GetV1());
         drange = TMath::Max(0.,-TMath::Log10(rms));
      }
      gdrange->SetPoint(i,i+0.5,drange);
      if (i > 0) {
         T->Draw(Form("(fVD64-%s)/(fVD64+0.01)",br->GetName()),"","goff");
         Double_t rms = TMath::RMS(n,T->GetV1());
         dval = TMath::Max(0.,-TMath::Log10(rms));
      }
      gdval->SetPoint(i,i+0.5,dval);
   }
   gcx->Draw("lp");
   gdrange->Draw("lp");
   gdval->Draw("lp");
   TLegend *legend = new TLegend(0.2,0.7,0.7,0.85);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(gcx,"Compression factor","lp");
   legend->AddEntry(gdrange,"Log of precision wrt range","lp");
   legend->AddEntry(gdval,"Log of precision wrt value","lp");
   legend->Draw();
   TPaveLabel *rang = new TPaveLabel(.75,.75,.88,.80,"[-pi,pi]","brNDC");   
   rang->Draw();
}
   
   
#if defined(__MAKECINT__)
#pragma link C++ class DemoDouble32;
#pragma link C++ class std::vector<Double32_t>;
#pragma link C++ class std::vector<Double_t>;
#pragma link C++ class std::vector<Int_t>;
#endif
