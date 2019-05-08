//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_TTbarAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/1lep/";
  
  /* The URL to the ATLAS Open Data website repository */
  //  TString path = "http://opendata.atlas.cern/release/samples/";

  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 5 options for MC (1, 2,3,4,5) and 4 for data (11,12,13,14) which can be run in parallel
  // If using the options (11,12,13,14) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//


  if (option==11 || option==0){
  TChain* chain_dataA = new TChain("mini");
  chain_dataA->AddFile(path+"Data/dataA_1lep.root");
  chain_dataA->Process("TTbarAnalysis.C+","dataA");
  }

  if (option==12 || option==0){
  TChain* chain_dataB = new TChain("mini");
  chain_dataB->AddFile(path+"Data/dataB_1lep.root");
  chain_dataB->Process("TTbarAnalysis.C+","dataB");
  }

  if (option==13 || option==0){
  TChain* chain_dataC = new TChain("mini");
  chain_dataC->AddFile(path+"Data/dataC_1lep.root");
  chain_dataC->Process("TTbarAnalysis.C+","dataC");
  }

  if (option==14 || option==0){
  TChain* chain_dataD = new TChain("mini");
  chain_dataD->AddFile(path+"Data/dataD_1lep.root");
  chain_dataD->Process("TTbarAnalysis.C+","dataD");
  }


  
  //////////////////////  MC samples

  if (option==2 || option==0)   {
  // W+jets inclusive  
  TChain* chain_Wplusenu = new TChain("mini");
  chain_Wplusenu->AddFile(path+"MC/mc15_13TeV.361100.PwPy8EG_AZNLOCTEQ6L1_Wplusenu.1lep_raw.root");
  chain_Wplusenu->Process("TTbarAnalysis.C+","Wplusenu");

  TChain* chain_Wplusmunu = new TChain("mini");
  chain_Wplusmunu->AddFile(path+"MC/mc15_13TeV.361101.PwPy8EG_AZNLOCTEQ6L1_Wplusmunu.1lep_raw.root");
  chain_Wplusmunu->Process("TTbarAnalysis.C+","Wplusmunu");

  TChain* chain_Wplustaunu = new TChain("mini");
  chain_Wplustaunu->AddFile(path+"MC/mc15_13TeV.361102.PwPy8EG_AZNLOCTEQ6L1_Wplustaunu.1lep_raw.root");
  chain_Wplustaunu->Process("TTbarAnalysis.C+","Wplustaunu");
  }

  if (option==3 || option==0)   {
  TChain* chain_Wminusenu = new TChain("mini");
  chain_Wminusenu->AddFile(path+"MC/mc15_13TeV.361103.PwPy8EG_AZNLOCTEQ6L1_Wminusenu.1lep_raw.root");
  chain_Wminusenu->Process("TTbarAnalysis.C+","Wminusenu");

  TChain* chain_Wminusmunu = new TChain("mini");
  chain_Wminusmunu->AddFile(path+"MC/mc15_13TeV.361104.PwPy8EG_AZNLOCTEQ6L1_Wminusmunu.1lep_raw.root");
  chain_Wminusmunu->Process("TTbarAnalysis.C+","Wminusmunu");

  TChain* chain_Wminustaunu = new TChain("mini");
  chain_Wminustaunu->AddFile(path+"MC/mc15_13TeV.361105.PwPy8EG_AZNLOCTEQ6L1_Wminustaunu.1lep_raw.root");
  chain_Wminustaunu->Process("TTbarAnalysis.C+","Wminustaunu");
  }

  if (option==4 || option==0)   {
  // diboson
  TChain* chain_WWlvlv = new TChain("mini");
  chain_WWlvlv->AddFile(path+"MC/mc15_13TeV.361600.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvlv.1lep_raw.root");
  chain_WWlvlv->Process("TTbarAnalysis.C+","WWlvlv");

  TChain* chain_WWlvqq = new TChain("mini");
  chain_WWlvqq->AddFile(path+"MC/mc15_13TeV.361606.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvqq.1lep_raw.root");
  chain_WWlvqq->Process("TTbarAnalysis.C+","WWlvqq");

  TChain* chain_ZZllll = new TChain("mini");
  chain_ZZllll->AddFile(path+"MC/mc15_13TeV.361603.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.1lep_raw.root");
  chain_ZZllll->Process("TTbarAnalysis.C+","ZZllll");

  TChain* chain_ZZvvll = new TChain("mini");
  chain_ZZvvll->AddFile(path+"MC/mc15_13TeV.361604.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvll_mll4.1lep_raw.root");
  chain_ZZvvll->Process("TTbarAnalysis.C+","ZZvvll");

  TChain* chain_ZZqqll = new TChain("mini");
  chain_ZZqqll->AddFile(path+"MC/mc15_13TeV.361610.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZqqll_mqq20mll20.1lep_raw.root");
  chain_ZZqqll->Process("TTbarAnalysis.C+","ZZqqll");

  TChain* chain_WZlvll = new TChain("mini");
  chain_WZlvll->AddFile(path+"MC/mc15_13TeV.361601.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4.1lep_raw.root");
  chain_WZlvll->Process("TTbarAnalysis.C+","WZlvll");

  TChain* chain_WZlvvv = new TChain("mini");
  chain_WZlvvv->AddFile(path+"MC/mc15_13TeV.361602.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvvv_mll4.1lep_raw.root");
  chain_WZlvvv->Process("TTbarAnalysis.C+","WZlvvv");

  TChain* chain_WZqqll = new TChain("mini");
  chain_WZqqll->AddFile(path+"MC/mc15_13TeV.361607.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZqqll_mll20.1lep_raw.root");
  chain_WZqqll->Process("TTbarAnalysis.C+","WZqqll");

  TChain* chain_WZlvqq = new TChain("mini");
  chain_WZlvqq->AddFile(path+"MC/mc15_13TeV.361609.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvqq_mqq20.1lep_raw.root");
  chain_WZlvqq->Process("TTbarAnalysis.C+","WZlvqq");

  // Z+jets inclusive
  TChain* chain_Z_ee = new TChain("mini");
  chain_Z_ee->AddFile(path+"MC/mc15_13TeV.361106.PwPy8EG_AZNLOCTEQ6L1_Zee.1lep_raw.root");
  chain_Z_ee->Process("TTbarAnalysis.C+","Z_ee");
  
  TChain* chain_Z_mumu = new TChain("mini");
  chain_Z_mumu->AddFile(path+"MC/mc15_13TeV.361107.PwPy8EG_AZNLOCTEQ6L1_Zmumu.1lep_raw.root");
  chain_Z_mumu->Process("TTbarAnalysis.C+","Z_mumu");

  TChain* chain_Z_tautau = new TChain("mini");
  chain_Z_tautau->AddFile(path+"MC/mc15_13TeV.361108.PwPy8EG_AZNLOCTEQ6L1_Ztautau.1lep_raw.root");
  chain_Z_tautau->Process("TTbarAnalysis.C+","Z_tautau");
  }

  if (option==5 || option==0)   {
  //single top
  TChain* chain_single_top_tchan = new TChain("mini");
  chain_single_top_tchan->AddFile(path+"MC/mc15_13TeV.410011.PwPyEG_P2012_singletop_tchan_lept_top.1lep_raw.root");
  chain_single_top_tchan->Process("TTbarAnalysis.C+","single_top_tchan");

  TChain* chain_single_antitop_tchan = new TChain("mini");
  chain_single_antitop_tchan->AddFile(path+"MC/mc15_13TeV.410012.PwPyEG_P2012_singletop_tchan_lept_antitop.1lep_raw.root");
  chain_single_antitop_tchan->Process("TTbarAnalysis.C+","single_antitop_tchan");

  TChain* chain_single_top_schan = new TChain("mini");
  chain_single_top_schan->AddFile(path+"MC/mc15_13TeV.410025.PwPyEG_P2012_SingleTopSchan_noAllHad_top.1lep_raw.root");
  chain_single_top_schan->Process("TTbarAnalysis.C+","single_top_schan");

  TChain* chain_single_antitop_schan = new TChain("mini");
  chain_single_antitop_schan->AddFile(path+"MC/mc15_13TeV.410026.PwPyEG_P2012_SingleTopSchan_noAllHad_antitop.1lep_raw.root");
  chain_single_antitop_schan->Process("TTbarAnalysis.C+","single_antitop_schan");

  TChain* chain_single_top_wtchan = new TChain("mini");
  chain_single_top_wtchan->AddFile(path+"MC/mc15_13TeV.410013.PwPyEG_P2012_Wt_inclusive_top.1lep_raw.root");
  chain_single_top_wtchan->Process("TTbarAnalysis.C+","single_top_wtchan");

  TChain* chain_single_antitop_wtchan = new TChain("mini");
  chain_single_antitop_wtchan->AddFile(path+"MC/mc15_13TeV.410014.PwPyEG_P2012_Wt_inclusive_antitop.1lep_raw.root");
  chain_single_antitop_wtchan->Process("TTbarAnalysis.C+","single_antitop_wtchan");
  }

  if (option==1 || option==0)   {

  //ttbar
  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc15_13TeV.410000.PwPyEG_P2012_ttbar_hdamp172p5_nonallhad.1lep_raw.root");
  chain_ttbar_lep->Process("TTbarAnalysis.C+","ttbar_lep");

  } 


/*
// For now, the use of PROOF is commented out, to be added...
//
   if (proof == 1)
  {
    TProof::Open("");

  
    chain_data->SetProof();

  }
*/


}
