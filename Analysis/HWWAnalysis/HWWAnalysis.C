/////////////////////////////////////////////////////////////
//// HWWAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define HWWAnalysis_cxx

#include "HWWAnalysis.h"
#include "HWWAnalysisHistograms.h"
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

void HWWAnalysis::Begin(TTree * )
{
  nEvents=0;
  xsec_SF = 0;
  totalSumOfWeights_SF = 0;
  filteff_SF = 0;
  kfac_SF = 0;
}

void HWWAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t HWWAnalysis::Process(Long64_t entry)
{
  
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 1000000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0){
    
    // **********************************************************************************************//
    // Begin analysis selection, largely based on: ATLAS Collaboration, Phys. Lett. B 789 (2019) 508 //
    // **********************************************************************************************//
      
    //Scale factors
    
    Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_LepTRIGGER*ScaleFactor_PILEUP*ScaleFactor_FTAG*ScaleFactor_JVT;

    //Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_PILEUP*ScaleFactor_BTAG*ScaleFactor_JVT;

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
            
    //Preselection cut for electron/muon trigger 
    if(trigE || trigM){
      
      trigger_cut++;
      
      // Preselection of good leptons
      int goodlep_index[lep_n];
      int goodlep_n = 0;
      int lep_index =0;
            
      for(Int_t i=0; i<lep_n; i++){
	
	TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i), lep_eta->at(i), lep_phi->at(i), lep_e->at(i));
	    
	// Lepton is Tight
	if( (lep_isTightID->at(i)==true) && (lep_isTightIso->at(i)==true) && (lep_isTrigMatched->at(i)==true)){
	  if( (lep_pt->at(i)>15.) ){
	    // electron selection
	    if ( (lep_type->at(i)==11) && (TMath::Abs(lep_eta->at(i))<2.47) && (TMath::Abs(lep_eta->at(i))<1.37 || TMath::Abs(lep_eta->at(i))>1.52) ){
	      goodlep_n = goodlep_n + 1;
	      goodlep_index[lep_index] = i;
	      lep_index++;
	      electron_n++;
	    }
	    // muon selection
	    if ( (lep_type->at(i)==13) && (TMath::Abs(lep_eta->at(i))<2.5) ){
	      goodlep_n = goodlep_n + 1;
	      goodlep_index[lep_index] = i;
	      lep_index++;
	      muon_n++;
	    }
	  }
	}// tight
      }
      
      //Exactly two good leptons, leading lepton with pT > 22 GeV and the subleading lepton with pT > 15 GeV
      if(goodlep_n==2){

	good_lepton_n_cut++;
	
	int goodlep1_index = goodlep_index[0];
	int goodlep2_index = goodlep_index[1];
	
	if(lep_pt->at(goodlep1_index) > 22.){
	    
	  //two different-flavour opposite-sign leptons
	  if ( lep_charge->at(goodlep1_index)*lep_charge->at(goodlep2_index) < 0 ){

	    OP_charge_leptons_cut++;
	    
	    if ( lep_type->at(goodlep1_index) != lep_type->at(goodlep2_index) ){
	      
	      type_leptons_cut++;
	      
	      // TLorentzVector definitions
	      TLorentzVector Lepton_1  = TLorentzVector();
	      TLorentzVector Lepton_2  = TLorentzVector();
	      TLorentzVector      MeT  = TLorentzVector();
	      
	      Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep1_index), lep_eta->at(goodlep1_index), lep_phi->at(goodlep1_index), lep_e->at(goodlep1_index));
	      Lepton_2.SetPtEtaPhiE(lep_pt->at(goodlep2_index), lep_eta->at(goodlep2_index), lep_phi->at(goodlep2_index), lep_e->at(goodlep2_index));
	      MeT.SetPtEtaPhiE(met, 0, met_phi , met);
	      
	      TLorentzVector     Lepton_12 = TLorentzVector();
	      Lepton_12 = Lepton_1 + Lepton_2;
		  
	      float mLL       = Lepton_12.Mag();
	      float ptLL      = Lepton_12.Pt();
	      
	      float dPhi_LL  = TMath::Abs(lep_phi->at(goodlep1_index) - lep_phi->at(goodlep2_index) );
	      dPhi_LL        = dPhi_LL < TMath::Pi() ? dPhi_LL : 2*TMath::Pi() - dPhi_LL;
		  
	      Float_t MET = met;
	      
	      float dPhiLLmet = TMath::Abs( Lepton_12.Phi() - MeT.Phi() );
	      dPhiLLmet    = dPhiLLmet < TMath::Pi() ? dPhiLLmet : 2*TMath::Pi() - dPhiLLmet;
		  
	      float mt    = sqrt(2*Lepton_12.Pt()*MeT.Et()*(1-cos(Lepton_12.DeltaPhi(MeT))));
			  
	      //Preselection of good jets
	      int goodjet_n = 0;
	      int goodbjet_n = 0;
		  
	      int goodjet_index[jet_n];
	      int jet_index = 0;
		  
	      int goodbjet_index[jet_n];
	      int bjet_index = 0;
		  
	      for(Int_t i=0; i<jet_n; i++){
		
		if(jet_pt->at(i)>20. && TMath::Abs(jet_eta->at(i))<2.5){

		  // JVT cleaning
		  bool jvt_pass=true;

		  if( jet_jvt->at(i)==false ) jvt_pass=false;

		  if( jvt_pass == true ){
		    // cut on 85% WP
		    if( jet_btag_quantile->at(i)>=2 && TMath::Abs(jet_eta->at(i))<2.5 ){
		      goodbjet_n++;
		      goodbjet_index[bjet_index] = i;
		      bjet_index++;
		    }	      
		    if( jet_pt->at(i)>30. ){
		      goodjet_n++;
		      goodjet_index[jet_index] = i;
		      jet_index++;
		    }
		  }
		}
	      }
			  
	      // fill histograms before any cut
	      double names_of_global_variable_pre[]={mLL, ptLL, dPhi_LL, dPhiLLmet, MET, mt, (double)goodjet_n, (double)goodbjet_n};
	      TString histonames_of_global_variable_pre[]={"histI_mLL", "histI_ptLL", "histI_dPhi_LL", "histI_dPhiLLmet", "histI_etmiss", "histI_mt", "histI_n_jets", "histI_n_bjets"};
	      int length_global_pre = sizeof(names_of_global_variable_pre)/sizeof(names_of_global_variable_pre[0]);
	      for (int i=0; i<length_global_pre; i++)                                              {
		FillHistogramsGlobal( names_of_global_variable_pre[i], weight, histonames_of_global_variable_pre[i]);
	      }
			  
	      //  remove low mass meson resonances and DY events; ggF regions, at least 1 jet
	      if ( mLL > 10 && goodjet_n <= 1 && MET > 20){
        	if ( dPhiLLmet > TMath::Pi()/2 ){
		  dPhiLLmet_cut++;
		  if ( ptLL > 30 ){
		    ptLL_cut++;
		    if ( mLL < 55 ){
		      mLL_cut++;
		      if ( dPhi_LL < 1.8 ){
			dPhi_LL_cut++;
			if ( goodbjet_n == 0 ){
			  bjets_cut++;
			  
			  //Start to fill histograms : definitions of x-axis variables
			  
			  double names_of_global_variable[]={mLL, ptLL, dPhi_LL, dPhiLLmet, MET, mt, (double)goodjet_n, (double)goodbjet_n};
			  
			  double names_of_leadlep_variable[]={Lepton_1.Pt(), Lepton_1.Eta(), Lepton_1.E(), Lepton_1.Phi(), (double)lep_charge->at(goodlep1_index), (double)lep_type->at(goodlep1_index) };
			  
			  double names_of_subleadlep_variable[]={Lepton_2.Pt(), Lepton_2.Eta(), Lepton_2.E(), Lepton_2.Phi(), (double)lep_charge->at(goodlep2_index), (double)lep_type->at(goodlep2_index)};
		        
			  //Start to fill histograms : definitions of histogram names
			  
			  TString histonames_of_global_variable[]={"hist_mLL", "hist_ptLL", "hist_dPhi_LL", "hist_dPhiLLmet", "hist_etmiss", "hist_mt", "hist_n_jets", "hist_n_bjets"};
			  TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta", "hist_leadleptE", "hist_leadleptphi", "hist_leadleptch", "hist_leadleptID"};
			  TString histonames_of_subleadlep_variable[]={"hist_subleadleptpt", "hist_subleadlepteta", "hist_subleadleptE", "hist_subleadleptphi", "hist_subleadleptch", "hist_subleadleptID"};
						  
			  int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
			  int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
			  int length_subleadlep = sizeof(names_of_subleadlep_variable)/sizeof(names_of_subleadlep_variable[0]);
						  
			  //Fill histograms
			  
			  for (int i=0; i<length_global; i++){
			    FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
			  }
			  
			  for (int i=0; i<length_leadlep; i++){
			    FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
			  }
						  
			  for (int i=0; i<length_subleadlep; i++){
			    FillHistogramsSubleadlept( names_of_subleadlep_variable[i], weight, histonames_of_subleadlep_variable[i]);
			  }
			}
		      }
		    }
		  } // selection			      
		} // jet cut
	      }
	    }
	  }
	}
      }
    }
  }
  
  return kTRUE;
}

void HWWAnalysis::SlaveTerminate()
{
  TString option = GetOption();
  bool is_data = option.Contains("data");
  
  hist_scale_factors->SetBinContent(0, xsec_SF);
  hist_scale_factors->SetBinContent(1, totalSumOfWeights_SF);
  hist_scale_factors->SetBinContent(2, filteff_SF);
  hist_scale_factors->SetBinContent(3, kfac_SF);
}

void HWWAnalysis::Terminate()
{

  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "trigger cut number: " << trigger_cut << endl;
  cout << "good lepton number: " << good_lepton_n_cut << endl;
  cout << "opposite charged leptons number: " << OP_charge_leptons_cut << endl;
  cout << "type leptons number: " << type_leptons_cut << endl;
  cout << "dPhiLLmet cut number: " << dPhiLLmet_cut << endl;
  cout << "ptLL cut number: " << ptLL_cut << endl;
  cout << "mLL cut number: " << mLL_cut << endl;
  cout << "dPhi_LL cut number: " << dPhi_LL_cut << endl;
  cout << "bjets cut number: " << bjets_cut << endl;
  cout << "good electron - muon leptons: " << electron_n << "\t" << muon_n << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "The scaling factors values are: " << endl;
  cout << "xsec: " << xsec_SF << endl;
  cout << "totalSumOfWeights: " << totalSumOfWeights_SF  << endl;
  cout << "filteff: " << filteff_SF << endl;
  cout << "kfac: " << kfac_SF << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_HWWAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();

}
