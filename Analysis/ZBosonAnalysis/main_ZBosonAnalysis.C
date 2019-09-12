//////////////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_ZBosonAnalysis(int proof = 0, int option= 1)
{
  // path to your local directory *or* URL, please change the default one!

  /* Local path example */
  TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/2lep/";
  
  /* The URL to the ATLAS Open Data website repository */
//  TString path = "http://opendata.atlas.cern/release/samples/";

  //////////////////////////////////////////////////////////////////////////////////////////
  // adding chains of all MC and data samples

  if (option==1)
  {
  //data
  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/dataA_2lep.root");
  chain_data->AddFile(path+"Data/dataB_2lep.root");
  chain_data->AddFile(path+"Data/dataC_2lep.root");
  chain_data->AddFile(path+"Data/dataD_2lep.root");
  chain_data->Process("ZBosonAnalysis.C+","data");
  }

  
  //////////////////////  MC samples

  if (option==2)   {

  // Z+jets inclusive
  TChain* chain_Zee = new TChain("mini");
  chain_Zee->AddFile(path+"MC/mc15_13TeV.361106.PwPy8EG_AZNLOCTEQ6L1_Zee.2lep_raw.root");
  chain_Zee->Process("ZBosonAnalysis.C+","Zee");
  }

  if (option==3)   {
  TChain* chain_Zmumu = new TChain("mini");
  chain_Zmumu->AddFile(path+"MC/mc15_13TeV.361107.PwPy8EG_AZNLOCTEQ6L1_Zmumu.2lep_raw.root");
  chain_Zmumu->Process("ZBosonAnalysis.C+","Zmumu");
  }

  if (option==4)   {
  TChain* chain_Ztautau = new TChain("mini");
  chain_Ztautau->AddFile(path+"MC/mc15_13TeV.361108.PwPy8EG_AZNLOCTEQ6L1_Ztautau.2lep_raw.root");
  chain_Ztautau->Process("ZBosonAnalysis.C+","Ztautau");
  }

  if (option==5)   {
  // W+jets inclusive  
  TChain* chain_Wplusenu = new TChain("mini");
  chain_Wplusenu->AddFile(path+"MC/mc15_13TeV.361100.PwPy8EG_AZNLOCTEQ6L1_Wplusenu.2lep_raw.root");
  chain_Wplusenu->Process("ZBosonAnalysis.C+","Wplusenu");

  TChain* chain_Wplusmunu = new TChain("mini");
  chain_Wplusmunu->AddFile(path+"MC/mc15_13TeV.361101.PwPy8EG_AZNLOCTEQ6L1_Wplusmunu.2lep_raw.root");
  chain_Wplusmunu->Process("ZBosonAnalysis.C+","Wplusmunu");

  TChain* chain_Wplustaunu = new TChain("mini");
  chain_Wplustaunu->AddFile(path+"MC/mc15_13TeV.361102.PwPy8EG_AZNLOCTEQ6L1_Wplustaunu.2lep_raw.root");
  chain_Wplustaunu->Process("ZBosonAnalysis.C+","Wplustaunu");

  TChain* chain_Wminusenu = new TChain("mini");
  chain_Wminusenu->AddFile(path+"MC/mc15_13TeV.361103.PwPy8EG_AZNLOCTEQ6L1_Wminusenu.2lep_raw.root");
  chain_Wminusenu->Process("ZBosonAnalysis.C+","Wminusenu");

  TChain* chain_Wminusmunu = new TChain("mini");
  chain_Wminusmunu->AddFile(path+"MC/mc15_13TeV.361104.PwPy8EG_AZNLOCTEQ6L1_Wminusmunu.2lep_raw.root");
  chain_Wminusmunu->Process("ZBosonAnalysis.C+","Wminusmunu");

  TChain* chain_Wminustaunu = new TChain("mini");
  chain_Wminustaunu->AddFile(path+"MC/mc15_13TeV.361105.PwPy8EG_AZNLOCTEQ6L1_Wminustaunu.2lep_raw.root");
  chain_Wminustaunu->Process("ZBosonAnalysis.C+","Wminustaunu");


  // diboson
  TChain* chain_WWlvlv = new TChain("mini");
  chain_WWlvlv->AddFile(path+"MC/mc15_13TeV.361600.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvlv.2lep_raw.root");
  chain_WWlvlv->Process("ZBosonAnalysis.C+","WWlvlv");

  TChain* chain_WWlvqq = new TChain("mini");
  chain_WWlvqq->AddFile(path+"MC/mc15_13TeV.361606.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvqq.2lep_raw.root");
  chain_WWlvqq->Process("ZBosonAnalysis.C+","WWlvqq");

  TChain* chain_ZZllll = new TChain("mini");
  chain_ZZllll->AddFile(path+"MC/mc15_13TeV.361603.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.2lep_raw.root");
  chain_ZZllll->Process("ZBosonAnalysis.C+","ZZllll");

  TChain* chain_ZZvvll = new TChain("mini");
  chain_ZZvvll->AddFile(path+"MC/mc15_13TeV.361604.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvll_mll4.2lep_raw.root");
  chain_ZZvvll->Process("ZBosonAnalysis.C+","ZZvvll");

  TChain* chain_ZZqqll = new TChain("mini");
  chain_ZZqqll->AddFile(path+"MC/mc15_13TeV.361610.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZqqll_mqq20mll20.2lep_raw.root");
  chain_ZZqqll->Process("ZBosonAnalysis.C+","ZZqqll");

  TChain* chain_WZlvll = new TChain("mini");
  chain_WZlvll->AddFile(path+"MC/mc15_13TeV.361601.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4.2lep_raw.root");
  chain_WZlvll->Process("ZBosonAnalysis.C+","WZlvll");

  TChain* chain_WZlvvv = new TChain("mini");
  chain_WZlvvv->AddFile(path+"MC/mc15_13TeV.361602.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvvv_mll4.2lep_raw.root");
  chain_WZlvvv->Process("ZBosonAnalysis.C+","WZlvvv");

  TChain* chain_WZqqll = new TChain("mini");
  chain_WZqqll->AddFile(path+"MC/mc15_13TeV.361607.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZqqll_mll20.2lep_raw.root");
  chain_WZqqll->Process("ZBosonAnalysis.C+","WZqqll");

  TChain* chain_WZlvqq = new TChain("mini");
  chain_WZlvqq->AddFile(path+"MC/mc15_13TeV.361609.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvqq_mqq20.2lep_raw.root");
  chain_WZlvqq->Process("ZBosonAnalysis.C+","WZlvqq");


  //single top

  TChain* chain_single_top_tchan = new TChain("mini");
  chain_single_top_tchan->AddFile(path+"MC/mc15_13TeV.410011.PwPyEG_P2012_singletop_tchan_lept_top.2lep_raw.root");
  chain_single_top_tchan->Process("ZBosonAnalysis.C+","single_top_tchan");

  TChain* chain_single_antitop_tchan = new TChain("mini");
  chain_single_antitop_tchan->AddFile(path+"MC/mc15_13TeV.410012.PwPyEG_P2012_singletop_tchan_lept_antitop.2lep_raw.root");
  chain_single_antitop_tchan->Process("ZBosonAnalysis.C+","single_antitop_tchan");

  TChain* chain_single_top_schan = new TChain("mini");
  chain_single_top_schan->AddFile(path+"MC/mc15_13TeV.410025.PwPyEG_P2012_SingleTopSchan_noAllHad_top.2lep_raw.root");
  chain_single_top_schan->Process("ZBosonAnalysis.C+","single_top_schan");

  TChain* chain_single_antitop_schan = new TChain("mini");
  chain_single_antitop_schan->AddFile(path+"MC/mc15_13TeV.410026.PwPyEG_P2012_SingleTopSchan_noAllHad_antitop.2lep_raw.root");
  chain_single_antitop_schan->Process("ZBosonAnalysis.C+","single_antitop_schan");

/*
  TChain* chain_single_top_wtchan = new TChain("mini");
  chain_single_top_wtchan->AddFile(path+"MC/mc15_13TeV.410013.PwPyEG_P2012_Wt_inclusive_top.2lep_raw.root");
  chain_single_top_wtchan->Process("ZBosonAnalysis.C+","single_top_wtchan");

  TChain* chain_single_antitop_wtchan = new TChain("mini");
  chain_single_antitop_wtchan->AddFile(path+"MC/mc15_13TeV.410014.PwPyEG_P2012_Wt_inclusive_antitop.2lep_raw.root");
  chain_single_antitop_wtchan->Process("ZBosonAnalysis.C+","single_antitop_wtchan");
*/

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc15_13TeV.410000.PwPyEG_P2012_ttbar_hdamp172p5_nonallhad.2lep_raw.root");
  chain_ttbar_lep->Process("ZBosonAnalysis.C+","ttbar_lep");
  }


/*
// PROOF usage
  if (proof == 1)
  {
    TProof::Open("");

  
    chain_data->SetProof();

  }
*/


}
