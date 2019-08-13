//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_WBosonAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/1lep/";
  
  /* The URL to the ATLAS Open Data website repository */
  //  TString path = "http://opendata.atlas.cern/release/samples/";

  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 4 options for MC (2,3,4,5) and 4 for data (11,12,13,14) which can be run in parallel
  // If using the options (11,12,13,14) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//


  if (option==11 || option==0){
  TChain* chain_dataA = new TChain("mini");
  chain_dataA->AddFile(path+"Data/dataA_1lep.root");
  chain_dataA->Process("WBosonAnalysis.C+","dataA");
  }

  if (option==12 || option==0){
  TChain* chain_dataB = new TChain("mini");
  chain_dataB->AddFile(path+"Data/dataB_1lep.root");
  chain_dataB->Process("WBosonAnalysis.C+","dataB");
  }

  if (option==13 || option==0){
  TChain* chain_dataC = new TChain("mini");
  chain_dataC->AddFile(path+"Data/dataC_1lep.root");
  chain_dataC->Process("WBosonAnalysis.C+","dataC");
  }

  if (option==14 || option==0){
  TChain* chain_dataD = new TChain("mini");
  chain_dataD->AddFile(path+"Data/dataD_1lep.root");
  chain_dataD->Process("WBosonAnalysis.C+","dataD");
  }


  
  //////////////////////  MC samples

  if (option==2 || option==0)   {
  // diboson
  TChain* chain_WWlvlv = new TChain("mini");
  chain_WWlvlv->AddFile(path+"MC/mc15_13TeV.361600.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvlv.1lep_raw.root");
  chain_WWlvlv->Process("WBosonAnalysis.C+","WWlvlv");

  TChain* chain_WWlvqq = new TChain("mini");
  chain_WWlvqq->AddFile(path+"MC/mc15_13TeV.361606.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WWlvqq.1lep_raw.root");
  chain_WWlvqq->Process("WBosonAnalysis.C+","WWlvqq");

  TChain* chain_ZZllll = new TChain("mini");
  chain_ZZllll->AddFile(path+"MC/mc15_13TeV.361603.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.1lep_raw.root");
  chain_ZZllll->Process("WBosonAnalysis.C+","ZZllll");

  TChain* chain_ZZvvll = new TChain("mini");
  chain_ZZvvll->AddFile(path+"MC/mc15_13TeV.361604.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZvvll_mll4.1lep_raw.root");
  chain_ZZvvll->Process("WBosonAnalysis.C+","ZZvvll");

  TChain* chain_ZZqqll = new TChain("mini");
  chain_ZZqqll->AddFile(path+"MC/mc15_13TeV.361610.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZqqll_mqq20mll20.1lep_raw.root");
  chain_ZZqqll->Process("WBosonAnalysis.C+","ZZqqll");

  TChain* chain_WZlvll = new TChain("mini");
  chain_WZlvll->AddFile(path+"MC/mc15_13TeV.361601.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4.1lep_raw.root");
  chain_WZlvll->Process("WBosonAnalysis.C+","WZlvll");

  TChain* chain_WZlvvv = new TChain("mini");
  chain_WZlvvv->AddFile(path+"MC/mc15_13TeV.361602.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvvv_mll4.1lep_raw.root");
  chain_WZlvvv->Process("WBosonAnalysis.C+","WZlvvv");

  TChain* chain_WZqqll = new TChain("mini");
  chain_WZqqll->AddFile(path+"MC/mc15_13TeV.361607.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZqqll_mll20.1lep_raw.root");
  chain_WZqqll->Process("WBosonAnalysis.C+","WZqqll");

  TChain* chain_WZlvqq = new TChain("mini");
  chain_WZlvqq->AddFile(path+"MC/mc15_13TeV.361609.PwPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvqq_mqq20.1lep_raw.root");
  chain_WZlvqq->Process("WBosonAnalysis.C+","WZlvqq");

  // Z+jets inclusive
  TChain* chain_Z_ee = new TChain("mini");
  chain_Z_ee->AddFile(path+"MC/mc15_13TeV.361106.PwPy8EG_AZNLOCTEQ6L1_Zee.1lep_raw.root");
  chain_Z_ee->Process("WBosonAnalysis.C+","Z_ee");
  
  TChain* chain_Z_mumu = new TChain("mini");
  chain_Z_mumu->AddFile(path+"MC/mc15_13TeV.361107.PwPy8EG_AZNLOCTEQ6L1_Zmumu.1lep_raw.root");
  chain_Z_mumu->Process("WBosonAnalysis.C+","Z_mumu");

  TChain* chain_Z_tautau = new TChain("mini");
  chain_Z_tautau->AddFile(path+"MC/mc15_13TeV.361108.PwPy8EG_AZNLOCTEQ6L1_Ztautau.1lep_raw.root");
  chain_Z_tautau->Process("WBosonAnalysis.C+","Z_tautau");
  
  }

  if (option==3 || option==0)   {
  //single top
  TChain* chain_single_top_tchan = new TChain("mini");
  chain_single_top_tchan->AddFile(path+"MC/mc15_13TeV.410011.PwPyEG_P2012_singletop_tchan_lept_top.1lep_raw.root");
  chain_single_top_tchan->Process("WBosonAnalysis.C+","single_top_tchan");

  TChain* chain_single_antitop_tchan = new TChain("mini");
  chain_single_antitop_tchan->AddFile(path+"MC/mc15_13TeV.410012.PwPyEG_P2012_singletop_tchan_lept_antitop.1lep_raw.root");
  chain_single_antitop_tchan->Process("WBosonAnalysis.C+","single_antitop_tchan");

  TChain* chain_single_top_schan = new TChain("mini");
  chain_single_top_schan->AddFile(path+"MC/mc15_13TeV.410025.PwPyEG_P2012_SingleTopSchan_noAllHad_top.1lep_raw.root");
  chain_single_top_schan->Process("WBosonAnalysis.C+","single_top_schan");

  TChain* chain_single_antitop_schan = new TChain("mini");
  chain_single_antitop_schan->AddFile(path+"MC/mc15_13TeV.410026.PwPyEG_P2012_SingleTopSchan_noAllHad_antitop.1lep_raw.root");
  chain_single_antitop_schan->Process("WBosonAnalysis.C+","single_antitop_schan");

  TChain* chain_single_top_wtchan = new TChain("mini");
  chain_single_top_wtchan->AddFile(path+"MC/mc15_13TeV.410013.PwPyEG_P2012_Wt_inclusive_top.1lep_raw.root");
  chain_single_top_wtchan->Process("WBosonAnalysis.C+","single_top_wtchan");

  TChain* chain_single_antitop_wtchan = new TChain("mini");
  chain_single_antitop_wtchan->AddFile(path+"MC/mc15_13TeV.410014.PwPyEG_P2012_Wt_inclusive_antitop.1lep_raw.root");
  chain_single_antitop_wtchan->Process("WBosonAnalysis.C+","single_antitop_wtchan");

  //ttbar
  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc15_13TeV.410000.PwPyEG_P2012_ttbar_hdamp172p5_nonallhad.1lep_raw.root");
  chain_ttbar_lep->Process("WBosonAnalysis.C+","ttbar_lep");

  } // option 3


  // Sherpa W+jets sliced samples
  if (option > 40 || option==0)   {

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

	    
chain_Wmunu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364156.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CVetoBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364157.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CFilterBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364158.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_BFilter.1lep_raw.root");
chain_Wmunu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364159.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CVetoBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364160.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CFilterBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364161.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_BFilter.1lep_raw.root");
chain_Wmunu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364162.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CVetoBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364163.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CFilterBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364164.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_BFilter.1lep_raw.root");
chain_Wmunu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364165.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CVetoBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364166.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CFilterBVeto.1lep_raw.root");
chain_Wmunu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364167.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_BFilter.1lep_raw.root");
chain_Wmunu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364168.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV500_1000.1lep_raw.root");
chain_Wmunu_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364169.Sh_221_NNPDF30NNLO_Wmunu_MAXHTPTV1000_E_CMS.1lep_raw.root");
chain_Wenu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364170.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CVetoBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364171.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CFilterBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364172.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_BFilter.1lep_raw.root");
chain_Wenu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364173.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CVetoBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364174.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CFilterBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364175.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_BFilter.1lep_raw.root");
chain_Wenu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364176.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CVetoBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364177.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CFilterBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364178.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_BFilter.1lep_raw.root");
chain_Wenu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364179.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CVetoBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364180.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CFilterBVeto.1lep_raw.root");
chain_Wenu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364181.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_BFilter.1lep_raw.root");
chain_Wenu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364182.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV500_1000.1lep_raw.root");
chain_Wenu_MAXHTPTV1000_E_CMS->AddFile(path+"MC/mc15_13TeV.364183.Sh_221_NNPDF30NNLO_Wenu_MAXHTPTV1000_E_CMS.1lep_raw.root");
chain_Wtaunu_MAXHTPTV0_70_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364184.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CVetoBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV0_70_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364185.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CFilterBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV0_70_BFilter->AddFile(path+"MC/mc15_13TeV.364186.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_BFilter.1lep_raw.root");
chain_Wtaunu_MAXHTPTV70_140_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364187.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CVetoBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV70_140_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364188.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CFilterBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV70_140_BFilter->AddFile(path+"MC/mc15_13TeV.364189.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_BFilter.1lep_raw.root");
chain_Wtaunu_MAXHTPTV140_280_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364190.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CVetoBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV140_280_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364191.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CFilterBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV140_280_BFilter->AddFile(path+"MC/mc15_13TeV.364192.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_BFilter.1lep_raw.root");
chain_Wtaunu_MAXHTPTV280_500_CVetoBVeto->AddFile(path+"MC/mc15_13TeV.364193.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CVetoBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV280_500_CFilterBVeto->AddFile(path+"MC/mc15_13TeV.364194.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CFilterBVeto.1lep_raw.root");
chain_Wtaunu_MAXHTPTV280_500_BFilter->AddFile(path+"MC/mc15_13TeV.364195.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_BFilter.1lep_raw.root");
chain_Wtaunu_MAXHTPTV500_1000->AddFile(path+"MC/mc15_13TeV.364196.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV500_1000.1lep_raw.root");
chain_Wtaunu_MAXHTPTV1000_E_CM->AddFile(path+"MC/mc15_13TeV.364197.Sh_221_NNPDF30NNLO_Wtaunu_MAXHTPTV1000_E_CMS.1lep_raw.root");


 if (option == 41 || option==0)   {
chain_Wmunu_MAXHTPTV0_70_CVetoBVeto->Process("WBosonAnalysis.C+","Wmu0_70CVetoBVeto");
chain_Wmunu_MAXHTPTV0_70_CFilterBVeto->Process("WBosonAnalysis.C+","Wmu0_70CFilterBVeto");
chain_Wmunu_MAXHTPTV0_70_BFilter->Process("WBosonAnalysis.C+","Wmu0_70BFilter");
chain_Wmunu_MAXHTPTV70_140_CVetoBVeto->Process("WBosonAnalysis.C+","Wmu70_140CVetoBVeto");
chain_Wmunu_MAXHTPTV70_140_CFilterBVeto->Process("WBosonAnalysis.C+","Wmu70_140CFilterBVeto");
chain_Wmunu_MAXHTPTV70_140_BFilter->Process("WBosonAnalysis.C+","Wmu70_140BFilter");
chain_Wmunu_MAXHTPTV140_280_CVetoBVeto->Process("WBosonAnalysis.C+","Wmu140_280CVetoBVeto");
chain_Wmunu_MAXHTPTV140_280_CFilterBVeto->Process("WBosonAnalysis.C+","Wmu140_280CFilterBVeto");
chain_Wmunu_MAXHTPTV140_280_BFilter->Process("WBosonAnalysis.C+","Wmu140_280BFilter");
chain_Wmunu_MAXHTPTV280_500_CVetoBVeto->Process("WBosonAnalysis.C+","Wmu280_500CVetoBVeto");
 }

 if (option == 42 || option==0)   {
chain_Wmunu_MAXHTPTV280_500_CFilterBVeto->Process("WBosonAnalysis.C+","Wmu280_500CFilterBVeto");
chain_Wmunu_MAXHTPTV280_500_BFilter->Process("WBosonAnalysis.C+","Wmu280_500BFilter");
chain_Wmunu_MAXHTPTV500_1000->Process("WBosonAnalysis.C+","Wmu500_1000");
chain_Wmunu_MAXHTPTV1000_E_CMS->Process("WBosonAnalysis.C+","Wmu1000");
chain_Wenu_MAXHTPTV0_70_CVetoBVeto->Process("WBosonAnalysis.C+","We0_70CVetoBVeto");
chain_Wenu_MAXHTPTV0_70_CFilterBVeto->Process("WBosonAnalysis.C+","We0_70CFilterBVeto");
chain_Wenu_MAXHTPTV0_70_BFilter->Process("WBosonAnalysis.C+","We0_70BFilter");
chain_Wenu_MAXHTPTV70_140_CVetoBVeto->Process("WBosonAnalysis.C+","We70_140CVetoBVeto");
chain_Wenu_MAXHTPTV70_140_CFilterBVeto->Process("WBosonAnalysis.C+","We70_140CFilterBVeto");
chain_Wenu_MAXHTPTV70_140_BFilter->Process("WBosonAnalysis.C+","We70_140BFilter");
 }

  if (option == 43 || option==0)   {
chain_Wenu_MAXHTPTV140_280_CVetoBVeto->Process("WBosonAnalysis.C+","We140_280CVetoBVeto");
chain_Wenu_MAXHTPTV140_280_CFilterBVeto->Process("WBosonAnalysis.C+","We140_280CFilterBVeto");
chain_Wenu_MAXHTPTV140_280_BFilter->Process("WBosonAnalysis.C+","We140_280BFilter");
chain_Wenu_MAXHTPTV280_500_CVetoBVeto->Process("WBosonAnalysis.C+","We280_500CVetoBVeto");
chain_Wenu_MAXHTPTV280_500_CFilterBVeto->Process("WBosonAnalysis.C+","We280_500CFilterBVeto");
chain_Wenu_MAXHTPTV280_500_BFilter->Process("WBosonAnalysis.C+","We280_500BFilter");
chain_Wenu_MAXHTPTV500_1000->Process("WBosonAnalysis.C+","We500_1000");
chain_Wenu_MAXHTPTV1000_E_CMS->Process("WBosonAnalysis.C+","We1000");
chain_Wtaunu_MAXHTPTV0_70_CVetoBVeto->Process("WBosonAnalysis.C+","Wtau0_70CVetoBVeto");
chain_Wtaunu_MAXHTPTV0_70_CFilterBVeto->Process("WBosonAnalysis.C+","Wtau0_70CFilterBVeto");
  }

   if (option == 44 || option==0)   {
chain_Wtaunu_MAXHTPTV0_70_BFilter->Process("WBosonAnalysis.C+","Wtau0_70BFilter");
chain_Wtaunu_MAXHTPTV70_140_CVetoBVeto->Process("WBosonAnalysis.C+","Wtau70_140CVetoBVeto");
chain_Wtaunu_MAXHTPTV70_140_CFilterBVeto->Process("WBosonAnalysis.C+","Wtau70_140CFilterBVeto");
chain_Wtaunu_MAXHTPTV70_140_BFilter->Process("WBosonAnalysis.C+","Wtau70_140BFilter");
chain_Wtaunu_MAXHTPTV140_280_CVetoBVeto->Process("WBosonAnalysis.C+","Wtau140_280CVetoBVeto");
chain_Wtaunu_MAXHTPTV140_280_CFilterBVeto->Process("WBosonAnalysis.C+","Wtau140_280CFilterBVeto");
chain_Wtaunu_MAXHTPTV140_280_BFilter->Process("WBosonAnalysis.C+","Wtau140_280BFilter");
chain_Wtaunu_MAXHTPTV280_500_CVetoBVeto->Process("WBosonAnalysis.C+","Wtau280_500CVetoBVeto");
chain_Wtaunu_MAXHTPTV280_500_CFilterBVeto->Process("WBosonAnalysis.C+","Wtau280_500CFilterBVeto");
chain_Wtaunu_MAXHTPTV280_500_BFilter->Process("WBosonAnalysis.C+","Wtau280_500BFilter");
chain_Wtaunu_MAXHTPTV500_1000->Process("WBosonAnalysis.C+","Wtau500_1000");
chain_Wtaunu_MAXHTPTV1000_E_CM->Process("WBosonAnalysis.C+","Wtau1000");
   }

  } // W+jets Sherpa



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
