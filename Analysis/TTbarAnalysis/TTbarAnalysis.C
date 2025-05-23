/////////////////////////////////////////////////////////////
//// TTbarAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define TTbarAnalysis_cxx

#include "TTbarAnalysis.h"
#include "TTbarAnalysisHistograms.h"
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

void TTbarAnalysis::Begin(TTree * )
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

void TTbarAnalysis::SlaveBegin(TTree * )
{  
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t TTbarAnalysis::Process(Long64_t entry)
{
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 1000000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0){

    // **********************************************************************************************//
    // Begin analysis selection, largely based on: ATLAS Collaboration, JHEP 11 (2017) 191           //
    // **********************************************************************************************//
    
    //Scale factors (adding b-tagging as it is used)
    Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_LepTRIGGER*ScaleFactor_PILEUP*ScaleFactor_FTAG*ScaleFactor_JVT;

    //MC weight
    Float_t m_mcWeight = mcWeight;
    
    // read input option
    TString option = GetOption();

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
    
    // cut on at least 4 jets
    if(jet_n > 3){
      
      // MET > 30 GeV
      if(met > 30.){
	
	// Preselection cut for electron/muon trigger, Good Run List, and good vertex
	if( (trigE==true) || (trigM==true) ){

	  trigger_cut++;
	  
	  // Preselection of good leptons
	  int goodlep_index = 0;
	  int goodlep_n = 0;
	  int lep_index = 0;
	  
	  for(Int_t i=0; i<lep_n; i++){

	    TLorentzVector leptemp;
	    leptemp.SetPtEtaPhiE(lep_pt->at(i), lep_eta->at(i), lep_phi->at(i), lep_e->at(i));

	    // Lepton is Tight
	    if( (lep_isTightID->at(i)==true) && (lep_isTightIso->at(i)==true) && (lep_isTrigMatched->at(i)==true) ){

	      lep_tight_n++;
	      
	      if( lep_pt->at(i)>30. ){
		
		leppt_n++;
		
		// electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
		if( (lep_type->at(i)==11) && (TMath::Abs(lep_eta->at(i))<2.47) && ( (TMath::Abs(lep_eta->at(i))<1.37) || (TMath::Abs(lep_eta->at(i))>1.52) ) ){
		  goodlep_n = goodlep_n + 1;
		  goodlep_index = i;
		  lep_index++;
	        }
		// muon selection
		if( (lep_type->at(i)==13) && (TMath::Abs(lep_eta->at(i)) < 2.5) ){
		  goodlep_n = goodlep_n + 1;
		  goodlep_index = i;
		  lep_index++;
	        }
	      }
	    }
	  }

	  //Exactly one good lepton
	  if(goodlep_n==1){
	    
	    good_lepton_n_cut++;
	    
	    //Preselection of good jets
	    int goodjet_n = 0;
	    int goodbjet_n = 0;

	    std::vector<int> goodjet_index(jet_n);
	    int jet_index = 0;

	    std::vector<int> goodbjet_index(jet_n);
	    int bjet_index = 0;
	    
	    for(Int_t i=0; i<jet_n; i++){
	      
	      if( (jet_pt->at(i)>30.) && (TMath::Abs(jet_eta->at(i))<2.5) ){
		
		// JVT cleaning
		bool jvt_pass=true;
		
		if( jet_jvt->at(i)==false ) jvt_pass=false;
		
		if( jvt_pass==true ){
		  goodjet_n++;
		  goodjet_index[jet_index] = i;
		  jet_index++;
		  
		  // cut on 0.8244273 is 70% WP	
		  if( jet_btag_quantile->at(i)>=4 ){
		    goodbjet_n++;
		    goodbjet_index[bjet_index] = i;
		    bjet_index++;
		  }
		}
	      }
	    }

	    // TLorentzVector definitions
	    TLorentzVector Lepton_1  = TLorentzVector();
	    TLorentzVector      MeT  = TLorentzVector();
	    
	    // nominal values		      
	    Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_e->at(goodlep_index));
	    MeT.SetPtEtaPhiE(met, 0, met_phi , met);
	    
	    //Calculation of MTW
	    float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
	    
	    // At least four good jets
	    if(goodjet_n>=4){
	      
	      int goodjet1_index = goodjet_index[0]; // leading jet
	      
	      //At least two b-tagged jets
	      if(goodbjet_n>=2){
		
		bjets_cut++;
		
		int goodbjet1_index = goodbjet_index[0]; // leading b-jet
		
		// MTW > 30 GeV
		if(mtw>30.){
		  
		  ///////// SAVE HISTOGRAMS /////////
		  double names_of_global_variable[]={met,mtw};
	  
		  double names_of_leadlep_variable[]={Lepton_1.Pt(), Lepton_1.Eta(), Lepton_1.E(), Lepton_1.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index)};
		  
		  double names_of_jet_variable[]={(double)goodjet_n, jet_pt->at(goodjet1_index),jet_eta->at(goodjet1_index),(double)goodbjet_n, jet_pt->at(goodbjet1_index),jet_eta->at(goodbjet1_index)};
		  
		  TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw"};
		  
		  TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID"};
		  
		  TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_n_bjets","hist_leadbjet_pt","hist_leadbjet_eta"};
		  
		  int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
		  
		  int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
		  
		  int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
		  
		  for (int i=0; i<length_global; i++){
		    FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
		  }
		  
		  for (int i=0; i<length_leadlep; i++){
		    FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
		  }
		  for (int i=0; i<length_leadjet; i++){
		    FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
		  }

		  // Invariant mass distribution of the 3-jets combination with the highest vector pT sum, a handle on the top mass
		  
		  float PTjjjmax=0;
		  float Mjjjmax=0;
		  int a=0; int b=0; int c=0;
		  
		  // iterate over 3 jets, build vectors
		  for(int i = 0; i < goodjet_n; ++i){
		    for(int j = i + 1; j < goodjet_n; ++j){
		      for(int k = j + 1; k < goodjet_n; ++k){
			TLorentzVector jet1  = TLorentzVector();
			jet1.SetPtEtaPhiE(jet_pt->at(goodjet_index[i]), jet_eta->at(goodjet_index[i]), jet_phi->at(goodjet_index[i]),jet_e->at(goodjet_index[i]));
			TLorentzVector jet2  = TLorentzVector();
			jet2.SetPtEtaPhiE(jet_pt->at(goodjet_index[j]), jet_eta->at(goodjet_index[j]), jet_phi->at(goodjet_index[j]),jet_e->at(goodjet_index[j]));
			TLorentzVector jet3  = TLorentzVector();
			jet3.SetPtEtaPhiE(jet_pt->at(goodjet_index[k]), jet_eta->at(goodjet_index[k]), jet_phi->at(goodjet_index[k]),jet_e->at(goodjet_index[k]));
			
			// find largest pT of 3-jet system,
			float PTjjjTemp = (jet1 + jet2 + jet3).Pt();
			
			if(PTjjjTemp>PTjjjmax){ 
			  PTjjjmax=PTjjjTemp;  
			  Mjjjmax = (jet1 + jet2 + jet3).M(); // this is m(jjj) 
			  a=i; b=j; c=k; // store the indices
			  
			  // among those jets, find largest pT of 2-jet system, a handle of the W-boson
			  float PTjjTemp12 = (jet1 + jet2).Pt();
			  float PTjjTemp13 = (jet1 + jet3).Pt();
			  float PTjjTemp23 = (jet2 + jet3).Pt();
			  
			  if(PTjjTemp12 > PTjjTemp13 && PTjjTemp12 > PTjjTemp23){a=i; b=j; c=k;}
			  if(PTjjTemp13 > PTjjTemp12 && PTjjTemp13 > PTjjTemp23){a=i; b=k; c=j;}
			  if(PTjjTemp23 > PTjjTemp12 && PTjjTemp23 > PTjjTemp13){a=j; b=k; c=i;}
			  
			}   
		      }
		    }
		  }
		  
		  // among the previous 3 jets, we search for those 2 that have the maximum pT, a handle on the W-boson mass
		  TLorentzVector j1  = TLorentzVector(); j1.SetPtEtaPhiE(jet_pt->at(goodjet_index[a]), jet_eta->at(goodjet_index[a]), jet_phi->at(goodjet_index[a]),jet_e->at(goodjet_index[a]));
		  TLorentzVector j2  = TLorentzVector(); j2.SetPtEtaPhiE(jet_pt->at(goodjet_index[b]), jet_eta->at(goodjet_index[b]), jet_phi->at(goodjet_index[b]),jet_e->at(goodjet_index[b]));
		  
		  float Mjjmax= ( j1 + j2 ).M(); // first indices  
		  
		  if( Mjjjmax>100 && Mjjjmax<250 ){
		    FillHistogramsTTbar(Mjjjmax,weight,"hist_Topmass");
		  }
		  if( Mjjmax>50 && Mjjmax<120){
		    FillHistogramsTTbar(Mjjmax,weight,"hist_Wmass");
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

  return kTRUE;
}

void TTbarAnalysis::SlaveTerminate()
{
  TString option = GetOption();
  bool is_data = option.Contains("data");
  
  hist_scale_factors->SetBinContent(0, xsec_SF);
  hist_scale_factors->SetBinContent(1, totalSumOfWeights_SF);
  hist_scale_factors->SetBinContent(2, filteff_SF);
  hist_scale_factors->SetBinContent(3, kfac_SF);
  
}

void TTbarAnalysis::Terminate()
{

  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "trigger cut number: " << trigger_cut << endl;
  cout << "good lepton number: " << good_lepton_n_cut << endl;
  //cout << "opposite charged leptons number: " << OP_charge_leptons_cut << endl;
  //cout << "type leptons number: " << type_leptons_cut << endl;
  cout << "bjets cut number: " << bjets_cut << endl;
  cout << "good electron - muon leptons: " << electron_n << "\t" << muon_n << endl;
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
  //cout << "lep type electron number: " << electron_n << endl;
  //cout << "lep type muon number: " << muon_n << endl;

  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_TTbarAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_TTbar(filename,"recreate");
  WriteHistograms();
  physicsoutput_TTbar.Close();
}
