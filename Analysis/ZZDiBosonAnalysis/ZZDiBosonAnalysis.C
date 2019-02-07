/////////////////////////////////////////////////////////////
//// ZZDiBosonAnalysis code
//// Author: ATLAS Collaboration (2018)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define ZZDiBosonAnalysis_cxx

#include "ZZDiBosonAnalysis.h"
#include "ZZDiBosonAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void ZZDiBosonAnalysis::Begin(TTree * )
{
}

void ZZDiBosonAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t ZZDiBosonAnalysis::Process(Long64_t entry)
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
      
      //Preselection cut for electron/muon trigger, Good Run List, and good vertex
      if(trigE || trigM)
	{
	  if(passGRL)
	    {
	      if(hasGoodVertex)
		{
		  // Preselection of good leptons
		  int goodlep_index[4];
		  int goodlep_n = 0;
		  int lep_index =0;
		  
		  for(unsigned int i=0; i<lep_n; i++)
		    {
		      // is Tight
		      if( bool(lep_flag[i] & 512)) 
			{
			  // isolated
			  if( lep_pt[i]>10000. && (lep_ptcone30[i]/lep_pt[i]) < 0.15 && (lep_etcone20[i]/lep_pt[i]) < 0.15)
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
		  
		  
		  //Exactly four good leptons
		  if(goodlep_n==4 )
		    {
		      
		      int goodlep1_index = goodlep_index[0];
		      int goodlep2_index = goodlep_index[1];
		      int goodlep3_index = goodlep_index[2];
		      int goodlep4_index = goodlep_index[3];
		      
		      //first lepton pT > 25 GeV to ensure high trigger efficiency		      
                      if (lep_pt[goodlep1_index] > 25000. ) 
			{ 		     
			  
			  
			  // TLorentzVector definitions
			  TLorentzVector Lepton_1  = TLorentzVector();
			  TLorentzVector Lepton_2  = TLorentzVector();
			  TLorentzVector Lepton_3  = TLorentzVector();
			  TLorentzVector Lepton_4  = TLorentzVector();
			  
			  Lepton_1.SetPtEtaPhiE(lep_pt[goodlep1_index], lep_eta[goodlep1_index], lep_phi[goodlep1_index],lep_E[goodlep1_index]);
			  Lepton_2.SetPtEtaPhiE(lep_pt[goodlep2_index], lep_eta[goodlep2_index], lep_phi[goodlep2_index],lep_E[goodlep2_index]);
			  Lepton_3.SetPtEtaPhiE(lep_pt[goodlep3_index], lep_eta[goodlep3_index], lep_phi[goodlep3_index],lep_E[goodlep3_index]);
			  Lepton_4.SetPtEtaPhiE(lep_pt[goodlep4_index], lep_eta[goodlep4_index], lep_phi[goodlep4_index],lep_E[goodlep4_index]);
			  
			  // minimisation of difference from the Z mass
			  float delta_Z1=0; 
                          float delta_Z2=0; 
			  float InvMassZ1=0; 
			  float InvMassZ2=0;
			  float delta_Z1_1=0; float delta_Z1_2=0; float delta_Z1_3=0;
			  float delta_Z2_1=0; float delta_Z2_2=0; float delta_Z2_3=0;
			  float InvMassZ1_1=0; float InvMassZ1_2=0; float InvMassZ1_3=0;
			  float InvMassZ2_1=0; float InvMassZ2_2=0; float InvMassZ2_3=0;
			  float sum_ZZ1=0; float sum_ZZ2=0; float sum_ZZ3=0;

			  // final values
                          float InvMassZ1_min=0; float InvMassZ2_min=0; float sum_ZZ_fin=0;
			  
			  
                          float sum_charges = lep_charge[goodlep1_index] + lep_charge[goodlep2_index] + lep_charge[goodlep3_index] + lep_charge[goodlep4_index];			 
 
			  // step-by-step
			  // opposite charge leptons
			  if ( sum_charges == 0  ) 
			    {
			      
			      
			      int sum_types  = abs (lep_type[goodlep1_index]) + abs (lep_type[goodlep2_index]) + abs (lep_type[goodlep3_index]) + abs (lep_type[goodlep4_index]) ;
			      
			      // type e=11, mu=13
			      // begin case e+e-e+e- or mu+mu-mu+mu-
			      if ( sum_types == 44 || sum_types == 52  )
				{
				  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep2_index]))
				    {
				      InvMassZ1_1=(Lepton_1+Lepton_2).Mag()/1000.;
				      InvMassZ2_1=(Lepton_3+Lepton_4).Mag()/1000.;
				      delta_Z1_1 =  TMath::Abs(InvMassZ1_1 - 91.18); 
				      delta_Z2_1 =  TMath::Abs(InvMassZ2_1 - 91.18);
				    }
				  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep3_index]))
				    {
				      InvMassZ1_2=(Lepton_1+Lepton_3).Mag()/1000.;
				      InvMassZ2_2=(Lepton_2+Lepton_4).Mag()/1000.;
				      delta_Z1_2 =  TMath::Abs(InvMassZ1_2 - 91.18); 
				      delta_Z2_2 =  TMath::Abs(InvMassZ2_2 - 91.18);
				    }
				  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep4_index]))
				    {
				      InvMassZ1_3=(Lepton_1+Lepton_4).Mag()/1000.;
				      InvMassZ2_3=(Lepton_2+Lepton_3).Mag()/1000.;
				      delta_Z1_3 =  TMath::Abs(InvMassZ1_3 - 91.18); 
				      delta_Z2_3 =  TMath::Abs(InvMassZ2_3 - 91.18);
				    }
				  
				  // sum of the two differences
				  sum_ZZ1 =  delta_Z1_1 + delta_Z2_1 ;
				  sum_ZZ2 =  delta_Z1_2 + delta_Z2_2 ;
				  sum_ZZ3 =  delta_Z1_3 + delta_Z2_3 ;
				  
				  
				  
				  //choose the smallest difference
				  if (sum_ZZ1< sum_ZZ2 && sum_ZZ1 < sum_ZZ3)
				    {
				      InvMassZ1_min = InvMassZ1_1;
				      InvMassZ2_min = InvMassZ2_1;
				      sum_ZZ_fin=sum_ZZ1;
				    }
				  if (sum_ZZ2< sum_ZZ1 && sum_ZZ2 < sum_ZZ3)
				    {
				      InvMassZ1_min = InvMassZ1_2;
				      InvMassZ2_min = InvMassZ2_2;
				      sum_ZZ_fin=sum_ZZ2;
				    }
				  if (sum_ZZ3< sum_ZZ1 && sum_ZZ3 < sum_ZZ2)
				    {
				      InvMassZ1_min = InvMassZ1_3;
				      InvMassZ2_min = InvMassZ2_3;
				      sum_ZZ_fin=sum_ZZ3;
				    }
				} // cases of eeee or mumumumu
			      
			      ////////////////////////////////////
			      // case eemumu 
			      if ( sum_types == 48 )
				{
				  
				  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep2_index]))
				    {
				      InvMassZ1=(Lepton_1+Lepton_2).Mag()/1000.;
				      InvMassZ2=(Lepton_3+Lepton_4).Mag()/1000.;
				      delta_Z1 =  TMath::Abs(InvMassZ1 - 91.18); 
				      delta_Z2 =  TMath::Abs(InvMassZ2 - 91.18);
				    }
				  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep3_index]))
				    {
				      InvMassZ1=(Lepton_1+Lepton_3).Mag()/1000.;
				      InvMassZ2=(Lepton_2+Lepton_4).Mag()/1000.;
				      delta_Z1 =  TMath::Abs(InvMassZ1 - 91.18); 
				      delta_Z2 =  TMath::Abs(InvMassZ2 - 91.18);
				    }
				  if ( abs (lep_type[goodlep1_index]) == abs (lep_type[goodlep4_index]))
				    {
				      InvMassZ1=(Lepton_1+Lepton_4).Mag()/1000.;
				      InvMassZ2=(Lepton_2+Lepton_3).Mag()/1000.;
				      delta_Z1 =  TMath::Abs(InvMassZ1 - 91.18); 
				      delta_Z2 =  TMath::Abs(InvMassZ2 - 91.18);
				    }
				  
				  sum_ZZ_fin =  delta_Z1 + delta_Z2 ;
				  InvMassZ1_min = InvMassZ1;
				  InvMassZ2_min = InvMassZ2;
				} // eemumu overe
			      
			      if ( (sum_types == 44 || sum_types == 52 || sum_types == 48) && sum_ZZ_fin < 30 )
				{
				  
				  double names_of_global_variable[]={InvMassZ1_min, InvMassZ2_min, vxp_z, (double)pvxp_n};
				  
				  double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge[goodlep1_index], (double)lep_type[goodlep1_index], lep_ptcone30[goodlep1_index]/lep_pt[goodlep1_index], lep_etcone20[goodlep1_index]/lep_pt[goodlep1_index], lep_z0[goodlep1_index], lep_trackd0pvunbiased[goodlep1_index]};
				  
				  double names_of_secondlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), lep_charge[goodlep2_index], (double)lep_type[goodlep2_index], lep_ptcone30[goodlep2_index]/lep_pt[goodlep2_index], lep_etcone20[goodlep2_index]/lep_pt[goodlep2_index], lep_z0[goodlep2_index], lep_trackd0pvunbiased[goodlep2_index]};
				  
				  double names_of_thirdlep_variable[]={Lepton_3.Pt()/1000., Lepton_3.Eta(), Lepton_3.E()/1000., Lepton_3.Phi(), lep_charge[goodlep3_index], (double)lep_type[goodlep3_index], lep_ptcone30[goodlep3_index]/lep_pt[goodlep3_index], lep_etcone20[goodlep3_index]/lep_pt[goodlep3_index], lep_z0[goodlep3_index], lep_trackd0pvunbiased[goodlep3_index]};
				  
				  double names_of_fourlep_variable[]={Lepton_4.Pt()/1000., Lepton_4.Eta(), Lepton_4.E()/1000., Lepton_4.Phi(), lep_charge[goodlep4_index], (double)lep_type[goodlep4_index], lep_ptcone30[goodlep4_index]/lep_pt[goodlep4_index], lep_etcone20[goodlep4_index]/lep_pt[goodlep4_index], lep_z0[goodlep4_index], lep_trackd0pvunbiased[goodlep4_index]};
				  
				  TString histonames_of_global_variable[]={"hist_mLL1","hist_mLL2","hist_vxp_z","hist_pvxp_n"};
				  
				  TString histonames_of_lep_variable[]={"hist_fourleptpt", "hist_fourlepteta", "hist_fourleptE", "hist_fourleptphi", "hist_fourleptch", "hist_fourleptID", "hist_fourlept_ptc", "hist_fourleptetc", "hist_fourlepz0", "hist_fourlepd0"};
				  
				  
				  int length_global    = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
				  int length_leadlep   = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
				  
				  for (int i=0; i<length_global; i++)
				    {
				      FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
				    }
				  
				  for (int i=0; i<length_leadlep; i++)
				    {
				      FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_lep_variable[i]);
				      FillHistogramsLeadlept( names_of_secondlep_variable[i], weight, histonames_of_lep_variable[i]);
				      FillHistogramsLeadlept( names_of_thirdlep_variable[i], weight, histonames_of_lep_variable[i]);
				      FillHistogramsLeadlept( names_of_fourlep_variable[i], weight, histonames_of_lep_variable[i]);
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

void ZZDiBosonAnalysis::SlaveTerminate()
{
}

void ZZDiBosonAnalysis::Terminate()
{

  name="Output_ZZDiBosonAnalysis/"+name+".root";
  const char* filename = name.c_str();

  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();

}
