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
  hist4->SetTitle("longitutal energy profile deposit");
  hist4->GetXaxis()->SetTitle("(mm)");
  hist4->GetYaxis()->SetTitle("(% of E inc)");
  hist4->Draw("HIST");
  c1->cd(2);
  TH1D* hist8 = (TH1D*)f.Get("h8");
  hist8->SetTitle("radial energy profile deposit");
  hist8->GetXaxis()->SetTitle("(mm)");
  hist8->GetYaxis()->SetTitle("(% of E inc)");
  hist8->Draw("HIST");

  c1->SaveAs("plotHisto.pdf");
  
}
