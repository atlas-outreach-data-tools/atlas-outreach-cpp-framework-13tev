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
  hist_mLL1         = new TH1F("hist_mLL1",        "Mass of Dilepton System; m_{Z1} [GeV];Events", 30, 50, 106);
  hist_mLL2         = new TH1F("hist_mLL2",        "Mass of Dilepton System; m_{Z2} [GeV];Events", 30, 12, 115);

  hist_fourlepsys_pt_win  = new TH1F("hist_fourlepsys_pt_win",        "Transverse Momentum of four-lepton system; p_{T,4l} [GeV];Events", 10, 0, 100);
  hist_fourlepsys_pt        = new TH1F("hist_fourlepsys_pt",        "Transverse Momentum of four-lepton system; p_{T,4l} [GeV];Events", 20, 0, 200);
  hist_fourlepsys_y         = new TH1F("hist_fourlepsys_y",         "Rapidity of four-lepton system; y_{4l} ;Events", 20, -3, 3);
  hist_fourlepsys_y_win     = new TH1F("hist_fourlepsys_y_win",     "Rapidity of four-lepton system; y_{4l} ;Events", 10, -3, 3);

  mass_four_lep_ext = new TH1F("mass_four_lep_ext",     "Mass of four-lepton system; m_{4l} [GeV];Events",30, 80, 250);
  mass_four_lep     = new TH1F("mass_four_lep",         "Mass of four-lepton system; m_{4l} [GeV];Events",15, 115, 130);
  mass_four_mu_win  = new TH1F("mass_four_mu_win",      "Mass of four-lepton system; m_{4#mu} [GeV];Events",15, 115, 130);
  mass_four_e_win   = new TH1F("mass_four_e_win",       "Mass of four-lepton system; m_{4e} [GeV];Events",15, 115, 130);
  mass_twomu_twoe_win = new TH1F("mass_twomu_twoe_win", "Mass of four-lepton system; m_{2e2#mu} [GeV];Events",15, 115, 130);

  hist_n_jets       = new TH1F("hist_n_jets",          "Number of Jets;N_{jets};Events", 4, -0.5, 3.5);



  // Lepton histograms
  hist_fourleptpt   = new TH1F("hist_fourleptpt",  " Leptons Transverse Momentum;p_{T}^{all lep} [GeV];Leptons", 5, 0, 200);
  hist_fourlepteta  = new TH1F("hist_fourlepteta", " Leptons Pseudorapidity; #eta^{all lep}; Leptons", 10, -3, 3);
  hist_fourleptE    = new TH1F("hist_fourleptE",   " Leptons Energy; E^{all lep} [GeV]; Leptons", 10, 0, 300);
  hist_fourleptphi  = new TH1F("hist_fourleptphi", " Leptons Azimuthal Angle ; #phi^{all lep}; Leptons", 8, -3.2, 3.2);
  hist_fourleptch   = new TH1F("hist_fourleptch",  " Leptons Charge; Q^{all lep}; Leptons", 7, -1.75, 1.75);
  hist_fourleptID   = new TH1F("hist_fourleptID",  " Leptons Absolute PDG ID; |PDG ID|^{all lep}; Leptons",  31, -0.5, 30.5);
  hist_fourlept_ptc  = new TH1F("hist_fourlept_ptc", " Leptons Relative Transverse Momentum Isolation; ptconerel30^{all lep}; Leptons", 10, -0.1, 0.4);
  hist_fourleptetc  = new TH1F("hist_fourleptetc", " Lepton Relative Transverse Energy Isolation; etconerel20^{all lep}; Leptons", 10, -0.1, 0.4);
  hist_fourlepz0    = new TH1F("hist_fourlepz0",   " Lepton z0 impact parameter; z_{0}^{all lep} [mm]; Leptons", 20, -1, 1);
  hist_fourlepd0    = new TH1F("hist_fourlepd0",   " Lepton d0 impact parameter; d_{0}^{all lep} [mm]; Leptons", 20, -1, 1);

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
  GetOutputList()->Add(hist_fourlepsys_pt_win);
  GetOutputList()->Add(hist_fourlepsys_y_win);
 
  GetOutputList()->Add(mass_four_lep);
  GetOutputList()->Add(mass_four_lep_ext);
  GetOutputList()->Add(mass_four_mu_win);
  GetOutputList()->Add(mass_four_e_win);
  GetOutputList()->Add(mass_twomu_twoe_win);

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
  hist_fourlepsys_pt_win->Write();
  hist_fourlepsys_y_win->Write();

  mass_four_lep->Write();
  mass_four_lep_ext->Write();
  mass_four_mu_win->Write();
  mass_four_e_win->Write();
  mass_twomu_twoe_win->Write();
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

  if (s.Contains("hist_fourlepsys_pt_win")) hist_fourlepsys_pt_win->Fill(m,w);

  if (s.Contains("hist_fourlepsys_y_win")) hist_fourlepsys_y_win->Fill(m,w);

  if (s.Contains("mass_four_lep")) mass_four_lep->Fill(m,w);

  if (s.Contains("mass_four_lep_ext")) mass_four_lep_ext->Fill(m,w);

  if (s.Contains("mass_four_mu_win")) mass_four_mu_win->Fill(m,w);

  if (s.Contains("mass_four_e_win")) mass_four_e_win->Fill(m,w);

  if (s.Contains("mass_twomu_twoe_win")) mass_twomu_twoe_win->Fill(m,w);

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
