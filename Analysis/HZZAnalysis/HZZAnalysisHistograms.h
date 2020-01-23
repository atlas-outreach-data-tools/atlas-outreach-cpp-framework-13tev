////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void HZZAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms variables
  hist_mLL1         = new TH1F("hist_mLL1",        "Mass of Dilepton System; m_{ll,1} [GeV];Events / bin", 30, 50, 106);
  hist_mLL2         = new TH1F("hist_mLL2",        "Mass of Dilepton System; m_{ll,2} [GeV];Events / bin", 30, 12, 140);

  hist_fourlepsys_pt        = new TH1F("hist_fourlepsys_pt",        "Transverse Momentum of four-lepton system; p_{T,4l} [GeV];Events / bin", 20, 0, 200);
  hist_fourlepsys_y         = new TH1F("hist_fourlepsys_y",         "Rapidity of four-lepton system; y_{4l} ;Events / bin", 20, -3, 3);

  mass_ext_four_lep = new TH1F("mass_ext_four_lep",     "Mass of four-lepton system; m_{4l} [GeV];Events / bin", 30, 80, 250);
  mass_four_lep     = new TH1F("mass_four_lep",         "Mass of four-lepton system; m_{4l} [GeV];Events / bin", 24, 80, 170);


  hist_n_jets       = new TH1F("hist_n_jets",          "Number of Jets;N_{jets};Events", 4, -0.5, 3.5);



  // Lepton histograms
  hist_fourleptpt   = new TH1F("hist_fourleptpt",  " Leptons Transverse Momentum;p_{T}^{all lep} [GeV];Leptons / bin", 5, 0, 200);
  hist_fourlepteta  = new TH1F("hist_fourlepteta", " Leptons Pseudorapidity; #eta^{all lep}; Leptons / bin", 10, -3, 3);
  hist_fourleptE    = new TH1F("hist_fourleptE",   " Leptons Energy; E^{all lep} [GeV]; Leptons / bin", 10, 0, 300);
  hist_fourleptphi  = new TH1F("hist_fourleptphi", " Leptons Azimuthal Angle ; #phi^{all lep}; Leptons / bin", 8, -3.2, 3.2);
  hist_fourleptch   = new TH1F("hist_fourleptch",  " Leptons Charge; Q^{all lep}; Leptons / bin", 7, -1.75, 1.75);
  hist_fourleptID   = new TH1F("hist_fourleptID",  " Leptons Absolute PDG ID; |PDG ID|^{all lep}; Leptons / bin",  15, 5.5, 20.5);

  hist_fourlept_ptc  = new TH1F("hist_fourlept_ptc", " Leptons Relative Transverse Momentum Isolation; ptconerel30^{all lep}; Leptons / bin", 10, -0.1, 0.4);
  hist_fourleptetc  = new TH1F("hist_fourleptetc", " Lepton Relative Transverse Energy Isolation; etconerel20^{all lep}; Leptons / bin", 10, -0.1, 0.4);
  hist_fourlepz0    = new TH1F("hist_fourlepz0",   " Lepton z0 impact parameter; z_{0}^{all lep} [mm]; Leptons / bin", 20, -1, 1);
  hist_fourlepd0    = new TH1F("hist_fourlepd0",   " Lepton d0 impact parameter; d_{0}^{all lep} [mm]; Leptons / bin", 20, -1, 1);

}

////////////////////////////////////////////////////////////////////////////////
void HZZAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_mLL1);
  GetOutputList()->Add(hist_mLL2);
 
  GetOutputList()->Add(hist_fourlepsys_pt);
  GetOutputList()->Add(hist_fourlepsys_y);
 
  GetOutputList()->Add(mass_four_lep);
  GetOutputList()->Add(mass_ext_four_lep);

  GetOutputList()->Add(hist_n_jets);

 // Add  Lepton histograms
  GetOutputList()->Add(hist_fourleptpt);
  GetOutputList()->Add(hist_fourlepteta);
  GetOutputList()->Add(hist_fourleptE);
  GetOutputList()->Add(hist_fourleptphi);
  GetOutputList()->Add(hist_fourleptch);
  GetOutputList()->Add(hist_fourleptID);
  GetOutputList()->Add(hist_fourlept_ptc);
  GetOutputList()->Add(hist_fourleptetc);
  GetOutputList()->Add(hist_fourlepz0);
  GetOutputList()->Add(hist_fourlepd0);

}

////////////////////////////////////////////////////////////////////////////////
void HZZAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_mLL1->Write();
  hist_mLL2->Write();
  hist_fourlepsys_pt->Write();
  hist_fourlepsys_y->Write();

  mass_four_lep->Write();
  mass_ext_four_lep->Write();
  hist_n_jets->Write();


  // Write  Lepton histograms
  hist_fourleptpt->Write();
  hist_fourlepteta->Write();
  hist_fourleptE->Write();
  hist_fourleptphi->Write();
  hist_fourleptch->Write();
  hist_fourleptID->Write();
  hist_fourlept_ptc->Write();
  hist_fourleptetc->Write();
  hist_fourlepz0->Write();
  hist_fourlepd0->Write();

}

void HZZAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Global histograms
  if (s.Contains("hist_mLL1")) hist_mLL1->Fill(m,w);

  if (s.Contains("hist_mLL2")) hist_mLL2->Fill(m,w);

  if (s.Contains("hist_fourlepsys_pt")) hist_fourlepsys_pt->Fill(m,w);

  if (s.Contains("hist_fourlepsys_y")) hist_fourlepsys_y->Fill(m,w);

  if (s.Contains("mass_four_lep")) mass_four_lep->Fill(m,w);

  if (s.Contains("mass_ext_four_lep")) mass_ext_four_lep->Fill(m,w);

  if (s.Contains("hist_n_jets")) hist_n_jets->Fill(m,w);

}

void HZZAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
{
  if (s.Contains("hist_fourleptpt")) hist_fourleptpt->Fill(m,w);
  if (s.Contains("hist_fourlepteta")) hist_fourlepteta->Fill(m,w);
  if (s.Contains("hist_fourleptE")) hist_fourleptE->Fill(m,w);
  if (s.Contains("hist_fourleptphi")) hist_fourleptphi->Fill(m,w);
  if (s.Contains("hist_fourleptch")) hist_fourleptch->Fill(m,w);
  if (s.Contains("hist_fourleptID")) hist_fourleptID->Fill(m,w);
  if (s.Contains("hist_fourlept_ptc")) hist_fourlept_ptc->Fill(m,w);
  if (s.Contains("hist_fourleptetc")) hist_fourleptetc->Fill(m,w);
  if (s.Contains("hist_fourlepz0")) hist_fourlepz0->Fill(m,w);
  if (s.Contains("hist_fourlepd0")) hist_fourlepd0->Fill(m,w);
}





////////////////////////////////////////////////////////////////////////////////
