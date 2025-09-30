//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

void main_HyyAnalysis(int proof = 0, int option= 0)
{
  /* The URL to the CERN Open Data portal repository */
  TString path = "root://eospublic.cern.ch//eos/opendata/atlas/rucio/opendata/";

  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 5 options for MC (2,3,4,5,6) and 1 for data (1) which can be run in parallel
  //***************************************************************************************************//

  TString skim = "GamGam";
  TString prefix = path+"ODEO_FEB2025_v0_"+skim+"_"; 

  if (option==1 || option==0){

    //data15
    TChain* chain_data = new TChain("analysis");
    chain_data->AddFile(prefix+"data15_periodD."+skim+".root");
    chain_data->AddFile(prefix+"data15_periodE."+skim+".root");
    chain_data->AddFile(prefix+"data15_periodF."+skim+".root");
    chain_data->AddFile(prefix+"data15_periodG."+skim+".root");
    chain_data->AddFile(prefix+"data15_periodH."+skim+".root");
    chain_data->AddFile(prefix+"data15_periodJ."+skim+".root");

    //data16
    chain_data->AddFile(prefix+"data16_periodA."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodB."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodC."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodD."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodE."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodF."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodG."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodI."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodK."+skim+".root");
    chain_data->AddFile(prefix+"data16_periodL."+skim+".root");
  
    chain_data->Process("HyyAnalysis.C+","data");
  } // option 1

  if (option==2 || option==0){

    //Higgs samples (H->WW)
    
    // ggH
    TChain* chain_ggH125_WW = new TChain("analysis");
    chain_ggH125_WW->AddFile(prefix+"mc_345324.PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5."+skim+".root");
    chain_ggH125_WW->Process("HyyAnalysis.C+","PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5");
   
    // VBF
    TChain* chain_VBFH125_WW = new TChain("analysis");
    chain_VBFH125_WW->AddFile(prefix+"mc_345948.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv."+skim+".root");
    chain_VBFH125_WW->Process("HyyAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv");

    // // Higgs MC, ggH production
    // TChain* chain_ggH125 = new TChain("mini");
    // chain_ggH125->AddFile(path+"MC/mc_343981.ggH125_gamgam.GamGam.root");
    // if (proof == 1)  chain_ggH125->SetProof();
    // chain_ggH125->Process("HyyAnalysis.C+","ggH125_gamgam");

    // // VBF Higgs production
    // TChain* chain_VBFH125 = new TChain("mini");
    // chain_VBFH125->AddFile(path+"MC/mc_345041.VBFH125_gamgam.GamGam.root");
    // if (proof == 1)  chain_VBFH125->SetProof();
    // chain_VBFH125->Process("HyyAnalysis.C+","VBFH125_gamgam");

    // // WH production
    // TChain* chain_WH125 = new TChain("mini");
    // chain_WH125->AddFile(path+"MC/mc_345318.WpH125J_Wincl_gamgam.GamGam.root");
    // if (proof == 1)  chain_WH125->SetProof();
    // chain_WH125->Process("HyyAnalysis.C+","WH125_gamgam");

    // // ZH production
    // TChain* chain_ZH125 = new TChain("mini");
    // chain_ZH125->AddFile(path+"MC/mc_345319.ZH125J_Zincl_gamgam.GamGam.root");
    // if (proof == 1)  chain_ZH125->SetProof();
    // chain_ZH125->Process("HyyAnalysis.C+","ZH125_gamgam");

    // // ttH production
    // TChain* chain_ttH125 = new TChain("mini");
    // chain_ttH125->AddFile(path+"MC/mc_341081.ttH125_gamgam.GamGam.root");
    // if (proof == 1)  chain_ttH125->SetProof();
    // chain_ttH125->Process("HyyAnalysis.C+","ttH125_gamgam");
  }//option 2
}
