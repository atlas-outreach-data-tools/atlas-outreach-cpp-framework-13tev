////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void HWWAnalysis::define_histograms()
{
  // HISTOGRAMS
  // Global histograms
  hist_vismass      = new TH1F("hist_vismass",     "Visible Mass; M^{vis}_{ll};Events", 10, 0, 200);
  hist_ptLL         = new TH1F("hist_ptLL",        "Tranvsere Momentum of Dilepton System; p_{T,ll};Events", 10, 0, 200);
  hist_deltaPhiLL   = new TH1F("hist_deltaPhiLL",  "Azimuthal Opening Angle between Leptons; |#Delta#phi_{ll}|;Events", 8, 0, 1.6);
  hist_etmiss       = new TH1F("hist_etmiss",      "Missing Transverse Momentum;E_{T,Miss} [GeV];Events", 10, 0, 200);
  hist_vxp_z        = new TH1F("hist_vxp_z",       "Primary Vertex Position; z_{Vertex}; Events", 10, -200, 200);
  hist_pvxp_n       = new TH1F("hist_pvxp_n",      "Number of Vertices; N_{vertex}; Events", 15, -0.5, 29.5);

  // Leading Lepton histograms
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Leptons", 20, 0, 200);
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Leading Lepton Pseudorapidity; #eta^{leadlep}; Leptons", 10, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Leading Lepton Energy; E^{leadlep} [GeV]; Leptons", 15, 0, 300);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Leptons", 8, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Leading Lepton Charge; Q^{leadlep}; Leptons", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Leading Lepton Absolute PDG ID; |PDG ID|^{leadlep}; Leptons",  31, -0.5, 30.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Leading Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Leptons", 20, -0.1, 0.4);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Leading Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Leptons", 20, -0.1, 0.4);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Leading Lepton z0 impact parameter; z_{0}^{leadlep} [mm]; Leptons", 40, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Leading Lepton d0 impact parameter; d_{0}^{leadlep} [mm]; Leptons", 40, -1, 1);

  // Subleading Lepton histograms
  hist_subleadleptpt  = new TH1F("hist_subleadleptpt", "Subleading Lepton Transverse Momentum;p_{T}^{traillep} [GeV];Leptons", 20, 0, 200);
  hist_subleadlepteta = new TH1F("hist_subleadlepteta","Subleading Lepton Pseudorapidity; #eta^{traillep}; Leptons", 10, -3, 3);
  hist_subleadleptE   = new TH1F("hist_subleadleptE",  "Subleading Lepton Energy; E^{traillep} [GeV]; Leptons", 15, 0, 300);
  hist_subleadleptphi = new TH1F("hist_subleadleptphi","Subleading Lepton Azimuthal Angle ; #phi^{traillep}; Leptons", 8, -3.2, 3.2);
  hist_subleadleptch  = new TH1F("hist_subleadleptch", "Subleading Lepton Charge; Q^{traillep}; Leptons", 7, -1.75, 1.75);
  hist_subleadleptID  = new TH1F("hist_subleadleptID", "Subleading Lepton Absolute PDG ID; |PDG ID|^{traillep}; Leptons",  31, -0.5, 30.5);
  hist_subleadlept_ptc = new TH1F("hist_subleadlept_ptc","Subleading Lepton Relative Transverse Momentum Isolation; ptconerel30^{traillep} [GeV]; Leptons", 20, -0.1, 0.4);
  hist_subleadleptetc = new TH1F("hist_subleadleptetc","Subleading Lepton Relative Transverse Energy Isolation; etconerel20^{traillep} [GeV]; Leptons", 20, -0.1, 0.4);
  hist_subleadlepz0   = new TH1F("hist_subleadlepz0",  "Subleading Lepton z0 impact parameter; z_{0}^{traillep} [mm]; Leptons", 40, -1, 1);
  hist_subleadlepd0   = new TH1F("hist_subleadlepd0",  "Trailing Lepton d0 impact parameter; d_{0}^{traillep} [mm]; Leptons", 40, -1, 1);

}

////////////////////////////////////////////////////////////////////////////////
void HWWAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_vxp_z);
  GetOutputList()->Add(hist_pvxp_n);
  GetOutputList()->Add(hist_vismass);
  GetOutputList()->Add(hist_ptLL);
  GetOutputList()->Add(hist_deltaPhiLL);
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

}

////////////////////////////////////////////////////////////////////////////////
void HWWAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_vxp_z->Write();
  hist_pvxp_n->Write();
  hist_vismass->Write();
  hist_ptLL->Write();
  hist_deltaPhiLL->Write();
  // Write Leading Lepton histograms
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
  // Write Subleading Lepton histograms
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

}

void HWWAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_vismass")) hist_vismass->Fill(m,w);

  if (s.Contains("hist_ptLL")) hist_ptLL->Fill(m,w);

  if (s.Contains("hist_deltaPhiLL")) hist_deltaPhiLL->Fill(m,w);

  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);

  if (s.Contains("hist_vxp_z")) hist_vxp_z->Fill(m,w);

  if (s.Contains("hist_pvxp_n")) hist_pvxp_n->Fill(m,w);

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
