////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void HyyAnalysis::define_histograms()
{
  hist_mYY_bin1   = new TH1F("hist_mYY_bin1","Diphoton invariant mass; m_{#gamma#gamma} [GeV];Events / bin", 60, 100, 160.);
  hist_mYY_cat_bin1   = new TH1F("hist_mYY_cat_bin1","Diphoton invariant mass unconv. central; m_{#gamma#gamma} [GeV];Events / bin", 60, 100, 160.);

  // Scaling factors histogram
  hist_scale_factors = new TH1F("hist_scale_factors", "Scale Factors; SF type; SF", 4, 0, 4);

}
////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::FillOutputList()
{
  GetOutputList()->Add(hist_mYY_bin1);
  GetOutputList()->Add(hist_mYY_cat_bin1);

  // Scaling factors histogram
  GetOutputList()->Add(hist_scale_factors);
}
////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::WriteHistograms()
{
  hist_mYY_bin1->Write();
  hist_mYY_cat_bin1->Write();

  // Scaling factors histogram
  hist_scale_factors->Write();
}
////////////////////////////////////////////////////////////////////////////////
void HyyAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  if (s.Contains("hist_mYY_bin1")) hist_mYY_bin1->Fill(m,w);
  if (s.Contains("hist_mYY_cat_bin1")) hist_mYY_cat_bin1->Fill(m,w);
}
////////////////////////////////////////////////////////////////////////////////
