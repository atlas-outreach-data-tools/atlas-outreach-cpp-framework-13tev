/////////////////////////////////////////////////////////////
//// ZBosonAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define ZBosonAnalysis_cxx

#include "ZBosonAnalysis.h"
#include "ZBosonAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void ZBosonAnalysis::Begin(TTree * )
{
  
  nEvents=0;

}

void ZBosonAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t ZBosonAnalysis::Process(Long64_t entry)
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
      
      //Preselection cut for electron/muon trigger
      if(trigE || trigM)
	{
	  
	  // Preselection of good leptons
	  int goodlep_index[2];
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
		      if ( lep_type->at(i)==11 && abs(lep_eta->at(i)<2.47) && ( abs(lep_eta->at(i) < 1.37) || abs(lep_eta->at(i) > 1.52) ) ) {
			goodlep_n = goodlep_n + 1;
			goodlep_index[lep_index] = i;
			lep_index++;
		      }
		      // muon selection 
		      if ( lep_type->at(i) ==13 && abs(lep_eta->at(i)<2.4) ) {
			goodlep_n = goodlep_n + 1;
			goodlep_index[lep_index] = i;
			lep_index++;
		      }
		    }
		}
	    }
	  
	  //exactly two good leptons
	  if(goodlep_n==2)
	    {
	      
	      int goodlep1_index = goodlep_index[0];
	      int goodlep2_index = goodlep_index[1];
	      
	      // TLorentzVector definitions
	      TLorentzVector Lepton_1  = TLorentzVector();
	      TLorentzVector Lepton_2  = TLorentzVector();
	      
	      Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep1_index), lep_eta->at(goodlep1_index), lep_phi->at(goodlep1_index),lep_E->at(goodlep1_index));
	      Lepton_2.SetPtEtaPhiE(lep_pt->at(goodlep2_index), lep_eta->at(goodlep2_index), lep_phi->at(goodlep2_index),lep_E->at(goodlep2_index));
	      
	      
	      TLorentzVector     Lepton_12 = TLorentzVector();
	      Lepton_12 = Lepton_1 + Lepton_2;
	      float InvMass_Leptons = Lepton_12.Mag()/1000.;
	      
	      //Leptons of opposite charge
	      if(lep_charge->at(goodlep1_index) * lep_charge->at(goodlep2_index)  < 0)
		{
		  // Leptons of same flavour
		  int type_one = lep_type->at(goodlep1_index);
		  int type_two = lep_type->at(goodlep2_index);
		  if(TMath::Abs(type_one) == TMath::Abs(type_two))
		    {
		      float InvMass_Leptons_ee = 0.; if(type_one==11) InvMass_Leptons_ee = InvMass_Leptons;
		      float InvMass_Leptons_mumu = 0.; if(type_one==13) InvMass_Leptons_mumu = InvMass_Leptons;
		      
		      // Invariant mass selection: m_ll - mZ < 25 GeV
		      if(TMath::Abs(InvMass_Leptons - 91.18) < 25.)
			{
			  
			  //Preselection of good jets
			  int goodjet_n = 0;
			  int goodjet_index = 0;
			  
			  if (jet_n > 0) 
			    {
			      for(unsigned int i=0; i<jet_n; i++)
				{
				  if(jet_pt->at(i)>25000. && abs(jet_eta->at(i)) < 2.5)
				    {
				      // JVT cleaning
				      bool jvt_pass=true;
				      if (jet_pt->at(i) < 60000. && abs(jet_eta->at(i)) < 2.4 && jet_jvt->at(i) < 0.59) jvt_pass=false;
				      if (jvt_pass) {
					goodjet_n++;
					goodjet_index = i;
					
				      }
				    }
				}
			    }
			  
			  // To add: we are using a MC sample known to describe poorly large jet multiplicity, thus we cut on nJets<2 for lepton kinematics
			  if(jet_n<2)
			    {
	                      //Start to fill histograms: definitions of variables
			  double names_of_global_variable[]={InvMass_Leptons, InvMass_Leptons_ee, InvMass_Leptons_mumu, met_et/1000.};
			  
			  double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep1_index), (double)lep_type->at(goodlep1_index), lep_ptcone30->at(goodlep1_index)/lep_pt->at(goodlep1_index), lep_etcone20->at(goodlep1_index)/lep_pt->at(goodlep1_index), lep_z0->at(goodlep1_index), lep_trackd0pvunbiased->at(goodlep1_index)};
			  
			  double names_of_subleadlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(),(double)lep_charge->at(goodlep2_index), (double)lep_type->at(goodlep2_index), lep_ptcone30->at(goodlep2_index)/lep_pt->at(goodlep2_index), lep_etcone20->at(goodlep2_index)/lep_pt->at(goodlep2_index), lep_z0->at(goodlep2_index), lep_trackd0pvunbiased->at(goodlep2_index)};
			  
			  
			  //Start to fill histograms : definitions of histogram names
			  TString histonames_of_global_variable[]={"hist_mLL","hist_mLL_ee","hist_mLL_mumu","hist_etmiss"};
			  
			  TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta", "hist_leadleptE", "hist_leadleptphi", "hist_leadleptch", "hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
			  
			  TString histonames_of_subleadlep_variable[]={"hist_subleadleptpt", "hist_subleadlepteta", "hist_subleadleptE", "hist_subleadleptphi", "hist_subleadleptch","hist_subleadleptID","hist_subleadlept_ptc","hist_subleadleptetc","hist_subleadlepz0","hist_subleadlepd0"};

			  //Start to fill histograms : find the histogram array length
			  int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
			  int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
			  int length_subleadlep = sizeof(names_of_subleadlep_variable)/sizeof(names_of_subleadlep_variable[0]);
			  
			  //Fill histograms
			  for (int i=0; i<length_global; i++)
			    {
			      FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
			    }
			  
			  for (int i=0; i<length_leadlep; i++)
			    {
			      FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
			    }

			  for (int i=0; i<length_subleadlep; i++)
			    {
			      FillHistogramsSubleadlept( names_of_subleadlep_variable[i], weight, histonames_of_subleadlep_variable[i]);
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
    }
  
  return kTRUE;
}

void ZBosonAnalysis::SlaveTerminate()
{
}

void ZBosonAnalysis::Terminate()
{
  name="Output_ZBosonAnalysis/"+name+".root";
  
  const char* filename = name.c_str();
  
  TFile physicsoutput_Z(filename,"recreate");
  WriteHistograms();
  physicsoutput_Z.Close();
  
}
