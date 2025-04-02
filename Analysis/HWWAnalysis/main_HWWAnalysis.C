//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
//#include <TProof.h>

void main_HWWAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  //TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/renamedLargeRJets/2lep/";
  
  /* The URL to the ATLAS Open Data website repository */
  //TString path = "https://atlas-opendata.web.cern.ch/atlas-opendata/samples/2020/2lep/";
  
  /* The URL to the CERN Open Data portal repository */
  //TString path = "http://opendata.cern.ch/eos/opendata/atlas/OutreachDatasets/2020-01-22/2lep/";
  //TString path = "/eos/user/g/garciarm/ntuple-production-samples/ntuples-open-data/";
  //TString path = "/eos/user/e/egramsta/OpenData/2J2LMET30/";
  TString path = "/eos/user/e/egramsta/OpenData/FEB2025/1LMET30/";
  
  /* The XROOTD path to the CERN Open Data portal repository */
  //TString path = "root://eospublic.cern.ch//eos/opendata/atlas/OutreachDatasets/2020-01-22/2lep/";
  
  /* An external mirror */
  //TString path = "http://www.universidad.ch/ATLAS/outreach/open-data-2020/2lep/";

  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 5 options for MC (2,3,4,5,6) and 4 for data (11,12,13,14) which can be run in parallel
  // If using the options (11,12,13,14) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//
  //if (proof == 1)  TProof::Open("");


  if (option==1 || option==0){

    //data15
    
    TChain* chain_data = new TChain("analysis");
    chain_data->AddFile(path+"Data/data15_periodD.1LMET30.root");
    chain_data->AddFile(path+"Data/data15_periodE.1LMET30.root");
    chain_data->AddFile(path+"Data/data15_periodF.1LMET30.root");
    chain_data->AddFile(path+"Data/data15_periodG.1LMET30.root");
    chain_data->AddFile(path+"Data/data15_periodH.1LMET30.root");
    chain_data->AddFile(path+"Data/data15_periodJ.1LMET30.root");

    //data16
    
    chain_data->AddFile(path+"Data/data16_periodA.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodB.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodC.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodD.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodE.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodF.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodG.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodI.1LMET30.root");
    //chain_data->AddFile(path+"Data/data16_PeriodI.root");
    chain_data->AddFile(path+"Data/data16_periodK.1LMET30.root");
    chain_data->AddFile(path+"Data/data16_periodL.1LMET30.root");

    //if (proof == 1)  chain_data->SetProof();                                                                                  
    chain_data->Process("HWWAnalysis.C+","data");

  }
  
  //////////////////////  MC samples
  
  if (option==2 || option==0){
    
    // ttbar samples

    TChain* chain_ttbar_nonallhad = new TChain("analysis");
    chain_ttbar_nonallhad->AddFile(path+"MC/mc_410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.1LMET30.root");
    //if (proof == 1)  chain_ttbar_nonallhad->SetProof();
    chain_ttbar_nonallhad->Process("HWWAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_nonallhad");

    TChain* chain_ttbar_allhad = new TChain("analysis");
    chain_ttbar_allhad->AddFile(path+"MC/mc_410471.PhPy8EG_A14_ttbar_hdamp258p75_allhad.1LMET30.root");
    //if (proof == 1)  chain_ttbar_allhad->SetProof();
    chain_ttbar_allhad->Process("HWWAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_allhad");
    
  }

  if (option==3 || option==0){

    //single top samples
 
    TChain* chain_tchan_BW50_lept_top = new TChain("analysis");
    chain_tchan_BW50_lept_top->AddFile(path+"MC/mc_410658.PhPy8EG_A14_tchan_BW50_lept_top.1LMET30.root");
    //if (proof == 1)  chain_tchan_BW50_lept_top->SetProof();
    chain_tchan_BW50_lept_top->Process("HWWAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_top");

    TChain* chain_tchan_BW50_lept_antitop = new TChain("analysis");
    chain_tchan_BW50_lept_antitop->AddFile(path+"MC/mc_410659.PhPy8EG_A14_tchan_BW50_lept_antitop.1LMET30.root");
    //if (proof == 1)  chain_tchan_BW50_lept_antitop->SetProof();
    chain_tchan_BW50_lept_antitop->Process("HWWAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_antitop");

    TChain* chain_schan_lept_top = new TChain("analysis");
    chain_schan_lept_top->AddFile(path+"MC/mc_410644.PowhegPythia8EvtGen_A14_singletop_schan_lept_top.1LMET30.root");
    //if (proof == 1)  chain_schan_lept_top->SetProof();
    chain_schan_lept_top->Process("HWWAnalysis.C+","PowhegPythia8EvtGen_A14_singletop_schan_lept_top");

    TChain* chain_schan_lept_antitop = new TChain("analysis");
    chain_schan_lept_antitop->AddFile(path+"MC/mc_410645.PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop.1LMET30.root");
    //if (proof == 1)  chain_schan_lept_antitop->SetProof();
    chain_schan_lept_antitop->Process("HWWAnalysis.C+","PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop");

    TChain* chain_tW_dyn_DR_incl_antitop = new TChain("analysis");
    chain_tW_dyn_DR_incl_antitop->AddFile(path+"MC/mc_601352.PhPy8EG_tW_dyn_DR_incl_antitop.1LMET30.root");
    //if (proof == 1)  chain_tW_dyn_DR_incl_antitop->SetProof();
    chain_tW_dyn_DR_incl_antitop->Process("HWWAnalysis.C+","PhPy8EG_tW_dyn_DR_incl_antitop");

    TChain* chain_tW_dyn_DR_incl_top = new TChain("analysis");
    chain_tW_dyn_DR_incl_top->AddFile(path+"MC/mc_601355.PhPy8EG_tW_dyn_DR_incl_top.1LMET30.root");
    //if (proof == 1)  chain_tW_dyn_DR_incl_top->SetProof();
    chain_tW_dyn_DR_incl_top->Process("HWWAnalysis.C+","PhPy8EG_tW_dyn_DR_incl_top");
    
  }

  if (option==4 || option==0){

    // diboson samples
    TChain* chain_llll = new TChain("analysis");
    chain_llll->AddFile(path+"MC/mc_700600.Sh_2212_llll.1LMET30.root");
    //if (proof == 1)  chain_llll->SetProof();
    chain_llll->Process("HWWAnalysis.C+","Sh_2212_llll");

    TChain* chain_lllv = new TChain("analysis");
    chain_lllv->AddFile(path+"MC/mc_700601.Sh_2212_lllv.1LMET30.root");
    //if (proof == 1)  chain_lllv->SetProof();
    chain_lllv->Process("HWWAnalysis.C+","Sh_2212_lllv");
    
    TChain* chain_llvv_os = new TChain("analysis");
    chain_llvv_os->AddFile(path+"MC/mc_700602.Sh_2212_llvv_os.1LMET30.root");
    //if (proof == 1)  chain_llvv_os->SetProof();
    chain_llvv_os->Process("HWWAnalysis.C+","Sh_2212_llvv_os");

    TChain* chain_llvv_ss = new TChain("analysis");
    chain_llvv_ss->AddFile(path+"MC/mc_700603.Sh_2212_llvv_ss.1LMET30.root");
    //if (proof == 1)  chain_llvv_ss->SetProof();
    chain_llvv_ss->Process("HWWAnalysis.C+","Sh_2212_llvv_ss");

    TChain* chain_lvvv = new TChain("analysis");
    chain_lvvv->AddFile(path+"MC/mc_700604.Sh_2212_lvvv.1LMET30.root");
    //if (proof == 1)  chain_lvvv->SetProof();
    chain_lvvv->Process("HWWAnalysis.C+","Sh_2212_lvvv");

    TChain* chain_vvvv = new TChain("analysis");
    chain_vvvv->AddFile(path+"MC/mc_700605.Sh_2212_vvvv.1LMET30.root");
    //if (proof == 1)  chain_vvvv->SetProof();
    chain_vvvv->Process("HWWAnalysis.C+","Sh_2212_vvvv");

    TChain* chain_WlvWqq = new TChain("analysis");
    chain_WlvWqq->AddFile(path+"MC/mc_700488.Sh_2211_WlvWqq.1LMET30.root");
    //if (proof == 1)  chain_WlvWqq->SetProof();
    chain_WlvWqq->Process("HWWAnalysis.C+","Sh_2211_WlvWqq");

    TChain* chain_WlvZqq = new TChain("analysis");
    chain_WlvZqq->AddFile(path+"MC/mc_700489.Sh_2211_WlvZqq.1LMET30.root");
    //if (proof == 1)  chain_WlvZqq->SetProof();
    chain_WlvZqq->Process("HWWAnalysis.C+","Sh_2211_WlvZqq");

    TChain* chain_WlvZbb = new TChain("analysis");
    chain_WlvZbb->AddFile(path+"MC/mc_700490.Sh_2211_WlvZbb.1LMET30.root");
    //if (proof == 1)  chain_WlvZbb->SetProof();
    chain_WlvZbb->Process("HWWAnalysis.C+","Sh_2211_WlvZbb");   
  
    TChain* chain_ZqqZll = new TChain("analysis");
    chain_ZqqZll->AddFile(path+"MC/mc_700493.Sh_2211_ZqqZll.1LMET30.root");
    //if (proof == 1)  chain_ZqqZll->SetProof();
    chain_ZqqZll->Process("HWWAnalysis.C+","Sh_2211_ZqqZll");

    TChain* chain_ZbbZll = new TChain("analysis");
    chain_ZbbZll->AddFile(path+"MC/mc_700494.Sh_2211_ZbbZll.1LMET30.root");
    //if (proof == 1)  chain_ZbbZll->SetProof();
    chain_ZbbZll->Process("HWWAnalysis.C+","Sh_2211_ZbbZll");

    TChain* chain_ZqqZvv = new TChain("analysis");
    chain_ZqqZvv->AddFile(path+"MC/mc_700495.Sh_2211_ZqqZvv.1LMET30.root");
    //if (proof == 1)  chain_ZqqZvv->SetProof();
    chain_ZqqZvv->Process("HWWAnalysis.C+","Sh_2211_ZqqZvv");
    
    TChain* chain_ZbbZvv = new TChain("analysis");
    chain_ZbbZvv->AddFile(path+"MC/mc_700496.Sh_2211_ZbbZvv.1LMET30.root");
    //if (proof == 1)  chain_ZbbZvv->SetProof();
    chain_ZbbZvv->Process("HWWAnalysis.C+","Sh_2211_ZbbZvv");

  }

  if (option==5 || option==0){

    // V_plus_jets samples

    TChain* chain_Zee_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zee_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700320.Sh_2211_Zee_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_BFilter->SetProof();
    chain_Zee_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Zee_maxHTpTV2_BFilter");

    TChain* chain_Zee_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zee_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Zee_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Zee_maxHTpTV2_CVetoBVeto");

    TChain* chain_Zmumu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700323.Sh_2211_Zmumu_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_BFilter->SetProof();
    chain_Zmumu_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_BFilter");

    TChain* chain_Zmumu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700324.Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Zmumu_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Zmumu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700325.Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Zmumu_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wenu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wenu_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700338.Sh_2211_Wenu_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_BFilter->SetProof();
    chain_Wenu_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_BFilter");

    TChain* chain_Wenu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700339.Sh_2211_Wenu_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wenu_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wenu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700340.Sh_2211_Wenu_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wenu_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wmunu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700341.Sh_2211_Wmunu_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_BFilter->SetProof();
    chain_Wmunu_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_BFilter");

    TChain* chain_Wmunu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700342.Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wmunu_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wmunu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700343.Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wmunu_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700344.Sh_2211_Wtaunu_L_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_BFilter->SetProof();
    chain_Wtaunu_L_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_L_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700345.Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700346.Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700347.Sh_2211_Wtaunu_H_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_BFilter->SetProof();
    chain_Wtaunu_H_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_H_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700348.Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700349.Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto");

    TChain* chain_Ztautau_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700792.Sh_2214_Ztautau_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_BFilter->SetProof();
    chain_Ztautau_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_BFilter");
    
    TChain* chain_Ztautau_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700793.Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Ztautau_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto");

    TChain* chain_Ztautau_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700794.Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Ztautau_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto");

  }

  if (option==6 || option==0){

    //Higgs samples (H->WW)
   
   // ggH
   TChain* chain_ggH125_WW = new TChain("analysis");
   chain_ggH125_WW->AddFile(path+"MC/mc_345324.PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5.1LMET30.root");
   //if (proof == 1)  chain_ggH125_WW->SetProof();
   chain_ggH125_WW->Process("HWWAnalysis.C+","PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5");
   
   // VBF
   TChain* chain_VBFH125_WW = new TChain("analysis");
   chain_VBFH125_WW->AddFile(path+"MC/mc_345948.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv.1LMET30.root");
   //if (proof == 1)  chain_VBFH125_WW->SetProof();
   chain_VBFH125_WW->Process("HWWAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv");
   
  }
  
}
