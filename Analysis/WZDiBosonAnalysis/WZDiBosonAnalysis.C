/////////////////////////////////////////////////////////////
//// WZDiBosonAnalysis code
//// Author: ATLAS Collaboration (2019)
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

  nEvents=0;

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
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;

  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, Phys. Lett. B 762 (2016) 1   //
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

      
      //Preselection cut for electron/muon trigger 
      if(trigE || trigM)
	{
	  
	  // Preselection of good leptons
	  int goodlep_index[3];
	  int goodlep_n = 0;
	  int lep_index =0;
	  
	  for(unsigned int i=0; i<lep_n; i++)
	    {
              TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);

	      // Lepton is Tight
	      if( lep_isTightID->at(i) )
		{
		  //  Lepton is isolated and with at least 20 GeV
		  if( lep_pt->at(i) > 20000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15) )
		    {
		      if ( lep_type->at(i)==11 && TMath::Abs(lep_eta->at(i)) < 2.47 && ( TMath::Abs(lep_eta->at(i)) < 1.37 || TMath::Abs(lep_eta->at(i)) > 1.52 ) ) {
                      if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 5 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
                        goodlep_n = goodlep_n + 1;
                        goodlep_index[lep_index] = i;
                        lep_index++;
                      }
                 }
                      // muon selection
                      if ( lep_type->at(i) == 13 && TMath::Abs(lep_eta->at(i)) < 2.5 ) {
                        if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 3 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
                          goodlep_n = goodlep_n + 1;
                          goodlep_index[lep_index] = i;
                          lep_index++;
                        }
                      }
                    }
                }
            }
	  
	  
	  
	  //Exactly three good leptons
	  if(goodlep_n==3 )
	    {
	      
	      int goodlep1_index = goodlep_index[0];
	      int goodlep2_index = goodlep_index[1];
	      int goodlep3_index = goodlep_index[2];
	      
	      
	      // TLorentzVector definitions
	      TLorentzVector Lepton_1  = TLorentzVector();
	      TLorentzVector Lepton_2  = TLorentzVector();
	      TLorentzVector Lepton_3  = TLorentzVector();
	      TLorentzVector      MeT  = TLorentzVector();
	      
	      Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep1_index), lep_eta->at(goodlep1_index), lep_phi->at(goodlep1_index),lep_E->at(goodlep1_index));
	      Lepton_2.SetPtEtaPhiE(lep_pt->at(goodlep2_index), lep_eta->at(goodlep2_index), lep_phi->at(goodlep2_index),lep_E->at(goodlep2_index));
	      Lepton_3.SetPtEtaPhiE(lep_pt->at(goodlep3_index), lep_eta->at(goodlep3_index), lep_phi->at(goodlep3_index),lep_E->at(goodlep3_index));
	      MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
	      
	      float InvMass12       = (Lepton_1+Lepton_2).Mag()/1000.;
	      float InvMass13       = (Lepton_1+Lepton_3).Mag()/1000.;
	      float InvMass23       = (Lepton_2+Lepton_3).Mag()/1000.;
	      
	      float delta_lep12_Z =  -1;
	      float delta_lep13_Z =  -1;
	      float delta_lep23_Z =  -1;
	      
	      // calculations are done step-by-step
	      
	      // charge of leptons coming from Z is different
	      if ( lep_charge->at(goodlep1_index) * lep_charge->at(goodlep2_index)  < 0 ) 
		{
		  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep2_index) )
		    {
		      delta_lep12_Z =  TMath::Abs(InvMass12 - 91.18);
		    }
		}
	      
	      if ( lep_charge->at(goodlep1_index) * lep_charge->at(goodlep3_index)  < 0 ) 
		{
		  if ( lep_type->at(goodlep1_index) == lep_type->at(goodlep3_index) )
		    {
		      delta_lep13_Z =  TMath::Abs(InvMass13 - 91.18);
		    }
		}
	      
	      if ( lep_charge->at(goodlep2_index) * lep_charge->at(goodlep3_index)  < 0 ) 
		{
		  if ( lep_type->at(goodlep2_index) == lep_type->at(goodlep3_index) )
		    {
		      delta_lep23_Z =  TMath::Abs(InvMass23 - 91.18);
		    }
		}
	      
	      // define candidates 
	      int wcand = 0;
	      float tmp = 0;
	      
	      
	      // begin all permutations 
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
	      
	      
	      
	      // in the case we have eemu or mumue
	      	      
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
	      
	      
	      // depending on which is the W candidate, build mtw
	      float mtw=0;
	      if(wcand==1) mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
	      if(wcand==2) mtw = sqrt(2*Lepton_2.Pt()*MeT.Et()*(1-cos(Lepton_2.DeltaPhi(MeT))));
	      if(wcand==3) mtw = sqrt(2*Lepton_3.Pt()*MeT.Et()*(1-cos(Lepton_3.DeltaPhi(MeT))));
	      
	      
	      // depending on which is the W candidate, build mll and ptll, pT of lepton from W > 20 GeV     
	      float mll=0; float ptll=0; float lepW=0;
	      if(wcand==1) {mll = InvMass23; ptll = (Lepton_2+Lepton_3).Pt()/1000.; lepW = Lepton_1.Pt()/1000.;}
	      if(wcand==2) {mll = InvMass13; ptll = (Lepton_1+Lepton_3).Pt()/1000.; lepW = Lepton_2.Pt()/1000.;}
	      if(wcand==3) {mll = InvMass12; ptll = (Lepton_1+Lepton_2).Pt()/1000.; lepW = Lepton_3.Pt()/1000.;}
	      
	      
	      // cut: m_ll - m(Z) < 10
	      if(tmp < 10.)
		{
		  // mtw > 30 GeV, at least one lepton with pT > 25 GeV 
		  if( mtw > 30000. && met_et > 30000. && (lep_pt->at(goodlep1_index)/1000. > 25 || lep_pt->at(goodlep2_index)/1000. > 25 || lep_pt->at(goodlep3_index)/1000. > 25) )
		  {
		      
		      //Start to fill histograms : definitions of x-axis variables
		      
		      double names_of_global_variable[]={mll, ptll, met_et/1000., mtw/1000.};
		      
		      double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep1_index), (double)lep_type->at(goodlep1_index)};
		      
		      double names_of_secondlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), (double)lep_charge->at(goodlep2_index), (double)lep_type->at(goodlep2_index)};
		      
		      double names_of_thirdlep_variable[]={Lepton_3.Pt()/1000., Lepton_3.Eta(), Lepton_3.E()/1000., Lepton_3.Phi(), (double)lep_charge->at(goodlep3_index), (double)lep_type->at(goodlep3_index)}; 
		      
		      
		      //Start to fill histograms : definitions of histogram names
		      TString histonames_of_global_variable[]={"hist_mLL","hist_ptLL","hist_etmiss","hist_mtw"};
		      
		      TString histonames_of_lep_variable[]={"hist_threeleptpt", "hist_threelepteta", "hist_threeleptE", "hist_threeleptphi", "hist_threeleptch", "hist_threeleptID"};
		      
		      //Start to fill histograms : find the histogram array length
		      
		      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
		      int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
		      int length_secondlep = sizeof(names_of_secondlep_variable)/sizeof(names_of_secondlep_variable[0]);
		      int length_thirdlep = sizeof(names_of_thirdlep_variable)/sizeof(names_of_thirdlep_variable[0]);
		      
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

  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_WZDiBosonAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();

}
