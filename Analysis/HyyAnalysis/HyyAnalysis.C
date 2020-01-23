/////////////////////////////////////////////////////////////
//// HyyAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define HyyAnalysis_cxx

#include "HyyAnalysis.h"
#include "HyyAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void HyyAnalysis::Begin(TTree * )
{
   nEvents=0;
   nEvent=0;
   nEvent2=0;
   nEvent3=0;
   nEvent4=0;
   nEvent5=0;
}

void HyyAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t HyyAnalysis::Process(Long64_t entry)
{

  fChain->GetTree()->GetEntry(entry);
  nEvent++; nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;


  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, PRD 98 (2018) 052005         //
      // **********************************************************************************************//

      //Scale factors
      Float_t scaleFactor = scaleFactor_PHOTON*scaleFactor_PhotonTRIGGER*scaleFactor_PILEUP;

      //MC weight
      Float_t m_mcWeight = mcWeight;
 
      //Total weight
      Float_t weight = scaleFactor*m_mcWeight;

      // Make difference between data and MC
      TString option = GetOption();
      if(option.Contains("data")) {  weight = 1.; }
 
      //Preselection cut for photon trigger
      if(trigP)
	{
	  nEvent2++; // counter

	  // Preselection of good photons
	  int goodphoton_index[2];
	  int goodphoton_n = 0;
	  int photon_index =0;
	  
	  for(unsigned int i=0; i<photon_n; i++)
	    {
	      // photons are tight
	      if( photon_isTightID->at(i) )
		{
         	  // photons with 25 GeV and excluding the transition region between the barrel and endcap calorimeters
		  if( photon_pt->at(i) >25000. && TMath::Abs(photon_eta->at(i))<2.37 && ( TMath::Abs(photon_eta->at(i)) < 1.37 || TMath::Abs(photon_eta->at(i)) > 1.52 ) )
		    {
		      goodphoton_n = goodphoton_n + 1;
		      goodphoton_index[photon_index] = i;
		      photon_index++;
		    }
		}
	    }
	  
	  //Exactly two photons
	  if(goodphoton_n==2 )
	    {
              nEvent3++; // counter
	      
	      int goodphoton1_index = goodphoton_index[0];
	      int goodphoton2_index = goodphoton_index[1];
	      
              // isolated photons
              if( ( (photon_ptcone30->at(goodphoton1_index)/photon_pt->at(goodphoton1_index)) < 0.065) && ( (photon_etcone20->at(goodphoton1_index) / photon_pt->at(goodphoton1_index)) < 0.065 ) )
		{
		  if( ( (photon_ptcone30->at(goodphoton2_index)/photon_pt->at(goodphoton2_index)) < 0.065) && ( (photon_etcone20->at(goodphoton2_index) / photon_pt->at(goodphoton2_index)) < 0.065 ) )
		    {
		      
		      nEvent4++; // counter 

                      // create 2 vectors		      
		      TLorentzVector Photon_1  = TLorentzVector();
		      TLorentzVector Photon_2  = TLorentzVector();
		      
		      Photon_1.SetPtEtaPhiE(photon_pt->at(goodphoton1_index), photon_eta->at(goodphoton1_index), photon_phi->at(goodphoton1_index),photon_E->at(goodphoton1_index));
		      Photon_2.SetPtEtaPhiE(photon_pt->at(goodphoton2_index), photon_eta->at(goodphoton2_index), photon_phi->at(goodphoton2_index),photon_E->at(goodphoton2_index));
		      
		      // calculate dPhi(photon-photon)
		      float dPhi_yy = TMath::Abs(photon_phi->at(goodphoton1_index) - photon_phi->at(goodphoton2_index) );
		      dPhi_yy       = dPhi_yy < TMath::Pi() ? dPhi_yy : 2*TMath::Pi() - dPhi_yy;
		      
		      // diphoton mass
		      float m_yy  = sqrt( 2 * Photon_1.Pt()/1000. * Photon_2.Pt()/1000. * (cosh( Photon_1.Eta() - Photon_2.Eta()) - cos(dPhi_yy)));
		      // kinematics
		      float Photon_1_kin = Photon_1.Pt()/1000. / m_yy;
		      float Photon_2_kin = Photon_2.Pt()/1000. / m_yy;
		      
		      // kinematical selection		      
		      if ( Photon_1_kin > 0.35 && Photon_2_kin > 0.25 ) 
			{ 		     
	
	                  nEvent5++; // counter

                          // mass-window cut			  
			  if(m_yy > 105 && m_yy < 160 ) 
			    {

                              FillHistogramsGlobal( m_yy, weight, "hist_mYY_bin1"); // 30 bins

			      nEvent6++; // counter 

			      // unconverted central category 
			      if ( TMath::Abs(photon_eta->at(goodphoton1_index)) < 0.75 && TMath::Abs(photon_eta->at(goodphoton2_index)) < 0.75 && photon_convType->at(goodphoton1_index)==0 && photon_convType->at(goodphoton2_index)==0 )
			      {
                                FillHistogramsGlobal( m_yy, weight, "hist_mYY_cat_bin1"); // 30 bins
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

void HyyAnalysis::SlaveTerminate()
{
}

void HyyAnalysis::Terminate()
{
  
  // Print counters (in case of local, not PROOF)
  /* 
  cout << "Analyzed a total of               : " << nEvent << " events" << endl;
  cout << "Counter after trigger selection   : " << nEvent2/nEvent  << " (fraction from previous) or " << nEvent2 << " events" << endl;
  cout << "Counter after 2 good tight photons: " << nEvent3/nEvent2 << " (fraction from previous) or " << nEvent3 << " events" << endl;
  cout << "Counter after 2 isolated photons  : " << nEvent4/nEvent3 << " (fraction from previous) or " << nEvent4 << " events" << endl;
  cout << "Counter after pT cuts on photons  : " << nEvent5/nEvent4 << " (fraction from previous) or " << nEvent5 << " events" << endl;
  cout << "Counter after mass-window cut     : " << nEvent6/nEvent5 << " (fraction from previous) or " << nEvent6 << " events" << endl;
  */

  // Save output
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_HyyAnalysis/"+filename_option+".root";
  const char* filename = output_name;
  
  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();
 
}
