////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void ZPrimeBoostedAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms
  hist_etmiss       = new TH1F("hist_etmiss",      "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 30, 0, 400);
  hist_mtw          = new TH1F("hist_mtw",         "Transverse Mass; M^{W}_{T};Events / bin", 30, 0, 250);

  // Jet variables histograms
  hist_n_jets           = new TH1F("hist_n_jets",          "Number of Jets;N_{selected Small-R jets};Events", 4, -0.5, 3.5);
  hist_leadjet_pt       = new TH1F("hist_leadjet_pt",      "Leading Jet Transverse Momentum; p_{T}^{selected Small-R jet} [GeV];Events / bin", 20, 0, 400);
  hist_leadjet_eta      = new TH1F("hist_leadjet_eta",     "Leading Jet Pseudorapidity; #eta^{selected Small-R jet}; Events / bin", 30, -3, 3);

  hist_n_bjets          = new TH1F("hist_n_bjets",         "Number of b-jets;N_{b-jets};Events", 4, -0.5, 3.5);
  hist_leadbjet_pt      = new TH1F("hist_leadbjet_pt",     "Leading b-jet Transverse Momentum;p_{T}^{b-jet} [GeV];Events / bin", 20, 0, 400);
  hist_leadbjet_eta     = new TH1F("hist_leadbjet_eta",    "Leading b-jet Pseudorapidity; #eta^{b-jet}; Events / bin", 30, -3, 3);

  //largeR jets
  hist_n_leadLRjets           = new TH1F("hist_n_leadLRjets",          "Number of top-tagged Large-R Jets;N^{Large-R jets};Events", 4, -0.5, 3.5);
  hist_leadLRjet_pt       = new TH1F("hist_leadLRjet_pt",      "Large-R Jet Transverse Momentum;p_{T}^{Large-R jet} [GeV];Events / bin", 30, 250, 700);
  hist_leadLRjet_eta      = new TH1F("hist_leadLRjet_eta",     "Large-R Jet Pseudorapidity; #eta^{Large-R jet}; Events / bin", 20, -3, 3);
  hist_leadLRjet_phi      = new TH1F("hist_leadLRjet_phi",     "Large-R Jet phi; #phi^{Large-R jet}; Events / bin", 12, -3.2, 3.2);
  hist_leadLRjet_m        = new TH1F("hist_leadLRjet_m",       "Large-R Jet mass; m^{Large-R jet} [GeV]; Events / bin", 30, 50, 250);
  hist_leadLRjet_tau32    = new TH1F("hist_leadLRjet_tau32",   "Large-R Jet N-subjettiness ratio; #tau_{32}^{Large-R jet} [GeV]; Events / bin", 20, 0, 1);

  // top-tagged largeR jets
  hist_n_TopLRjets           = new TH1F("hist_n_TopLRjets",          "Number of Top-tagged Large-R Jets;N^{Top-tagged Large-R jets};Events", 4, -0.5, 3.5);
  hist_leadTopLRjet_pt       = new TH1F("hist_leadTopLRjet_pt",      "Top-tagged Large-R Jet Transverse Momentum;p_{T}^{Top-tagged Large-R jet} [GeV];Events / bin", 30, 250, 700);
  hist_leadTopLRjet_eta      = new TH1F("hist_leadTopLRjet_eta",     "Top-tagged Large-R Jet Pseudorapidity; #eta^{Top-tagged Large-R jet}; Events / bin", 20, -3, 3);
  hist_leadTopLRjet_phi      = new TH1F("hist_leadTopLRjet_phi",     "Top-tagged Large-R Jet phi; #phi^{Top-tagged Large-R jet}; Events / bin", 12, -3.2, 3.2);
  hist_leadTopLRjet_m        = new TH1F("hist_leadTopLRjet_m",       "Top-tagged Large-R Jet mass; m^{Top-tagged Large-R jet} [GeV]; Events / bin", 25, 100, 250);
  hist_leadTopLRjet_tau32    = new TH1F("hist_leadTopLRjet_tau32",   "Top-tagged Large-R Jet N-subjettiness ratio; #tau_{32}^{Top-tagged Large-R jet} [GeV]; Events / bin", 20, 0, 1);

  // largeR + smallR + lepton (missing neutrino)
  hist_ttbarMLR   = new TH1F("hist_ttbarMLR",  " (Almost) ttbar mass (no neutrino); m^{Top-tagged Large-R jet, Small-R jet, Lepton} [GeV]; Events / bin", 20, 400, 1600);

  // systematics on largeRjets
  hist_leadTopLRjet_syst_pt   = new TH1F("hist_leadTopLRjet_syst_pt",  "Leading  top-tagged Large-R Jet pT after syst; p_{T}^{Top-tagged Large-R jet} [GeV] (after p_{T}^{Large-R Jet} syst.); Events / bin", 30, 250, 700);



  // Leading Lepton histograms
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Leptons", 20, 0, 400);
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Leading Lepton Pseudorapidity; #eta^{leadlep}; Leptons", 30, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Leading Lepton Energy; E^{leadlep} [GeV]; Leptons", 30, 0, 500);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Leptons", 32, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Leading Lepton Charge; Q^{leadlep}; Leptons", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Leading Lepton Absolute PDG ID; |PDG ID|^{leadlep}; Leptons",  15, 5.5, 20.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Leading Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Leptons", 20, -0.1, 0.2);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Leading Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Leptons", 20, -0.1, 0.2);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Leading Lepton z0 impact parameter; z_{0}^{leadlep} [mm]; Leptons", 20, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Leading Lepton d0 impact parameter; d_{0}^{leadlep} [mm]; Leptons", 20, -0.2, 0.2);
}

////////////////////////////////////////////////////////////////////////////////
void ZPrimeBoostedAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_mtw);

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

  // Add Jet variables histograms
  GetOutputList()->Add(hist_n_jets);
  GetOutputList()->Add(hist_leadjet_pt);
  GetOutputList()->Add(hist_leadjet_eta);
  GetOutputList()->Add(hist_n_bjets);
  GetOutputList()->Add(hist_leadbjet_pt);
  GetOutputList()->Add(hist_leadbjet_eta);

  GetOutputList()->Add(hist_n_leadLRjets);
  GetOutputList()->Add(hist_leadLRjet_pt);
  GetOutputList()->Add(hist_leadLRjet_eta);
  GetOutputList()->Add(hist_leadLRjet_phi);
  GetOutputList()->Add(hist_leadLRjet_m);
  GetOutputList()->Add(hist_leadLRjet_tau32);

  GetOutputList()->Add(hist_n_TopLRjets);
  GetOutputList()->Add(hist_leadTopLRjet_pt);
  GetOutputList()->Add(hist_leadTopLRjet_eta);
  GetOutputList()->Add(hist_leadTopLRjet_phi);
  GetOutputList()->Add(hist_leadTopLRjet_m);
  GetOutputList()->Add(hist_leadTopLRjet_tau32);
  GetOutputList()->Add(hist_leadTopLRjet_syst_pt);

  GetOutputList()->Add(hist_ttbarMLR);

}

////////////////////////////////////////////////////////////////////////////////
void ZPrimeBoostedAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_mtw->Write();


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

  // Write Jet variables histograms
  hist_n_jets->Write();
  hist_leadjet_pt->Write();
  hist_leadjet_eta->Write();
  hist_n_bjets->Write();
  hist_leadbjet_pt->Write();
  hist_leadbjet_eta->Write();

  hist_n_leadLRjets->Write();
  hist_leadLRjet_pt->Write();
  hist_leadLRjet_eta->Write();
  hist_leadLRjet_phi->Write();
  hist_leadLRjet_m->Write();
  hist_leadLRjet_tau32->Write();

  hist_n_TopLRjets->Write();
  hist_leadTopLRjet_pt->Write();
  hist_leadTopLRjet_eta->Write();
  hist_leadTopLRjet_phi->Write();
  hist_leadTopLRjet_m->Write();
  hist_leadTopLRjet_tau32->Write();
  hist_leadTopLRjet_syst_pt->Write();

  hist_ttbarMLR->Write();


}

void ZPrimeBoostedAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);
  if (s.Contains("hist_mtw")) hist_mtw->Fill(m,w);

}

void ZPrimeBoostedAnalysis::FillHistogramsBoosted( double m, float w , TString s)
{

if (s.Contains("hist_n_leadLRjets"))  hist_n_leadLRjets->Fill(m,w);
if (s.Contains("hist_leadLRjet_pt"))  hist_leadLRjet_pt->Fill(m,w);
if (s.Contains("hist_leadLRjet_eta"))  hist_leadLRjet_eta->Fill(m,w);
if (s.Contains("hist_leadLRjet_phi"))  hist_leadLRjet_phi->Fill(m,w);
if (s.Contains("hist_leadLRjet_m"))  hist_leadLRjet_m->Fill(m,w);
if (s.Contains("hist_leadLRjet_tau32"))  hist_leadLRjet_tau32->Fill(m,w);


if (s.Contains("hist_n_TopLRjets"))  hist_n_TopLRjets->Fill(m,w);
if (s.Contains("hist_leadTopLRjet_pt"))  hist_leadTopLRjet_pt->Fill(m,w);
if (s.Contains("hist_leadTopLRjet_eta"))  hist_leadTopLRjet_eta->Fill(m,w);
if (s.Contains("hist_leadTopLRjet_phi"))  hist_leadTopLRjet_phi->Fill(m,w);
if (s.Contains("hist_leadTopLRjet_m"))  hist_leadTopLRjet_m->Fill(m,w);
if (s.Contains("hist_leadTopLRjet_tau32"))  hist_leadTopLRjet_tau32->Fill(m,w);
if (s.Contains("hist_leadTopLRjet_syst_pt")) hist_leadTopLRjet_syst_pt->Fill(m,w);


if (s.Contains("hist_ttbarMLR")) hist_ttbarMLR->Fill(m,w);



}



void ZPrimeBoostedAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
{
  //Leading lepton histograms
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


void ZPrimeBoostedAnalysis::FillHistogramsLeadJet( double m, float w , TString s)
{
  //Leading Jet histograms
  if (s.Contains("hist_n_jets")) hist_n_jets->Fill(m,w);
  if (s.Contains("hist_leadjet_pt")) hist_leadjet_pt->Fill(m,w);
  if (s.Contains("hist_leadjet_eta")) hist_leadjet_eta->Fill(m,w);
  if (s.Contains("hist_n_bjets")) hist_n_bjets->Fill(m,w);
  if (s.Contains("hist_leadbjet_pt")) hist_leadbjet_pt->Fill(m,w);
  if (s.Contains("hist_leadbjet_eta")) hist_leadbjet_eta->Fill(m,w);




}


////////////////////////////////////////////////////////////////////////////////
