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

  // Scale factors histograms

  hist_ScaleFactor_PILEUP = new TH1F("hist_ScaleFactor_PILEUP", "Scale Factor for PILEUP; ; Events / 0.1 bins", 100, -2, 4);
  hist_ScaleFactor_BTAG = new TH1F("hist_ScaleFactor_BTAG", "Scale Factor for BTAG; ; Events / 0.05 bins", 100, -2, 4);
  hist_ScaleFactor_ELE = new TH1F("hist_ScaleFactor_ELE", "Scale Factor for ELE; ; Events / 0.05 bins", 100, -2, 4);
  hist_ScaleFactor_MUON = new TH1F("hist_ScaleFactor_MUON", "Scale Factor for MUON; ; Events / 0.05 bins", 100, -2, 4);
  hist_ScaleFactor_PHOTON = new TH1F("hist_ScaleFactor_PHOTON", "Scale Factor for PHOTON; ; Events / 0.05 bins", 100, -2, 4);
  hist_ScaleFactor_TAU = new TH1F("hist_ScaleFactor_TAU", "Scale Factor for TAU; ; Events / 0.05 bins", 100, -1, 4);
  hist_ScaleFactor_lepTRIGGER = new TH1F("hist_ScaleFactor_lepTRIGGER", "Scale Factor for lepTRIGGER; ; Events / 0.05 bins", 100, -1, 4);
  hist_ScaleFactor_JVT = new TH1F("hist_ScaleFactor_JVT", "Scale Factor for JVT; ; Events / 0.05 bins", 100, -1, 4);
  
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

  // Scale factors histograms

  GetOutputList()->Add(hist_ScaleFactor_PILEUP);
  GetOutputList()->Add(hist_ScaleFactor_BTAG);
  GetOutputList()->Add(hist_ScaleFactor_ELE);
  GetOutputList()->Add(hist_ScaleFactor_MUON);
  GetOutputList()->Add(hist_ScaleFactor_PHOTON);
  GetOutputList()->Add(hist_ScaleFactor_TAU);
  GetOutputList()->Add(hist_ScaleFactor_lepTRIGGER);
  GetOutputList()->Add(hist_ScaleFactor_JVT);
  
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

  hist_ScaleFactor_PHOTON->Write();
  hist_ScaleFactor_ELE->Write();
  hist_ScaleFactor_MUON->Write();
  hist_ScaleFactor_TAU->Write();
  hist_ScaleFactor_BTAG->Write();
  hist_ScaleFactor_PILEUP->Write();
  hist_ScaleFactor_lepTRIGGER->Write();
  hist_ScaleFactor_JVT->Write();
  
}

void TTbarDilepAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_met")) hist_met->Fill(m,w);
  if (s.Contains("hist_lep_pt")) hist_lep_pt->Fill(m,w);
  if (s.Contains("hist_lep_eta")) hist_lep_eta->Fill(m,w);
 
}


void TTbarDilepAnalysis::mc_under_and_overflow(){

  //*******************************************
  // Add the contents of the underflow bin to the first bin
  //*******************************************

  // For hist_ScaleFactor_PILEUP
  if (TMath::Abs(hist_ScaleFactor_PILEUP->GetBinContent(0)) > 0) {
    hist_ScaleFactor_PILEUP->AddBinContent(1, hist_ScaleFactor_PILEUP->GetBinContent(0));
  }

  // For hist_ScaleFactor_BTAG
  if (TMath::Abs(hist_ScaleFactor_BTAG->GetBinContent(0)) > 0) {
    hist_ScaleFactor_BTAG->AddBinContent(1, hist_ScaleFactor_BTAG->GetBinContent(0));
  }

  // For hist_ScaleFactor_ELE
  if (TMath::Abs(hist_ScaleFactor_ELE->GetBinContent(0)) > 0) {
    hist_ScaleFactor_ELE->AddBinContent(1, hist_ScaleFactor_ELE->GetBinContent(0));
  }

  // For hist_ScaleFactor_MUON
  if (TMath::Abs(hist_ScaleFactor_MUON->GetBinContent(0)) > 0) {
    hist_ScaleFactor_MUON->AddBinContent(1, hist_ScaleFactor_MUON->GetBinContent(0));
  }

  // For hist_ScaleFactor_PHOTON
  if (TMath::Abs(hist_ScaleFactor_PHOTON->GetBinContent(0)) > 0) {
    hist_ScaleFactor_PHOTON->AddBinContent(1, hist_ScaleFactor_PHOTON->GetBinContent(0));
  }

  // For hist_ScaleFactor_TAU
  if (TMath::Abs(hist_ScaleFactor_TAU->GetBinContent(0)) > 0) {
    hist_ScaleFactor_TAU->AddBinContent(1, hist_ScaleFactor_TAU->GetBinContent(0));
  }

  // For hist_ScaleFactor_lepTRIGGER
  if (TMath::Abs(hist_ScaleFactor_lepTRIGGER->GetBinContent(0)) > 0) {
    hist_ScaleFactor_lepTRIGGER->AddBinContent(1, hist_ScaleFactor_lepTRIGGER->GetBinContent(0));
  }

  // For hist_ScaleFactor_JVT
  if (TMath::Abs(hist_ScaleFactor_JVT->GetBinContent(0)) > 0) {
    hist_ScaleFactor_JVT->AddBinContent(1, hist_ScaleFactor_JVT->GetBinContent(0));
  }

  //*******************************************
  // Add the contents of the overflow bin to the first bin
  //*******************************************

  // For hist_ScaleFactor_PILEUP
  if( TMath::Abs(hist_ScaleFactor_PILEUP->GetBinContent(hist_ScaleFactor_PILEUP->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_PILEUP->AddBinContent(hist_ScaleFactor_PILEUP->GetNbinsX(), hist_ScaleFactor_PILEUP->GetBinContent(hist_ScaleFactor_PILEUP->GetNbinsX()+1));
  }

  // For hist_ScaleFactor_BTAG
  if( TMath::Abs(hist_ScaleFactor_BTAG->GetBinContent(hist_ScaleFactor_BTAG->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_BTAG->AddBinContent(hist_ScaleFactor_BTAG->GetNbinsX(), hist_ScaleFactor_BTAG->GetBinContent(hist_ScaleFactor_BTAG->GetNbinsX()+1));
  }

  // For hist_ScaleFactor_ELE
  if( TMath::Abs(hist_ScaleFactor_ELE->GetBinContent(hist_ScaleFactor_ELE->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_ELE->AddBinContent(hist_ScaleFactor_ELE->GetNbinsX(), hist_ScaleFactor_ELE->GetBinContent(hist_ScaleFactor_ELE->GetNbinsX()+1));
  }
  
  // For hist_ScaleFactor_MUON
  if( TMath::Abs(hist_ScaleFactor_MUON->GetBinContent(hist_ScaleFactor_MUON->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_MUON->AddBinContent(hist_ScaleFactor_MUON->GetNbinsX(), hist_ScaleFactor_MUON->GetBinContent(hist_ScaleFactor_MUON->GetNbinsX()+1));
  }

  // For hist_ScaleFactor_PHOTON
  if( TMath::Abs(hist_ScaleFactor_PHOTON->GetBinContent(hist_ScaleFactor_PHOTON->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_PHOTON->AddBinContent(hist_ScaleFactor_PHOTON->GetNbinsX(), hist_ScaleFactor_PHOTON->GetBinContent(hist_ScaleFactor_PHOTON->GetNbinsX()+1));
  }

  // For hist_ScaleFactor_TAU
  if( TMath::Abs(hist_ScaleFactor_TAU->GetBinContent(hist_ScaleFactor_TAU->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_TAU->AddBinContent(hist_ScaleFactor_TAU->GetNbinsX(), hist_ScaleFactor_TAU->GetBinContent(hist_ScaleFactor_TAU->GetNbinsX()+1));
  }

  // For hist_ScaleFactor_lepTRIGGER
  if( TMath::Abs(hist_ScaleFactor_lepTRIGGER->GetBinContent(hist_ScaleFactor_lepTRIGGER->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_lepTRIGGER->AddBinContent(hist_ScaleFactor_lepTRIGGER->GetNbinsX(), hist_ScaleFactor_lepTRIGGER->GetBinContent(hist_ScaleFactor_lepTRIGGER->GetNbinsX()+1));
  }

  // For hist_ScaleFactor_JVT
  if( TMath::Abs(hist_ScaleFactor_JVT->GetBinContent(hist_ScaleFactor_JVT->GetNbinsX()+1)) > 0 ){
    hist_ScaleFactor_JVT->AddBinContent(hist_ScaleFactor_JVT->GetNbinsX(), hist_ScaleFactor_JVT->GetBinContent(hist_ScaleFactor_JVT->GetNbinsX()+1));
  }
  
}

void TTbarDilepAnalysis::fill_hist_scale_factors(float SF_PILEUP, float SF_BTAG, float SF_ELE, float SF_MUON, float SF_PHOTON, float SF_TAU, float SF_lepTRIGGER, float SF_JVT){

  hist_ScaleFactor_PILEUP->Fill(SF_PILEUP);
  hist_ScaleFactor_BTAG->Fill(SF_BTAG);
  hist_ScaleFactor_ELE->Fill(SF_ELE);
  hist_ScaleFactor_MUON->Fill(SF_MUON);
  hist_ScaleFactor_PHOTON->Fill(SF_PHOTON);
  hist_ScaleFactor_TAU->Fill(SF_TAU);
  hist_ScaleFactor_lepTRIGGER->Fill(SF_lepTRIGGER);
  hist_ScaleFactor_JVT->Fill(SF_JVT);
  
}


////////////////////////////////////////////////////////////////////////////////
