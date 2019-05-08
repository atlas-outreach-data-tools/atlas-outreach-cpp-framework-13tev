//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_ZZDiBosonAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/2lep/";
  
  /* The URL to the ATLAS Open Data website repository */
  //  TString path = "http://opendata.atlas.cern/release/samples/";

  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 4 options for MC (2,3,4,5) and 1 for data (1) which can be run in parallel
  //***************************************************************************************************//

  if (option==1 || option==0)
  {
  //data
  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/dataA_2lep.root");
  chain_data->AddFile(path+"Data/dataB_2lep.root");
  chain_data->AddFile(path+"Data/dataC_2lep.root");
  chain_data->AddFile(path+"Data/dataD_2lep.root");
  chain_data->Process("ZZDiBosonAnalysis.C+","data");
  }

  
  //////////////////////  MC samples


  if (option==2 || option==0)   {
  // diboson
  TChain* chain_WWlvlv = new TChain("mini");
  chain_WWlvlv->AddFile(path+"MC/mc15_13TeV.361600.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvlv.2lep_raw.root");
  chain_WWlvlv->Process("ZZDiBosonAnalysis.C+","WWlvlv");

  TChain* chain_WWlvqq = new TChain("mini");
  chain_WWlvqq->AddFile(path+"MC/mc15_13TeV.361606.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvqq.2lep_raw.root");
  chain_WWlvqq->Process("ZZDiBosonAnalysis.C+","WWlvqq");

  TChain* chain_ZZllll = new TChain("mini");
  chain_ZZllll->AddFile(path+"MC/mc15_13TeV.361603.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.2lep_raw.root");
  chain_ZZllll->Process("ZZDiBosonAnalysis.C+","ZZllll");

  TChain* chain_ZZvvll = new TChain("mini");
  chain_ZZvvll->AddFile(path+"MC/mc15_13TeV.361604.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvll_mll4.2lep_raw.root");
  chain_ZZvvll->Process("ZZDiBosonAnalysis.C+","ZZvvll");

  TChain* chain_ZZqqll = new TChain("mini");
  chain_ZZqqll->AddFile(path+"MC/mc15_13TeV.361610.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZqqll_mqq20mll20.2lep_raw.root");
  chain_ZZqqll->Process("ZZDiBosonAnalysis.C+","ZZqqll");

  TChain* chain_WZlvll = new TChain("mini");
  chain_WZlvll->AddFile(path+"MC/mc15_13TeV.361601.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4.2lep_raw.root");
  chain_WZlvll->Process("ZZDiBosonAnalysis.C+","WZlvll");

  TChain* chain_WZlvvv = new TChain("mini");
  chain_WZlvvv->AddFile(path+"MC/mc15_13TeV.361602.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvvv_mll4.2lep_raw.root");
  chain_WZlvvv->Process("ZZDiBosonAnalysis.C+","WZlvvv");

  TChain* chain_WZqqll = new TChain("mini");
  chain_WZqqll->AddFile(path+"MC/mc15_13TeV.361607.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZqqll_mll20.2lep_raw.root");
  chain_WZqqll->Process("ZZDiBosonAnalysis.C+","WZqqll");

  TChain* chain_WZlvqq = new TChain("mini");
  chain_WZlvqq->AddFile(path+"MC/mc15_13TeV.361609.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvqq_mqq20.2lep_raw.root");
  chain_WZlvqq->Process("ZZDiBosonAnalysis.C+","WZlvqq");
  }


  if (option==3 || option==0)   {
  // Z+jets inclusive
  TChain* chain_Z_ee = new TChain("mini");
  chain_Z_ee->AddFile(path+"MC/mc15_13TeV.361106.PwPy8EG_AZNLOCTEQ6L1_Zee.2lep_raw.root");
  chain_Z_ee->Process("ZZDiBosonAnalysis.C+","Z_ee");
  }

  if (option==4 || option==0)   {
  TChain* chain_Z_mumu = new TChain("mini");
  chain_Z_mumu->AddFile(path+"MC/mc15_13TeV.361107.PwPy8EG_AZNLOCTEQ6L1_Zmumu.2lep_raw.root");
  chain_Z_mumu->Process("ZZDiBosonAnalysis.C+","Z_mumu");
  }

  if (option==5 || option==0)   {
  TChain* chain_Z_tautau = new TChain("mini");
  chain_Z_tautau->AddFile(path+"MC/mc15_13TeV.361108.PwPy8EG_AZNLOCTEQ6L1_Ztautau.2lep_raw.root");
  chain_Z_tautau->Process("ZZDiBosonAnalysis.C+","Z_tautau");

  // W+jets inclusive  
  TChain* chain_Wplusenu = new TChain("mini");
  chain_Wplusenu->AddFile(path+"MC/mc15_13TeV.361100.PwPy8EG_AZNLOCTEQ6L1_Wplusenu.2lep_raw.root");
  chain_Wplusenu->Process("ZZDiBosonAnalysis.C+","Wplusenu");

  TChain* chain_Wplusmunu = new TChain("mini");
  chain_Wplusmunu->AddFile(path+"MC/mc15_13TeV.361101.PwPy8EG_AZNLOCTEQ6L1_Wplusmunu.2lep_raw.root");
  chain_Wplusmunu->Process("ZZDiBosonAnalysis.C+","Wplusmunu");

  TChain* chain_Wplustaunu = new TChain("mini");
  chain_Wplustaunu->AddFile(path+"MC/mc15_13TeV.361102.PwPy8EG_AZNLOCTEQ6L1_Wplustaunu.2lep_raw.root");
  chain_Wplustaunu->Process("ZZDiBosonAnalysis.C+","Wplustaunu");

  TChain* chain_Wminusenu = new TChain("mini");
  chain_Wminusenu->AddFile(path+"MC/mc15_13TeV.361103.PwPy8EG_AZNLOCTEQ6L1_Wminusenu.2lep_raw.root");
  chain_Wminusenu->Process("ZZDiBosonAnalysis.C+","Wminusenu");

  TChain* chain_Wminusmunu = new TChain("mini");
  chain_Wminusmunu->AddFile(path+"MC/mc15_13TeV.361104.PwPy8EG_AZNLOCTEQ6L1_Wminusmunu.2lep_raw.root");
  chain_Wminusmunu->Process("ZZDiBosonAnalysis.C+","Wminusmunu");

  TChain* chain_Wminustaunu = new TChain("mini");
  chain_Wminustaunu->AddFile(path+"MC/mc15_13TeV.361105.PwPy8EG_AZNLOCTEQ6L1_Wminustaunu.2lep_raw.root");
  chain_Wminustaunu->Process("ZZDiBosonAnalysis.C+","Wminustaunu");

  //single top
  TChain* chain_single_top_tchan = new TChain("mini");
  chain_single_top_tchan->AddFile(path+"MC/mc15_13TeV.410011.PwPyEG_P2012_singletop_tchan_lept_top.2lep_raw.root");
  chain_single_top_tchan->Process("ZZDiBosonAnalysis.C+","single_top_tchan");

  TChain* chain_single_antitop_tchan = new TChain("mini");
  chain_single_antitop_tchan->AddFile(path+"MC/mc15_13TeV.410012.PwPyEG_P2012_singletop_tchan_lept_antitop.2lep_raw.root");
  chain_single_antitop_tchan->Process("ZZDiBosonAnalysis.C+","single_antitop_tchan");

  TChain* chain_single_top_schan = new TChain("mini");
  chain_single_top_schan->AddFile(path+"MC/mc15_13TeV.410025.PwPyEG_P2012_SingleTopSchan_noAllHad_top.2lep_raw.root");
  chain_single_top_schan->Process("ZZDiBosonAnalysis.C+","single_top_schan");

  TChain* chain_single_antitop_schan = new TChain("mini");
  chain_single_antitop_schan->AddFile(path+"MC/mc15_13TeV.410026.PwPyEG_P2012_SingleTopSchan_noAllHad_antitop.2lep_raw.root");
  chain_single_antitop_schan->Process("ZZDiBosonAnalysis.C+","single_antitop_schan");

  TChain* chain_single_top_wtchan = new TChain("mini");
  chain_single_top_wtchan->AddFile(path+"MC/mc15_13TeV.410013.PwPyEG_P2012_Wt_inclusive_top.2lep_raw.root");
  chain_single_top_wtchan->Process("ZZDiBosonAnalysis.C+","single_top_wtchan");

  TChain* chain_single_antitop_wtchan = new TChain("mini");
  chain_single_antitop_wtchan->AddFile(path+"MC/mc15_13TeV.410014.PwPyEG_P2012_Wt_inclusive_antitop.2lep_raw.root");
  chain_single_antitop_wtchan->Process("ZZDiBosonAnalysis.C+","single_antitop_wtchan");

  //ttbar

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc15_13TeV.410000.PwPyEG_P2012_ttbar_hdamp172p5_nonallhad.2lep_raw.root");
  chain_ttbar_lep->Process("ZZDiBosonAnalysis.C+","ttbar_lep");
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
