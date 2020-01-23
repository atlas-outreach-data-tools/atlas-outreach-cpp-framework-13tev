////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void WZDiBosonAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms variables
  hist_mLL           = new TH1F("hist_mLL",          "Mass of Dilepton System; m_{ll} [GeV];Events / bin", 20, 76, 106);
  hist_etmiss        = new TH1F("hist_etmiss",       "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0, 160);
  hist_mtw           = new TH1F("hist_mtw",          "Transverse Mass; M^{W}_{T} [GeV];Events / bin", 20, 0, 200);
  hist_ptLL          = new TH1F("hist_ptLL",         "Transverse momentum of Dilepton System; p^{ll}_{T} [GeV];Events / bin", 20, 0, 400);

  // Lepton histograms
  hist_threeleptpt   = new TH1F("hist_threeleptpt",  " Lepton Transverse Momentum;p_{T}^{all lep} [GeV]; Leptons / bin", 10, 25, 200);
  hist_threelepteta  = new TH1F("hist_threelepteta", " Lepton Pseudorapidity; #eta^{all lep}; Leptons / bin", 15, -3, 3);
  hist_threeleptE    = new TH1F("hist_threeleptE",   " Lepton Energy; E^{all lep} [GeV]; Leptons / bin", 15, 0, 300);
  hist_threeleptphi  = new TH1F("hist_threeleptphi", " Lepton Azimuthal Angle ; #phi^{all lep}; Leptons / bin", 16, -3.2, 3.2);
  hist_threeleptch   = new TH1F("hist_threeleptch",  " Lepton Charge; Q^{all lep}; Leptons / bin", 7, -1.75, 1.75);
  hist_threeleptID   = new TH1F("hist_threeleptID",  " Lepton Absolute PDG ID; |PDG ID|^{all lep}; Leptons / bin",  15, 5.5, 20.5);
  hist_threelept_ptc  = new TH1F("hist_threelept_ptc", " Lepton Relative Transverse Momentum Isolation; ptconerel30^{all lep}; Leptons / bin", 10, -0.1, 0.2);
  hist_threeleptetc  = new TH1F("hist_threeleptetc", " Lepton Relative Transverse Energy Isolation; etconerel20^{all lep}; Leptons / bin", 10, -0.1, 0.2);
  hist_threelepz0    = new TH1F("hist_threelepz0",   " Lepton z0 impact parameter; z_{0}^{all lep} [mm]; Leptons / bin", 10, -1, 1);
  hist_threelepd0    = new TH1F("hist_threelepd0",   " Lepton d0 impact parameter; d_{0}^{all lep} [mm]; Leptons / bin", 10, -0.2, 0.2);

}

////////////////////////////////////////////////////////////////////////////////
void WZDiBosonAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_mLL);
  GetOutputList()->Add(hist_mtw);
  GetOutputList()->Add(hist_ptLL);

 // Add  Lepton histograms
  GetOutputList()->Add(hist_threeleptpt);
  GetOutputList()->Add(hist_threelepteta);
  GetOutputList()->Add(hist_threeleptE);
  GetOutputList()->Add(hist_threeleptphi);
  GetOutputList()->Add(hist_threeleptch);
  GetOutputList()->Add(hist_threeleptID);
  GetOutputList()->Add(hist_threelept_ptc);
  GetOutputList()->Add(hist_threeleptetc);
  GetOutputList()->Add(hist_threelepz0);
  GetOutputList()->Add(hist_threelepd0);

}

////////////////////////////////////////////////////////////////////////////////
void WZDiBosonAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_mLL->Write();
  hist_mtw->Write();
  hist_ptLL->Write();

  // Write  Lepton histograms
  hist_threeleptpt->Write();
  hist_threelepteta->Write();
  hist_threeleptE->Write();
  hist_threeleptphi->Write();
  hist_threeleptch->Write();
  hist_threeleptID->Write();
  hist_threelept_ptc->Write();
  hist_threeleptetc->Write();
  hist_threelepz0->Write();
  hist_threelepd0->Write();

}

void WZDiBosonAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Global histograms
  if (s.Contains("hist_mLL")) hist_mLL->Fill(m,w);

  if (s.Contains("hist_ptLL")) hist_ptLL->Fill(m,w);

  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);

  if (s.Contains("hist_mtw")) hist_mtw->Fill(m,w);

}

void WZDiBosonAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
{
  if (s.Contains("hist_threeleptpt")) hist_threeleptpt->Fill(m,w);
  if (s.Contains("hist_threelepteta")) hist_threelepteta->Fill(m,w);
  if (s.Contains("hist_threeleptE")) hist_threeleptE->Fill(m,w);
  if (s.Contains("hist_threeleptphi")) hist_threeleptphi->Fill(m,w);
  if (s.Contains("hist_threeleptch")) hist_threeleptch->Fill(m,w);
  if (s.Contains("hist_threeleptID")) hist_threeleptID->Fill(m,w);
  if (s.Contains("hist_threelept_ptc")) hist_threelept_ptc->Fill(m,w);
  if (s.Contains("hist_threeleptetc")) hist_threeleptetc->Fill(m,w);
  if (s.Contains("hist_threelepz0")) hist_threelepz0->Fill(m,w);
  if (s.Contains("hist_threelepd0")) hist_threelepd0->Fill(m,w);
}





////////////////////////////////////////////////////////////////////////////////
