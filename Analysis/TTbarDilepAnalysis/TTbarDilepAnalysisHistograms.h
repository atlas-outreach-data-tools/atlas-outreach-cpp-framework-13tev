////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void TTbarDilepAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms

  hist_met = new TH1F("hist_met", "Missing Transverse Energy distribution; E_{T}^{miss} [GeV]; Events", 30, 0, 200);
  hist_lep_pt = new TH1F("hist_lep_pt", "p_{T} distribution of the dilepton system; p_{T}^{e #mu} [GeV]; Events", 50, 0, 450);
  hist_lep_eta = new TH1F("hist_lep_eta", "|#eta| distribution of the dilepton system; |#eta_{e #mu}|; Events", 25, 0, 2.5);
  hist_scale_factors = new TH1F("hist_scale_factors", "Scale Factors; SF type; SF", 4, 0, 4);

}

////////////////////////////////////////////////////////////////////////////////
void TTbarDilepAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_met);
  GetOutputList()->Add(hist_lep_pt);
  GetOutputList()->Add(hist_lep_eta);
  GetOutputList()->Add(hist_scale_factors);

}

////////////////////////////////////////////////////////////////////////////////
void TTbarDilepAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_met->Write();
  hist_lep_pt->Write();
  hist_lep_eta->Write();
  hist_scale_factors->Write();
}

void TTbarDilepAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_met")) hist_met->Fill(m,w);
  if (s.Contains("hist_lep_pt")) hist_lep_pt->Fill(m,w);
  if (s.Contains("hist_lep_eta")) hist_lep_eta->Fill(m,w);
 
}



////////////////////////////////////////////////////////////////////////////////
