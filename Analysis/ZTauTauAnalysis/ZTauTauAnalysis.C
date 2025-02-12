/////////////////////////////////////////////////////////////
//// ZTauTauAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define ZTauTauAnalysis_cxx

#include "ZTauTauAnalysis.h"
#include "ZTauTauAnalysisHistograms.h"

#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom3.h>

string name;

void ZTauTauAnalysis::Begin(TTree * )
{
  
  nEvents=0;
  xsec_SF = 0;
  totalSumOfWeights_SF = 0;
  filteff_SF = 0;
  kfac_SF = 0;
  
}

void ZTauTauAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t ZTauTauAnalysis::Process(Long64_t entry)
{
  
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 10000000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0){

    // ****************************************************************************************************************************//
    //  Begin simplified selection based on: ATLAS Collaboration, Eur. Phys. J. C 78 (2018) 163 and Phys. Rev. D 99, 072001 (2019) //
    // ****************************************************************************************************************************//
    
    //Scale factors (adding the one for tau)

    Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_TAU*ScaleFactor_LepTRIGGER*ScaleFactor_PILEUP*ScaleFactor_JVT;
    
    //Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_TAU*ScaleFactor_PILEUP*ScaleFactor_JVT;

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
    if( trigE || trigM ){
	  
      // Preselection, one of the tau-leptons decays leptonically (tau_lep) and the other hadronically (tau_had). Leptonic tau decays are reconstructed as electrons and muons
      int goodlep_index =0;
      int goodlep_n = 0;
      int lep_index =0;
	  
      for(Int_t i=0; i<lep_n; i++){
	
	TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i), lep_eta->at(i), lep_phi->at(i), lep_e->at(i));
	
	// Lepton is Tight
	if( (lep_isTightID->at(i)==true) && (lep_isTightIso->at(i)==true) && (lep_isTrigMatched->at(i)==true) ){

	  if( (lep_pt->at(i)>30.) ){
	    // electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
	    if( (lep_type->at(i)==11) && (TMath::Abs(lep_eta->at(i))<2.47) && (TMath::Abs(lep_eta->at(i))<1.37 || TMath::Abs(lep_eta->at(i)) > 1.52) ){
	      goodlep_n = goodlep_n + 1;
	      goodlep_index = i;
	      lep_index++;
	    }

	    // muon selection 
	    if( (lep_type->at(i)==13) && (TMath::Abs(lep_eta->at(i))<2.5) ){
	      goodlep_n = goodlep_n + 1;
	      goodlep_index = i;
	      lep_index++;
	    }
	  }
	}
      }
    
      // good tau hadronic selection
      int goodtau_index = 0;
      int goodtau_n = 0;
      int tau_index =0;
      
      for(Int_t i=0; i< tau_n ; i++){
	// tau is Tight
	if( tau_isTight->at(i)==true ){
	  // tau pT and eta requirements
	  if( (tau_pt->at(i)>25.) && (TMath::Abs(tau_eta->at(i))<2.5) ){
	    goodtau_n = goodtau_n + 1;
	    goodtau_index = i;
	    tau_index++;
	  }
	}
      }
	  
      //exactly one good lepton and good tau
      if( goodlep_n==1 && goodtau_n==1 ){
	// opposite charge
	if( lep_charge->at(goodlep_index)*tau_charge->at(goodtau_index)<0 ){
	  
	  // TLorentzVector definitions
	  TLorentzVector Lepton  = TLorentzVector();
	  TLorentzVector HadTau  = TLorentzVector();
	  
	  Lepton.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index), lep_e->at(goodlep_index));
	  HadTau.SetPtEtaPhiE(tau_pt->at(goodtau_index), tau_eta->at(goodtau_index), tau_phi->at(goodtau_index), tau_e->at(goodtau_index));
	  
	  TLorentzVector      MeT  = TLorentzVector();
	  MeT.SetPtEtaPhiE(met, 0, met_phi , met);
	  
	  // MT
	  float mt = TMath::Sqrt(2*Lepton.Pt()*MeT.Et()*(1-TMath::Cos(Lepton.DeltaPhi(MeT))));
	  int type_one = lep_type->at(goodlep_index);
	  float mt_etau=0.;   if(type_one==11)  {mt_etau = mt;  }
	  float mt_mutau=0.;  if(type_one==13)  {mt_mutau = mt; }
	  
	  TLorentzVector     Lepton_12 = TLorentzVector();
	  Lepton_12 = Lepton + HadTau;
	  float VisibleMass_LepTau = Lepton_12.Mag(); //  visible mass is defined as the invariant mass of the lepton and the hadronic tau candidate.

	  //**************
	  //There is no a branch with ditau_m computed through the missing-mass calculator in the third release of data.
	  
	  //float MMC_mass = ditau_m; // The ditau invariant mass is determined using the missing-mass calculator (MMC) [Nucl. Instrum. Meth. A 654 (2011) 481,]
	  //**************

	  float dPhi_tau_MET  = TMath::Abs(tau_phi->at(goodtau_index) - MeT.Phi() );
	  dPhi_tau_MET        = dPhi_tau_MET < TMath::Pi() ? dPhi_tau_MET : 2*TMath::Pi() - dPhi_tau_MET;
	  
	  float dPhi_lep_MET = TMath::Abs( Lepton.Phi() - MeT.Phi() );
	  dPhi_lep_MET       = dPhi_lep_MET < TMath::Pi() ? dPhi_lep_MET : 2*TMath::Pi() - dPhi_lep_MET;
	  
	  float sum_dPhi = dPhi_tau_MET  + dPhi_lep_MET;
	  
	  //Preselection of good jets
	  int goodjet_n = 0;
	  int goodjet_index = 0;
	  
	  if (jet_n>0){
	    for(Int_t i=0; i<jet_n; i++){
	      if( (jet_pt->at(i)>25.) && (TMath::Abs(jet_eta->at(i))<2.5) ){
		// JVT cleaning
		bool jvt_pass=true;
		if( jet_jvt->at(i)==false ) jvt_pass=false;

		if (jvt_pass){
		  goodjet_n++;
		  goodjet_index = i;
		}
	      }
	    }
	  }
	  
	  // transverse mass less than 30 GeV, suppresses the W + jets background
	  // dPhi requirement suppresses event topologies in which the MET lies outside of the angle spanned by the tau candidate and the lepton, which are common for W+jets processes and rare for signal events. 
	  // visible mass window of 35 - 75 GeV cut applied to increase the Z->tautau signal purity and maximize the separation from Z->ll background
	  if ( (VisibleMass_LepTau>35) && (VisibleMass_LepTau<75) && (mt<30) && (sum_dPhi<3.5) ) {
		 
	    //Start to fill histograms: definitions of variables
	    //*******************
	    // There is no branch called ditau_m, so there is no MMC value
	    //double names_of_global_variable[]      = { VisibleMass_LepTau, MMC_mass, met,  mt_etau, mt_mutau, sum_dPhi, (double)jet_n };
	    //TString histonames_of_global_variable[]= {"hist_mLL", "hist_MMC", "hist_etmiss", "hist_mt_etau", "hist_mt_mutau", "hist_sum_dPhi", "hist_n_jets"};
	    //*******************
	    
	    double names_of_global_variable[]      = { VisibleMass_LepTau, met,  mt_etau, mt_mutau, sum_dPhi, (double)jet_n };
	    TString histonames_of_global_variable[]= {"hist_mLL", "hist_etmiss", "hist_mt_etau", "hist_mt_mutau", "hist_sum_dPhi", "hist_n_jets"};
	    
	    double names_of_leadlep_variable[]     = {Lepton.Pt(), Lepton.Eta(), Lepton.E(), Lepton.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index)};
	    TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta", "hist_leadleptE", "hist_leadleptphi", "hist_leadleptch", "hist_leadleptID"};

	    //*************
	    // There is no a branch called tau_BDTid
	    //double names_of_tau_variable[]={HadTau.Pt(), HadTau.Eta(), HadTau.E(), HadTau.Phi(), (double)tau_nTracks->at(goodtau_index), tau_BDTid->at(goodtau_index) };
	    //TString histonames_of_tau_variable[]={"hist_taupt", "hist_taueta", "hist_tauE", "hist_tauphi", "hist_tau_nTracks", "hist_tau_BDTid"};
	    //************
	    
	    double names_of_tau_variable[] ={ HadTau.Pt(), HadTau.Eta(), HadTau.E(), HadTau.Phi(), (double)tau_nTracks->at(goodtau_index) };
	    TString histonames_of_tau_variable[]={"hist_taupt", "hist_taueta", "hist_tauE", "hist_tauphi", "hist_tau_nTracks" };
	     
	    //Start to fill histograms : find the histogram array length
	    int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
	    int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
	    int length_tau = sizeof(names_of_tau_variable)/sizeof(names_of_tau_variable[0]);
	    
	    //Fill histograms
	    for (int i=0; i<length_global; i++){
	      FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
	    }
	    
	    for (int i=0; i<length_leadlep; i++){
	      FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
	    }
		    
	    for (int i=0; i<length_tau; i++){
	      FillHistogramsTau( names_of_tau_variable[i], weight, histonames_of_tau_variable[i]);
	    }
		    
	    /*
	    // systematic variations on tau pT
	    // Sample a random number from a Gaussian distribution with a given mean and sigma
	    TRandom3* gRand = new TRandom3(0);
	    Double_t      mean     = tau_pt->at(goodtau_index)/1000. ; // nominal
	    Double_t      sigma    = tau_pt_syst->at(goodtau_index)/1000. ; // width corresponds to the uncertainty
	    float tau_pt_variation = gRand->Gaus(mean, sigma); // this is the variation up and down
	    
	    if(tau_pt_variation>25) FillHistogramsTau( tau_pt_variation , weight, "hist_syst_taupt");
	    */
	    
	    // fill jets
	    if (jet_n > 0){
	      double names_of_jet_variable[]={jet_pt->at(goodjet_index), jet_eta->at(goodjet_index)};
	      TString histonames_of_jet_variable[]={"hist_leadjet_pt","hist_leadjet_eta"};
	      int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
	      for (int i=0; i<length_leadjet; i++){
		FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
	      }
	    } // jet_n 
	  }
	} 
      }
    }
  }
  
  return kTRUE;
}

void ZTauTauAnalysis::SlaveTerminate()
{
  TString option = GetOption();
  bool is_data = option.Contains("data");
  
  hist_scale_factors->SetBinContent(0, xsec_SF);
  hist_scale_factors->SetBinContent(1, totalSumOfWeights_SF);
  hist_scale_factors->SetBinContent(2, filteff_SF);
  hist_scale_factors->SetBinContent(3, kfac_SF);
  
}

void ZTauTauAnalysis::Terminate()
{
  /*
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
  */
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "The scaling factors values are: " << endl;
  cout << "xsec: " << xsec_SF << endl;
  cout << "totalSumOfWeights: " << totalSumOfWeights_SF  << endl;
  cout << "filteff: " << filteff_SF << endl;
  cout << "kfac: " << kfac_SF << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_ZTauTauAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_Z(filename,"recreate");
  WriteHistograms();
  physicsoutput_Z.Close();
  
}
