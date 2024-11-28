/////////////////////////////////////////////////////////////
//// TTbarDilepAnalysis code
//// Author: ATLAS Collaboration (2024)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define TTbarDilepAnalysis_cxx

#include "TTbarDilepAnalysis.h"
#include "TTbarDilepAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom3.h>

string name;

void TTbarDilepAnalysis::Begin(TTree * )
{
  nEvents=0;
  xsec_SF = 0;
  totalSumOfWeights_SF = 0;
  filteff_SF = 0;
  kfac_SF = 0;

  good_event_lep = 0;
  two_electrons_lep = 0;
  two_muons_lep = 0;
  lep_tight_n = 0;
  leppt_n = 0;
  lep_ptvarcone_n = 0;
  lep_etcone_n = 0;
  leptype_elec_n = 0;
  leptype_muon_n = 0;
  lep_elec_d0 = 0;
  lep_muon_d0 = 0;
  lep_elec_z0 = 0;
  lep_muon_z0 = 0;

}

void TTbarDilepAnalysis::SlaveBegin(TTree * )
{
  cout << "************************************************************************************************************************" << endl;
  cout << "************************************************************************************************************************" << endl;
  
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t TTbarDilepAnalysis::Process(Long64_t entry)
{
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  
  if(nEvents % 1000000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetEntries() << " in this chain of samples" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0){
    
    // **********************************************************************************************//
    // Begin analysis selection, largely based on: ATLAS Collaboration, JHEP 11 (2017) 191           //
    // **********************************************************************************************//
      
    //Scale factors (adding b-tagging as it is used)
    
    //Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_LepTRIGGER*ScaleFactor_PILEUP*ScaleFactor_BTAG*ScaleFactor_JVT;

    Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_PILEUP*ScaleFactor_BTAG*ScaleFactor_LepTRIGGER;

    //Float_t scaleFactor = 1.0;
    
    //MC weight
    Float_t m_mcWeight = mcWeight;

    // read input option
    TString option = GetOption();
    if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs

    //Total weight
    Float_t weight = scaleFactor*m_mcWeight;

    // Make difference between data and MC

    bool is_data = option.Contains("data");
    
    if( is_data==true ){
      weight = 1.;
      if(entry==0){
	xsec_SF = 1.;
	totalSumOfWeights_SF = 1.;
	filteff_SF = 1.;
	kfac_SF = 1.;
      }
    }
    if( is_data==false ){
      if(entry==0){
	xsec_SF = xsec;
	filteff_SF = filteff;
	kfac_SF = kfac;
	totalSumOfWeights_SF = initial_sum_of_weights;
      }
    }
    
    // lep trigger cut
    if( (trigE==true) || (trigM==true) ){

      trigger_cut++;
      
      int goodlep_index[lep_n];
      int goodlep_n = 0;
      int lep_index = 0;
      
      for(Int_t ii=0; ii<lep_n; ii++){
	
	TLorentzVector leptemp = TLorentzVector();  
	leptemp.SetPtEtaPhiE(lep_pt->at(ii), lep_eta->at(ii), lep_phi->at(ii), lep_e->at(ii));
        
	// Lepton is Tight
	if( (lep_isTightID->at(ii)==true) && (lep_isTightIso->at(ii)==true)){
	  lep_tight_n++;
	  if( lep_pt->at(ii) > 25. ){
	    leppt_n++;
	    // electron selection
		
	    if( lep_type->at(ii)==11 && TMath::Abs(lep_eta->at(ii))<2.47 && (TMath::Abs(lep_eta->at(ii))<1.37 || TMath::Abs(lep_eta->at(ii))>1.52) ){
	      goodlep_n++;
	      goodlep_index[lep_index] = ii;
	      lep_index++;
	      electron_n++;
	      
	    }
		
	    // muon selection
	    if( lep_type->at(ii)==13 && TMath::Abs(lep_eta->at(ii))<2.5 ){
	      goodlep_n++;
	      goodlep_index[lep_index] = ii;
	      lep_index++;
	      muon_n++;
	    }
	  }
	}
      }
      
      // goodlep number cut
      
      if( goodlep_n==2 ){
	good_lepton_n_cut++;
	
	//Exactly two good leptons, leading lepton with pT > 22 GeV and the subleading lepton with pT > 15 GeV
	int lep_index1 = goodlep_index[0];
	int lep_index2 = goodlep_index[1];
	
	if( (lep_type->at(lep_index1)==11) && (lep_type->at(lep_index2)==13) ){
          good_event_lep++;
        }
	
        if( (lep_type->at(lep_index1)==11) && (lep_type->at(lep_index2)==11) ){
          two_electrons_lep++;
        }

        if( (lep_type->at(lep_index1)==13) && (lep_type->at(lep_index2)==13) ){
          two_muons_lep++;
        }
	
	// Cut on opposite charged leptons
	if( lep_charge->at(lep_index1)*lep_charge->at(lep_index2) < 0){  

	  OP_charge_leptons_cut++;

	  // Cut on different types of leptons
	  if( lep_type->at(lep_index1) != lep_type->at(lep_index2)){ 

	    type_leptons_cut++;

	    //Preselection of good b-jets
  
	    int goodbjet_n = 0;
	    int goodbjet_index[jet_n];
	    int bjet_index = 0;
	    
	    for(Int_t ii=0; ii<jet_n; ii++){
	      if( (jet_pt->at(ii) > 25.) && (TMath::Abs(jet_eta->at(ii)) < 2.5)){
		  
		// JVT cleaning
		bool jvt_pass=true;
		
		if(jet_jvt->at(ii)==false) jvt_pass=false;
		
		if(jvt_pass==true){
		  if( jet_btag_quantile->at(ii) >= 2 && TMath::Abs(jet_eta->at(ii)) < 2.5 ){
		    goodbjet_n++;
		    goodbjet_index[bjet_index] = ii;
		    bjet_index++;
		  } 
		}
	      }
	    }
	    
	    // Cut on good bjets number
	    if( goodbjet_n >= 2 ){
	      bjets_cut++;
	      
	      int bjet_index1 = goodbjet_index[0];
	      int bjet_index2 = goodbjet_index[1];    
	      
	      TLorentzVector lep1 = TLorentzVector();  
	      TLorentzVector lep2 = TLorentzVector();
	      TLorentzVector dilep = TLorentzVector();
	      
	      lep1.SetPtEtaPhiE(lep_pt->at(lep_index1), lep_eta->at(lep_index1), lep_phi->at(lep_index1), lep_e->at(lep_index1));
	      lep2.SetPtEtaPhiE(lep_pt->at(lep_index2), lep_eta->at(lep_index2), lep_phi->at(lep_index2), lep_e->at(lep_index2));
	      dilep = lep1 + lep2;
		      
	      ///////// SAVE HISTOGRAMS /////////
	      double names_of_global_variable[]={met, dilep.Pt(), TMath::Abs(dilep.Eta())};
	
	      //cout << "The event passed theselection. Filling the histograms" << endl;
	      
	      TString histonames_of_global_variable[]={"hist_met", "hist_lep_pt", "hist_lep_eta"};
				  
	      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
	      
	      for (int ii=0; ii<length_global; ii++){
		FillHistogramsGlobal( names_of_global_variable[ii], weight, histonames_of_global_variable[ii] );
	      }

	      fill_hist_scale_factors(ScaleFactor_PILEUP, ScaleFactor_BTAG, ScaleFactor_ELE, ScaleFactor_MUON, ScaleFactor_PHOTON, ScaleFactor_TAU, ScaleFactor_LepTRIGGER, ScaleFactor_JVT);
	    }		   		  		      
	  }
	}
      }
    } 
  }

  return kTRUE;
}

void TTbarDilepAnalysis::SlaveTerminate()
{
  TString option = GetOption();
  bool is_data = option.Contains("data");
   
  hist_scale_factors->SetBinContent(0, xsec_SF);
  hist_scale_factors->SetBinContent(1, totalSumOfWeights_SF);
  hist_scale_factors->SetBinContent(2, filteff_SF);
  hist_scale_factors->SetBinContent(3, kfac_SF);
}

void TTbarDilepAnalysis::Terminate()
{
  
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "trigger cut number: " << trigger_cut << endl;
  cout << "good lepton number: " << good_lepton_n_cut << endl;
  cout << "opposite charged leptons number: " << OP_charge_leptons_cut << endl;
  cout << "type leptons number: " << type_leptons_cut << endl;
  cout << "bjets cut number: " << bjets_cut << endl;
  cout << "good electron - muon leptons: " << electron_n << "\t" << muon_n << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "Number of events with two good leptons: " << good_lepton_n_cut << endl;
  cout << "Number of events with two good electrons: " << two_electrons_lep << endl;
  cout << "Number of events with two good muons: " << two_muons_lep << endl;
  cout << "Number of events with one electron and one muon: " << good_event_lep << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "The scaling factors values are: " << endl;
  cout << "xsec: " << xsec_SF << endl;
  cout << "totalSumOfWeights: " << totalSumOfWeights_SF << endl;
  cout << "filteff: " << filteff_SF << endl;
  cout << "kfac: " << kfac_SF << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "trigger cut number: " << trigger_cut << endl;
  cout << "lep tight number: " << lep_tight_n << endl;
  cout << "lep pt>25GeV number: " << leppt_n << endl;
  cout << "lep type electron number: " << electron_n << endl;
  cout << "lep type muon number: " << muon_n << endl;
  
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_TTbarDilepAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_TTbarDilep(filename,"recreate");
  mc_under_and_overflow();
  WriteHistograms();
  physicsoutput_TTbarDilep.Close();
}
