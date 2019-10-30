////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void ZTauTauAnalysis::define_histograms()
{
  // HISTOGRAMS
  
  // Global variables histograms
  hist_mLL          = new TH1F("hist_mLL",         "Visible mass; m_{vis} [GeV];Events / bin", 30, 20, 100);
  hist_MMC          = new TH1F("hist_MMC",          "Invariant mass (MMC); m^{MMC}_{#tau#tau} [GeV];Events / bin", 15, 50, 200);
  hist_mt_etau      = new TH1F("hist_mt_etau",      "Transverse Mass; m_{T}(e,E_{T}^{miss}) [GeV];Events / bin"  , 30, 1, 150);
  hist_mt_mutau     = new TH1F("hist_mt_mutau",     "Transverse Mass; m_{T}(#mu,E_{T}^{miss}) [GeV];Events / bin", 30, 1, 150);
  hist_sum_dPhi     = new TH1F("hist_sum_dPhi",     "sum dPhi; #Sigma#Delta#phi;Events / bin", 30, 0, 6.3);
  hist_etmiss       = new TH1F("hist_etmiss",      "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0, 150);

  // Jet variables histograms
  hist_n_jets           = new TH1F("hist_n_jets",          "Number of Jets;N_{jets};Events", 6, -0.5, 5.5);
  hist_leadjet_pt       = new TH1F("hist_leadjet_pt",      "Leading Jet Transverse Momentum;p_{T}^{leadjet} [GeV];Jets", 15, 0, 150);
  hist_leadjet_eta      = new TH1F("hist_leadjet_eta",     "Leading Jet Pseudorapidity; #eta^{leadjet}; Jets", 15, -3, 3);

  // Leading Lepton histograms
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Events / bin", 20, 0, 200);
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Leading Lepton Pseudorapidity; #eta^{leadlep}; Events / bin", 20, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Leading Lepton Energy; E^{leadlep} [GeV]; Events / bin", 20, 0, 300);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Events / bin", 20, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Leading Lepton Charge; Q^{leadlep}; Events / bin", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Leading Lepton Absolute PDG ID; |PDG ID|^{leadlep}; Events / bin",  15, 5.5, 20.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Leading Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Events / bin", 40, -0.1, 0.4);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Leading Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Events / bin", 40, -0.1, 0.4);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Leading Lepton z0 impact parameter; z_{0}^{leadlep} [mm]; Events / bin", 40, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Leading Lepton d0 impact parameter; d_{0}^{leadlep} [mm]; Events / bin", 40, -1, 1);

  // leading tau histograms
  hist_taupt  = new TH1F("hist_taupt", "Hadronic tau Transverse Momentum;p_{T}^{#tau_{h}} [GeV];Events / bin", 20, 25, 75);
  hist_taueta = new TH1F("hist_taueta","Hadronic tau Pseudorapidity; #eta^{#tau_{h}}; Events / bin", 20, -3, 3);
  hist_tauE   = new TH1F("hist_tauE",  "Hadronic tau Energy; E^{#tau_{h}} [GeV]; Events / bin", 20, 0, 200);
  hist_tauphi = new TH1F("hist_tauphi","Hadronic tau Azimuthal Angle ; #phi^{#tau_{h}}; Events / bin", 20, -3.2, 3.2);
  hist_tau_nTracks  = new TH1F("hist_tau_nTracks", "Hadronic tau number of tracks ; N_{tracks} (#tau_{h});Events", 5, -0.5, 4.5);
  hist_tau_BDTid    = new TH1F("hist_tau_BDTid", "Hadronic BDTid ; BDTid (#tau_{h});Events / bin"      , 20, 0.6, 1);

  hist_syst_taupt  = new TH1F("hist_syst_taupt", "Hadronic tau Transverse Momentum;p_{T}^{#tau_{h}} [GeV] (after p_{T,#tau_{h}} syst. uncert.);Events / bin", 20, 25, 75);

}

////////////////////////////////////////////////////////////////////////////////
void ZTauTauAnalysis::FillOutputList()
{
  // histograms

  // Add Global variables histograms
  GetOutputList()->Add(hist_etmiss);

  GetOutputList()->Add(hist_sum_dPhi);

  GetOutputList()->Add(hist_mLL);   
  GetOutputList()->Add(hist_MMC);  

  GetOutputList()->Add(hist_mt_etau);
  GetOutputList()->Add(hist_mt_mutau);



  // Add Leading Lepton histograms
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

  // Add Hadronic tau histograms
  GetOutputList()->Add(hist_taupt);
  GetOutputList()->Add(hist_taueta);
  GetOutputList()->Add(hist_tauE);
  GetOutputList()->Add(hist_tauphi);
  GetOutputList()->Add(hist_syst_taupt);

  GetOutputList()->Add(hist_tau_nTracks);
  GetOutputList()->Add(hist_tau_BDTid);

  //Add Jet variables histograms
  GetOutputList()->Add(hist_n_jets);
  GetOutputList()->Add(hist_leadjet_pt);
  GetOutputList()->Add(hist_leadjet_eta);

}

////////////////////////////////////////////////////////////////////////////////
void ZTauTauAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  
  hist_sum_dPhi->Write();
  
  hist_mLL->Write();
  hist_MMC->Write();

  hist_mt_etau->Write();
  hist_mt_mutau->Write();


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

  //Write Hadronic tau histograms
  hist_taupt->Write();
  hist_taueta->Write();
  hist_tauE->Write();
  hist_tauphi->Write();
  hist_syst_taupt->Write();


  hist_tau_nTracks->Write();
  hist_tau_BDTid->Write();


  //Write Jet variables histograms
  hist_n_jets->Write();
  hist_leadjet_pt->Write();
  hist_leadjet_eta->Write();

}

void ZTauTauAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{

  //Fill Global histograms
  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);
  if (s.Contains("hist_sum_dPhi")) hist_sum_dPhi->Fill(m,w);
  if (s.Contains("hist_mLL")) hist_mLL->Fill(m,w);
  if (s.Contains("hist_MMC")) hist_MMC->Fill(m,w);
  if (s.Contains("hist_mt_etau")) hist_mt_etau->Fill(m,w);
  if (s.Contains("hist_mt_mutau")) hist_mt_mutau->Fill(m,w);
  if (s.Contains("hist_n_jets")) hist_n_jets->Fill(m,w);

}

void ZTauTauAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
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

void ZTauTauAnalysis::FillHistogramsTau( double m, float w , TString s)
{
  //Fill Subleading lepton histograms
  if (s.Contains("hist_taupt")) hist_taupt->Fill(m,w);

  if (s.Contains("hist_syst_taupt")) hist_syst_taupt->Fill(m,w);

  if (s.Contains("hist_taueta")) hist_taueta->Fill(m,w);

  if (s.Contains("hist_tauE")) hist_tauE->Fill(m,w);

  if (s.Contains("hist_tauphi")) hist_tauphi->Fill(m,w);

  if (s.Contains("hist_tau_nTracks")) hist_tau_nTracks->Fill(m,w);

  if (s.Contains("hist_tau_BDTid")) hist_tau_BDTid->Fill(m,w);

}

void ZTauTauAnalysis::FillHistogramsLeadJet( double m, float w , TString s)
{
  //Fill Leading Jet histograms
  if (s.Contains("hist_leadjet_pt")) hist_leadjet_pt->Fill(m,w);
  if (s.Contains("hist_leadjet_eta")) hist_leadjet_eta->Fill(m,w);

}

////////////////////////////////////////////////////////////////////////////////
