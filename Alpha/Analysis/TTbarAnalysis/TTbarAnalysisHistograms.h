////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void TTbarAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms
  hist_etmiss       = new TH1F("hist_etmiss",      "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0, 300);
  hist_mtw          = new TH1F("hist_mtw",         "Transverse Mass; M^{W}_{T} [GeV];Events / bin", 20, 0, 300);
  hist_syst_etmiss  = new TH1F("hist_syst_etmiss",      "Missing Transverse Momentum (MET syst);E_{T}^{miss} [GeV] (after E_{T}^{miss} syst. uncert.);Events / bin", 20, 0, 300);
  hist_syst_mtw     = new TH1F("hist_syst_mtw",         "Transverse Mass (MET syst); M^{W}_{T} [GeV] (after E_{T}^{miss} and p_{T}^{lep} syst. uncert.);Events / bin", 20, 0, 300);


  // Jet variables histograms
  hist_n_jets           = new TH1F("hist_n_jets",          "Number of Jets;N_{jets};Events", 5, 3.5, 8.5);
  hist_leadjet_pt       = new TH1F("hist_leadjet_pt",      "Leading Jet Transverse Momentum;p_{T}^{jet} [GeV];Events / bin", 20, 0, 450);
  hist_syst_leadjet_pt  = new TH1F("hist_syst_leadjet_pt",      "Leading Jet Transverse Momentum;p_{T}^{jet} [GeV] (after p_{T}^{jet} syst. uncert.);Events / bin", 20, 0, 450);
  hist_leadjet_eta      = new TH1F("hist_leadjet_eta",     "Leading Jet Pseudorapidity; #eta^{jet}; Events / bin", 30, -3, 3);
  hist_n_bjets          = new TH1F("hist_n_bjets",         "Number of b-jets;N_{b-jets};Events", 3, 1.5, 4.5);
  hist_leadbjet_pt      = new TH1F("hist_leadbjet_pt",     "Leading b-jet Transverse Momentum;p_{T}^{b-jet} [GeV];Events / bin", 20, 0, 350);
  hist_leadbjet_eta     = new TH1F("hist_leadbjet_eta",    "Leading b-jet Pseudorapidity; #eta^{b-jet}; Events / bin", 30, -3, 3);

  // W and top variables
  hist_Topmass       = new TH1F("hist_Topmass",      "Mass of three jets;m_{jjj}^{max p_{T}} [GeV];Events / bin", 40, 100, 250);

  hist_Wmass       = new TH1F("hist_Wmass",      "Mass of two jets;m_{jj}^{max p_{T}} [GeV];Events / bin", 40, 50, 120);



  // Leading Lepton histograms
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Events / bin", 20, 0, 200);
  hist_syst_leadleptpt  = new TH1F("hist_syst_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV] (after p_{T}^{lep} syst. uncert.);Events / bin", 20, 0, 200);

 
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Leading Lepton Pseudorapidity; #eta^{leadlep}; Events / bin", 30, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Leading Lepton Energy; E^{leadlep} [GeV]; Events / bin", 30, 0, 300);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Events / bin", 32, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Leading Lepton Charge; Q^{leadlep}; Events / bin", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Leading Lepton Absolute PDG ID; |PDG ID|^{leadlep}; Events / bin",  15, 5.5, 20.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Leading Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Events / bin", 20, -0.1, 0.2);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Leading Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Events / bin", 20, -0.1, 0.2);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Leading Lepton z0 impact parameter; z_{0}^{leadlep} [mm]; Events / bin", 20, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Leading Lepton d0 impact parameter; d_{0}^{leadlep} [mm]; Events / bin", 20, -0.2, 0.2);
}

////////////////////////////////////////////////////////////////////////////////
void TTbarAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_mtw);
  GetOutputList()->Add(hist_Topmass);
  GetOutputList()->Add(hist_syst_etmiss);
  GetOutputList()->Add(hist_syst_mtw);
  GetOutputList()->Add(hist_Wmass);


  // Add Leading Lepton histograms
  GetOutputList()->Add(hist_leadleptpt);
  GetOutputList()->Add(hist_syst_leadleptpt);
  GetOutputList()->Add(hist_leadlepteta);
  GetOutputList()->Add(hist_leadleptE);
  GetOutputList()->Add(hist_leadleptphi);
  GetOutputList()->Add(hist_leadleptch);
  GetOutputList()->Add(hist_leadleptID);
  GetOutputList()->Add(hist_leadlept_ptc);
  GetOutputList()->Add(hist_leadleptetc);
  GetOutputList()->Add(hist_leadlepz0);
  GetOutputList()->Add(hist_leadlepd0);

  // Add Jet variables histograms
  GetOutputList()->Add(hist_n_jets);
  GetOutputList()->Add(hist_leadjet_pt);
  GetOutputList()->Add(hist_syst_leadjet_pt);
  GetOutputList()->Add(hist_leadjet_eta);
  GetOutputList()->Add(hist_n_bjets);
  GetOutputList()->Add(hist_leadbjet_pt);
  GetOutputList()->Add(hist_leadbjet_eta);


}

////////////////////////////////////////////////////////////////////////////////
void TTbarAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_mtw->Write();
  hist_Topmass->Write();
  hist_syst_etmiss->Write();
  hist_syst_mtw->Write();
  hist_Wmass->Write();


  // Write Leading Lepton histograms
  hist_leadleptpt->Write();
  hist_syst_leadleptpt->Write();
  hist_leadlepteta->Write();
  hist_leadleptE->Write();
  hist_leadleptphi->Write();
  hist_leadleptch->Write();
  hist_leadleptID->Write();
  hist_leadlept_ptc->Write();
  hist_leadleptetc->Write();
  hist_leadlepz0->Write();
  hist_leadlepd0->Write();

  // Write Jet variables histograms
  hist_n_jets->Write();
  hist_leadjet_pt->Write();
  hist_syst_leadjet_pt->Write();
  hist_leadjet_eta->Write();
  hist_n_bjets->Write();
  hist_leadbjet_pt->Write();
  hist_leadbjet_eta->Write();


}

void TTbarAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);
  if (s.Contains("hist_mtw")) hist_mtw->Fill(m,w);
  if (s.Contains("hist_syst_etmiss")) hist_syst_etmiss->Fill(m,w);
  if (s.Contains("hist_syst_mtw")) hist_syst_mtw->Fill(m,w);


}

void TTbarAnalysis::FillHistogramsTTbar( double m, float w , TString s)
{
    if (s.Contains("hist_Topmass")) hist_Topmass->Fill(m,w);
    if (s.Contains("hist_Wmass")) hist_Wmass->Fill(m,w);
}



void TTbarAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
{
  //Leading lepton histograms
  if (s.Contains("hist_leadleptpt")) hist_leadleptpt->Fill(m,w);
  if (s.Contains("hist_syst_leadleptpt")) hist_syst_leadleptpt->Fill(m,w);
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


void TTbarAnalysis::FillHistogramsLeadJet( double m, float w , TString s)
{
  //Leading Jet histograms
  if (s.Contains("hist_n_jets")) hist_n_jets->Fill(m,w);
  if (s.Contains("hist_leadjet_pt")) hist_leadjet_pt->Fill(m,w);
  if (s.Contains("hist_syst_leadjet_pt")) hist_syst_leadjet_pt->Fill(m,w);
  if (s.Contains("hist_leadjet_eta")) hist_leadjet_eta->Fill(m,w);
  if (s.Contains("hist_n_bjets")) hist_n_bjets->Fill(m,w);
  if (s.Contains("hist_leadbjet_pt")) hist_leadbjet_pt->Fill(m,w);
  if (s.Contains("hist_leadbjet_eta")) hist_leadbjet_eta->Fill(m,w);




}


////////////////////////////////////////////////////////////////////////////////
