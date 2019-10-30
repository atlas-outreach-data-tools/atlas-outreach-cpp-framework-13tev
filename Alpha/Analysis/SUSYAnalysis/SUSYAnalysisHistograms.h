////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void SUSYAnalysis::define_histograms(vector<TString> channels)
{
  // HISTOGRAMS
  // Global histograms
  for(const auto & ch:channels){
    hist_mLL[ch]    = new TH1F("hist_mLL_"+ch,    "Mass of Dilepton System; m_{ll} [GeV];Events / bin", 20, 0, 500);
    hist_etmiss[ch] = new TH1F("hist_etmiss_"+ch, "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0, 2000);
    hist_mt2[ch]    = new TH1F("hist_mt2_"+ch,    "Stransverse Mass; M_{T2} [GeV]; Events / bin", 20, 0, 400); 
    hist_rebin_etmiss[ch] = new TH1F("hist_rebin_etmiss_"+ch, "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 10, 0, 300);

    // Leading Lepton histograms
    hist_leadleptpt[ch]  = new TH1F("hist_leadleptpt_"+ch,  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Events / bin", 30, 0, 500);
    hist_leadlepteta[ch] = new TH1F("hist_leadlepteta_"+ch, "Leading Lepton Pseudorapidity; #eta^{leadlep}; Events / bin", 40, -3, 3);
    hist_leadleptE[ch]   = new TH1F("hist_leadleptE_"+ch,   "Leading Lepton Energy; E^{leadlep} [GeV]; Events / bin", 30, 0, 1500);
    hist_leadleptphi[ch] = new TH1F("hist_leadleptphi_"+ch, "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Events / bin", 40, -3.2, 3.2);


    // Subleading Lepton histograms
    hist_subleadleptpt[ch] = new TH1F("hist_subleadleptpt_"+ch, "Subleading Lepton Transverse Momentum;p_{T}^{traillep} [GeV];Events / bin", 30, 0, 500);
    hist_subleadlepteta[ch] = new TH1F("hist_subleadlepteta_"+ch, "Subleading Lepton Pseudorapidity; #eta^{traillep}; Events / bin", 40, -3, 3);
    hist_subleadleptE[ch] = new TH1F("hist_subleadleptE_"+ch,  "Subleading Lepton Energy; E^{traillep} [GeV]; Events / bin", 30, 0, 1500);
    hist_subleadleptphi[ch] = new TH1F("hist_subleadleptphi_"+ch,"Subleading Lepton Azimuthal Angle ; #phi^{traillep}; Events / bin", 20, -3.2, 3.2);



  }
}

////////////////////////////////////////////////////////////////////////////////
void SUSYAnalysis::FillOutputList(vector<TString> channels)
{
  // histograms
  for(const auto & chn:channels){
    // Add Global histograms
    GetOutputList()->Add(hist_etmiss[chn]);
    GetOutputList()->Add(hist_mLL[chn]);
    GetOutputList()->Add(hist_mt2[chn]); 
    GetOutputList()->Add(hist_rebin_etmiss[chn]);

    // Add Leading Lepton histograms
    GetOutputList()->Add(hist_leadleptpt[chn]);
    GetOutputList()->Add(hist_leadlepteta[chn]);
    GetOutputList()->Add(hist_leadleptE[chn]);
    GetOutputList()->Add(hist_leadleptphi[chn]);

    // Add Subleading Lepton histograms
    GetOutputList()->Add(hist_subleadleptpt[chn]);
    GetOutputList()->Add(hist_subleadlepteta[chn]);
    GetOutputList()->Add(hist_subleadleptE[chn]);
    GetOutputList()->Add(hist_subleadleptphi[chn]);

 

  }
}

////////////////////////////////////////////////////////////////////////////////
void SUSYAnalysis::WriteHistograms(vector<TString> channels)
{
  // histograms
  TString histname; 

  for(const auto & ch:channels){
    // Write Global histograms
    histname = "hist_etmiss_"+ch; 
    hist_etmiss[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_etmiss[ch]->Write();

    histname = "hist_mLL_"+ch; 
    hist_mLL[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_mLL[ch]->Write();

    histname = "hist_mt2_"+ch; 
    hist_mt2[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_mt2[ch]->Write(); 

    histname = "hist_rebin_etmiss_"+ch;
    hist_rebin_etmiss[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data());
    hist_rebin_etmiss[ch]->Write();

    // Write Leading Lepton histograms
    histname = "hist_leadleptpt_"+ch; 
    hist_leadleptpt[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_leadleptpt[ch]->Write();

    histname = "hist_leadlepteta_"+ch; 
    hist_leadlepteta[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_leadlepteta[ch]->Write();

    histname = "hist_leadleptE_"+ch; 
    hist_leadleptE[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_leadleptE[ch]->Write();

    histname = "hist_leadleptphi_"+ch; 
    hist_leadleptphi[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_leadleptphi[ch]->Write();

    // Write Subleading Lepton histograms
    histname = "hist_subleadleptpt_"+ch; 
    hist_subleadleptpt[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_subleadleptpt[ch]->Write();

    histname = "hist_subleadlepteta_"+ch; 
    hist_subleadlepteta[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_subleadlepteta[ch]->Write();

    histname = "hist_subleadleptE_"+ch; 
    hist_subleadleptE[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_subleadleptE[ch]->Write();

    histname = "hist_subleadleptphi_"+ch; 
    hist_subleadleptphi[ch] = (TH1F*) GetOutputList()->FindObject(histname.Data()); 
    hist_subleadleptphi[ch]->Write();


  }
}

void SUSYAnalysis::FillHistogramsGlobal( double m, float w , TString s, TString ch)
{
  //Fill Global histograms
  if (s.Contains("hist_mLL")) hist_mLL[ch]->Fill(m,w);
  
  if (s.Contains("hist_etmiss")) hist_etmiss[ch]->Fill(m,w);
   
  if (s.Contains("hist_rebin_etmiss")) hist_rebin_etmiss[ch]->Fill(m,w);

  if (s.Contains("hist_mt2")) hist_mt2[ch]->Fill(m,w); 

}

void SUSYAnalysis::FillHistogramsLeadlept( double m, float w , TString s, TString ch)
{
  //Fill Leading lepton histograms

  if (s.Contains("hist_leadleptpt")) hist_leadleptpt[ch]->Fill(m,w);
    
  if (s.Contains("hist_leadlepteta")) hist_leadlepteta[ch]->Fill(m,w);

  if (s.Contains("hist_leadleptE")) hist_leadleptE[ch]->Fill(m,w);

  if (s.Contains("hist_leadleptphi")) hist_leadleptphi[ch]->Fill(m,w);
  


}

void SUSYAnalysis::FillHistogramsSubleadlept( double m, float w , TString s, TString ch)
{
  //Fill Subleading lepton histograms

  if (s.Contains("hist_subleadleptpt")) hist_subleadleptpt[ch]->Fill(m,w);
  
  if (s.Contains("hist_subleadlepteta")) hist_subleadlepteta[ch]->Fill(m,w);

  if (s.Contains("hist_subleadleptE")) hist_subleadleptE[ch]->Fill(m,w);

  if (s.Contains("hist_subleadleptphi")) hist_subleadleptphi[ch]->Fill(m,w);


}



////////////////////////////////////////////////////////////////////////////////
