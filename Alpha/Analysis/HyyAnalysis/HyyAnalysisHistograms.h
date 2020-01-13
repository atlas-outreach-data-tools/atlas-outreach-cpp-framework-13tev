////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void HyyAnalysis::define_histograms()
{
  hist_mYY_bin1   = new TH1F("hist_mYY_bin1","Diphoton invariant mass; m_{#gamma#gamma} [GeV];Events / bin", 30, 105, 160.);
  hist_mYY_cat_bin1   = new TH1F("hist_mYY_cat_bin1","Diphoton invariant mass unconv. central; m_{#gamma#gamma} [GeV];Events / bin", 30, 105, 160.);
}
////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::FillOutputList()
{
  GetOutputList()->Add(hist_mYY_bin1);
  GetOutputList()->Add(hist_mYY_cat_bin1);
}
////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::WriteHistograms()
{
  hist_mYY_bin1->Write();
  hist_mYY_cat_bin1->Write();
}
////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  if (s.Contains("hist_mYY_bin1")) hist_mYY_bin1->Fill(m,w);
  if (s.Contains("hist_mYY_cat_bin1")) hist_mYY_cat_bin1->Fill(m,w);
}
////////////////////////////////////////////////////////////////////////////////
