/////////////////////////////////////////////////////////////
//// SingleTopAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define SingleTopAnalysis_cxx

#include "SingleTopAnalysis.h"
#include "SingleTopAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void SingleTopAnalysis::Begin(TTree * )
{
  
  nEvents=0;
  
}

void SingleTopAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t SingleTopAnalysis::Process(Long64_t entry)
{
  
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // ***************************************************************************************************//
      // Begin simplified selection based on: ATLAS Collaboration, JHEP04 (2017) 086  and JHEP04 (2017) 124 //
      // ***************************************************************************************************//

      //Scale factors
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP*scaleFactor_BTAG;

      //MC weight
      Float_t m_mcWeight = mcWeight;

      // read input option
      TString option = GetOption();
      if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs

      //Total weight
      Float_t weight = scaleFactor*m_mcWeight;
    
      // Make difference between data and MC
      if(option.Contains("data")) {  weight = 1.; }  
      
      // Missing Et of the event in GeV
      Float_t missingEt = met_et;

      //First cut : missing energy larger than 30 GeV
      if(missingEt > 30000)
	{
	  
	  // Preselection cut for electron/muon trigger
	  if(trigE || trigM)
	    {
	      
	      // Preselection of good leptons
	      int goodlep_index = 0;
	      int goodlep_n = 0;
	      int lep_index =0;
	      
	      for(unsigned int i=0; i<lep_n; i++)
		{
		  
                  // create a temporary TLorentzVector of the lepton 
                  TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);
		  
		  // Lepton is Tight
		  if( lep_isTightID->at(i) )
		    {
		      // Lepton is highly isolated and very hard pT to remove any multijet
		      if( lep_pt->at(i) > 35000. && ( (lep_ptcone30->at(i) / lep_pt->at(i)) < 0.1) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.1 ) )
			{
                	  // electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
			  if ( lep_type->at(i) == 11 && TMath::Abs(lep_eta->at(i)) < 2.47 && ( TMath::Abs(lep_eta->at(i)) < 1.37 || TMath::Abs(lep_eta->at(i)) > 1.52 ) ) {
			    // longitudinal and longitudinal impact parameter cuts
			    if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) > 5) continue;  
			    if( TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) > 0.5) continue; 
			    
                            goodlep_n = goodlep_n + 1;
			    goodlep_index = i;
			    lep_index++;
			  }
			  
			  // muon selection
			  if ( lep_type->at(i) == 13 && TMath::Abs(lep_eta->at(i)) < 2.5 ) {
			    
                            if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) > 3) continue;  
                            if( TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) > 0.5) continue;
			    
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
		  
		  //Preselection of good jets
		  int goodjet_n = 0;
		  int goodbjet_n = 0;
		  int goodljet_n = 0;
		  
		  int goodjet_index[jet_n];
		  int jet_index = 0;
		  
		  int goodbjet_index[jet_n];
		  int bjet_index = 0;
		  
		  
		  for(unsigned int i=0; i<jet_n; i++)
		    {
		      if(jet_pt->at(i) > 30000. && TMath::Abs(jet_eta->at(i)) < 2.5)
			{
			  // JVT cleaning
			  bool jvt_pass=true;
			  if (jet_pt->at(i) < 60000. && TMath::Abs(jet_eta->at(i)) < 2.4 && jet_jvt->at(i) < 0.59) jvt_pass=false;
			  if (jvt_pass)
			    {
			      goodjet_n++;
			      goodjet_index[jet_index] = i;
			      jet_index++;
			      
			      // cut on 0.8244273 is 70% WP
			      if (jet_MV2c10->at(i) >0.8244273       )
				{
				  goodbjet_n++;
				  goodbjet_index[bjet_index] = i;
				  bjet_index++;
				}
			    }
			}
		    }
		  
		  // TLorentzVector definitions
		  TLorentzVector Lepton_1  = TLorentzVector();
		  TLorentzVector      MeT  = TLorentzVector();
		  
		  Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
		  MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
		  
		  //Calculation of the W-boson transverse mass
		  float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
		  
		  
                  //transverse mass larger than 60 GeV
		  if(mtw > 60000.)
		    {
		      
                      // exactly two good jets
                      if(goodjet_n == 2)
                        {
			  
                          int goodjet1_index = goodjet_index[0]; // leading jet
                          int goodjet2_index = goodjet_index[1]; // second jet
			  
                          //exactly one b-tagged jets
                          if(goodbjet_n == 1)
                            {
                              int taggedjet_index = goodbjet_index[0]; // b-jet
                              int untagged_index = -999;
			      if (goodjet1_index==taggedjet_index) untagged_index =goodjet2_index; 
                              if (goodjet2_index==taggedjet_index) untagged_index =goodjet1_index;
			      
                              //the spectator quark tends to be produced in the forward direction in the t-channel process.
			      if ( TMath::Abs(jet_eta->at(untagged_index)) > 1.5 ) 
  			        {
				  
				  //separation in  between the untagged jet and the b-tagged jet must be larger than 1.5, to reduce the contribution from tt background events.
				  float deltaeta = TMath::Abs( jet_eta->at(untagged_index) - jet_eta->at(taggedjet_index) );		
				  if (deltaeta > 1.5)
				    {
				      
				      //The scalar sum of the pT of the lepton, the pT of the jets and MET  must be larger than 195 GeV
				      float HT = Lepton_1.Pt()/1000. +  jet_pt->at(untagged_index)/1000. + jet_pt->at(taggedjet_index)/1000. + missingEt/1000.;
				      if (HT > 195)
					{
					  // mass of reconstructed top quark (lepton, neutrino, b) cut
					  TLorentzVector bjet  = TLorentzVector(); bjet.SetPtEtaPhiE(jet_pt->at(taggedjet_index), jet_eta->at(taggedjet_index), jet_phi->at(taggedjet_index),jet_E->at(taggedjet_index));
					  
					  float Mlb = ( bjet + Lepton_1 ).M()/1000.; 
					  
					  if (Mlb < 150)
					    {	
					      
					      
					      //Start to fill histograms : definitions of x-axis variables
					      double names_of_global_variable[]={missingEt/1000., mtw/1000. , deltaeta, HT, Mlb};
					      
					      double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index)};
					      
					      
					      //Start to fill histograms : definitions of histogram names
					      TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw","hist_deltaeta","hist_HT", "hist_Mlb"};
					      
					      TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID"};
					      
					      //Start to fill histograms : find the histogram array length
					      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
					      int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
					      
					      //Fill histograms
					      for (int i=0; i<length_global; i++)
						{
						  FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
						}
					      
					      for (int i=0; i<length_leadlep; i++)
						{
						  FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
						}
					      
					      // fill jets
					      double names_of_jet_variable[]={(double)goodjet_n, jet_pt->at(untagged_index)/1000.,jet_eta->at(untagged_index),(double)goodbjet_n, jet_pt->at(taggedjet_index)/1000.,jet_eta->at(taggedjet_index)};
					      
					      
					      TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_n_bjets","hist_leadbjet_pt","hist_leadbjet_eta"};
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
		}
	    }
	}
    }
  
  return kTRUE;
}

void SingleTopAnalysis::SlaveTerminate()
{
}

void SingleTopAnalysis::Terminate()
{

  // creating the output file
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_SingleTopAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();
  
}
