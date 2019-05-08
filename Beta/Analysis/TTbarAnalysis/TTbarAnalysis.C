/////////////////////////////////////////////////////////////
//// TTbarAnalysis code
//// Author: ATLAS Collaboration (2018)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define TTbarAnalysis_cxx

#include "TTbarAnalysis.h"
#include "TTbarAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void TTbarAnalysis::Begin(TTree * )
{

  nEvents=0;

}

void TTbarAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t TTbarAnalysis::Process(Long64_t entry)
{
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, JHEP 11 (2017) 191           //
      // **********************************************************************************************//
      
      
      //Scale factors
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER;
      //Event weight (adding btag SF corresponding to 70% working point)
      Float_t eventWeight = mcWeight*scaleFactor_PILEUP*scaleFactor_BTAG;
      //Total weight
      Float_t weight = scaleFactor*eventWeight;
      
      // Make difference between data and MC
      if (weight == 0.) weight = 1.;
      
      // cut on at least 4 jets
      if (jet_n > 3)
	{
	  
	  // MET > 30 GeV
	  if(met_et > 30000.)
	    {
	      
	      // Preselection cut for electron/muon trigger, Good Run List, and good vertex
	      if(trigE || trigM)
		{
		  
		  // Preselection of good leptons
		  int goodlep_index =0;
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
				goodlep_index = i;
				lep_index++;
			      }
			      // muon selection
			      if ( lep_type->at(i) ==13 && abs(lep_eta->at(i)<2.5) ) {
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
		      
		      int goodljet_index[jet_n];
		      int ljet_index = 0;
		      
		      
		      for(unsigned int i=0; i<jet_n; i++)
			{
			  if(jet_pt->at(i)>25000. && abs(jet_eta->at(i)) < 2.5)
			    {
			      // JVT cleaning
			      bool jvt_pass=true;
			      if (jet_pt->at(i) < 60000. && abs(jet_eta->at(i)) < 2.4 && jet_jvt->at(i) < 0.59) jvt_pass=false;
			      if (jvt_pass) 
				{
				  goodjet_n++;
				  goodjet_index[jet_index] = i;
				  jet_index++;
				  
				  // cut on 0.8244273 is 70% WP	
				  if (jet_MV2c10->at(i) >0.8244273	 )
				    {
				      goodbjet_n++;
				      goodbjet_index[bjet_index] = i;
				      bjet_index++;
				    }
				  if (jet_MV2c10->at(i) >0.8244273     )
				    {
				      goodljet_n++;
				      goodljet_index[ljet_index] = i;
				      ljet_index++;
				    }
				}
			    }
			}
		    	      
	  
		      // TLorentzVector definitions
		      TLorentzVector Lepton_1  = TLorentzVector();
		      TLorentzVector      MeT  = TLorentzVector();
		      
		      Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
		      MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
		      
		      
		      //Calculation of MTW
		      float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
		      
		      
		      // At least four good jets
		      if(goodjet_n >= 4)
			{
			  int goodjet1_index = goodjet_index[0]; // leading jet
			  
			  //At least two b-tagged jets
			  if(goodbjet_n >= 2)
			    {
			      int goodbjet1_index = goodbjet_index[0]; // leading b-jet
			      
			      // MTW > 30 GeV
			      if(mtw > 30000.)
				{
							  
				  
				  double names_of_global_variable[]={met_et/1000., mtw/1000.};
				  
				  double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index), lep_ptcone30->at(goodlep_index)/lep_pt->at(goodlep_index), lep_etcone20->at(goodlep_index)/lep_pt->at(goodlep_index), lep_z0->at(goodlep_index), lep_trackd0pvunbiased->at(goodlep_index)};

				  double names_of_jet_variable[]={(double)goodjet_n, jet_pt->at(goodjet1_index)/1000.,jet_eta->at(goodjet1_index),(double)goodbjet_n, jet_pt->at(goodbjet1_index)/1000.,jet_eta->at(goodbjet1_index)};
				  
				  TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw"};

				  TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};

				  TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_n_bjets","hist_leadbjet_pt","hist_leadbjet_eta"};
				  
				  int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);

				  int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);

				  int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
				  
				  for (int i=0; i<length_global; i++)
				    {
				      FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
				    }
				  
				  for (int i=0; i<length_leadlep; i++)
				    {
				      FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
				    }
				  for (int i=0; i<length_leadjet; i++)
				    {
				      FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
				    }





				  // Invariant mass distribution of the 3-jets combination with the highest vector pT sum
				  
				    float PTjjjmax=0;
				    float Mjjjmax=0;
				    
				    
				    for ( int i = 0; i < goodjet_n; ++i) {
				      for ( int j = i + 1; j < goodjet_n; ++j) {
                                        for ( int k = j + 1; k < goodjet_n; ++k) {
					 TLorentzVector jet1  = TLorentzVector(); jet1.SetPtEtaPhiE(jet_pt->at(goodjet_index[i]), jet_eta->at(goodjet_index[i]), jet_phi->at(goodjet_index[i]),jet_E->at(goodjet_index[i]));
					 TLorentzVector jet2  = TLorentzVector(); jet2.SetPtEtaPhiE(jet_pt->at(goodjet_index[j]), jet_eta->at(goodjet_index[j]), jet_phi->at(goodjet_index[j]),jet_E->at(goodjet_index[j]));
					 TLorentzVector jet3  = TLorentzVector(); jet3.SetPtEtaPhiE(jet_pt->at(goodjet_index[k]), jet_eta->at(goodjet_index[k]), jet_phi->at(goodjet_index[k]),jet_E->at(goodjet_index[k]));
					  
					  float PTjjjTemp = (jet1 + jet2 + jet3).Pt()/1000. ;
					  if (PTjjjTemp>PTjjjmax) { 
						  PTjjjmax=PTjjjTemp;  
						  Mjjjmax = (jet1 + jet2 + jet3).M()/1000.; 
					  }   
					  
					}
				      }
				    }
				    
				    
				    double names_of_ttbar_variable[]={Mjjjmax};
				    
				    TString histonames_of_ttbar_variable[]={"hist_Topmass"};
				    
				    int length_ttbar = sizeof(names_of_ttbar_variable)/sizeof(names_of_ttbar_variable[0]);
				    
				    for (int i=0; i<length_ttbar; i++)
				      {
					FillHistogramsTTbar( names_of_ttbar_variable[i], weight, histonames_of_ttbar_variable[i]);
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

void TTbarAnalysis::SlaveTerminate()
{
}

void TTbarAnalysis::Terminate()
{
  name="Output_TTbarAnalysis/"+name+".root";
  
  const char* filename = name.c_str();

  TFile physicsoutput_TTbar(filename,"recreate");
  WriteHistograms();
  physicsoutput_TTbar.Close();
}
