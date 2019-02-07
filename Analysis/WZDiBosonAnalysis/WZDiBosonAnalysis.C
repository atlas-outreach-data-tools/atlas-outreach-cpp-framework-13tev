/////////////////////////////////////////////////////////////
//// WZDiBosonAnalysis code
//// Author: ATLAS Collaboration (2018)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define WZDiBosonAnalysis_cxx

#include "WZDiBosonAnalysis.h"
#include "WZDiBosonAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void WZDiBosonAnalysis::Begin(TTree * )
{
}

void WZDiBosonAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t WZDiBosonAnalysis::Process(Long64_t entry)
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
      
      //Preselection cut for electron/muon trigger, Good Run List, and good vertex
      if(trigE || trigM)
	{
	  if(passGRL)
	    {
	      if(hasGoodVertex)
		{
		  // Preselection of good leptons
		  int goodlep_index[3];
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
				goodlep_index[lep_index] = i;
				lep_index++;
			      }
			    }
			}
		    }
		  
		  
		  //Exactly three good leptons
		  if(goodlep_n==3)
		    {
		      
		      int goodlep1_index = goodlep_index[0];
		      int goodlep2_index = goodlep_index[1];
		      int goodlep3_index = goodlep_index[2];
		      
		      
		      // TLorentzVector definitions
		      TLorentzVector Lepton_1  = TLorentzVector();
		      TLorentzVector Lepton_2  = TLorentzVector();
		      TLorentzVector Lepton_3  = TLorentzVector();
		      TLorentzVector      MeT  = TLorentzVector();
		      
		      Lepton_1.SetPtEtaPhiE(lep_pt[goodlep1_index], lep_eta[goodlep1_index], lep_phi[goodlep1_index],lep_E[goodlep1_index]);
		      Lepton_2.SetPtEtaPhiE(lep_pt[goodlep2_index], lep_eta[goodlep2_index], lep_phi[goodlep2_index],lep_E[goodlep2_index]);
		      Lepton_3.SetPtEtaPhiE(lep_pt[goodlep3_index], lep_eta[goodlep3_index], lep_phi[goodlep3_index],lep_E[goodlep3_index]);
		      MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
		      
		      float InvMass12       = (Lepton_1+Lepton_2).Mag()/1000.;
		      float InvMass13       = (Lepton_1+Lepton_3).Mag()/1000.;
		      float InvMass23       = (Lepton_2+Lepton_3).Mag()/1000.;
		      
		      float delta_lep12_Z =  -1;
		      float delta_lep13_Z =  -1;
		      float delta_lep23_Z =  -1;
		      
		      
		      // charge of leptons coming from Z is different
		      if (lep_charge[goodlep1_index] * lep_charge[goodlep2_index]  < 0 ) 
			{
			  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep2_index])  )
			    {
			      delta_lep12_Z =  TMath::Abs(InvMass12 - 91.18);
			    }
			}
		      
		      if (lep_charge[goodlep1_index] * lep_charge[goodlep3_index]  < 0 ) 
			{
			  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep3_index]) )
			    {
			      delta_lep13_Z =  TMath::Abs(InvMass13 - 91.18);
			    }
			}
		      
		      if ( lep_charge[goodlep2_index] * lep_charge[goodlep3_index]  < 0 ) 
			{
			  if ( abs (lep_type[goodlep2_index]) == abs (lep_type[goodlep3_index]) )
			    {
			      delta_lep23_Z =  TMath::Abs(InvMass23 - 91.18);
			    }
			}
		      
                      // define candidates 
		      int wcand = 0;
		      float tmp = 0;
		      
		      
		      // begin all permutations, for easy understanding write them by hand
		      // in the case we have eee or mumumu
		      ////		      
		      if( ( delta_lep12_Z >0 && delta_lep23_Z >0)  && delta_lep13_Z < 0 && (delta_lep12_Z < delta_lep23_Z) ) {
			tmp = delta_lep12_Z; 
			wcand = 3;
		      } 
		      
                      if( ( delta_lep12_Z >0 && delta_lep23_Z >0)   && delta_lep13_Z < 0 && (delta_lep12_Z > delta_lep23_Z) ) {
			tmp = delta_lep23_Z; 
			wcand = 1;
                      }
		      
                      if( ( delta_lep12_Z >0 && delta_lep13_Z >0 )  && delta_lep23_Z < 0 && (delta_lep12_Z < delta_lep13_Z) ) {
			tmp = delta_lep12_Z;
			wcand = 3;
                      }
		      
                      if( ( delta_lep12_Z >0 && delta_lep13_Z >0 ) && delta_lep23_Z < 0 && (delta_lep12_Z > delta_lep13_Z) ) {
			tmp = delta_lep13_Z;
			wcand = 2;
                      }
		      
                      if( ( delta_lep13_Z >0 && delta_lep23_Z >0)  && delta_lep12_Z < 0 && (delta_lep13_Z < delta_lep23_Z) ) {
			tmp = delta_lep13_Z;
			wcand = 2;
                      }
		      
                      if( ( delta_lep13_Z >0 && delta_lep23_Z >0)  && delta_lep12_Z < 0 && (delta_lep13_Z > delta_lep23_Z) ) {
			tmp = delta_lep23_Z;
			wcand = 1;
                      }
		      ////
		      
		      
		      // in the case we have eemu or mumue
		      ////
		      
                      if ( delta_lep12_Z < 0 && delta_lep23_Z  < 0 && delta_lep13_Z > 0) {
			tmp = delta_lep13_Z; 
			wcand = 2;
                      }
		      
                      if ( delta_lep12_Z < 0 && delta_lep13_Z  < 0 && delta_lep23_Z > 0) {
			tmp = delta_lep23_Z;
			wcand = 1;
                      }
		      
                      if ( delta_lep23_Z < 0 && delta_lep13_Z  < 0 && delta_lep12_Z > 0) {
			tmp = delta_lep12_Z;
			wcand = 3;
                      }
		      ////
		      
		      // depending on which is the W candidate, build mtw
		      float mtw=0;
		      if(wcand==1) mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
		      if(wcand==2) mtw = sqrt(2*Lepton_2.Pt()*MeT.Et()*(1-cos(Lepton_2.DeltaPhi(MeT))));
		      if(wcand==3) mtw = sqrt(2*Lepton_3.Pt()*MeT.Et()*(1-cos(Lepton_3.DeltaPhi(MeT))));
		      
		      
		      // depending on which is the W candidate, build mll     
                      float mll=0;
		      if(wcand==1) mll = InvMass23;
                      if(wcand==2) mll = InvMass13;
                      if(wcand==3) mll = InvMass12;
		      
		      
		      // cut: m_ll - m(Z) < 10
		      if(tmp < 10.)
			{
			  //mtw > 30 GeV
			  if(mtw > 30000.)
			    {
			      
			      
			      double names_of_global_variable[]={mll, missingEt, vxp_z, (double)pvxp_n, mtw/1000.};
			      
			      double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge[goodlep1_index], (double)lep_type[goodlep1_index], lep_ptcone30[goodlep1_index]/lep_pt[goodlep1_index], lep_etcone20[goodlep1_index]/lep_pt[goodlep1_index], lep_z0[goodlep1_index], lep_trackd0pvunbiased[goodlep1_index]};
			      
			      double names_of_secondlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), lep_charge[goodlep2_index], (double)lep_type[goodlep2_index], lep_ptcone30[goodlep2_index]/lep_pt[goodlep2_index], lep_etcone20[goodlep2_index]/lep_pt[goodlep2_index], lep_z0[goodlep2_index], lep_trackd0pvunbiased[goodlep2_index]};
			      
			      double names_of_thirdlep_variable[]={Lepton_3.Pt()/1000., Lepton_3.Eta(), Lepton_3.E()/1000., Lepton_3.Phi(), lep_charge[goodlep3_index], (double)lep_type[goodlep3_index], lep_ptcone30[goodlep3_index]/lep_pt[goodlep3_index], lep_etcone20[goodlep3_index]/lep_pt[goodlep3_index], lep_z0[goodlep3_index], lep_trackd0pvunbiased[goodlep3_index]};
			      
			      
			      TString histonames_of_global_variable[]={"hist_mLL","hist_etmiss","hist_vxp_z","hist_pvxp_n","hist_mt"};
			      
			      TString histonames_of_lep_variable[]={"hist_threeleptpt", "hist_threelepteta", "hist_threeleptE", "hist_threeleptphi", "hist_threeleptch", "hist_threeleptID", "hist_threelept_ptc", "hist_threeleptetc", "hist_threelepz0", "hist_threelepd0"};
			      
			      
			      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
			      int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
			      int length_secondlep = sizeof(names_of_secondlep_variable)/sizeof(names_of_secondlep_variable[0]);
			      int length_thirdlep = sizeof(names_of_thirdlep_variable)/sizeof(names_of_thirdlep_variable[0]);
			      
			      
			      for (int i=0; i<length_global; i++)
				{
				  FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
				}
			      
			      for (int i=0; i<length_leadlep; i++)
				{
				  FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_lep_variable[i]);
				  FillHistogramsLeadlept( names_of_secondlep_variable[i], weight, histonames_of_lep_variable[i]);
				  FillHistogramsLeadlept( names_of_thirdlep_variable[i], weight, histonames_of_lep_variable[i]);
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

void WZDiBosonAnalysis::SlaveTerminate()
{
}

void WZDiBosonAnalysis::Terminate()
{

  name="Output_WZDiBosonAnalysis/"+name+".root";
  const char* filename = name.c_str();

  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();

}
