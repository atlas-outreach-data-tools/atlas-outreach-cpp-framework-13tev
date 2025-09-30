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
#include <TRandom3.h>

string name;

void HyyAnalysis::Begin(TTree * )
{
	xsec_SF = 0;
	totalSumOfWeights_SF = 0;
	filteff_SF = 0;
	kfac_SF = 0;

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

Bool_t HyyAnalysis::Process(Long64_t entry){

  fChain->GetTree()->GetEntry(entry);
  nEvent++; nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;

	if(fChain->GetTree()->GetEntries()>0){

		// **********************************************************************************************//
		// Begin analysis selection, largely based on: ATLAS Collaboration, PRD 98 (2018) 052005         //
		// **********************************************************************************************//

		//Scale factors
		Float_t scaleFactor = ScaleFactor_PHOTON*ScaleFactor_PILEUP;

		//MC weight
		Float_t m_mcWeight = mcWeight;

		// read input option
    	TString option = GetOption();

		//Total weight
		Float_t weight = scaleFactor*m_mcWeight;
	
		// Make difference between data and MC
		
		bool is_data = option.Contains("data");
		
		if( is_data==true ){
			weight = 1.;
			if(entry==0){
				xsec_SF = 1.;
				totalSumOfWeights_SF = 1.;
				filteff_SF = 1.;
				kfac_SF = 1.;
			}
		}

		if( is_data==false ){
			if(entry==0){
				xsec_SF = xsec;
				filteff_SF = filteff;
				kfac_SF = kfac;
				totalSumOfWeights_SF = initial_sum_of_weights;
			}
		}
    
		if(photon_isTightID->at(0)==true && photon_isTightID->at(1)==true){
			nEvent2++;
			// Cut: pT cut - photon 1 has pT > 50 GeV and photon 2 has pT > 30 GeV
			if(photon_pt->at(0) > 50. && photon_pt->at(1) > 30.){
				nEvent3++;
				// Only the events where the calorimeter isolation is less than 5.5% are kept
				if(photon_ptcone20->at(0)/photon_pt->at(0) < 0.055 && photon_ptcone20->at(1)/photon_pt->at(1) < 0.055){
					nEvent4++;
					// Cut on the pseudorapidity in barrel/end-cap transition region
					if((TMath::Abs(photon_eta->at(0)) < 2.37) && 
					(TMath::Abs(photon_eta->at(0)) < 1.37 || TMath::Abs(photon_eta->at(0)) > 1.52)){
						if((TMath::Abs(photon_eta->at(1)) < 2.37) && 
						(TMath::Abs(photon_eta->at(1)) < 1.37 || TMath::Abs(photon_eta->at(1)) > 1.52)){
							nEvent5++;
							// TLorentzVector definitions
							TLorentzVector Photon_1 = TLorentzVector();
							TLorentzVector Photon_2 = TLorentzVector();

							Photon_1.SetPtEtaPhiE(photon_pt->at(0), photon_eta->at(0), photon_phi->at(0), photon_e->at(0));
							Photon_2.SetPtEtaPhiE(photon_pt->at(1), photon_eta->at(1), photon_phi->at(1), photon_e->at(1));
							
							// Calculation of the Invariant Mass using TLorentz vectors
							TLorentzVector Photon_12 = Photon_1 + Photon_2;
							float inv_mass_Hyy = Photon_12.M();

							// Cut on null diphoton invariant mass
							if(inv_mass_Hyy != 0){
								// Cut on mass-window cut
								if(inv_mass_Hyy > 100. && inv_mass_Hyy < 160.){
									// Cut on diphoton invariant mass based isolation. Only the events where 
									// the invididual photon invariant mass based isolation is larger than 35% are kept
									if((photon_pt->at(0)/inv_mass_Hyy > 0.35) && (photon_pt->at(1)/inv_mass_Hyy > 0.35)){
										nEvent6++;
										// Filling with the mass of the gamma-gamma system
										FillHistogramsGlobal( inv_mass_Hyy, weight, "hist_mYY_bin1"); // 30 bins
										// unconverted central category 
										if ( TMath::Abs(photon_eta->at(0)) < 0.75 && TMath::Abs(photon_eta->at(1)) < 0.75 ){
											FillHistogramsGlobal( inv_mass_Hyy, weight, "hist_mYY_cat_bin1"); // 30 bins
										}
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

void HyyAnalysis::SlaveTerminate()
{
}

void HyyAnalysis::Terminate()
{
  
  // Print counters (in case of local, not PROOF)
   
//   cout << "Analyzed a total of               : " << nEvent << " events" << endl;
//   cout << "Counter after trigger selection   : " << nEvent2/nEvent  << " (fraction from previous) or " << nEvent2 << " events" << endl;
//   cout << "Counter after 2 good tight photons: " << nEvent3/nEvent2 << " (fraction from previous) or " << nEvent3 << " events" << endl;
//   cout << "Counter after 2 isolated photons  : " << nEvent4/nEvent3 << " (fraction from previous) or " << nEvent4 << " events" << endl;
//   cout << "Counter after pT cuts on photons  : " << nEvent5/nEvent4 << " (fraction from previous) or " << nEvent5 << " events" << endl;
//   cout << "Counter after mass-window cut     : " << nEvent6/nEvent5 << " (fraction from previous) or " << nEvent6 << " events" << endl;
  
  // Save output
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_HyyAnalysis/"+filename_option+".root";
  const char* filename = output_name;
  
  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();
 
}
