//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_ZTauTauAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  TString path = "/eos/user/t/thsteven/OpenData/opentuplepostprocess/renamed/1lep1tau/";
  
  /* The URL to the ATLAS Open Data website repository */
  //  TString path = "http://opendata.atlas.cern/release/samples/";

  //***************************************************************************************************//
  // Adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 4 option for MC (2,3,4,5) and 1 for data (1) which can be run in parallel
  //***************************************************************************************************//

  if (option==1 || option==0)
  {
  //data
  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/data_A.1tau1lep.root");
  chain_data->AddFile(path+"Data/data_B.1tau1lep.root");
  chain_data->AddFile(path+"Data/data_C.1tau1lep.root");
  chain_data->AddFile(path+"Data/data_D.1tau1lep.root");
  chain_data->Process("ZTauTauAnalysis.C+","data");
  }

  
  //////////////////////  MC samples
  if (option==2 || option==0)   {

  //single top
  TChain* chain_single_top_tchan = new TChain("mini");
  chain_single_top_tchan->AddFile(path+"MC/mc_410011.single_top_tchan.1lep1tau.root");
  chain_single_top_tchan->Process("ZTauTauAnalysis.C+","single_top_tchan");

  TChain* chain_single_antitop_tchan = new TChain("mini");
  chain_single_antitop_tchan->AddFile(path+"MC/mc_410012.single_antitop_tchan.1lep1tau.root");
  chain_single_antitop_tchan->Process("ZTauTauAnalysis.C+","single_antitop_tchan");

  TChain* chain_single_top_schan = new TChain("mini");
  chain_single_top_schan->AddFile(path+"MC/mc_410025.single_top_schan.1lep1tau.root");
  chain_single_top_schan->Process("ZTauTauAnalysis.C+","single_top_schan");

  TChain* chain_single_antitop_schan = new TChain("mini");
  chain_single_antitop_schan->AddFile(path+"MC/mc_410026.single_antitop_schan.1lep1tau.root");
  chain_single_antitop_schan->Process("ZTauTauAnalysis.C+","single_antitop_schan");

  TChain* chain_single_top_wtchan = new TChain("mini");
  chain_single_top_wtchan->AddFile(path+"MC/mc_410013.single_top_wtchan.1lep1tau.root");
  chain_single_top_wtchan->Process("ZTauTauAnalysis.C+","single_top_wtchan");

  TChain* chain_single_antitop_wtchan = new TChain("mini");
  chain_single_antitop_wtchan->AddFile(path+"MC/mc_410014.single_antitop_wtchan.1lep1tau.root");
  chain_single_antitop_wtchan->Process("ZTauTauAnalysis.C+","single_antitop_wtchan");

  //ttbar

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc_410000.ttbar_lep.1lep1tau.root");
  chain_ttbar_lep->Process("ZTauTauAnalysis.C+","ttbar_lep");
  }


  if (option==3 || option==0)   {
  // Sherpa Z+jets

TChain* chain_Zmumu_PTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV0_70_BFilter = new TChain("mini");
TChain* chain_Zmumu_PTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV70_140_BFilter = new TChain("mini");
TChain* chain_Zmumu_PTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV140_280_BFilter = new TChain("mini");
TChain* chain_Zmumu_PTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_PTV280_500_BFilter = new TChain("mini");
TChain* chain_Zmumu_PTV500_1000 = new TChain("mini");
TChain* chain_Zmumu_PTV1000_E_CMS = new TChain("mini");
TChain* chain_Zee_PTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_PTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_PTV0_70_BFilter = new TChain("mini");
TChain* chain_Zee_PTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_PTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_PTV70_140_BFilter = new TChain("mini");
TChain* chain_Zee_PTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_PTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_PTV140_280_BFilter = new TChain("mini");
TChain* chain_Zee_PTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_PTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_PTV280_500_BFilter = new TChain("mini");
TChain* chain_Zee_PTV500_1000 = new TChain("mini");
TChain* chain_Zee_PTV1000_E_CMS = new TChain("mini");
TChain* chain_Ztautau_PTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV0_70_BFilter = new TChain("mini");
TChain* chain_Ztautau_PTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV70_140_BFilter = new TChain("mini");
TChain* chain_Ztautau_PTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV140_280_BFilter = new TChain("mini");
TChain* chain_Ztautau_PTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_PTV280_500_BFilter = new TChain("mini");
TChain* chain_Ztautau_PTV500_1000 = new TChain("mini");
TChain* chain_Ztautau_PTV1000_E_CMS = new TChain("mini");


chain_Zmumu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364100.Zmumu_PTV0_70_CVetoBVeto.1lep1tau.root");
chain_Zmumu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364101.Zmumu_PTV0_70_CFilterBVeto.1lep1tau.root");
chain_Zmumu_PTV0_70_BFilter->AddFile(path+"MC/mc_364102.Zmumu_PTV0_70_BFilter.1lep1tau.root");
chain_Zmumu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364103.Zmumu_PTV70_140_CVetoBVeto.1lep1tau.root");
chain_Zmumu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364104.Zmumu_PTV70_140_CFilterBVeto.1lep1tau.root");
chain_Zmumu_PTV70_140_BFilter->AddFile(path+"MC/mc_364105.Zmumu_PTV70_140_BFilter.1lep1tau.root");
chain_Zmumu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364106.Zmumu_PTV140_280_CVetoBVeto.1lep1tau.root");
chain_Zmumu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364107.Zmumu_PTV140_280_CFilterBVeto.1lep1tau.root");
chain_Zmumu_PTV140_280_BFilter->AddFile(path+"MC/mc_364108.Zmumu_PTV140_280_BFilter.1lep1tau.root");
chain_Zmumu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364109.Zmumu_PTV280_500_CVetoBVeto.1lep1tau.root");
chain_Zmumu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364110.Zmumu_PTV280_500_CFilterBVeto.1lep1tau.root");
chain_Zmumu_PTV280_500_BFilter->AddFile(path+"MC/mc_364111.Zmumu_PTV280_500_BFilter.1lep1tau.root");
chain_Zmumu_PTV500_1000->AddFile(path+"MC/mc_364112.Zmumu_PTV500_1000.1lep1tau.root");
chain_Zmumu_PTV1000_E_CMS->AddFile(path+"MC/mc_364113.Zmumu_PTV1000_E_CMS.1lep1tau.root");
chain_Zee_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364114.Zee_PTV0_70_CVetoBVeto.1lep1tau.root");
chain_Zee_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364115.Zee_PTV0_70_CFilterBVeto.1lep1tau.root");
chain_Zee_PTV0_70_BFilter->AddFile(path+"MC/mc_364116.Zee_PTV0_70_BFilter.1lep1tau.root");
chain_Zee_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364117.Zee_PTV70_140_CVetoBVeto.1lep1tau.root");
chain_Zee_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364118.Zee_PTV70_140_CFilterBVeto.1lep1tau.root");
chain_Zee_PTV70_140_BFilter->AddFile(path+"MC/mc_364119.Zee_PTV70_140_BFilter.1lep1tau.root");
chain_Zee_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364120.Zee_PTV140_280_CVetoBVeto.1lep1tau.root");
chain_Zee_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364121.Zee_PTV140_280_CFilterBVeto.1lep1tau.root");
chain_Zee_PTV140_280_BFilter->AddFile(path+"MC/mc_364122.Zee_PTV140_280_BFilter.1lep1tau.root");
chain_Zee_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364123.Zee_PTV280_500_CVetoBVeto.1lep1tau.root");
chain_Zee_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364124.Zee_PTV280_500_CFilterBVeto.1lep1tau.root");
chain_Zee_PTV280_500_BFilter->AddFile(path+"MC/mc_364125.Zee_PTV280_500_BFilter.1lep1tau.root");
chain_Zee_PTV500_1000->AddFile(path+"MC/mc_364126.Zee_PTV500_1000.1lep1tau.root");
chain_Zee_PTV1000_E_CMS->AddFile(path+"MC/mc_364127.Zee_PTV1000_E_CMS.1lep1tau.root");
chain_Ztautau_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364128.Ztautau_PTV0_70_CVetoBVeto.1lep1tau.root");
chain_Ztautau_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364129.Ztautau_PTV0_70_CFilterBVeto.1lep1tau.root");
chain_Ztautau_PTV0_70_BFilter->AddFile(path+"MC/mc_364130.Ztautau_PTV0_70_BFilter.1lep1tau.root");
chain_Ztautau_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364131.Ztautau_PTV70_140_CVetoBVeto.1lep1tau.root");
chain_Ztautau_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364132.Ztautau_PTV70_140_CFilterBVeto.1lep1tau.root");
chain_Ztautau_PTV70_140_BFilter->AddFile(path+"MC/mc_364133.Ztautau_PTV70_140_BFilter.1lep1tau.root");
chain_Ztautau_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364134.Ztautau_PTV140_280_CVetoBVeto.1lep1tau.root");
chain_Ztautau_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364135.Ztautau_PTV140_280_CFilterBVeto.1lep1tau.root");
chain_Ztautau_PTV140_280_BFilter->AddFile(path+"MC/mc_364136.Ztautau_PTV140_280_BFilter.1lep1tau.root");
chain_Ztautau_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364137.Ztautau_PTV280_500_CVetoBVeto.1lep1tau.root");
chain_Ztautau_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364138.Ztautau_PTV280_500_CFilterBVeto.1lep1tau.root");
chain_Ztautau_PTV280_500_BFilter->AddFile(path+"MC/mc_364139.Ztautau_PTV280_500_BFilter.1lep1tau.root");
chain_Ztautau_PTV500_1000->AddFile(path+"MC/mc_364140.Ztautau_PTV500_1000.1lep1tau.root");
chain_Ztautau_PTV1000_E_CMS->AddFile(path+"MC/mc_364141.Ztautau_PTV1000_E_CMS.1lep1tau.root");

chain_Zmumu_PTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV0_70_CVetoBVeto");
chain_Zmumu_PTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV0_70_CFilterBVeto");
chain_Zmumu_PTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Zmumu_PTV0_70_BFilter");
chain_Zmumu_PTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV70_140_CVetoBVeto");
chain_Zmumu_PTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV70_140_CFilterBVeto");
chain_Zmumu_PTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Zmumu_PTV70_140_BFilter");
chain_Zmumu_PTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV140_280_CVetoBVeto");
chain_Zmumu_PTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV140_280_CFilterBVeto");
chain_Zmumu_PTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Zmumu_PTV140_280_BFilter");
chain_Zmumu_PTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV280_500_CVetoBVeto");
chain_Zmumu_PTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu_PTV280_500_CFilterBVeto");
chain_Zmumu_PTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Zmumu_PTV280_500_BFilter");
chain_Zmumu_PTV500_1000->Process("ZTauTauAnalysis.C+","Zmumu_PTV500_1000");
chain_Zmumu_PTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Zmumu_PTV1000");
chain_Zee_PTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV0_70_CVetoBVeto");
chain_Zee_PTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV0_70_CFilterBVeto");
chain_Zee_PTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Zee_PTV0_70_BFilter");
chain_Zee_PTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV70_140_CVetoBVeto");
chain_Zee_PTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV70_140_CFilterBVeto");
chain_Zee_PTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Zee_PTV70_140_BFilter");
chain_Zee_PTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV140_280_CVetoBVeto");
chain_Zee_PTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV140_280_CFilterBVeto");
chain_Zee_PTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Zee_PTV140_280_BFilter");
chain_Zee_PTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV280_500_CVetoBVeto");
chain_Zee_PTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee_PTV280_500_CFilterBVeto");
chain_Zee_PTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Zee_PTV280_500_BFilter");
chain_Zee_PTV500_1000->Process("ZTauTauAnalysis.C+","Zee_PTV500_1000");
chain_Zee_PTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Zee_PTV1000");
chain_Ztautau_PTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV0_70_CVetoBVeto");
chain_Ztautau_PTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV0_70_CFilterBVeto");
chain_Ztautau_PTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Ztautau_PTV0_70_BFilter");
chain_Ztautau_PTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV70_140_CVetoBVeto");
chain_Ztautau_PTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV70_140_CFilterBVeto");
chain_Ztautau_PTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Ztautau_PTV70_140_BFilter");
chain_Ztautau_PTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV140_280_CVetoBVeto");
chain_Ztautau_PTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV140_280_CFilterBVeto");
chain_Ztautau_PTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Ztautau_PTV140_280_BFilter");
chain_Ztautau_PTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV280_500_CVetoBVeto");
chain_Ztautau_PTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau_PTV280_500_CFilterBVeto");
chain_Ztautau_PTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Ztautau_PTV280_500_BFilter");
chain_Ztautau_PTV500_1000->Process("ZTauTauAnalysis.C+","Ztautau_PTV500_1000");
chain_Ztautau_PTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Ztautau_PTV1000");

  }

  if (option==4 || option==0)   {
  // Sherpa W+jets

TChain* chain_Wmunu_PTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV0_70_BFilter = new TChain("mini");
TChain* chain_Wmunu_PTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV70_140_BFilter = new TChain("mini");
TChain* chain_Wmunu_PTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV140_280_BFilter = new TChain("mini");
TChain* chain_Wmunu_PTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_PTV280_500_BFilter = new TChain("mini");
TChain* chain_Wmunu_PTV500_1000 = new TChain("mini");
TChain* chain_Wmunu_PTV1000_E_CMS = new TChain("mini");
TChain* chain_Wenu_PTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_PTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_PTV0_70_BFilter = new TChain("mini");
TChain* chain_Wenu_PTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_PTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_PTV70_140_BFilter = new TChain("mini");
TChain* chain_Wenu_PTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_PTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_PTV140_280_BFilter = new TChain("mini");
TChain* chain_Wenu_PTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_PTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_PTV280_500_BFilter = new TChain("mini");
TChain* chain_Wenu_PTV500_1000 = new TChain("mini");
TChain* chain_Wenu_PTV1000_E_CMS = new TChain("mini");
TChain* chain_Wtaunu_PTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV0_70_BFilter = new TChain("mini");
TChain* chain_Wtaunu_PTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV70_140_BFilter = new TChain("mini");
TChain* chain_Wtaunu_PTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV140_280_BFilter = new TChain("mini");
TChain* chain_Wtaunu_PTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_PTV280_500_BFilter = new TChain("mini");
TChain* chain_Wtaunu_PTV500_1000 = new TChain("mini");
TChain* chain_Wtaunu_PTV1000_E_CM = new TChain("mini");


chain_Wmunu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364156.Wmunu_PTV0_70_CVetoBVeto.1lep1tau.root");
chain_Wmunu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364157.Wmunu_PTV0_70_CFilterBVeto.1lep1tau.root");
chain_Wmunu_PTV0_70_BFilter->AddFile(path+"MC/mc_364158.Wmunu_PTV0_70_BFilter.1lep1tau.root");
chain_Wmunu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364159.Wmunu_PTV70_140_CVetoBVeto.1lep1tau.root");
chain_Wmunu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364160.Wmunu_PTV70_140_CFilterBVeto.1lep1tau.root");
chain_Wmunu_PTV70_140_BFilter->AddFile(path+"MC/mc_364161.Wmunu_PTV70_140_BFilter.1lep1tau.root");
chain_Wmunu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364162.Wmunu_PTV140_280_CVetoBVeto.1lep1tau.root");
chain_Wmunu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364163.Wmunu_PTV140_280_CFilterBVeto.1lep1tau.root");
chain_Wmunu_PTV140_280_BFilter->AddFile(path+"MC/mc_364164.Wmunu_PTV140_280_BFilter.1lep1tau.root");
chain_Wmunu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364165.Wmunu_PTV280_500_CVetoBVeto.1lep1tau.root");
chain_Wmunu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364166.Wmunu_PTV280_500_CFilterBVeto.1lep1tau.root");
chain_Wmunu_PTV280_500_BFilter->AddFile(path+"MC/mc_364167.Wmunu_PTV280_500_BFilter.1lep1tau.root");
chain_Wmunu_PTV500_1000->AddFile(path+"MC/mc_364168.Wmunu_PTV500_1000.1lep1tau.root");
chain_Wmunu_PTV1000_E_CMS->AddFile(path+"MC/mc_364169.Wmunu_PTV1000_E_CMS.1lep1tau.root");
chain_Wenu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364170.Wenu_PTV0_70_CVetoBVeto.1lep1tau.root");
chain_Wenu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364171.Wenu_PTV0_70_CFilterBVeto.1lep1tau.root");
chain_Wenu_PTV0_70_BFilter->AddFile(path+"MC/mc_364172.Wenu_PTV0_70_BFilter.1lep1tau.root");
chain_Wenu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364173.Wenu_PTV70_140_CVetoBVeto.1lep1tau.root");
chain_Wenu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364174.Wenu_PTV70_140_CFilterBVeto.1lep1tau.root");
chain_Wenu_PTV70_140_BFilter->AddFile(path+"MC/mc_364175.Wenu_PTV70_140_BFilter.1lep1tau.root");
chain_Wenu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364176.Wenu_PTV140_280_CVetoBVeto.1lep1tau.root");
chain_Wenu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364177.Wenu_PTV140_280_CFilterBVeto.1lep1tau.root");
chain_Wenu_PTV140_280_BFilter->AddFile(path+"MC/mc_364178.Wenu_PTV140_280_BFilter.1lep1tau.root");
chain_Wenu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364179.Wenu_PTV280_500_CVetoBVeto.1lep1tau.root");
chain_Wenu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364180.Wenu_PTV280_500_CFilterBVeto.1lep1tau.root");
chain_Wenu_PTV280_500_BFilter->AddFile(path+"MC/mc_364181.Wenu_PTV280_500_BFilter.1lep1tau.root");
chain_Wenu_PTV500_1000->AddFile(path+"MC/mc_364182.Wenu_PTV500_1000.1lep1tau.root");
chain_Wenu_PTV1000_E_CMS->AddFile(path+"MC/mc_364183.Wenu_PTV1000_E_CMS.1lep1tau.root");
chain_Wtaunu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364184.Wtaunu_PTV0_70_CVetoBVeto.1lep1tau.root");
chain_Wtaunu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364185.Wtaunu_PTV0_70_CFilterBVeto.1lep1tau.root");
chain_Wtaunu_PTV0_70_BFilter->AddFile(path+"MC/mc_364186.Wtaunu_PTV0_70_BFilter.1lep1tau.root");
chain_Wtaunu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364187.Wtaunu_PTV70_140_CVetoBVeto.1lep1tau.root");
chain_Wtaunu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364188.Wtaunu_PTV70_140_CFilterBVeto.1lep1tau.root");
chain_Wtaunu_PTV70_140_BFilter->AddFile(path+"MC/mc_364189.Wtaunu_PTV70_140_BFilter.1lep1tau.root");
chain_Wtaunu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364190.Wtaunu_PTV140_280_CVetoBVeto.1lep1tau.root");
chain_Wtaunu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364191.Wtaunu_PTV140_280_CFilterBVeto.1lep1tau.root");
chain_Wtaunu_PTV140_280_BFilter->AddFile(path+"MC/mc_364192.Wtaunu_PTV140_280_BFilter.1lep1tau.root");
chain_Wtaunu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364193.Wtaunu_PTV280_500_CVetoBVeto.1lep1tau.root");
chain_Wtaunu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364194.Wtaunu_PTV280_500_CFilterBVeto.1lep1tau.root");
chain_Wtaunu_PTV280_500_BFilter->AddFile(path+"MC/mc_364195.Wtaunu_PTV280_500_BFilter.1lep1tau.root");
chain_Wtaunu_PTV500_1000->AddFile(path+"MC/mc_364196.Wtaunu_PTV500_1000.1lep1tau.root");
chain_Wtaunu_PTV1000_E_CM->AddFile(path+"MC/mc_364197.Wtaunu_PTV1000_E_CMS.1lep1tau.root");


chain_Wmunu_PTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV0_70_CVetoBVeto");
chain_Wmunu_PTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV0_70_CFilterBVeto");
chain_Wmunu_PTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Wmunu_PTV0_70_BFilter");
chain_Wmunu_PTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV70_140_CVetoBVeto");
chain_Wmunu_PTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV70_140_CFilterBVeto");
chain_Wmunu_PTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Wmunu_PTV70_140_BFilter");
chain_Wmunu_PTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV140_280_CVetoBVeto");
chain_Wmunu_PTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV140_280_CFilterBVeto");
chain_Wmunu_PTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Wmunu_PTV140_280_BFilter");
chain_Wmunu_PTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV280_500_CVetoBVeto");
chain_Wmunu_PTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmunu_PTV280_500_CFilterBVeto");
chain_Wmunu_PTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Wmunu_PTV280_500_BFilter");
chain_Wmunu_PTV500_1000->Process("ZTauTauAnalysis.C+","Wmunu_PTV500_1000");
chain_Wmunu_PTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Wmunu_PTV1000");
chain_Wenu_PTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV0_70_CVetoBVeto");
chain_Wenu_PTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV0_70_CFilterBVeto");
chain_Wenu_PTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Wenu_PTV0_70_BFilter");
chain_Wenu_PTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV70_140_CVetoBVeto");
chain_Wenu_PTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV70_140_CFilterBVeto");
chain_Wenu_PTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Wenu_PTV70_140_BFilter");
chain_Wenu_PTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV140_280_CVetoBVeto");
chain_Wenu_PTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV140_280_CFilterBVeto");
chain_Wenu_PTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Wenu_PTV140_280_BFilter");
chain_Wenu_PTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV280_500_CVetoBVeto");
chain_Wenu_PTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wenu_PTV280_500_CFilterBVeto");
chain_Wenu_PTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Wenu_PTV280_500_BFilter");
chain_Wenu_PTV500_1000->Process("ZTauTauAnalysis.C+","Wenu_PTV500_1000");
chain_Wenu_PTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Wenu_PTV1000");
chain_Wtaunu_PTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV0_70_CVetoBVeto");
chain_Wtaunu_PTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV0_70_CFilterBVeto");
chain_Wtaunu_PTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Wtaunu_PTV0_70_BFilter");
chain_Wtaunu_PTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV70_140_CVetoBVeto");
chain_Wtaunu_PTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV70_140_CFilterBVeto");
chain_Wtaunu_PTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Wtaunu_PTV70_140_BFilter");
chain_Wtaunu_PTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV140_280_CVetoBVeto");
chain_Wtaunu_PTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV140_280_CFilterBVeto");
chain_Wtaunu_PTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Wtaunu_PTV140_280_BFilter");
chain_Wtaunu_PTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV280_500_CVetoBVeto");
chain_Wtaunu_PTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtaunu_PTV280_500_CFilterBVeto");
chain_Wtaunu_PTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Wtaunu_PTV280_500_BFilter");
chain_Wtaunu_PTV500_1000->Process("ZTauTauAnalysis.C+","Wtaunu_PTV500_1000");
chain_Wtaunu_PTV1000_E_CM->Process("ZTauTauAnalysis.C+","Wtaunu_PTV1000");

}


/*
// For now, the use of PROOF is commented out, to be added...
  if (proof == 1)
  {
    TProof::Open("");

  
    chain_data->SetProof();

  }
*/


}
