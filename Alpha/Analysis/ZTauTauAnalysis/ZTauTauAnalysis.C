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
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {

      // ****************************************************************************************************************************//
      //  Begin simplified selection based on: ATLAS Collaboration, Eur. Phys. J. C 78 (2018) 163 and Phys. Rev. D 99, 072001 (2019) //
      // ****************************************************************************************************************************//
      
      //Scale factors (adding the one for tau)
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP*scaleFactor_TAU;
      
      //MC weight
      Float_t m_mcWeight = mcWeight;

      // read input option
      TString option = GetOption();
      if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs
      
      //Total weight
      Float_t weight = scaleFactor*m_mcWeight;
      
      // Make difference between data and MC
      if(option.Contains("data")) {  weight = 1.; }
      
      
      //Preselection cut for electron/muon trigger
      if( trigE || trigM)
	{
	  
	  // Preselection, one of the tau-leptons decays leptonically (tau_lep) and the other hadronically (tau_had). Leptonic tau decays are reconstructed as electrons and muons
	  int goodlep_index =0;
	  int goodlep_n = 0;
	  int lep_index =0;
	  
	  for(unsigned int i=0; i<lep_n; i++)
	    {
	      
	      TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);
	      
	      // Lepton is Tight
	      if( lep_isTightID->at(i) )
	      	{
		  // Lepton is highly isolated and hard 
		  if( lep_pt->at(i) >30000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.1) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.1 ) )
		    {
		      // electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
		      if ( lep_type->at(i)==11 && TMath::Abs(lep_eta->at(i)) < 2.47 && ( TMath::Abs(lep_eta->at(i)) < 1.37 || TMath::Abs(lep_eta->at(i)) > 1.52 ) ) {
			if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 5 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
			  goodlep_n = goodlep_n + 1;
			  goodlep_index = i;
			  lep_index++;
			}
		      }
		      // muon selection 
		      if ( lep_type->at(i) ==13 && TMath::Abs(lep_eta->at(i)) < 2.5 ) {
                        if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 3 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
   			  goodlep_n = goodlep_n + 1;
			  goodlep_index = i;
			  lep_index++;
                        }
		      }
		    }
		}
	    }
	  
	  // good tau hadronic selection
	  int goodtau_index = 0;
	  int goodtau_n = 0;
	  int tau_index =0;
	  
	  
	  for(unsigned int i=0; i< tau_n ; i++)
            {
              // tau is Tight
              if( tau_isTightID->at(i) )
                {
                  // tau pT and eta requirements
                  if( tau_pt->at(i) >25000. && TMath::Abs(tau_eta->at(i)) < 2.5 )
                    {
		      goodtau_n = goodtau_n + 1;
		      goodtau_index = i;
		      tau_index++;
                    }
                }
            }
	  
	  //exactly one good lepton and good tau
	  if(goodlep_n==1 && goodtau_n==1)
	    {
              // opposite charge
              if(lep_charge->at(goodlep_index) * tau_charge->at(goodtau_index)  < 0)
		{
		  
		  // TLorentzVector definitions
		  TLorentzVector Lepton  = TLorentzVector();
		  TLorentzVector HadTau  = TLorentzVector();
		  
		  Lepton.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
		  HadTau.SetPtEtaPhiE(tau_pt->at(goodtau_index), tau_eta->at(goodtau_index), tau_phi->at(goodtau_index),tau_E->at(goodtau_index));
		  
		  TLorentzVector      MeT  = TLorentzVector();
		  MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
		  
		  // MT
		  float mt = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));
		  int type_one = lep_type->at(goodlep_index);
		  float mt_etau=0.;   if(type_one==11)  {mt_etau = mt/1000.;  }
		  float mt_mutau=0.;  if(type_one==13)  {mt_mutau = mt/1000.; }
		  
		  TLorentzVector     Lepton_12 = TLorentzVector();
		  Lepton_12 = Lepton + HadTau;
		  float VisibleMass_LepTau = Lepton_12.Mag()/1000.; //  visible mass is defined as the invariant mass of the lepton and the hadronic tau candidate.
		  
		  float MMC_mass = ditau_m; // The ditau invariant mass is determined using the missing-mass calculator (MMC) [Nucl. Instrum. Meth. A 654 (2011) 481,]
		  
		  float dPhi_tau_MET  = TMath::Abs(tau_phi->at(goodtau_index) - MeT.Phi() );
		  dPhi_tau_MET        = dPhi_tau_MET < TMath::Pi() ? dPhi_tau_MET : 2*TMath::Pi() - dPhi_tau_MET;
		  
		  float dPhi_lep_MET = TMath::Abs( Lepton.Phi() - MeT.Phi() );
		  dPhi_lep_MET       = dPhi_lep_MET < TMath::Pi() ? dPhi_lep_MET : 2*TMath::Pi() - dPhi_lep_MET;
		  
		  float sum_dPhi = dPhi_tau_MET  + dPhi_lep_MET;
		  
		  
		  //Preselection of good jets
		  int goodjet_n = 0;
		  int goodjet_index = 0;
		  		  
		  if (jet_n > 0) 
		    {
		      for(unsigned int i=0; i<jet_n; i++)
			{
			  if(jet_pt->at(i) > 25000. && TMath::Abs(jet_eta->at(i)) < 2.5)
			    {
			      // JVT cleaning
			      bool jvt_pass=true;
			      if (jet_pt->at(i) < 60000. && TMath::Abs(jet_eta->at(i)) < 2.4 && jet_jvt->at(i) < 0.59) jvt_pass=false;
			      if (jvt_pass) {
				goodjet_n++;
				goodjet_index = i;
				
			      }
			    }
			}
		    }
		  
		  // transverse mass less than 30 GeV, suppresses the W + jets background
		  // dPhi requirement suppresses event topologies in which the MET lies outside of the angle spanned by the tau candidate and the lepton, which are common for W+jets processes and rare for signal events. 
		  // visible mass window of 35 - 75 GeV cut applied to increase the Z->tautau signal purity and maximize the separation from Z->ll background
		  if ( VisibleMass_LepTau > 35 && VisibleMass_LepTau < 75 && mt < 30000 && sum_dPhi < 3.5 ) {
		 
		    //Start to fill histograms: definitions of variables
		    double names_of_global_variable[]      ={VisibleMass_LepTau, MMC_mass, met_et/1000.,  mt_etau,        mt_mutau, sum_dPhi, (double)jet_n };
		    TString histonames_of_global_variable[]={"hist_mLL",      "hist_MMC",   "hist_etmiss", "hist_mt_etau", "hist_mt_mutau", "hist_sum_dPhi", "hist_n_jets"};
		    
		    double names_of_leadlep_variable[]={Lepton.Pt()/1000., Lepton.Eta(), Lepton.E()/1000., Lepton.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index)};
		    TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta", "hist_leadleptE", "hist_leadleptphi", "hist_leadleptch", "hist_leadleptID"};
		    
		    double names_of_tau_variable[]={HadTau.Pt()/1000., HadTau.Eta(), HadTau.E()/1000., HadTau.Phi(), (double)tau_nTracks->at(goodtau_index), tau_BDTid->at(goodtau_index) };
		    TString histonames_of_tau_variable[]={"hist_taupt", "hist_taueta", "hist_tauE", "hist_tauphi", "hist_tau_nTracks", "hist_tau_BDTid"};
		    
		    
		    //Start to fill histograms : find the histogram array length
		    int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
		    int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
		    int length_tau = sizeof(names_of_tau_variable)/sizeof(names_of_tau_variable[0]);
		    
		    //Fill histograms
		    for (int i=0; i<length_global; i++)
		      {
			FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
		      }
		    
		    for (int i=0; i<length_leadlep; i++)
		      {
			FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
		      }
		    
		    for (int i=0; i<length_tau; i++)
		      {
			FillHistogramsTau( names_of_tau_variable[i], weight, histonames_of_tau_variable[i]);
		      }
		    
		    
		    // systematic variations on tau pT
		    // Sample a random number from a Gaussian distribution with a given mean and sigma
		    TRandom3* gRand = new TRandom3(0);
		    Double_t      mean     = tau_pt->at(goodtau_index)/1000. ; // nominal
		    Double_t      sigma    = tau_pt_syst->at(goodtau_index)/1000. ; // width corresponds to the uncertainty
		    float tau_pt_variation = gRand->Gaus(mean, sigma); // this is the variation up and down
		    
		    if(tau_pt_variation>25) FillHistogramsTau( tau_pt_variation , weight, "hist_syst_taupt");
		    
	      
		    // fill jets
		    if (jet_n > 0) 
		      {
			double names_of_jet_variable[]={jet_pt->at(goodjet_index)/1000., jet_eta->at(goodjet_index)};
			TString histonames_of_jet_variable[]={"hist_leadjet_pt","hist_leadjet_eta"};
			int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
			for (int i=0; i<length_leadjet; i++)
			  {
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
}

void ZTauTauAnalysis::Terminate()
{

  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_ZTauTauAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_Z(filename,"recreate");
  WriteHistograms();
  physicsoutput_Z.Close();
  
}
