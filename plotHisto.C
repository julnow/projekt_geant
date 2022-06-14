#include "TAxis.h"
#include "TH1.h"
#include "TArrayD.h"

Double_t ScaleX(Double_t x)
{
  Double_t v;
  v = 30000 * x; // "linear scaling" function example
  return v;
}

Double_t ScaleY(Double_t y)
{
  Double_t v;
  v = 20 * y + 200; // "linear scaling" function example
  return v;
}

Double_t ScaleZ(Double_t z)
{
  Double_t v;
  v = 30 * z + 300; // "linear scaling" function example
  return v;
}

void ScaleAxis(TAxis *a, Double_t (*Scale)(Double_t))
{
  if (!a) return; // just a precaution
  if (a->GetXbins()->GetSize())
    {
      // an axis with variable bins
      // note: bins must remain in increasing order, hence the "Scale"
      // function must be strictly (monotonically) increasing
      TArrayD X(*(a->GetXbins()));
      for(Int_t i = 0; i < X.GetSize(); i++) X[i] = Scale(X[i]);
      a->Set((X.GetSize() - 1), X.GetArray()); // new Xbins
    }
  else
    {
      // an axis with fix bins
      // note: we modify Xmin and Xmax only, hence the "Scale" function
      // must be linear (and Xmax must remain greater than Xmin)
      a->Set( a->GetNbins(),
              Scale(a->GetXmin()), // new Xmin
              Scale(a->GetXmax()) ); // new Xmax
    }
  return;
}

void ScaleXaxis(TH1 *h, Double_t (*Scale)(Double_t))
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetXaxis(), Scale);
  return;
}

void ScaleYaxis(TH1 *h, Double_t (*Scale)(Double_t))
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetYaxis(), Scale);
  return;
}

void ScaleZaxis(TH1 *h, Double_t (*Scale)(Double_t))
{
  if (!h) return; // just a precaution
  ScaleAxis(h->GetZaxis(), Scale);
  return;
}

void plotHisto(const char* filename)
{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile f(filename);
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->Divide(1, 2);

  c1->cd(1);
  TH1D* hist4 = (TH1D*)f.Get("h4");
  ScaleXaxis(hist4, ScaleX);
  hist4->SetTitle("longitutal energy profile deposit");
  hist4->GetXaxis()->SetTitle("(mm)");
  hist4->GetYaxis()->SetTitle("(% of E inc)");
  hist4->Draw("HIST");
  c1->cd(2);
  TH1D* hist8 = (TH1D*)f.Get("h8");
  ScaleXaxis(hist8, ScaleX);
  hist8->SetTitle("radial energy profile deposit");
  hist8->GetXaxis()->SetTitle("(mm)");
  hist8->GetYaxis()->SetTitle("(% of E inc)");
  hist8->Draw("HIST");

  c1->SaveAs("plotHisto.pdf");
  
}
