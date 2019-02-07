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
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      //Begin analysis
      
      //SF
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER;
      //EventW
      Float_t eventWeight = mcWeight*scaleFactor_PILEUP;
      //weight = SF * EventW
      Float_t weight = scaleFactor*eventWeight;
      
      // Make difference between data and MC
      if (weight == 0.) weight = 1.;
      
      // Missing Et of the event in GeV
      Float_t missingEt = met_et/1000.;
      
      
      // Preselection cut for electron/muon trigger, Good Run List, and good vertex
      if(trigE || trigM)
	{
	  //if(passGRL)
	  // {
	  // if(hasGoodVertex)
	  //{
	  // Preselection of good leptons
	  int goodlep_index =0;
	  int goodlep_n = 0;
	  
	  for(unsigned int i=0; i<lep_n; i++)
	    {
	      // is Tight
	      if( lep_isTightID->at(i) )
		{
		  // isolated
		  if( lep_pt->at(i) >25000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15 ) )
		    {
		      // electron or muon
		      if ( lep_type->at(i)==11 ||  lep_type->at(i) ==13) {
			goodlep_n = goodlep_n + 1;
			goodlep_index = i;
		      }
		    }
		}
	    }
	  
	  //Preselection of good jets
	  int goodjet_n = 0;
	  int goodbjet_n = 0;
	  int goodjet_index[3];
	  int jet_index = 0;
	  
	  for(unsigned int i=0; i<jet_n; i++)
	    {
	      if(jet_pt->at(i)>25000. && abs(jet_eta->at(i)) < 2.5)
		{
		  // JVT cleaning
		  bool jvt_pass=true;
		  if (jet_pt->at(i) < 60000. && abs(jet_eta->at(i)) < 2.4 && jet_jvt->at(i) < 0.59) jvt_pass=false;
		  if (jvt_pass) {
		    goodjet_n++;
		    goodjet_index[jet_index] = i;
		    jet_index++;
		    
		    // 70% WP
		    if (jet_MV2c10->at(i) >0.8244273	 ){
		      goodbjet_n++;
		    }
		  }
		}
	    }
	  
	  
	  
	  //Exactly one good lepton
	  if(goodlep_n==1)
	    {
	      
	      // TLorentzVector definitions
	      TLorentzVector Lepton_1  = TLorentzVector();
	      TLorentzVector      MeT  = TLorentzVector();
	      TLorentzVector   Lepton1_MeT = TLorentzVector();
	      
	      Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
	      MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
	      
	      
	      //Calculation of MTW
	      Lepton1_MeT = Lepton_1 + MeT;
	      float InvMass1       = Lepton1_MeT.Mag();
	      float InvMass1_inGeV = InvMass1/1000.;
	      float MTW = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
	      
	      
	      // At least four jets
	      if(goodjet_n > 3)
		{
		  int goodjet1_index = goodjet_index[0];
		  
		  //At least two b-tagged jets
		  if(goodbjet_n > 1)
		    {
		      // MET > 30 GeV
		      if(met_et > 30000.)
			{
			  // MTW > 30 GeV
			  if(MTW > 30000.)
			    {
			      
			      double names_of_global_variable[]={missingEt, MTW/1000.};
			      //    double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index), lep_ptcone30->at(goodlep_index)/lep_pt->at(goodlep_index), lep_etcone20->at(goodlep_index)/lep_pt->at(goodlep_index), lep_z0->at(goodlep_index), lep_trackd0pvunbiased->at(goodlep_index)};
			      //  double names_of_jet_variable[]={(double)goodjet_n, jet_pt->at(goodjet1_index)/1000., jet_eta->at(goodjet1_index), jet_m->at(goodjet1_index)/1000., jet_jvf->at(goodjet1_index), jet_MV1->at(goodjet1_index)};
			      
			      TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw"};
			      //   TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
			      //  TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_leadjet_m", "hist_leadjet_jvf", "hist_leadjet_MV1"};
			      
			      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
			      //int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
			      //  int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
			      
			      for (int i=0; i<length_global; i++)
				{
				  FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
				}
			      /*
				for (int i=0; i<length_leadlep; i++)
				{
				FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
				}
				for (int i=0; i<length_leadjet; i++)
				{
				FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
				}
			      */
			    }
			}
		    }
		}
	    }
	}
      //}
      //}
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
