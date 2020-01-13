/////////////////////////////////////////////////////////////
//// ZZDiBosonAnalysis code
//// Author: ATLAS Collaboration (2019)
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

  nEvents=0;

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
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, PRL 116 (2016) 101801        //
      // **********************************************************************************************//
      
      //Scale factors
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP;

      //MC weight
      Float_t m_mcWeight = mcWeight;

      // read input option
      TString option = GetOption();
      if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs

      //Total weight
      Float_t weight = scaleFactor*m_mcWeight;

      // Make difference between data and MC
      if(option.Contains("data")) {  weight = 1.; }

      // inmediate cut on the number of leptons
      if(lep_n>=4)
      {

      //Preselection cut for electron/muon trigger
      if(trigE || trigM)
	{
	  
	  // Preselection of good leptons
	  int goodlep_index[4];
	  int goodlep_n = 0;
	  int lep_index =0;
	  
	  for(unsigned int i=0; i<lep_n; i++)
	    {

              TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);

	      // Lepton is Tight
	      if( lep_isTightID->at(i) )
		{
		  // Lepton is isolated and with at least 20 GeV
		  if( lep_pt->at(i) >20000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15 ) )
		    {
		      if ( lep_type->at(i)==11 && TMath::Abs(lep_eta->at(i)) < 2.47) {
                        if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 5 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
			goodlep_n = goodlep_n + 1;
			goodlep_index[lep_index] = i;
			lep_index++;
                        }
		      }
		      // muon selection
		      if ( lep_type->at(i) ==13 && TMath::Abs(lep_eta->at(i)) < 2.5 ) {
                        if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 3 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
			goodlep_n = goodlep_n + 1;
			goodlep_index[lep_index] = i;
			lep_index++;
  		        }
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
	      
	      // calculations are done step-by-step

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
		 
		      sum_ZZ_fin =  delta_Z1 + delta_Z2 ;
		      InvMassZ1_min = InvMassZ1;
		      InvMassZ2_min = InvMassZ2;
		    } // eemumu over
		 
                  // at least one lepton with pT > 25 GeV 
		  if( lep_pt->at(goodlep1_index)/1000. > 25 || lep_pt->at(goodlep2_index)/1000. > 25 || lep_pt->at(goodlep3_index)/1000. > 25 || lep_pt->at(goodlep4_index)/1000. > 25 )
		  {

		  // final selection, each lepton pair must have an invariant mass in the range 66–116 GeV, sum of differences < 50 GeV
		  if ( (sum_types == 44 || sum_types == 52 || sum_types == 48) && sum_ZZ_fin < 50 )
		    {
		     		      
		      TLorentzVector FourLepSystem = TLorentzVector();
		      FourLepSystem = Lepton_1 + Lepton_2 + Lepton_3 + Lepton_4;
		      float FourLepSystem_pt = FourLepSystem.Pt()/1000.;
		      float FourLepSystem_y = FourLepSystem.Rapidity();
		      float FourLepSystem_m = FourLepSystem.M()/1000.;
		      
		       //Start to fill histograms : definitions of x-axis variables
                      double names_of_global_variable[]={InvMassZ1_min, InvMassZ2_min, FourLepSystem_pt, FourLepSystem_y, FourLepSystem_m};

                      double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep1_index), (double)lep_type->at(goodlep1_index)};

                      double names_of_secondlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), (double)lep_charge->at(goodlep2_index), (double)lep_type->at(goodlep2_index)};

                      double names_of_thirdlep_variable[]={Lepton_3.Pt()/1000., Lepton_3.Eta(), Lepton_3.E()/1000., Lepton_3.Phi(), (double)lep_charge->at(goodlep3_index), (double)lep_type->at(goodlep3_index)};

                      double names_of_fourlep_variable[]={Lepton_4.Pt()/1000., Lepton_4.Eta(), Lepton_4.E()/1000., Lepton_4.Phi(), (double)lep_charge->at(goodlep4_index), (double)lep_type->at(goodlep4_index)};

                      //Start to fill histograms : definitions of histogram names
                      TString histonames_of_global_variable[]={"hist_mLL1","hist_mLL2","hist_fourlepsys_pt","hist_fourlepsys_y","hist_fourlepsys_m"};

                      TString histonames_of_lep_variable[]={"hist_fourleptpt", "hist_fourlepteta", "hist_fourleptE", "hist_fourleptphi", "hist_fourleptch", "hist_fourleptID"};

                      //Start to fill histograms : find the histogram array length
                      int length_global    = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
                      int length_leadlep   = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);

                      //Fill histograms
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
  
  
  return kTRUE;
}

void ZZDiBosonAnalysis::SlaveTerminate()
{
}

void ZZDiBosonAnalysis::Terminate()
{

  // creating the output file
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_ZZDiBosonAnalysis/"+filename_option+".root";
  const char* filename = output_name;


  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();

}
