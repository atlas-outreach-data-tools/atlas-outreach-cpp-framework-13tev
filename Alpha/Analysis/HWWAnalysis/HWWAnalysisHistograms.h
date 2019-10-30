////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void HWWAnalysis::define_histograms()
{
  // HISTOGRAMS
  
  // Global variables histograms
  hist_mLL          = new TH1F("hist_mLL",       "Mass of Dilepton System; m_{ll} [GeV];Events / bin", 30, 0, 170);
  hist_ptLL         = new TH1F("hist_ptLL",      "Transverse Momentum of Dilepton System; p_{T}^{ll} [GeV];Events / bin", 30, 0, 200);
  hist_dPhi_LL      = new TH1F("hist_dPhi_LL",   "dPhi_LL Dilepton System; #Delta#phi (ll);Events / bin", 20, 0, 3.2);
  hist_dPhiLLmet    = new TH1F("hist_dPhiLLmet", "dPhiLLmet Dilepton System; #Delta#phi (ll,E_{T}^{miss});Events / bin", 30, 0, 3.2);
  hist_etmiss       = new TH1F("hist_etmiss",    "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0,200);
  hist_mt           = new TH1F("hist_mt",        "Dilepton System Transverse Mass; m_{T} [GeV];Events / bin", 15, 50, 200);
  hist_n_jets       = new TH1F("hist_n_jets",    "Number of Jets;N_{jets};Events", 5, -0.5, 4.5);
  hist_n_bjets      = new TH1F("hist_n_bjets",   "Number of b-Jets;N_{b-jets};Events", 3, -0.5, 2.5);

  // pre-cut
  histI_mLL          = new TH1F("histI_mLL",       "Mass of Dilepton System; m_{ll} [GeV];Events / bin", 30, 0, 170);
  histI_ptLL         = new TH1F("histI_ptLL",      "Transverse Momentum of Dilepton System; p_{T}^{ll} [GeV];Events / bin", 30, 0, 200);
  histI_dPhi_LL      = new TH1F("histI_dPhi_LL",   "dPhi_LL Dilepton System; #Delta#phi (ll);Events / bin", 20, 0, 3.2);
  histI_dPhiLLmet    = new TH1F("histI_dPhiLLmet", "dPhiLLmet Dilepton System; #Delta#phi (ll,E_{T}^{miss});Events / bin", 30, 0, 3.2);
  histI_etmiss       = new TH1F("histI_etmiss",    "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0,200);
  histI_mt           = new TH1F("histI_mt",        "Dilepton System Transverse Mass; m_{T} [GeV];Events / bin", 15, 50, 200);
  histI_n_jets       = new TH1F("histI_n_jets",    "Number of Jets;N_{jets};Events / bin", 5, -0.5, 4.5);
  histI_n_bjets      = new TH1F("histI_n_bjets",   "Number of b-Jets;N_{b-jets};Events / bin", 3, -0.5, 2.5);

  // Jet variables histograms
  hist_leadjet_pt       = new TH1F("hist_leadjet_pt",      "Leading Jet Transverse Momentum;p_{T}^{leadjet} [GeV];Events / bin", 20, 0, 200);
  hist_leadjet_eta      = new TH1F("hist_leadjet_eta",     "Leading Jet Pseudorapidity; #eta^{leadjet}; Events / bin", 30, -3, 3);

  // Leading Lepton histograms
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Events / bin", 15, 0, 150);
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Leading Lepton Pseudorapidity; #eta^{leadlep}; Events / bin", 10, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Leading Lepton Energy; E^{leadlep} [GeV]; Events / bin", 15, 0, 250);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Events / bin", 16, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Leading Lepton Charge; Q^{leadlep}; Events / bin", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Leading Lepton Absolute PDG ID; |PDG ID|^{leadlep}; Events / bin", 15, 5.5, 20.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Leading Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Events / bin", 40, -0.1, 0.4);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Leading Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Events / bin", 40, -0.1, 0.4);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Leading Lepton z0 impact parameter; z_{0}^{leadlep} [mm]; Events / bin", 40, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Leading Lepton d0 impact parameter; d_{0}^{leadlep} [mm]; Events / bin", 40, -1, 1);

  // Subleading Lepton histograms
  hist_subleadleptpt  = new TH1F("hist_subleadleptpt", "Subleading Lepton Transverse Momentum;p_{T}^{traillep} [GeV];Events / bin", 10, 0, 100);
  hist_subleadlepteta = new TH1F("hist_subleadlepteta","Subleading Lepton Pseudorapidity; #eta^{traillep}; Events / bin", 10, -3, 3);
  hist_subleadleptE   = new TH1F("hist_subleadleptE",  "Subleading Lepton Energy; E^{traillep} [GeV]; Events / bin", 15, 0, 250);
  hist_subleadleptphi = new TH1F("hist_subleadleptphi","Subleading Lepton Azimuthal Angle ; #phi^{traillep}; Events / bin", 10, -3.2, 3.2);
  hist_subleadleptch  = new TH1F("hist_subleadleptch", "Subleading Lepton Charge; Q^{traillep}; Events / bin", 7, -1.75, 1.75);
  hist_subleadleptID  = new TH1F("hist_subleadleptID", "Subleading Lepton Absolute PDG ID; |PDG ID|^{traillep}; Events / bin",  15, 5.5, 20.5);
  hist_subleadlept_ptc = new TH1F("hist_subleadlept_ptc","Subleading Lepton Relative Transverse Momentum Isolation; ptconerel30^{traillep} [GeV]; Events / bin", 40, -0.1, 0.4);
  hist_subleadleptetc = new TH1F("hist_subleadleptetc","Subleading Lepton Relative Transverse Energy Isolation; etconerel20^{traillep} [GeV]; Events / bin", 40, -0.1, 0.4);
  hist_subleadlepz0   = new TH1F("hist_subleadlepz0",  "Subleading Lepton z0 impact parameter; z_{0}^{traillep} [mm]; Events / bin", 40, -1, 1);
  hist_subleadlepd0   = new TH1F("hist_subleadlepd0",  "Trailing Lepton d0 impact parameter; d_{0}^{traillep} [mm]; Events / bin", 40, -1, 1);

}

////////////////////////////////////////////////////////////////////////////////
void HWWAnalysis::FillOutputList()
{
  // histograms

  // Add Global variables histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_mLL);  
  GetOutputList()->Add(hist_ptLL);  
  GetOutputList()->Add(hist_dPhi_LL);
  GetOutputList()->Add(hist_dPhiLLmet);
  GetOutputList()->Add(hist_mt);

  GetOutputList()->Add(histI_etmiss);
  GetOutputList()->Add(histI_mLL);
  GetOutputList()->Add(histI_ptLL);
  GetOutputList()->Add(histI_dPhi_LL);
  GetOutputList()->Add(histI_dPhiLLmet);
  GetOutputList()->Add(histI_mt);




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

  // Add Subleading Lepton histograms
  GetOutputList()->Add(hist_subleadleptpt);
  GetOutputList()->Add(hist_subleadlepteta);
  GetOutputList()->Add(hist_subleadleptE);
  GetOutputList()->Add(hist_subleadleptphi);
  GetOutputList()->Add(hist_subleadleptch);
  GetOutputList()->Add(hist_subleadleptID);
  GetOutputList()->Add(hist_subleadlept_ptc);
  GetOutputList()->Add(hist_subleadleptetc);
  GetOutputList()->Add(hist_subleadlepz0);
  GetOutputList()->Add(hist_subleadlepd0);

  //Add Jet variables histograms
  GetOutputList()->Add(hist_n_jets);
  GetOutputList()->Add(hist_n_bjets);
  GetOutputList()->Add(histI_n_jets);
  GetOutputList()->Add(histI_n_bjets);



  GetOutputList()->Add(hist_leadjet_pt);
  GetOutputList()->Add(hist_leadjet_eta);

}

////////////////////////////////////////////////////////////////////////////////
void HWWAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_mLL->Write();  
  hist_ptLL->Write();  
  hist_dPhi_LL->Write();
  hist_dPhiLLmet->Write();
  hist_mt->Write();

  histI_etmiss->Write();
  histI_mLL->Write();
  histI_ptLL->Write();
  histI_dPhi_LL->Write();
  histI_dPhiLLmet->Write();
  histI_mt->Write();



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

  //Write Subleading Lepton histograms
  hist_subleadleptpt->Write();
  hist_subleadlepteta->Write();
  hist_subleadleptE->Write();
  hist_subleadleptphi->Write();
  hist_subleadleptch->Write();
  hist_subleadleptID->Write();
  hist_subleadlept_ptc->Write();
  hist_subleadleptetc->Write();
  hist_subleadlepz0->Write();
  hist_subleadlepd0->Write();

  //Write Jet variables histograms
  hist_n_jets->Write();
  hist_n_bjets->Write();

  histI_n_jets->Write();
  histI_n_bjets->Write();





  hist_leadjet_pt->Write();
  hist_leadjet_eta->Write();

}

void HWWAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{

  //Fill Global histograms
  if (s.Contains("hist_mLL"))    hist_mLL->Fill(m,w);  
  if (s.Contains("hist_ptLL"))   hist_ptLL->Fill(m,w);  
  if (s.Contains("hist_dPhi_LL")) hist_dPhi_LL->Fill(m,w);
  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);
  if (s.Contains("hist_mt"))     hist_mt->Fill(m,w);
  if (s.Contains("hist_dPhiLLmet")) hist_dPhiLLmet->Fill(m,w);
  if (s.Contains("hist_n_jets")) hist_n_jets->Fill(m,w);
  if (s.Contains("hist_n_bjets")) hist_n_bjets->Fill(m,w);

  if (s.Contains("histI_mLL"))    histI_mLL->Fill(m,w);
  if (s.Contains("histI_ptLL"))   histI_ptLL->Fill(m,w);
  if (s.Contains("histI_dPhi_LL")) histI_dPhi_LL->Fill(m,w);
  if (s.Contains("histI_etmiss")) histI_etmiss->Fill(m,w);
  if (s.Contains("histI_mt"))     histI_mt->Fill(m,w);
  if (s.Contains("histI_dPhiLLmet")) histI_dPhiLLmet->Fill(m,w);
  if (s.Contains("histI_n_jets")) histI_n_jets->Fill(m,w);
  if (s.Contains("histI_n_bjets")) histI_n_bjets->Fill(m,w);




}

void HWWAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
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

void HWWAnalysis::FillHistogramsSubleadlept( double m, float w , TString s)
{
  //Fill Subleading lepton histograms
  if (s.Contains("hist_subleadleptpt")) hist_subleadleptpt->Fill(m,w);

  if (s.Contains("hist_subleadlepteta")) hist_subleadlepteta->Fill(m,w);

  if (s.Contains("hist_subleadleptE")) hist_subleadleptE->Fill(m,w);

  if (s.Contains("hist_subleadleptphi")) hist_subleadleptphi->Fill(m,w);

  if (s.Contains("hist_subleadleptch")) hist_subleadleptch->Fill(m,w);

  if (s.Contains("hist_subleadleptID")) hist_subleadleptID->Fill(m,w);

  if (s.Contains("hist_subleadlept_ptc")) hist_subleadlept_ptc->Fill(m,w);

  if (s.Contains("hist_subleadleptetc")) hist_subleadleptetc->Fill(m,w);

  if (s.Contains("hist_subleadlepz0")) hist_subleadlepz0->Fill(m,w);

  if (s.Contains("hist_subleadlepd0")) hist_subleadlepd0->Fill(m,w);
}

////////////////////////////////////////////////////////////////////////////////
