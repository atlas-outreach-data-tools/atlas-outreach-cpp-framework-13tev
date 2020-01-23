////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void WBosonAnalysis::define_histograms()
{
  // HISTOGRAMS

  //Global variables
  hist_etmiss       = new TH1F("hist_etmiss",       "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 30, 0, 200);
  hist_mtw          = new TH1F("hist_mtw",          "Transverse Mass; M^{W}_{T} [GeV];Events / bin", 40, 39, 180);
  hist_mtw_enu      = new TH1F("hist_mtw_enu",      "Transverse Mass; M^{W #rightarrow e#nu}_{T} [GeV];Events / bin", 40, 39, 180);
  hist_mtw_munu     = new TH1F("hist_mtw_munu",     "Transverse Mass; M^{W #rightarrow #mu#nu}_{T} [GeV];Events / bin", 40, 39, 180);
    
  // Jet variables
  hist_n_jets       = new TH1F("hist_n_jets",      "Number of Jets;N_{jets};Events", 6, -0.5, 5.5);
  hist_leadjet_pt   = new TH1F("hist_leadjet_pt",  "Leading Jet Transverse Momentum;p_{T}^{jet} [GeV];Events / bin", 20, 0, 120);
  hist_leadjet_eta  = new TH1F("hist_leadjet_eta", "Leading Jet Pseudorapidity; #eta^{jet}; Events / bin", 30, -3, 3);

  // Leading Lepton variables
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Lepton Transverse Momentum;p_{T}^{lep} [GeV];Events / bin", 20, 0, 200);
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Lepton Pseudorapidity; #eta^{lep}; Events / bin", 30, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Lepton Energy; E^{lep} [GeV]; Events / bin", 30, 0, 300);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Lepton Azimuthal Angle ; #phi^{lep}; Events / bin", 32, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Lepton Charge; Q^{lep}; Events / bin", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Lepton Absolute PDG ID; |PDG ID|^{lep}; Events / bin",  15, 5.5, 20.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Events / bin", 20, -0.1, 0.2);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Events / bin", 20, -0.1, 0.2);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Lepton longitudinal impact parameter; z_{0}^{lep} [mm]; Events / bin", 20, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Lepton transverse impact parameter; d_{0}^{lep} [mm]; Events / bin", 20, -5, 5);

}

////////////////////////////////////////////////////////////////////////////////
void WBosonAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_mtw);  GetOutputList()->Add(hist_mtw_enu);  GetOutputList()->Add(hist_mtw_munu);

  //Add Leading Lepton histograms
  GetOutputList()->Add(hist_leadleptpt);
  GetOutputList()->Add(hist_leadlepteta);
  GetOutputList()->Add(hist_leadleptE);
  GetOutputList()->Add(hist_leadleptphi);
  GetOutputList()->Add(hist_leadleptch);
  GetOutputList()->Add(hist_leadleptID);
  GetOutputList()->Add(hist_leadlept_ptc);
  GetOutputList()->Add(hist_leadleptetc);
  GetOutputList()->Add(hist_leadlepz0);
  GetOutputList()->Add(hist_leadlepd0);

  //Add Jet histograms
  GetOutputList()->Add(hist_n_jets);
  GetOutputList()->Add(hist_leadjet_pt);
  GetOutputList()->Add(hist_leadjet_eta);
}

////////////////////////////////////////////////////////////////////////////////
void WBosonAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_mtw->Write();  hist_mtw_enu->Write();  hist_mtw_munu->Write();
  //Write Leading Lepton histograms
  hist_leadleptpt->Write();
  hist_leadlepteta->Write();
  hist_leadleptE->Write();
  hist_leadleptphi->Write();
  hist_leadleptch->Write();
  hist_leadleptID->Write();
  hist_leadlept_ptc->Write();
  hist_leadleptetc->Write();
  hist_leadlepz0->Write();
  hist_leadlepd0->Write();
  //Write Jet histograms
  hist_n_jets->Write();
  hist_leadjet_pt->Write();
  hist_leadjet_eta->Write();
}

void WBosonAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);

  if (s.Contains("hist_mtw_enu")) hist_mtw_enu->Fill(m,w);

  if (s.Contains("hist_mtw_munu")) hist_mtw_munu->Fill(m,w);

  if (s.Contains("hist_mtw")) hist_mtw->Fill(m,w);

}

void WBosonAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
{
  //Fill Leading lepton histograms
  if (s.Contains("hist_leadleptpt")) hist_leadleptpt->Fill(m,w);

  if (s.Contains("hist_leadlepteta")) hist_leadlepteta->Fill(m,w);

  if (s.Contains("hist_leadleptE")) hist_leadleptE->Fill(m,w);

  if (s.Contains("hist_leadleptphi")) hist_leadleptphi->Fill(m,w);

  if (s.Contains("hist_leadleptch")) hist_leadleptch->Fill(m,w);

  if (s.Contains("hist_leadleptID")) hist_leadleptID->Fill(m,w);

  if (s.Contains("hist_leadlept_ptc")) hist_leadlept_ptc->Fill(m,w);

  if (s.Contains("hist_leadleptetc")) hist_leadleptetc->Fill(m,w);

  if (s.Contains("hist_leadlepz0")) hist_leadlepz0->Fill(m,w);

  if (s.Contains("hist_leadlepd0")) hist_leadlepd0->Fill(m,w);
}


void WBosonAnalysis::FillHistogramsLeadJet( double m, float w , TString s)
{
  //Fill Leading Jet histograms
  if (s.Contains("hist_n_jets")) hist_n_jets->Fill(m,w);

  if (s.Contains("hist_leadjet_pt")) hist_leadjet_pt->Fill(m,w);

  if (s.Contains("hist_leadjet_eta")) hist_leadjet_eta->Fill(m,w);

}
