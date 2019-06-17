/////////////////////////////////////////////////////////////
//// WBosonAnalysis code
//// Author: ATLAS Collaboration (2018)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define WBosonAnalysis_cxx

#include "WBosonAnalysis.h"
#include "WBosonAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void WBosonAnalysis::Begin(TTree * )
{
  
  nEvents=0;
  
}

void WBosonAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t WBosonAnalysis::Process(Long64_t entry)
{
  
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, Phys. Lett. B 759 (2016) 601 //
      // **********************************************************************************************//
      
      //Scale factors
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER;
      //Event weight
      Float_t eventWeight = mcWeight*scaleFactor_PILEUP;
      //Total weight
      Float_t weight = scaleFactor*eventWeight;
      
      // Make difference between data and MC
      if (weight == 0.) weight = 1.;
      
      // Missing Et of the event in GeV
      Float_t missingEt = met_et/1000.;
      
      //First cut : missing energy larger than 25 GeV
      if(missingEt > 25.)
	{
	  
	  // Preselection cut for electron/muon trigger
	  if(trigE || trigM)
	    {
	      
	      // Preselection of good leptons
	      int goodlep_index = 0;
	      int goodlep_n = 0;
	      int lep_index =0;
	      
	      for(unsigned int i=0; i<lep_n; i++)
		{
		  // Lepton is Tight
		  if( lep_isTightID->at(i) )
		    {
		      // Lepton is isolated and hard pT
		      if( lep_pt->at(i) >25000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15 ) )
			{
                	  // electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
			  if ( lep_type->at(i)==11 && TMath::Abs(lep_eta->at(i)<2.47) && ( TMath::Abs(lep_eta->at(i) < 1.37) || TMath::Abs(lep_eta->at(i) > 1.52) ) ) {
			    goodlep_n = goodlep_n + 1;
			    goodlep_index = i;
			    lep_index++;
			  }
			  // muon selection
			  if ( lep_type->at(i) ==13 && TMath::Abs(lep_eta->at(i)<2.4) ) {
			    goodlep_n = goodlep_n + 1;
			    goodlep_index = i;
			    lep_index++;
			  }
			}
		    }
		}
	      
	      //Exactly one good lepton
	      if(goodlep_n==1)
		{
		  
		  // TLorentzVector definitions
		  TLorentzVector Lepton_1  = TLorentzVector();
		  TLorentzVector      MeT  = TLorentzVector();
		  
		  Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
		  MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
		  
		  //Calculation of the W-boson transverse mass
		  float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
		  
		  int type_one = lep_type->at(goodlep_index);
		  float mtw_enu=0.; 
		  if(type_one==11)  {mtw_enu = mtw;  }
		  float mtw_munu=0.; 
		  if(type_one==13) {mtw_munu = mtw; }
		  
		  //transverse mass larger than 50 GeV
		  if(mtw > 50000.)
		    {
		      
		      //Preselection of good jets
		      int goodjet_n = 0;
		      int goodjet_index = 0;
		      
		      if (jet_n > 0) 
			{
			  for(unsigned int i=0; i<jet_n; i++)
			    {
			      if(jet_pt->at(i)>25000. && TMath::Abs(jet_eta->at(i)) < 2.5)
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
		      
		      // To add: we are using a MC sample known to describe poorly large jet multiplicity, thus we cut on nJets<2 for lepton kinematics
		      if(jet_n<1)
			{
			  
			  //Start to fill histograms : definitions of x-axis variables
			  double names_of_global_variable[]={missingEt, mtw/1000. , mtw_enu/1000., mtw_munu/1000.};
			  
			  double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index), lep_ptcone30->at(goodlep_index)/lep_pt->at(goodlep_index), lep_etcone20->at(goodlep_index)/lep_pt->at(goodlep_index), lep_z0->at(goodlep_index), lep_trackd0pvunbiased->at(goodlep_index)};
			  
			  
			  //Start to fill histograms : definitions of histogram names
			  TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw","hist_mtw_enu","hist_mtw_munu"};
			  
			  TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
			  
			  //Start to fill histograms : find the histogram array length
			  int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
			  int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
			  
			  //Fill histograms
			  for (int i=0; i<length_global; i++)
			    {
			      FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
			    }
			  
			  for (int i=0; i<length_leadlep; i++)
			    {
			      FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
			    }
			
			}//jet cut		    
		      
		      // fill jets
		      if (jet_n > 0)
			{
			  double names_of_jet_variable[]={(double)jet_n, jet_pt->at(goodjet_index)/1000., jet_eta->at(goodjet_index)};
			  TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta"};
			  int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
			  for (int i=0; i<length_leadjet; i++)
			    {
			      FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
			    }
			}
		    }
		}
	    }
	}
    }
  
  return kTRUE;
}

void WBosonAnalysis::SlaveTerminate()
{
}

void WBosonAnalysis::Terminate()
{

  name="Output_WBosonAnalysis/"+name+".root";

  const char* filename = name.c_str();

  TFile physicsoutput_W(filename,"recreate");
  WriteHistograms();
  physicsoutput_W.Close();
  
}
