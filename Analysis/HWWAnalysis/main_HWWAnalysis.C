//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

void main_HWWAnalysis(int proof = 0, int option= 0)
{
  /* The URL to the CERN Open Data portal repository */
  TString path = "root://eospublic.cern.ch//eos/opendata/atlas/rucio/opendata/";
 
  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 5 options for MC (2,3,4,5,6) and 1 for data (1) which can be run in parallel
  //***************************************************************************************************//
  
  TString skim = "1LMET30";
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

    chain_data->Process("HWWAnalysis.C+","data");

  }
  
  //////////////////////  MC samples
  
  if (option==2 || option==0){
    
    // ttbar samples
    
    TChain* chain_ttbar_nonallhad = new TChain("analysis");
    chain_ttbar_nonallhad->AddFile(prefix+"mc_410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad."+skim+".root");
    chain_ttbar_nonallhad->Process("HWWAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_nonallhad");

    TChain* chain_ttbar_allhad = new TChain("analysis");
    chain_ttbar_allhad->AddFile(prefix+"mc_410471.PhPy8EG_A14_ttbar_hdamp258p75_allhad."+skim+".root");
    chain_ttbar_allhad->Process("HWWAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_allhad");
    
  }

  if (option==3 || option==0){

    //single top samples
 
    TChain* chain_tchan_BW50_lept_top = new TChain("analysis");
    chain_tchan_BW50_lept_top->AddFile(prefix+"mc_410658.PhPy8EG_A14_tchan_BW50_lept_top."+skim+".root");
    chain_tchan_BW50_lept_top->Process("HWWAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_top");

    TChain* chain_tchan_BW50_lept_antitop = new TChain("analysis");
    chain_tchan_BW50_lept_antitop->AddFile(prefix+"mc_410659.PhPy8EG_A14_tchan_BW50_lept_antitop."+skim+".root");
    chain_tchan_BW50_lept_antitop->Process("HWWAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_antitop");

    TChain* chain_schan_lept_top = new TChain("analysis");
    chain_schan_lept_top->AddFile(prefix+"mc_410644.PowhegPythia8EvtGen_A14_singletop_schan_lept_top."+skim+".root");
    chain_schan_lept_top->Process("HWWAnalysis.C+","PowhegPythia8EvtGen_A14_singletop_schan_lept_top");

    TChain* chain_schan_lept_antitop = new TChain("analysis");
    chain_schan_lept_antitop->AddFile(prefix+"mc_410645.PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop."+skim+".root");
    chain_schan_lept_antitop->Process("HWWAnalysis.C+","PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop");

    TChain* chain_tW_dyn_DR_incl_antitop = new TChain("analysis");
    chain_tW_dyn_DR_incl_antitop->AddFile(prefix+"mc_601352.PhPy8EG_tW_dyn_DR_incl_antitop."+skim+".root");
    chain_tW_dyn_DR_incl_antitop->Process("HWWAnalysis.C+","PhPy8EG_tW_dyn_DR_incl_antitop");

    TChain* chain_tW_dyn_DR_incl_top = new TChain("analysis");
    chain_tW_dyn_DR_incl_top->AddFile(prefix+"mc_601355.PhPy8EG_tW_dyn_DR_incl_top."+skim+".root");
    chain_tW_dyn_DR_incl_top->Process("HWWAnalysis.C+","PhPy8EG_tW_dyn_DR_incl_top");
    
  }

  if (option==4 || option==0){

    // diboson samples
    TChain* chain_llll = new TChain("analysis");
    chain_llll->AddFile(prefix+"mc_700600.Sh_2212_llll."+skim+".root");
    chain_llll->Process("HWWAnalysis.C+","Sh_2212_llll");

    TChain* chain_lllv = new TChain("analysis");
    chain_lllv->AddFile(prefix+"mc_700601.Sh_2212_lllv."+skim+".root");
    chain_lllv->Process("HWWAnalysis.C+","Sh_2212_lllv");
    
    TChain* chain_llvv_os = new TChain("analysis");
    chain_llvv_os->AddFile(prefix+"mc_700602.Sh_2212_llvv_os."+skim+".root");
    chain_llvv_os->Process("HWWAnalysis.C+","Sh_2212_llvv_os");

    TChain* chain_llvv_ss = new TChain("analysis");
    chain_llvv_ss->AddFile(prefix+"mc_700603.Sh_2212_llvv_ss."+skim+".root");
    chain_llvv_ss->Process("HWWAnalysis.C+","Sh_2212_llvv_ss");

    TChain* chain_lvvv = new TChain("analysis");
    chain_lvvv->AddFile(prefix+"mc_700604.Sh_2212_lvvv."+skim+".root");
    chain_lvvv->Process("HWWAnalysis.C+","Sh_2212_lvvv");

    TChain* chain_vvvv = new TChain("analysis");
    chain_vvvv->AddFile(prefix+"mc_700605.Sh_2212_vvvv."+skim+".root");
    chain_vvvv->Process("HWWAnalysis.C+","Sh_2212_vvvv");

    TChain* chain_WlvWqq = new TChain("analysis");
    chain_WlvWqq->AddFile(prefix+"mc_700488.Sh_2211_WlvWqq."+skim+".root");
    chain_WlvWqq->Process("HWWAnalysis.C+","Sh_2211_WlvWqq");

    TChain* chain_WlvZqq = new TChain("analysis");
    chain_WlvZqq->AddFile(prefix+"mc_700489.Sh_2211_WlvZqq."+skim+".root");
    chain_WlvZqq->Process("HWWAnalysis.C+","Sh_2211_WlvZqq");

    TChain* chain_WlvZbb = new TChain("analysis");
    chain_WlvZbb->AddFile(prefix+"mc_700490.Sh_2211_WlvZbb."+skim+".root");
    chain_WlvZbb->Process("HWWAnalysis.C+","Sh_2211_WlvZbb");   
  
    TChain* chain_ZqqZll = new TChain("analysis");
    chain_ZqqZll->AddFile(prefix+"mc_700493.Sh_2211_ZqqZll."+skim+".root");
    chain_ZqqZll->Process("HWWAnalysis.C+","Sh_2211_ZqqZll");

    TChain* chain_ZbbZll = new TChain("analysis");
    chain_ZbbZll->AddFile(prefix+"mc_700494.Sh_2211_ZbbZll."+skim+".root");
    chain_ZbbZll->Process("HWWAnalysis.C+","Sh_2211_ZbbZll");

    TChain* chain_ZqqZvv = new TChain("analysis");
    chain_ZqqZvv->AddFile(prefix+"mc_700495.Sh_2211_ZqqZvv."+skim+".root");
    chain_ZqqZvv->Process("HWWAnalysis.C+","Sh_2211_ZqqZvv");
    
    TChain* chain_ZbbZvv = new TChain("analysis");
    chain_ZbbZvv->AddFile(prefix+"mc_700496.Sh_2211_ZbbZvv."+skim+".root");
    chain_ZbbZvv->Process("HWWAnalysis.C+","Sh_2211_ZbbZvv");

  }

  if (option==5 || option==0){

    // V_plus_jets samples

    TChain* chain_Zee_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zee_maxHTpTV2_BFilter->AddFile(prefix+"mc_700320.Sh_2211_Zee_maxHTpTV2_BFilter."+skim+".root");
    chain_Zee_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Zee_maxHTpTV2_BFilter");

    TChain* chain_Zee_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zee_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Zee_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Zee_maxHTpTV2_CVetoBVeto");

    TChain* chain_Zmumu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_BFilter->AddFile(prefix+"mc_700323.Sh_2211_Zmumu_maxHTpTV2_BFilter."+skim+".root");
    chain_Zmumu_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_BFilter");

    TChain* chain_Zmumu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700324.Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Zmumu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700325.Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wenu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wenu_maxHTpTV2_BFilter->AddFile(prefix+"mc_700338.Sh_2211_Wenu_maxHTpTV2_BFilter."+skim+".root");
    chain_Wenu_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_BFilter");

    TChain* chain_Wenu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700339.Sh_2211_Wenu_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wenu_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wenu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700340.Sh_2211_Wenu_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wenu_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wmunu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_BFilter->AddFile(prefix+"mc_700341.Sh_2211_Wmunu_maxHTpTV2_BFilter."+skim+".root");
    chain_Wmunu_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_BFilter");

    TChain* chain_Wmunu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700342.Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wmunu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700343.Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_BFilter->AddFile(prefix+"mc_700344.Sh_2211_Wtaunu_L_maxHTpTV2_BFilter."+skim+".root");
    chain_Wtaunu_L_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_L_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700345.Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700346.Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_BFilter->AddFile(prefix+"mc_700347.Sh_2211_Wtaunu_H_maxHTpTV2_BFilter."+skim+".root");
    chain_Wtaunu_H_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_H_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700348.Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700349.Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto");

    TChain* chain_Ztautau_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_BFilter->AddFile(prefix+"mc_700792.Sh_2214_Ztautau_maxHTpTV2_BFilter."+skim+".root");
    chain_Ztautau_maxHTpTV2_BFilter->Process("HWWAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_BFilter");
    
    TChain* chain_Ztautau_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700793.Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->Process("HWWAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto");

    TChain* chain_Ztautau_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700794.Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->Process("HWWAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto");

  }

  if (option==6 || option==0){

    //Higgs samples (H->WW)
    
    // ggH
    TChain* chain_ggH125_WW = new TChain("analysis");
    chain_ggH125_WW->AddFile(prefix+"mc_345324.PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5."+skim+".root");
    chain_ggH125_WW->Process("HWWAnalysis.C+","PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5");
   
    // VBF
    TChain* chain_VBFH125_WW = new TChain("analysis");
    chain_VBFH125_WW->AddFile(prefix+"mc_345948.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv."+skim+".root");
    chain_VBFH125_WW->Process("HWWAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv");
   
  }
  
}
