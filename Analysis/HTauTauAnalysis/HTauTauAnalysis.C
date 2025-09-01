/////////////////////////////////////////////////////////////
//// HTauTauAnalysis code
//// Author: ATLAS Collaboration (2025)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define HTauTauAnalysis_cxx

#include "HTauTauAnalysis.h"
#include "HTauTauAnalysisHistograms.h"

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
#include <TMatrixD.h>

//  mass collinear definition 
bool MassCollinearCore(const TLorentzVector &k1,
                       const TLorentzVector &k2,
                       const double met_x,
                       const double met_y,
                       double &mass, double &xp1, double &xp2) {
    TMatrixD K(2, 2);
    K(0, 0) = k1.Px();
    K(0, 1) = k2.Px();
    K(1, 0) = k1.Py();
    K(1, 1) = k2.Py();

    if (K.Determinant() == 0)
        return false;

    TMatrixD M(2, 1);
    M(0, 0) = met_x;
    M(1, 0) = met_y;

    TMatrixD Kinv = K;
    Kinv.Invert();

    TMatrixD X = Kinv * M;

    double X1 = X(0, 0);
    double X2 = X(1, 0);
    double x1 = 1. / (1. + X1);
    double x2 = 1. / (1. + X2);

    TLorentzVector p1 = k1 * (1. / x1);
    TLorentzVector p2 = k2 * (1. / x2);
    mass = (p1 + p2).M();

    if (k1.Pt() > k2.Pt()) {
        xp1 = x1;
        xp2 = x2;
    } else {
        xp1 = x2;
        xp2 = x1;
    }

    return true;
}

void HTauTauAnalysis::Begin(TTree * )
{
  
  nEvents=0;
  xsec_SF = 0;
  totalSumOfWeights_SF = 0;
  filteff_SF = 0;
  kfac_SF = 0;
  
}

void HTauTauAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t HTauTauAnalysis::Process(Long64_t entry)
{
  
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 10000000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0){

    // ******************************************************************************************************************
    //  Begin simplified selection based on: ATLAS Collaboration, Eur. Phys. J. C 78 (2018) 163 and Phys. Rev. D 99, 072001 (2019) 
    // ******************************************************************************************************************
    
    //Scale factors (adding the one for tau)
    
    Float_t scaleFactor = ScaleFactor_ELE*ScaleFactor_MUON*ScaleFactor_TAU*ScaleFactor_LepTRIGGER*ScaleFactor_PILEUP*ScaleFactor_JVT;
    
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
    
    //Preselection cut for electron/muon trigger
    if( trigE || trigM ){
	  
      // Preselection, one of the tau-leptons decays leptonically (tau_lep) and the other hadronically (tau_had). Leptonic tau decays are reconstructed as electrons and muons
      int goodlep_index =0;
      int goodlep_n = 0;
      int lep_index =0;
	  
      for(Int_t i=0; i<lep_n; i++){
	
	TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i), lep_eta->at(i), lep_phi->at(i), lep_e->at(i));
	
	// Lepton is Medium, ISo is tight for muon and loose for electron
	if( (lep_isMediumID->at(i)==true) && ((lep_isTightIso->at(i)==true && lep_type->at(i)==13) || (lep_isLooseIso->at(i)==true && lep_type->at(i)==11 )) && (lep_isTrigMatched->at(i)==true) ){

	  if( (lep_pt->at(i)>21. && lep_type->at(i)==11) || (lep_pt->at(i)>27.3 && lep_type->at(i)==13) ){
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
	// tau istau_RNNJetScore->at(i)<0.2  Tight tau_isTight->at(i)==true
	if(tau_isTight->at(i)==true ){   // hadronic tau
	  // tau pT and eta requirements
	  if( (tau_pt->at(i)>30.) && (TMath::Abs(tau_eta->at(i))<2.5) ){
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
          
          double m_col = -1;
          double x1_col = -1;
          double x2_col = -1;

          //double met_x = met * TMath::Cos(met_phi);
          //double met_y = met * TMath::Sin(met_phi);
          double met_x = met_mpx;
          double met_y = met_mpy;
          bool hasColMass = MassCollinearCore(Lepton, HadTau, met_x, met_y, m_col, x1_col, x2_col);

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
	      if( (jet_pt->at(i)>40.) && (TMath::Abs(jet_eta->at(i))<2.5) ){
		// JVT cleaning
		bool jvt_pass=true;
		if( jet_jvt->at(i)==false ) jvt_pass=false;

		if (jvt_pass == true){
		  goodjet_n++;
		  goodjet_index = i;
		}
	      }
	    }
	  }
          float deltaR = Lepton.DeltaR(HadTau);
	  // transverse mass less than 30 GeV, suppresses the W + jets background
	  // dPhi requirement suppresses event topologies in which the MET lies outside of the angle spanned by the tau candidate and the lepton, which are common for W+jets processes and rare for signal events. 
	  // visible mass window of 35 - 75 GeV cut applied to increase the Z->tautau signal purity and maximize the separation from Z->ll background
          TLorentzVector total_system = Lepton + HadTau + MeT;
          double m_total = total_system.M();	  
          if ( deltaR<2.5 && mt<70 && (VisibleMass_LepTau>35) && (VisibleMass_LepTau<175) &&(sum_dPhi<3.5) ) {
            if (!hasColMass) return kTRUE; 
            if (x1_col <= 0.1 || x1_col >= 1.2) return kTRUE;
            if (x2_col <= 0.1 || x2_col >= 1.4) return kTRUE;
	    //Start to fill histograms: definitions of variables
	    double names_of_global_variable[]      = { VisibleMass_LepTau, m_col, met,  mt_etau, mt_mutau, sum_dPhi, (double)jet_n, m_total };
	    TString histonames_of_global_variable[]= {"hist_mLL","hist_m_col", "hist_etmiss", "hist_mt_etau", "hist_mt_mutau", "hist_sum_dPhi", "hist_n_jets", "hist_m_total"};
	    double names_of_leadlep_variable[]     = {Lepton.Pt(), Lepton.Eta(), Lepton.E(), Lepton.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index)};
	    TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta", "hist_leadleptE", "hist_leadleptphi", "hist_leadleptch", "hist_leadleptID"};

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
		    	    
	    // fill jets
	    if (jet_n > 0){
	      double names_of_jet_variable[]={jet_pt->at(goodjet_index), jet_eta->at(goodjet_index)};
	      TString histonames_of_jet_variable[]={"hist_leadjet_pt","hist_leadjet_eta"};
	      int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
	      for (int i=0; i<length_leadjet; i++){
		FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
	      }
	    } // jet_n 
	  } //loop
	} 
      }
    }
  }
  
  return kTRUE;
}

void HTauTauAnalysis::SlaveTerminate()
{
  TString option = GetOption();
  bool is_data = option.Contains("data");
  
  hist_scale_factors->SetBinContent(0, xsec_SF);
  hist_scale_factors->SetBinContent(1, totalSumOfWeights_SF);
  hist_scale_factors->SetBinContent(2, filteff_SF);
  hist_scale_factors->SetBinContent(3, kfac_SF);
  
}

void HTauTauAnalysis::Terminate()
{

  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "The scaling factors values are: " << endl;
  cout << "xsec: " << xsec_SF << endl;
  cout << "totalSumOfWeights: " << totalSumOfWeights_SF  << endl;
  cout << "filteff: " << filteff_SF << endl;
  cout << "kfac: " << kfac_SF << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_HTauTauAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_Z(filename,"recreate");
  WriteHistograms();
  physicsoutput_Z.Close();
  
}
