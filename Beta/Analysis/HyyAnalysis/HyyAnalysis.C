/////////////////////////////////////////////////////////////
//// HyyAnalysis code
//// Author: ATLAS Collaboration (2018)
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
  nEvent++;
//  if (nEvent % 50000 == 0) std::cout << "Analysed a total of: " << nEvent << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, PRD 98 (2018) 052005         //
      // **********************************************************************************************//

      //Scale factors
      Float_t scaleFactor = scaleFactor_PHOTON*scaleFactor_PhotonTRIGGER;
      //Event weight
      Float_t eventWeight = mcWeight*scaleFactor_PILEUP;
      //Total weight
      Float_t weight = scaleFactor*eventWeight;
      
      // Make difference between data and MC
      if (weight == 0.) weight = 1.;
      
      //Preselection cut for photon trigger
      if(trigP)
	{
	  nEvent2++; 

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
		  if( photon_pt->at(i) >25000. && abs(photon_eta->at(i)<2.37) && ( abs(photon_eta->at(i) < 1.37) || abs(photon_eta->at(i) > 1.52) ) )
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
              nEvent3++; // counter after good eta and pT
	      
	      int goodphoton1_index = goodphoton_index[0];
	      int goodphoton2_index = goodphoton_index[1];
	      
              // isolated photons
              if( ( (photon_ptcone30->at(goodphoton1_index)/photon_pt->at(goodphoton1_index)) < 0.065) && ( (photon_etcone20->at(goodphoton1_index) / photon_pt->at(goodphoton1_index)) < 0.065 ) )
		{
		  if( ( (photon_ptcone30->at(goodphoton2_index)/photon_pt->at(goodphoton2_index)) < 0.065) && ( (photon_etcone20->at(goodphoton2_index) / photon_pt->at(goodphoton2_index)) < 0.065 ) )
		    {
		      
		      nEvent4++; // counter after isolation
		      
		      
		      TLorentzVector Photon_1  = TLorentzVector();
		      TLorentzVector Photon_2  = TLorentzVector();
		      
		      Photon_1.SetPtEtaPhiE(photon_pt->at(goodphoton1_index), photon_eta->at(goodphoton1_index), photon_phi->at(goodphoton1_index),photon_E->at(goodphoton1_index));
		      Photon_2.SetPtEtaPhiE(photon_pt->at(goodphoton2_index), photon_eta->at(goodphoton2_index), photon_phi->at(goodphoton2_index),photon_E->at(goodphoton2_index));
		      
		      
		      float dPhi_yy = fabs(photon_phi->at(goodphoton1_index) - photon_phi->at(goodphoton2_index) );
		      dPhi_yy       = dPhi_yy < TMath::Pi() ? dPhi_yy : 2*TMath::Pi() - dPhi_yy;
		      
		      float m_yy  = sqrt( 2 * Photon_1.Pt()/1000. * Photon_2.Pt()/1000. * (cosh( Photon_1.Eta() - Photon_2.Eta()) - cos(dPhi_yy)));
		      
		      float Photon_1_kin = Photon_1.Pt()/1000. / m_yy;
		      float Photon_2_kin = Photon_2.Pt()/1000. / m_yy;
		      
		      
		      // kinematical selection		      
		      if ( Photon_1_kin > 0.35 && Photon_2_kin > 0.25 ) 
			{ 		     
	
	                  nEvent5++; // relative pT cuts

			  FillHistogramsGlobal( m_yy, weight, "hist_mYY_incl");
			  
			  if(m_yy > 105 && m_yy < 160 ) 
			    {
			      FillHistogramsGlobal( m_yy, weight, "hist_mYY_win");
			      
			      nEvent6++; // counter final
			      
			      
			      TLorentzVector DiPhoton = TLorentzVector(); DiPhoton = Photon_1+Photon_2;
			      float pt_yy = DiPhoton.Pt()/1000.;
			      
			      //if( pt_yy> 70 && pt_yy < 170)
				//{
				  //FillHistogramsGlobal( m_yy, weight, "hist_mYY_pt");
				//}
			      
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
  
  name="Output_HyyAnalysis/"+name+".root";
  const char* filename = name.c_str();
  
  cout << "analyzed an total  " << nEvent << " events" << endl;
  cout << "after trigger      " << nEvent2/nEvent << " or " << nEvent2 << " events" << endl;
  cout << "after 2 good tight " << nEvent3/nEvent2<< " or " << nEvent2 << " events" << endl;
  cout << "after 2 isolated   " << nEvent4/nEvent3 << " or " << nEvent3 <<" events" << endl;
  cout << "after pT cuts      " << nEvent5/nEvent4 << " or " << nEvent4 << " events" << endl;
  cout << "after window  cut  " << nEvent6/nEvent5 << " or " << nEvent5 << " events" << endl;
  
  
  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();
 
  cout << "wrote histograms to file " << filename <<  endl;


}
