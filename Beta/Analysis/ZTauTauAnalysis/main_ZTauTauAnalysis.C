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
  TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/1lep1tau/";
  
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
  chain_data->AddFile(path+"Data/dataA_1tau1lep.root");
  chain_data->AddFile(path+"Data/dataB_1tau1lep.root");
  chain_data->AddFile(path+"Data/dataC_1tau1lep.root");
  chain_data->AddFile(path+"Data/dataD_1tau1lep.root");
  chain_data->Process("ZTauTauAnalysis.C+","data");
  }

  
  //////////////////////  MC samples
  if (option==2 || option==0)   {

  //single top
  TChain* chain_single_top_tchan = new TChain("mini");
  chain_single_top_tchan->AddFile(path+"MC/mc15_13TeV.410011.PwPyEG_P2012_singletop_tchan_lept_top.1lep1tau_raw.root");
  chain_single_top_tchan->Process("ZTauTauAnalysis.C+","single_top_tchan");

  TChain* chain_single_antitop_tchan = new TChain("mini");
  chain_single_antitop_tchan->AddFile(path+"MC/mc15_13TeV.410012.PwPyEG_P2012_singletop_tchan_lept_antitop.1lep1tau_raw.root");
  chain_single_antitop_tchan->Process("ZTauTauAnalysis.C+","single_antitop_tchan");

  TChain* chain_single_top_schan = new TChain("mini");
  chain_single_top_schan->AddFile(path+"MC/mc15_13TeV.410025.PwPyEG_P2012_SingleTopSchan_noAllHad_top.1lep1tau_raw.root");
  chain_single_top_schan->Process("ZTauTauAnalysis.C+","single_top_schan");

  TChain* chain_single_antitop_schan = new TChain("mini");
  chain_single_antitop_schan->AddFile(path+"MC/mc15_13TeV.410026.PwPyEG_P2012_SingleTopSchan_noAllHad_antitop.1lep1tau_raw.root");
  chain_single_antitop_schan->Process("ZTauTauAnalysis.C+","single_antitop_schan");

  TChain* chain_single_top_wtchan = new TChain("mini");
  chain_single_top_wtchan->AddFile(path+"MC/mc15_13TeV.410013.PwPyEG_P2012_Wt_inclusive_top.1lep1tau_raw.root");
  chain_single_top_wtchan->Process("ZTauTauAnalysis.C+","single_top_wtchan");

  TChain* chain_single_antitop_wtchan = new TChain("mini");
  chain_single_antitop_wtchan->AddFile(path+"MC/mc15_13TeV.410014.PwPyEG_P2012_Wt_inclusive_antitop.1lep1tau_raw.root");
  chain_single_antitop_wtchan->Process("ZTauTauAnalysis.C+","single_antitop_wtchan");

  //ttbar

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc15_13TeV.410000.PwPyEG_P2012_ttbar_hdamp172p5_nonallhad.1lep1tau_raw.root");
  chain_ttbar_lep->Process("ZTauTauAnalysis.C+","ttbar_lep");
  }


  if (option==3 || option==0)   {
  // Sherpa Z+jets

TChain* chain_Zmumu_MAXHTPTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV0_70_BFilter = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV70_140_BFilter = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV140_280_BFilter = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV280_500_BFilter = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV500_1000 = new TChain("mini");
TChain* chain_Zmumu_MAXHTPTV1000_E_CMS = new TChain("mini");
TChain* chain_Zee_MAXHTPTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV0_70_BFilter = new TChain("mini");
TChain* chain_Zee_MAXHTPTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV70_140_BFilter = new TChain("mini");
TChain* chain_Zee_MAXHTPTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV140_280_BFilter = new TChain("mini");
TChain* chain_Zee_MAXHTPTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Zee_MAXHTPTV280_500_BFilter = new TChain("mini");
TChain* chain_Zee_MAXHTPTV500_1000 = new TChain("mini");
TChain* chain_Zee_MAXHTPTV1000_E_CMS = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV0_70_BFilter = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV70_140_BFilter = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV140_280_BFilter = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV280_500_BFilter = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV500_1000 = new TChain("mini");
TChain* chain_Ztautau_MAXHTPTV1000_E_CMS = new TChain("mini");


chain_Zmumu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364100.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CVetoBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364101.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CFilterBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364102.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_BFilter.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364103.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CVetoBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364104.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CFilterBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364105.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_BFilter.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364106.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CVetoBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364107.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CFilterBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364108.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_BFilter.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364109.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CVetoBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364110.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CFilterBVeto.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364111.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_BFilter.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364112.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV500_1000.1lep1tau_raw.root");
chain_Zmumu_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364113.Sh_221_NNPDF30NNLO_Zmumu_MAXHTPTV1000_E_CMS.1lep1tau_raw.root");
chain_Zee_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364114.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CVetoBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364115.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CFilterBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364116.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_BFilter.1lep1tau_raw.root");
chain_Zee_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364117.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CVetoBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364118.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CFilterBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364119.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_BFilter.1lep1tau_raw.root");
chain_Zee_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364120.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CVetoBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364121.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CFilterBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364122.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_BFilter.1lep1tau_raw.root");
chain_Zee_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364123.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CVetoBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364124.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CFilterBVeto.1lep1tau_raw.root");
chain_Zee_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364125.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_BFilter.1lep1tau_raw.root");
chain_Zee_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364126.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV500_1000.1lep1tau_raw.root");
chain_Zee_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364127.Sh_221_NNPDF30NNLO_Zee_MAXHTPTV1000_E_CMS.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364128.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CVetoBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364129.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CFilterBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364130.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_BFilter.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364131.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CVetoBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364132.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CFilterBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364133.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_BFilter.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364134.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CVetoBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364135.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CFilterBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364136.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_BFilter.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364137.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CVetoBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364138.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CFilterBVeto.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364139.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_BFilter.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364140.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV500_1000.1lep1tau_raw.root");
chain_Ztautau_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364141.Sh_221_NNPDF30NNLO_Ztautau_MAXHTPTV1000_E_CMS.1lep1tau_raw.root");

chain_Zmumu_MAXHTPTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu0_70CVetoBVeto");
chain_Zmumu_MAXHTPTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu0_70CFilterBVeto");
chain_Zmumu_MAXHTPTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Zmumu0_70BFilter");
chain_Zmumu_MAXHTPTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu70_140CVetoBVeto");
chain_Zmumu_MAXHTPTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu70_140CFilterBVeto");
chain_Zmumu_MAXHTPTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Zmumu70_140BFilter");
chain_Zmumu_MAXHTPTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu140_280CVetoBVeto");
chain_Zmumu_MAXHTPTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu140_280CFilterBVeto");
chain_Zmumu_MAXHTPTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Zmumu140_280BFilter");
chain_Zmumu_MAXHTPTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zmumu280_500CVetoBVeto");
chain_Zmumu_MAXHTPTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zmumu280_500CFilterBVeto");
chain_Zmumu_MAXHTPTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Zmumu280_500BFilter");
chain_Zmumu_MAXHTPTV500_1000->Process("ZTauTauAnalysis.C+","Zmumu500_1000");
chain_Zmumu_MAXHTPTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Zmumu1000");
chain_Zee_MAXHTPTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee0_70CVetoBVeto");
chain_Zee_MAXHTPTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee0_70CFilterBVeto");
chain_Zee_MAXHTPTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Zee0_70BFilter");
chain_Zee_MAXHTPTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee70_140CVetoBVeto");
chain_Zee_MAXHTPTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee70_140CFilterBVeto");
chain_Zee_MAXHTPTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Zee70_140BFilter");
chain_Zee_MAXHTPTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee140_280CVetoBVeto");
chain_Zee_MAXHTPTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee140_280CFilterBVeto");
chain_Zee_MAXHTPTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Zee140_280BFilter");
chain_Zee_MAXHTPTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Zee280_500CVetoBVeto");
chain_Zee_MAXHTPTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Zee280_500CFilterBVeto");
chain_Zee_MAXHTPTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Zee280_500BFilter");
chain_Zee_MAXHTPTV500_1000->Process("ZTauTauAnalysis.C+","Zee500_1000");
chain_Zee_MAXHTPTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Zee1000");
chain_Ztautau_MAXHTPTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau0_70CVetoBVeto");
chain_Ztautau_MAXHTPTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau0_70CFilterBVeto");
chain_Ztautau_MAXHTPTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Ztautau0_70BFilter");
chain_Ztautau_MAXHTPTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau70_140CVetoBVeto");
chain_Ztautau_MAXHTPTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau70_140CFilterBVeto");
chain_Ztautau_MAXHTPTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Ztautau70_140BFilter");
chain_Ztautau_MAXHTPTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau140_280CVetoBVeto");
chain_Ztautau_MAXHTPTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau140_280CFilterBVeto");
chain_Ztautau_MAXHTPTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Ztautau140_280BFilter");
chain_Ztautau_MAXHTPTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Ztautau280_500CVetoBVeto");
chain_Ztautau_MAXHTPTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Ztautau280_500CFilterBVeto");
chain_Ztautau_MAXHTPTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Ztautau280_500BFilter");
chain_Ztautau_MAXHTPTV500_1000->Process("ZTauTauAnalysis.C+","Ztautau500_1000");
chain_Ztautau_MAXHTPTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Ztautau1000");

  }

  if (option==4 || option==0)   {
  // Sherpa W+jets

TChain* chain_Wmunu_MAXHTPTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV0_70_BFilter = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV70_140_BFilter = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV140_280_BFilter = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV280_500_BFilter = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV500_1000 = new TChain("mini");
TChain* chain_Wmunu_MAXHTPTV1000_E_CMS = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV0_70_BFilter = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV70_140_BFilter = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV140_280_BFilter = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV280_500_BFilter = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV500_1000 = new TChain("mini");
TChain* chain_Wenu_MAXHTPTV1000_E_CMS = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV0_70_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV0_70_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV0_70_BFilter = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV70_140_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV70_140_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV70_140_BFilter = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV140_280_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV140_280_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV140_280_BFilter = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV280_500_CVetoBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV280_500_CFilterBVeto = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV280_500_BFilter = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV500_1000 = new TChain("mini");
TChain* chain_Wtaunu_MAXHTPTV1000_E_CM = new TChain("mini");


chain_Wmunu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364156.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CVetoBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364157.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CFilterBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364158.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_BFilter.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364159.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CVetoBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364160.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CFilterBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364161.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_BFilter.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364162.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CVetoBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364163.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CFilterBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364164.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_BFilter.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364165.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CVetoBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364166.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CFilterBVeto.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364167.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_BFilter.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364168.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV500_1000.1lep1tau_raw.root");
chain_Wmunu_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364169.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV1000_E_CMS.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364170.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CVetoBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364171.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CFilterBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364172.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_BFilter.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364173.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CVetoBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364174.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CFilterBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364175.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_BFilter.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364176.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CVetoBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364177.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CFilterBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364178.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_BFilter.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364179.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CVetoBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364180.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CFilterBVeto.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364181.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_BFilter.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364182.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV500_1000.1lep1tau_raw.root");
chain_Wenu_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364183.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV1000_E_CMS.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364184.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CVetoBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364185.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CFilterBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364186.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_BFilter.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364187.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CVetoBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364188.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CFilterBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364189.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_BFilter.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364190.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CVetoBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364191.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CFilterBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364192.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_BFilter.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364193.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CVetoBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364194.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CFilterBVeto.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364195.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_BFilter.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364196.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV500_1000.1lep1tau_raw.root");
chain_Wtaunu_MAXHTPTV1000_E_CM->AddFile(path+"MC/mc15_13TeV.364197.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV1000_E_CMS.1lep1tau_raw.root");


chain_Wmunu_MAXHTPTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmu0_70CVetoBVeto");
chain_Wmunu_MAXHTPTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmu0_70CFilterBVeto");
chain_Wmunu_MAXHTPTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Wmu0_70BFilter");
chain_Wmunu_MAXHTPTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmu70_140CVetoBVeto");
chain_Wmunu_MAXHTPTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmu70_140CFilterBVeto");
chain_Wmunu_MAXHTPTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Wmu70_140BFilter");
chain_Wmunu_MAXHTPTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmu140_280CVetoBVeto");
chain_Wmunu_MAXHTPTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmu140_280CFilterBVeto");
chain_Wmunu_MAXHTPTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Wmu140_280BFilter");
chain_Wmunu_MAXHTPTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wmu280_500CVetoBVeto");
chain_Wmunu_MAXHTPTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wmu280_500CFilterBVeto");
chain_Wmunu_MAXHTPTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Wmu280_500BFilter");
chain_Wmunu_MAXHTPTV500_1000->Process("ZTauTauAnalysis.C+","Wmu500_1000");
chain_Wmunu_MAXHTPTV1000_E_CMS->Process("ZTauTauAnalysis.C+","Wmu1000");
chain_Wenu_MAXHTPTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","We0_70CVetoBVeto");
chain_Wenu_MAXHTPTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","We0_70CFilterBVeto");
chain_Wenu_MAXHTPTV0_70_BFilter->Process("ZTauTauAnalysis.C+","We0_70BFilter");
chain_Wenu_MAXHTPTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","We70_140CVetoBVeto");
chain_Wenu_MAXHTPTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","We70_140CFilterBVeto");
chain_Wenu_MAXHTPTV70_140_BFilter->Process("ZTauTauAnalysis.C+","We70_140BFilter");
chain_Wenu_MAXHTPTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","We140_280CVetoBVeto");
chain_Wenu_MAXHTPTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","We140_280CFilterBVeto");
chain_Wenu_MAXHTPTV140_280_BFilter->Process("ZTauTauAnalysis.C+","We140_280BFilter");
chain_Wenu_MAXHTPTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","We280_500CVetoBVeto");
chain_Wenu_MAXHTPTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","We280_500CFilterBVeto");
chain_Wenu_MAXHTPTV280_500_BFilter->Process("ZTauTauAnalysis.C+","We280_500BFilter");
chain_Wenu_MAXHTPTV500_1000->Process("ZTauTauAnalysis.C+","We500_1000");
chain_Wenu_MAXHTPTV1000_E_CMS->Process("ZTauTauAnalysis.C+","We1000");
chain_Wtaunu_MAXHTPTV0_70_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtau0_70CVetoBVeto");
chain_Wtaunu_MAXHTPTV0_70_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtau0_70CFilterBVeto");
chain_Wtaunu_MAXHTPTV0_70_BFilter->Process("ZTauTauAnalysis.C+","Wtau0_70BFilter");
chain_Wtaunu_MAXHTPTV70_140_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtau70_140CVetoBVeto");
chain_Wtaunu_MAXHTPTV70_140_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtau70_140CFilterBVeto");
chain_Wtaunu_MAXHTPTV70_140_BFilter->Process("ZTauTauAnalysis.C+","Wtau70_140BFilter");
chain_Wtaunu_MAXHTPTV140_280_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtau140_280CVetoBVeto");
chain_Wtaunu_MAXHTPTV140_280_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtau140_280CFilterBVeto");
chain_Wtaunu_MAXHTPTV140_280_BFilter->Process("ZTauTauAnalysis.C+","Wtau140_280BFilter");
chain_Wtaunu_MAXHTPTV280_500_CVetoBVeto->Process("ZTauTauAnalysis.C+","Wtau280_500CVetoBVeto");
chain_Wtaunu_MAXHTPTV280_500_CFilterBVeto->Process("ZTauTauAnalysis.C+","Wtau280_500CFilterBVeto");
chain_Wtaunu_MAXHTPTV280_500_BFilter->Process("ZTauTauAnalysis.C+","Wtau280_500BFilter");
chain_Wtaunu_MAXHTPTV500_1000->Process("ZTauTauAnalysis.C+","Wtau500_1000");
chain_Wtaunu_MAXHTPTV1000_E_CM->Process("ZTauTauAnalysis.C+","Wtau1000");

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
