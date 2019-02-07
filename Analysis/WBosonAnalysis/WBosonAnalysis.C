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
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      //Begin analysis
      
      //SF
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_TRIGGER;
      //EventW
      Float_t eventWeight = mcWeight*scaleFactor_PILEUP*scaleFactor_ZVERTEX;
      //weight = SF * EventW
      Float_t weight = scaleFactor*eventWeight;
      
      // Make difference between data and MC
      if (weight == 0.) weight = 1.;
      
      // Missing Et of the event in GeV
      Float_t missingEt = met_et/1000.;

      //First cut : missing energy larger than 30GeV
      if(missingEt > 30.)
	{

	  // Preselection cut for electron/muon trigger, Good Run List, and good vertex
	  if(trigE || trigM)
	    {
	      if(passGRL)
		{
		  if(hasGoodVertex)
		    {
		      // Preselection of good leptons
		      int goodlep_index = 0;
		      int goodlep_n = 0;
		      int lep_index =0;
		      
		      for(unsigned int i=0; i<lep_n; i++)
			{
			  // is Tight
			  if( bool(lep_flag[i] & 512)) 
			    {
			      // isolated
			      if( lep_pt[i]>25000. && (lep_ptcone30[i]/lep_pt[i]) < 0.15 && (lep_etcone20[i]/lep_pt[i]) < 0.15)
				{
				  // electron or muon
				  if ( abs(lep_type[i])==11 ||  abs(lep_type[i])==13) {
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
			  TLorentzVector   Lepton1_MeT = TLorentzVector();
			  
			  Lepton_1.SetPtEtaPhiE(lep_pt[goodlep_index], lep_eta[goodlep_index], lep_phi[goodlep_index],lep_E[goodlep_index]);
			  MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
			  
			  //Calculation of the Invariant Mass using TLorentz vectors (First Lepton + MeT)
			  Lepton1_MeT = Lepton_1 + MeT;
			  float InvMass1       = Lepton1_MeT.Mag();
			  float InvMass1_inGeV = InvMass1/1000.;
			  float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
			  
			  //Third cut : transverse mass larger than 30GeV
			  if(mtw > 30000.)
			    {
			      
			      //Preselection of good jets
			      int goodjet_n = 0;
			      int goodjet_index = 0;
			      
			      for(unsigned int i=0; i<jet_n; i++)
				{
				  if(jet_pt[i]>25000. && abs(jet_eta[i]) < 2.5)
				    {
				      // JVF cleaning
				      bool jvf_pass=true;
				      if (jet_pt[i] < 50000. && abs(jet_eta[i]) < 2.4 && jet_jvf[i] < 0.50) jvf_pass=false;
				      if (jvf_pass) {
					goodjet_n++;
					goodjet_index = i;
								
				      }
				    }
				}
			      
		      
			      
			      //Start to fill histograms : definitions of x-axis variables
			      double names_of_global_variable[]={missingEt, vxp_z, (double)pvxp_n, mtw/1000.};
			      double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge[goodlep_index], (double)lep_type[goodlep_index], lep_ptcone30[goodlep_index]/lep_pt[goodlep_index], lep_etcone20[goodlep_index]/lep_pt[goodlep_index], lep_z0[goodlep_index], lep_trackd0pvunbiased[goodlep_index]};
			      double names_of_jet_variable[]={(double)jet_n, jet_pt[goodjet_index]/1000., jet_eta[goodjet_index], jet_m[goodjet_index]/1000., jet_jvf[goodjet_index], jet_MV1[goodjet_index]};
			      
			      //Start to fill histograms : definitions of histogram names
			      TString histonames_of_global_variable[]={"hist_etmiss","hist_vxp_z","hist_pvxp_n", "hist_mt"};
			      TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
			      TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_leadjet_m", "hist_leadjet_jvf", "hist_leadjet_MV1"};
			      
			      //Start to fill histograms : find the histogram array length
			      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
			      int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
			      int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
			      
			      //Fill histograms
			      for (int i=0; i<length_global; i++)
				{
				  FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
				}
			      for (int i=0; i<length_leadlep; i++)
				{
				  FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
				}
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
