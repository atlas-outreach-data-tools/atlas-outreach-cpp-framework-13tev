//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

void main_HTauTauAnalysis(int proof = 0, int option= 0){
  
  /* The URL to the CERN Open Data portal repository */
  TString path = "root://eospublic.cern.ch//eos/opendata/atlas/rucio/opendata/";
  
  //***************************************************************************************************//
  // Adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 5 options for MC (2,3,4,5 and 6) and 1 for data (1)
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

    chain_data->Process("HTauTauAnalysis.C+","data");
    
  }

  
  //////////////////////  MC samples

  if (option==2 || option==0){
 
    // diboson
    
    TChain* chain_llll = new TChain("analysis");
    chain_llll->AddFile(prefix+"mc_700600.Sh_2212_llll."+skim+".root");
    chain_llll->Process("HTauTauAnalysis.C+","Sh_2212_llll");

    TChain* chain_lllv = new TChain("analysis");
    chain_lllv->AddFile(prefix+"mc_700601.Sh_2212_lllv."+skim+".root");
    chain_lllv->Process("HTauTauAnalysis.C+","Sh_2212_lllv");
    
    TChain* chain_llvv_os = new TChain("analysis");
    chain_llvv_os->AddFile(prefix+"mc_700602.Sh_2212_llvv_os."+skim+".root");
    chain_llvv_os->Process("HTauTauAnalysis.C+","Sh_2212_llvv_os");

    TChain* chain_llvv_ss = new TChain("analysis");
    chain_llvv_ss->AddFile(prefix+"mc_700603.Sh_2212_llvv_ss."+skim+".root");
    chain_llvv_ss->Process("HTauTauAnalysis.C+","Sh_2212_llvv_ss");

    TChain* chain_lvvv = new TChain("analysis");
    chain_lvvv->AddFile(prefix+"mc_700604.Sh_2212_lvvv."+skim+".root");
    chain_lvvv->Process("HTauTauAnalysis.C+","Sh_2212_lvvv");

    TChain* chain_vvvv = new TChain("analysis");
    chain_vvvv->AddFile(prefix+"mc_700605.Sh_2212_vvvv."+skim+".root");
    chain_vvvv->Process("HTauTauAnalysis.C+","Sh_2212_vvvv");

    TChain* chain_WlvWqq = new TChain("analysis");
    chain_WlvWqq->AddFile(prefix+"mc_700488.Sh_2211_WlvWqq."+skim+".root");
    chain_WlvWqq->Process("HTauTauAnalysis.C+","Sh_2211_WlvWqq");

    TChain* chain_WlvZqq = new TChain("analysis");
    chain_WlvZqq->AddFile(prefix+"mc_700489.Sh_2211_WlvZqq."+skim+".root");
    chain_WlvZqq->Process("HTauTauAnalysis.C+","Sh_2211_WlvZqq");

    TChain* chain_WlvZbb = new TChain("analysis");
    chain_WlvZbb->AddFile(prefix+"mc_700490.Sh_2211_WlvZbb."+skim+".root");
    chain_WlvZbb->Process("HTauTauAnalysis.C+","Sh_2211_WlvZbb");   
  
    TChain* chain_ZqqZll = new TChain("analysis");
    chain_ZqqZll->AddFile(prefix+"mc_700493.Sh_2211_ZqqZll."+skim+".root");
    chain_ZqqZll->Process("HTauTauAnalysis.C+","Sh_2211_ZqqZll");

    TChain* chain_ZbbZll = new TChain("analysis");
    chain_ZbbZll->AddFile(prefix+"mc_700494.Sh_2211_ZbbZll."+skim+".root");
    chain_ZbbZll->Process("HTauTauAnalysis.C+","Sh_2211_ZbbZll");

    TChain* chain_ZqqZvv = new TChain("analysis");
    chain_ZqqZvv->AddFile(prefix+"mc_700495.Sh_2211_ZqqZvv."+skim+".root");
    chain_ZqqZvv->Process("HTauTauAnalysis.C+","Sh_2211_ZqqZvv");
    
    TChain* chain_ZbbZvv = new TChain("analysis");
    chain_ZbbZvv->AddFile(prefix+"mc_700496.Sh_2211_ZbbZvv."+skim+".root");
    chain_ZbbZvv->Process("HTauTauAnalysis.C+","Sh_2211_ZbbZvv");
    
  }

  if (option==3 || option==0){
    
    //single top
    
    TChain* chain_tchan_BW50_lept_top = new TChain("analysis");
    chain_tchan_BW50_lept_top->AddFile(prefix+"mc_410658.PhPy8EG_A14_tchan_BW50_lept_top."+skim+".root");
    chain_tchan_BW50_lept_top->Process("HTauTauAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_top");

    TChain* chain_tchan_BW50_lept_antitop = new TChain("analysis");
    chain_tchan_BW50_lept_antitop->AddFile(prefix+"mc_410659.PhPy8EG_A14_tchan_BW50_lept_antitop."+skim+".root");
    chain_tchan_BW50_lept_antitop->Process("HTauTauAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_antitop");

    TChain* chain_schan_lept_top = new TChain("analysis");
    chain_schan_lept_top->AddFile(prefix+"mc_410644.PowhegPythia8EvtGen_A14_singletop_schan_lept_top."+skim+".root");
    chain_schan_lept_top->Process("HTauTauAnalysis.C+","PowhegPythia8EvtGen_A14_singletop_schan_lept_top");

    TChain* chain_schan_lept_antitop = new TChain("analysis");
    chain_schan_lept_antitop->AddFile(prefix+"mc_410645.PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop."+skim+".root");
    chain_schan_lept_antitop->Process("HTauTauAnalysis.C+","PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop");

    TChain* chain_tW_dyn_DR_incl_antitop = new TChain("analysis");
    chain_tW_dyn_DR_incl_antitop->AddFile(prefix+"mc_601352.PhPy8EG_tW_dyn_DR_incl_antitop."+skim+".root");
    chain_tW_dyn_DR_incl_antitop->Process("HTauTauAnalysis.C+","PhPy8EG_tW_dyn_DR_incl_antitop");

    TChain* chain_tW_dyn_DR_incl_top = new TChain("analysis");
    chain_tW_dyn_DR_incl_top->AddFile(prefix+"mc_601355.PhPy8EG_tW_dyn_DR_incl_top."+skim+".root");
    chain_tW_dyn_DR_incl_top->Process("HTauTauAnalysis.C+","PhPy8EG_tW_dyn_DR_incl_top");
    
  }

  if (option==4 || option==0){
    // Higgs
    TChain* chain_ggH_1317 = new TChain("analysis");
    chain_ggH_1317->AddFile(prefix+"mc_345120.PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautaul13l7."+skim+".root");
    chain_ggH_1317->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautaul13l7");
    
    TChain* chain_ggH_m1520 = new TChain("analysis");
    chain_ggH_m1520->AddFile(prefix+"mc_345121.PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautaulm15hp20."+skim+".root");
    chain_ggH_m1520->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautaulm15hp20");

    TChain* chain_ggH_15m20 = new TChain("analysis");
    chain_ggH_15m20->AddFile(prefix+"mc_345122.PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautaulp15hm20."+skim+".root");
    chain_ggH_15m20->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautaulp15hm20");

    TChain* chain_ggH_3020 = new TChain("analysis");
    chain_ggH_3020->AddFile(prefix+"mc_345123.PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautauh30h20."+skim+".root");
    chain_ggH_3020->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNLOPS_nnlo_30_ggH125_tautauh30h20");
 
    TChain* chain_ggH_etau = new TChain("analysis");
    chain_ggH_etau->AddFile(prefix+"mc_345124.PowhegPy8EG_NNLOPS_nnlo_30_ggH125_etau_filt."+skim+".root");
    chain_ggH_etau->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNLOPS_nnlo_30_ggH125_etau_filt");

     TChain* chain_VBFH125_tautaul13l7 = new TChain("analysis");
    chain_VBFH125_tautaul13l7->AddFile(prefix+"mc_346190.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautaul13l7."+skim+".root");
    chain_VBFH125_tautaul13l7->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautaul13l7");

    TChain* chain_VBFH125_tautaulm15hp20 = new TChain("analysis");
    chain_VBFH125_tautaulm15hp20->AddFile(prefix+"mc_346191.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautaulm15hp20."+skim+".root");
    chain_VBFH125_tautaulm15hp20->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautaulm15hp20");
     
    TChain* chain_VBFH125_tautaulp15hm20 = new TChain("analysis");
    chain_VBFH125_tautaulp15hm20->AddFile(prefix+"mc_346192.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautaulp15hm20."+skim+".root");
    chain_VBFH125_tautaulp15hm20->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautaulp15hm20");

    TChain* chain_VBFH125_tautauh30h20 = new TChain("analysis");
    chain_VBFH125_tautauh30h20->AddFile(prefix+"mc_346193.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautauh30h20."+skim+".root");
    chain_VBFH125_tautauh30h20->Process("HTauTauAnalysis.C+","PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_tautauh30h20");
    

   TChain* chain_ttH125_allhad = new TChain("analysis");
    chain_ttH125_allhad->AddFile(prefix+"mc_346343.PhPy8EG_A14NNPDF23_NNPDF30ME_ttH125_allhad."+skim+".root");
    chain_ttH125_allhad->Process("HTauTauAnalysis.C+","PhPy8EG_A14NNPDF23_NNPDF30ME_ttH125_allhad");
  
    TChain* chain_ttH125_semilep = new TChain("analysis");
    chain_ttH125_semilep->AddFile(prefix+"mc_346344.PhPy8EG_A14NNPDF23_NNPDF30ME_ttH125_semilep."+skim+".root");
    chain_ttH125_semilep->Process("HTauTauAnalysis.C+","PhPy8EG_A14NNPDF23_NNPDF30ME_ttH125_semilep");
   
    TChain* chain_ttH125_dilep = new TChain("analysis");
    chain_ttH125_dilep->AddFile(prefix+"mc_346345.PhPy8EG_A14NNPDF23_NNPDF30ME_ttH125_dilep."+skim+".root");
    chain_ttH125_dilep->Process("HTauTauAnalysis.C+","PhPy8EG_A14NNPDF23_NNPDF30ME_ttH125_dilep");
   
    TChain* chain_ggZH = new TChain("analysis");
    chain_ggZH->AddFile(prefix+"mc_600686.PhPy8EG_NNPDF3_AZNLO_ggZH125_Htautau_Zinc."+skim+".root");
    chain_ggZH->Process("HTauTauAnalysis.C+","PhPy8EG_NNPDF3_AZNLO_ggZH125_Htautau_Zinc");
    // ttbar samples

    TChain* chain_ttbar_nonallhad = new TChain("analysis");
    chain_ttbar_nonallhad->AddFile(prefix+"mc_410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad."+skim+".root");
    chain_ttbar_nonallhad->Process("HTauTauAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_nonallhad");

    TChain* chain_ttbar_allhad = new TChain("analysis");
    chain_ttbar_allhad->AddFile(prefix+"mc_410471.PhPy8EG_A14_ttbar_hdamp258p75_allhad."+skim+".root");
    chain_ttbar_allhad->Process("HTauTauAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_allhad");
    
  }
  

  if (option==5 || option==0){

    // W+jets
    
    TChain* chain_Wenu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wenu_maxHTpTV2_BFilter->AddFile(prefix+"mc_700338.Sh_2211_Wenu_maxHTpTV2_BFilter."+skim+".root");
    chain_Wenu_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_BFilter");

    TChain* chain_Wenu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700339.Sh_2211_Wenu_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wenu_maxHTpTV2_CFilterBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wenu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700340.Sh_2211_Wenu_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wenu_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wmunu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_BFilter->AddFile(prefix+"mc_700341.Sh_2211_Wmunu_maxHTpTV2_BFilter."+skim+".root");
    chain_Wmunu_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_BFilter");

    TChain* chain_Wmunu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700342.Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wmunu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700343.Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_BFilter->AddFile(prefix+"mc_700344.Sh_2211_Wtaunu_L_maxHTpTV2_BFilter."+skim+".root");
    chain_Wtaunu_L_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_L_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700345.Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700346.Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_BFilter->AddFile(prefix+"mc_700347.Sh_2211_Wtaunu_H_maxHTpTV2_BFilter."+skim+".root");
    chain_Wtaunu_H_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_H_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700348.Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700349.Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto");

  } // W+jets Sherpa


  // Sherpa Z+jets sliced samples
  if (option==6 || option==0){

    // Z+jets inclusive

    TChain* chain_Zee_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zee_maxHTpTV2_BFilter->AddFile(prefix+"mc_700320.Sh_2211_Zee_maxHTpTV2_BFilter."+skim+".root");
    chain_Zee_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2211_Zee_maxHTpTV2_BFilter");

    TChain* chain_Zee_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zee_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Zee_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Zee_maxHTpTV2_CVetoBVeto");

    TChain* chain_Zmumu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_BFilter->AddFile(prefix+"mc_700323.Sh_2211_Zmumu_maxHTpTV2_BFilter."+skim+".root");
    chain_Zmumu_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_BFilter");

    TChain* chain_Zmumu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700324.Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Zmumu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700325.Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto");
    
    TChain* chain_Ztautau_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_BFilter->AddFile(prefix+"mc_700792.Sh_2214_Ztautau_maxHTpTV2_BFilter."+skim+".root");
    chain_Ztautau_maxHTpTV2_BFilter->Process("HTauTauAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_BFilter");
    
    TChain* chain_Ztautau_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->AddFile(prefix+"mc_700793.Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto."+skim+".root");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->Process("HTauTauAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto");

    TChain* chain_Ztautau_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->AddFile(prefix+"mc_700794.Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto."+skim+".root");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->Process("HTauTauAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto");
    
  }

}
  
