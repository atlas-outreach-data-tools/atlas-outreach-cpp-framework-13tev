/////////////////////////////////////////////////////////////
//// SUSYAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define SUSYAnalysis_cxx

#include "SUSYAnalysis.h"
#include "SUSYAnalysisHistograms.h"
#include "CalcGenericMT2/MT2_ROOT.h"

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h> 
#include <math.h>
#include <cstdlib>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>


string name; 
string leptons; 
TString option; 
vector<TString> current_channels; 
vector<TString> all_channels = {"SFOS", "eeOS", "mumuOS", "SR_loose", "SR_tight"}; 
vector<int> remove_jet;
int n_light_jets_pt60; 
int n_bjets_pt20; 


void SUSYAnalysis::Begin(TTree * )
{

  nEvents=0;

}

void SUSYAnalysis::SlaveBegin(TTree * )
{
  option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());

  name=option;

  define_histograms(all_channels);

  FillOutputList(all_channels);

}


Bool_t SUSYAnalysis::Process(Long64_t entry)
{

  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;

  if(fChain->GetTree()->GetEntries()>0){

    // **********************************************************************************************//
    // Begin simplified selection based on: ATLAS Collaboration, Eur. Phys. J. C 78 (2018) 995       //
    // **********************************************************************************************//


    current_channels.clear(); 

    
    //------------------------------//
    // Event selection & Kinematics //
    //------------------------------//

    if(lep_n<2) return kTRUE; // Immediately get rid of events with <2 leptons 

    int n_lep = 0;
    int n_lepbase = 0;
    int n_lepsign = 0;
    vector<int> lep_indices;
    lep_indices.clear(); 

    TLorentzVector leptemp;
    TLorentzVector jettemp; 
    int removed_leptons = 0; 
    remove_jet.clear(); 

    // Loop over leptons in event  
    for(UInt_t i = 0; i<lep_n; i++){

      leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);

      if(leptemp.Pt() <= 10)continue;
      if(TMath::Abs((int)lep_type->at(i))==11 && TMath::Abs(leptemp.Eta()) >= 2.47)continue;
      if(TMath::Abs((int)lep_type->at(i))==13 && TMath::Abs(leptemp.Eta()) >= 2.7)continue;

      double dR;
      bool removeLep = false;
      bool removeJet;

      // Overlap removal 
      for(UInt_t j = 0; j<jet_n; j++){
	if(std::find(remove_jet.begin(), remove_jet.end(), j) != remove_jet.end())continue;
	removeJet = false;
	if(jet_pt->at(j) < 20000)continue;
	if(TMath::Abs(jet_eta->at(j)) >= 4.5)continue;
	if(jet_pt->at(j) < 60000 && TMath::Abs(jet_eta->at(j)) < 2.4){
	  if(TMath::Abs(jet_jvt->at(j))<=0.59)continue;
	}

	jettemp.SetPtEtaPhiE(jet_pt->at(j)/1000., jet_eta->at(j), jet_phi->at(j), jet_E->at(j)/1000.); 
	dR = jettemp.DeltaR(leptemp);
	if(jet_MV2c10->at(j)>0.1758475){
	  if(TMath::Abs((int)lep_type->at(i))==11 && dR < 0.2)removeLep = true;
	  if(TMath::Abs((int)lep_type->at(i))==13 && dR < 0.4)removeLep = true;
	}else{
	  if(TMath::Abs((int)lep_type->at(i))==11 && dR < 0.2)removeJet = true;
	  if(TMath::Abs((int)lep_type->at(i))==13 && dR < 0.4)removeLep = true;
	}
	if(!removeJet){
	  if(TMath::Abs((int)lep_type->at(i))==11 && dR < 0.4)removeLep = true;
	}else{
	  remove_jet.push_back(j);
	}
      }
    
      if(removeLep) continue;

      // Impact parameter cuts  
      if(TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) > 0.5) continue; 

      // Isolation cuts
      if( lep_etcone20->at(i)/lep_pt->at(i) > 0.15 ) continue;
      if( lep_ptcone30->at(i)/lep_pt->at(i) > 0.15 ) continue;

      if( TMath::Abs((int)lep_type->at(i)) == 11 ){
	if(TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) > 5) continue;  
      }
      if( TMath::Abs((int)lep_type->at(i)) == 13 ){
	if(TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) > 3) continue;  
      }

      n_lep++; // Count "good" leptons 
      lep_indices.push_back(i); 

    }

    if( n_lep != 2 ) return kTRUE; // Select only events with two good lepton candidates  

    int l1_i = lep_indices.at(0); // Index of first lepton  
    int l2_i = lep_indices.at(1); // Index of second lepton 

    if(lep_type->at(l1_i) != lep_type->at(l2_i)) return kTRUE; // Same flavour
    if(lep_charge->at(l1_i) == lep_charge->at(l2_i)) return kTRUE; // Opposite charge  

    // Set Lorentz vectors (l1 = leading lepton, l2 = subleading lepton) 
    TLorentzVector l1, l2; 
    if(lep_pt->at(l1_i)>lep_pt->at(l2_i)){
      l1.SetPtEtaPhiE(lep_pt->at(l1_i)/1000., lep_eta->at(l1_i), lep_phi->at(l1_i), lep_E->at(l1_i)/1000.);
      l2.SetPtEtaPhiE(lep_pt->at(l2_i)/1000., lep_eta->at(l2_i), lep_phi->at(l2_i), lep_E->at(l2_i)/1000.);
    }else{
      l1.SetPtEtaPhiE(lep_pt->at(l2_i)/1000., lep_eta->at(l2_i), lep_phi->at(l2_i), lep_E->at(l2_i)/1000.);
      l2.SetPtEtaPhiE(lep_pt->at(l1_i)/1000., lep_eta->at(l1_i), lep_phi->at(l1_i), lep_E->at(l1_i)/1000.);
    }

    // Lepton pT cut 
    if(l1.Pt() < 25) return kTRUE; 
    if(l2.Pt() < 20) return kTRUE; 

    // Identify the leptons 
    if(TMath::Abs((int)lep_type->at(l1_i))==11){ leptons = "ee";} // Electrons  
    if(TMath::Abs((int)lep_type->at(l1_i))==13){ leptons = "mumu";} // Muons 
      
    if(leptons == "ee"){
      // Electron eta cut
      if(TMath::Abs(l1.Eta()) > 2.47){return kTRUE;}
      if(TMath::Abs(l2.Eta()) > 2.47){return kTRUE;}
      // Electron trigger
      if(trigE != 1){return kTRUE;}
    }
    if(leptons == "mumu"){
      // Muon eta cut
      if(TMath::Abs(l1.Eta()) > 2.4){return kTRUE;}
      if(TMath::Abs(l2.Eta()) > 2.4){return kTRUE;}
      // Muon trigger 
      if(trigM != 1){return kTRUE;}
    }
       
    // Invariant mass cut  
    TLorentzVector dileptons = l1 + l2; 
    float mLL = dileptons.M();
    if(mLL < 40) return kTRUE; // End of pre-selection 

    if(leptons == "ee") current_channels.push_back("eeOS");
    if(leptons == "mumu") current_channels.push_back("mumuOS"); 
    current_channels.push_back("SFOS"); 

    // Count light jets and b-jets
    n_light_jets_pt60 = 0; 
    n_bjets_pt20 = 0; 
    for(UInt_t i = 0; i<jet_n; i++){
      if((jet_pt->at(i))/1000. > 60 && jet_MV2c10->at(i)<0.645925){ n_light_jets_pt60++; } // using 77% WP
      if((jet_pt->at(i))/1000. > 20 && jet_MV2c10->at(i)>0.645925){ n_bjets_pt20++; } // using 77% WP 
    }

    // pathological high-weight event in Sherpa sample
    if(option.Contains("Wmunu_PTV0_70_CVetoBVeto")) if (met_et/1000. > 1500) met_et = 0;

    // Set Lorentz vector for MET
    TLorentzVector met;
    met.SetPtEtaPhiM((met_et)/1000.,0.0,met_phi,0);

    // Calculate the MT2 variable 
    ComputeMT2 calcMT2 = ComputeMT2(l1, l2, met);  
    float MT2 = calcMT2.Compute();

    // Apply signal region definitions 
    if( n_light_jets_pt60 == 0 && n_bjets_pt20 == 0 ){ 
      if( mLL > 111 && MT2 > 100 ){ current_channels.push_back("SR_loose");  } 
      if( mLL > 300 && MT2 > 130 ){ current_channels.push_back("SR_tight");  } 
    }

    //-----------------// 
    // Event weighting // 
    //-----------------//    

    // Scale factors  
    Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP;

    //MC weight
    Float_t m_mcWeight = mcWeight;

    // read input option
    if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs

    //Total weight
    Float_t weight = scaleFactor*m_mcWeight;

    // Make difference between data and MC
    option = GetOption(); 
    if(option.Contains("data")) {  weight = 1.; }

    //-----------------// 
    // Fill histograms //
    //-----------------//

    double names_of_global_variable[]={mLL, met.Et(), MT2, met.Et()};
    double names_of_leadlep_variable[]={l1.Pt(), l1.Eta(), l1.E(), l1.Phi()}; 
    double names_of_subleadlep_variable[]={l2.Pt(), l2.Eta(), l2.E(), l2.Phi()};

    for( const auto & ch:current_channels ){
      TString histonames_of_global_variable[]={"hist_mLL_"+ch, "hist_etmiss_"+ch, "hist_mt2_"+ch, "hist_rebin_etmiss_"+ch};
      TString histonames_of_leadlep_variable[]={"hist_leadleptpt_"+ch, "hist_leadlepteta_"+ch, "hist_leadleptE_"+ch, "hist_leadleptphi_"+ch};
      TString histonames_of_subleadlep_variable[]={"hist_subleadleptpt_"+ch, "hist_subleadlepteta_"+ch, "hist_subleadleptE_"+ch, "hist_subleadleptphi_"+ch}; 			      
			      
      //Start to fill histograms : find the histogram array length
      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
      int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
      int length_subleadlep = sizeof(names_of_subleadlep_variable)/sizeof(names_of_subleadlep_variable[0]);			      

      //Fill histograms
      for (int i=0; i<length_global; i++){
	FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i], ch);
      }
      for (int i=0; i<length_leadlep; i++){
	FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i], ch);
      }
      for (int i=0; i<length_subleadlep; i++){
	FillHistogramsSubleadlept( names_of_subleadlep_variable[i], weight, histonames_of_subleadlep_variable[i], ch);
      }

    }

  }
				      
  return kTRUE;

}

void SUSYAnalysis::SlaveTerminate()
{
}

void SUSYAnalysis::Terminate()
{
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_SUSYAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_SUSY(filename,"recreate");
  WriteHistograms(all_channels);
  physicsoutput_SUSY.Close();
  
}
