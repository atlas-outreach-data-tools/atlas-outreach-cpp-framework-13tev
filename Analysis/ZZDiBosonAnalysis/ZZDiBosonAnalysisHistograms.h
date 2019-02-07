////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void ZZDiBosonAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms variables
  hist_mLL1         = new TH1F("hist_mLL1",        "Mass of Dilepton System; m_{Z1} [GeV];Events", 10, 60, 120);
  hist_mLL2         = new TH1F("hist_mLL2",        "Mass of Dilepton System; m_{Z2} [GeV];Events", 10, 60, 120);
  hist_vxp_z        = new TH1F("hist_vxp_z",       "Primary Vertex Position; z_{Vertex}; Events", 10, -200,200);
  hist_pvxp_n       = new TH1F("hist_pvxp_n",      "Number of Vertices; N_{vertex}; Events", 10, -0.5,29.5);
  
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
void ZZDiBosonAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_vxp_z);
  GetOutputList()->Add(hist_pvxp_n);
  GetOutputList()->Add(hist_mLL1);
  GetOutputList()->Add(hist_mLL2);
 
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
void ZZDiBosonAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_vxp_z->Write();
  hist_pvxp_n->Write();
  hist_mLL1->Write();
  hist_mLL2->Write();

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

void ZZDiBosonAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Global histograms
  if (s.Contains("hist_mLL1")) hist_mLL1->Fill(m,w);

  if (s.Contains("hist_mLL2")) hist_mLL2->Fill(m,w);

  if (s.Contains("hist_vxp_z")) hist_vxp_z->Fill(m,w);

  if (s.Contains("hist_pvxp_n")) hist_pvxp_n->Fill(m,w);


}

void ZZDiBosonAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
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
