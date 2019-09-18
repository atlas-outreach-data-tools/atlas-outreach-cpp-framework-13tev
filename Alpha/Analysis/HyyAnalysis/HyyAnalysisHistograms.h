////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void HyyAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms variables
  hist_mYY_incl   = new TH1F("hist_mYY_incl","Diphoton invariant mass; m_{#gamma#gamma} [GeV];Events", 25, 105, 160.);
  hist_mYY_win   = new TH1F("hist_mYY_win","Diphoton invariant mass; m_{#gamma#gamma} [GeV];Events", 55, 105, 160.);
  hist_mYY_pt   = new TH1F("hist_mYY_pt","Diphoton invariant mass; m_{#gamma#gamma} [GeV];Events", 30, 105, 160.);




}

////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_mYY_incl);
  GetOutputList()->Add(hist_mYY_win);
  GetOutputList()->Add(hist_mYY_pt);


}

////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_mYY_incl->Write();
  hist_mYY_win->Write();
  hist_mYY_pt->Write();

}

void HyyAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Global histograms
  if (s.Contains("hist_mYY_incl")) hist_mYY_incl->Fill(m,w);
  if (s.Contains("hist_mYY_win")) hist_mYY_win->Fill(m,w);
  if (s.Contains("hist_mYY_pt")) hist_mYY_pt->Fill(m,w);


}

////////////////////////////////////////////////////////////////////////////////
