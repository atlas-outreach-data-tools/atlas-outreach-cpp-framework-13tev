/////////////////////////////////////////////////////////////
//// HZZAnalysis code
//// Author: ATLAS Collaboration (2018)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define HZZAnalysis_cxx

#include "HZZAnalysis.h"
#include "HZZAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void HZZAnalysis::Begin(TTree * )
{
  
  nEvents=0;

}

void HZZAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t HZZAnalysis::Process(Long64_t entry)
{
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, JHEP 10 (2017) 132           //
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
	  int goodlep_index[4];
	  int goodlep_n = 0;
	  int lep_index =0;
	  
	  for(unsigned int i=0; i<lep_n; i++)
	    {
	      
              // isolated and very loose pT
	      if( lep_pt->at(i) >5000. && TMath::Abs(lep_eta->at(i)<2.7) && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15 ) )
		{
		  // electron
		  if ( lep_type->at(i)==11 && lep_pt->at(i) >7000. && TMath::Abs(lep_eta->at(i)<2.47) ) {
		    goodlep_n = goodlep_n + 1;
		    goodlep_index[lep_index] = i;
		    lep_index++;
		  }
		  //muon
		  if ( lep_type->at(i)==13) {
		    goodlep_n = goodlep_n + 1;
		    goodlep_index[lep_index] = i;
		    lep_index++;
		  }
		}
	    }
	  
	  
	  //Exactly four good leptons
	  if(goodlep_n>=4 )
	    {
	      
	      int goodlep1_index = goodlep_index[0];
	      int goodlep2_index = goodlep_index[1];
	      int goodlep3_index = goodlep_index[2];
	      int goodlep4_index = goodlep_index[3];
	      
	      //first lepton pT > 20 GeV and second 15 GeV and third 10 GeV		      
	      if (lep_pt->at(goodlep1_index) > 20000. && lep_pt->at(goodlep2_index) > 15000. && lep_pt->at(goodlep3_index) > 10000. ) 
		{ 		     
		  
		  
		  // TLorentzVector definitions
		  TLorentzVector Lepton_1  = TLorentzVector();
		  TLorentzVector Lepton_2  = TLorentzVector();
		  TLorentzVector Lepton_3  = TLorentzVector();
		  TLorentzVector Lepton_4  = TLorentzVector();
		  
		  Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep1_index), lep_eta->at(goodlep1_index), lep_phi->at(goodlep1_index),lep_E->at(goodlep1_index));
		  Lepton_2.SetPtEtaPhiE(lep_pt->at(goodlep2_index), lep_eta->at(goodlep2_index), lep_phi->at(goodlep2_index),lep_E->at(goodlep2_index));
		  Lepton_3.SetPtEtaPhiE(lep_pt->at(goodlep3_index), lep_eta->at(goodlep3_index), lep_phi->at(goodlep3_index),lep_E->at(goodlep3_index));
		  Lepton_4.SetPtEtaPhiE(lep_pt->at(goodlep4_index), lep_eta->at(goodlep4_index), lep_phi->at(goodlep4_index),lep_E->at(goodlep4_index));
		  
		  
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
		  
		  
		  float sum_charges = lep_charge->at(goodlep1_index) + lep_charge->at(goodlep2_index) + lep_charge->at(goodlep3_index) + lep_charge->at(goodlep4_index);			 
		  
		  // step-by-step
		  // opposite charge leptons
		  if ( sum_charges == 0  ) 
		    {
		      
		      
		      int sum_types  = lep_type->at(goodlep1_index) + lep_type->at(goodlep2_index) + lep_type->at(goodlep3_index) + lep_type->at(goodlep4_index) ;
		      
		      // type e=11, mu=13
		      // begin case e+e-e+e- or mu+mu-mu+mu-
		      if ( sum_types == 44 || sum_types == 52  )
			{
			  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep2_index) && ( (lep_charge->at(goodlep1_index) * lep_charge->at(goodlep2_index)) < 0 )  )
			    {
		              InvMassZ1_1=(Lepton_1+Lepton_2).Mag()/1000.;
			      InvMassZ2_1=(Lepton_3+Lepton_4).Mag()/1000.;
			      delta_Z1_1 =  TMath::Abs(InvMassZ1_1 - 91.18); 
			      delta_Z2_1 =  TMath::Abs(InvMassZ2_1 - 91.18);
			    }
			  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep3_index)  && ( (lep_charge->at(goodlep1_index) * lep_charge->at(goodlep3_index)) < 0 ) )
			    {
			      InvMassZ1_2=(Lepton_1+Lepton_3).Mag()/1000.;
			      InvMassZ2_2=(Lepton_2+Lepton_4).Mag()/1000.;
			      delta_Z1_2 =  TMath::Abs(InvMassZ1_2 - 91.18); 
			      delta_Z2_2 =  TMath::Abs(InvMassZ2_2 - 91.18);
			    }
			  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep4_index)  && ( (lep_charge->at(goodlep1_index) * lep_charge->at(goodlep4_index)) < 0 ) )
			    {
			      InvMassZ1_3=(Lepton_1+Lepton_4).Mag()/1000.;
			      InvMassZ2_3=(Lepton_2+Lepton_3).Mag()/1000.;
			      delta_Z1_3 =  TMath::Abs(InvMassZ1_3 - 91.18); 
			      delta_Z2_3 =  TMath::Abs(InvMassZ2_3 - 91.18);
			    }

			  if(delta_Z1_1 < delta_Z2_1) { InvMassZ1_min = InvMassZ1_1; InvMassZ2_min = InvMassZ2_1;}
                          if(delta_Z2_1 < delta_Z1_1) { InvMassZ1_min = InvMassZ2_1; InvMassZ2_min = InvMassZ1_1;}

			  if(delta_Z1_2 < delta_Z2_2) { InvMassZ1_min = InvMassZ1_2; InvMassZ2_min = InvMassZ2_2;}
                          if(delta_Z2_2 < delta_Z1_2) { InvMassZ1_min = InvMassZ2_2; InvMassZ2_min = InvMassZ1_2;}

			  if(delta_Z1_3 < delta_Z2_3) { InvMassZ1_min = InvMassZ1_3; InvMassZ2_min = InvMassZ2_3;}
                          if(delta_Z2_3 < delta_Z1_3) { InvMassZ1_min = InvMassZ2_3; InvMassZ2_min = InvMassZ1_3;}

			} // cases of eeee or mumumumu
		      
		      ////////////////////////////////////
		      // case eemumu 
		      if ( sum_types == 48 )
			{
			  
			  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep2_index)  && ( (lep_charge->at(goodlep1_index) * lep_charge->at(goodlep2_index)) < 0 ) )
			    {
			      InvMassZ1=(Lepton_1+Lepton_2).Mag()/1000.;
			      InvMassZ2=(Lepton_3+Lepton_4).Mag()/1000.;
			      delta_Z1 =  TMath::Abs(InvMassZ1 - 91.18); 
			      delta_Z2 =  TMath::Abs(InvMassZ2 - 91.18);
			    }
			  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep3_index)  && ( (lep_charge->at(goodlep1_index) * lep_charge->at(goodlep3_index)) < 0 ) )
			    {
			      InvMassZ1=(Lepton_1+Lepton_3).Mag()/1000.;
			      InvMassZ2=(Lepton_2+Lepton_4).Mag()/1000.;
			      delta_Z1 =  TMath::Abs(InvMassZ1 - 91.18); 
			      delta_Z2 =  TMath::Abs(InvMassZ2 - 91.18);
			    }
			  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep4_index)  && ( (lep_charge->at(goodlep1_index) * lep_charge->at(goodlep4_index)) < 0 ) )
			    {
			      InvMassZ1=(Lepton_1+Lepton_4).Mag()/1000.;
			      InvMassZ2=(Lepton_2+Lepton_3).Mag()/1000.;
			      delta_Z1 =  TMath::Abs(InvMassZ1 - 91.18); 
			      delta_Z2 =  TMath::Abs(InvMassZ2 - 91.18);
			    }
			  
			  if(delta_Z1 < delta_Z2) { InvMassZ1_min = InvMassZ1; InvMassZ2_min = InvMassZ2;}
			  if(delta_Z2 < delta_Z1) { InvMassZ1_min = InvMassZ2; InvMassZ2_min = InvMassZ1;}
			} // eemumu overe
		      
		      if ( (sum_types == 44 || sum_types == 52 || sum_types == 48) )
			{
			  
				  
				  TLorentzVector FourLepSystem = TLorentzVector();
				  FourLepSystem = Lepton_1 + Lepton_2 + Lepton_3 + Lepton_4;
				  float FourLepSystem_M = FourLepSystem.Mag()/1000.;
				  float FourLepSystem_pt = FourLepSystem.Pt()/1000.;
				  float FourLepSystem_y = FourLepSystem.Rapidity();
				  
				  
				  //Preselection of good jets
				  int goodjet_n = 0;
				  int goodjet_index = 0;
				  
				  if (jet_n > 0)
				    {
				      for(unsigned int i=0; i<jet_n; i++)
					{
					  if(jet_pt->at(i)>30000. && TMath::Abs(jet_eta->at(i)) < 4.4)
					    {
					      goodjet_n++;
					      goodjet_index = i;
					    }
					}
				    }
				  
				  
				  //Start to fill histograms : definitions of x-axis variables
				  
				  double names_of_global_variable[]={InvMassZ1_min, InvMassZ2_min, FourLepSystem_pt, FourLepSystem_y, FourLepSystem_M, (double)goodjet_n};
				  
				  double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep1_index), (double)lep_type->at(goodlep1_index), lep_ptcone30->at(goodlep1_index)/lep_pt->at(goodlep1_index), lep_etcone20->at(goodlep1_index)/lep_pt->at(goodlep1_index), lep_z0->at(goodlep1_index), lep_trackd0pvunbiased->at(goodlep1_index)};
				  
				  double names_of_secondlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), (double)lep_charge->at(goodlep2_index), (double)lep_type->at(goodlep2_index), lep_ptcone30->at(goodlep2_index)/lep_pt->at(goodlep2_index), lep_etcone20->at(goodlep2_index)/lep_pt->at(goodlep2_index), lep_z0->at(goodlep2_index), lep_trackd0pvunbiased->at(goodlep2_index)};
				  
				  double names_of_thirdlep_variable[]={Lepton_3.Pt()/1000., Lepton_3.Eta(), Lepton_3.E()/1000., Lepton_3.Phi(), (double)lep_charge->at(goodlep3_index), (double)lep_type->at(goodlep3_index), lep_ptcone30->at(goodlep3_index)/lep_pt->at(goodlep3_index), lep_etcone20->at(goodlep3_index)/lep_pt->at(goodlep3_index), lep_z0->at(goodlep3_index), lep_trackd0pvunbiased->at(goodlep3_index)};
				  
				  double names_of_fourlep_variable[]={Lepton_4.Pt()/1000., Lepton_4.Eta(), Lepton_4.E()/1000., Lepton_4.Phi(), (double)lep_charge->at(goodlep4_index), (double)lep_type->at(goodlep4_index), lep_ptcone30->at(goodlep4_index)/lep_pt->at(goodlep4_index), lep_etcone20->at(goodlep4_index)/lep_pt->at(goodlep4_index), lep_z0->at(goodlep4_index), lep_trackd0pvunbiased->at(goodlep4_index)};
				  
				  
				  //Start to fill histograms : definitions of histogram names
				  TString histonames_of_global_variable[]={"hist_mLL1","hist_mLL2","hist_fourlepsys_pt","hist_fourlepsys_y","mass_four_lep_ext","hist_n_jets"};
				  
				  TString histonames_of_lep_variable[]={"hist_fourleptpt", "hist_fourlepteta", "hist_fourleptE", "hist_fourleptphi", "hist_fourleptch", "hist_fourleptID", "hist_fourlept_ptc", "hist_fourleptetc", "hist_fourlepz0", "hist_fourlepd0"};
				  
				  //Start to fill histograms : find the histogram array length
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
				  
				  // mass window
				  if (FourLepSystem_M > 115 && FourLepSystem_M < 130)
				    {
				      
				      double names_of_winglobal_variable[]={FourLepSystem_pt,  FourLepSystem_y, FourLepSystem_M};
				      int length_winglobal    = sizeof(names_of_winglobal_variable)/sizeof(names_of_winglobal_variable[0]);
                                      TString histonames_of_winglobal_variable[]={"hist_fourlepsys_pt_win","hist_fourlepsys_y_win","mass_four_lep"};

				      for (int i=0; i<length_winglobal; i++)
					{
					  FillHistogramsGlobal( names_of_winglobal_variable[i], weight, histonames_of_winglobal_variable[i]);
					}
				      
				      // types
				      if ( sum_types == 52  ) FillHistogramsGlobal ( FourLepSystem_M, weight, "mass_four_mu_win");
				      if ( sum_types == 44  ) FillHistogramsGlobal ( FourLepSystem_M, weight, "mass_four_e_win");
				      if ( sum_types == 48  ) FillHistogramsGlobal ( FourLepSystem_M, weight, "mass_twomu_twoe_win");
				      
				    }
				  
				}
			    }
			}
		    }
		}
	    }
  
  return kTRUE;
}

void HZZAnalysis::SlaveTerminate()
{
}

void HZZAnalysis::Terminate()
{
  
  name="Output_HZZAnalysis/"+name+".root";
  const char* filename = name.c_str();
  
  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();
  
}
