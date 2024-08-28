

//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
//#include "TProof.h"

void main_TTbarDilepAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!
  /* Local path example */
  TString path = "/eos/user/g/garciarm/ntuple-production-samples/ntuples-open-data/";
  
  /* The URL to the ATLAS Open Data website repository */
  //TString path = "https://atlas-opendata.web.cern.ch/atlas-opendata/samples/2020/1lep/";

  /* The URL to the CERN Open Data portal repository */
  //TString path = "http://opendata.cern.ch/eos/opendata/atlas/OutreachDatasets/2020-01-22/1lep/";

  /* The XROOTD path to the CERN Open Data portal repository */
  //TString path = "root://eospublic.cern.ch//eos/opendata/atlas/OutreachDatasets/2020-01-22/1lep/";

  /* An external mirror */
  //TString path = "http://www.universidad.ch/ATLAS/outreach/open-data-2020/1lep/";
  
  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 4 options for MC (2,3,4,5) and 4 for data (11,12,13,14) which can be run in parallel
  // If using the options (11,12,13,14) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//

  //if (proof == 1)  TProof::Open("");
  
  if (option==11 || option==0){

    //data15
    TChain* chain_data15_A = new TChain("analysis");
    chain_data15_A->AddFile(path+"ntuples-data-samples/data15_A.root");
    //if (proof == 1)  chain_data15->SetProof();
    chain_data15_A->Process("TTbarDilepAnalysis.C+","data15_A");
 
    TChain* chain_data15_B = new TChain("analysis");
    chain_data15_B->AddFile(path+"ntuples-data-samples/data15_B.root");
    //if (proof == 1)  chain_data15->SetProof();
    chain_data15_B->Process("TTbarDilepAnalysis.C+","data15_B");
  }
  
  if (option==12 || option==0){

    //data16
    TChain* chain_data16_A = new TChain("analysis");
    chain_data16_A->AddFile(path+"ntuples-data-samples/data16_A.root");
    //if (proof == 1)  chain_data16_A->SetProof();
    chain_data16_A->Process("TTbarDilepAnalysis.C+","data16_A");
  
    TChain* chain_data16_B = new TChain("analysis");
    chain_data16_B->AddFile(path+"ntuples-data-samples/data16_B.root");
    //if (proof == 1)  chain_data16_B->SetProof();
    chain_data16_B->Process("TTbarDilepAnalysis.C+","data16_B");
  
    TChain* chain_data16_C = new TChain("analysis");
    chain_data16_C->AddFile(path+"ntuples-data-samples/data16_C.root");
    //if (proof == 1)  chain_data16_C->SetProof();
    chain_data16_C->Process("TTbarDilepAnalysis.C+","data16_C");
  
    TChain* chain_data16_D = new TChain("analysis");
    chain_data16_D->AddFile(path+"ntuples-data-samples/data16_D.root");
    //if (proof == 1)  chain_data16_D->SetProof();
    chain_data16_D->Process("TTbarDilepAnalysis.C+","data16_D");
    
    TChain* chain_data16_E = new TChain("analysis");
    chain_data16_E->AddFile(path+"ntuples-data-samples/data16_E.root");
    //if (proof == 1)  chain_data16_E->SetProof();
    chain_data16_E->Process("TTbarDilepAnalysis.C+","data16_E");
  
    TChain* chain_data16_F = new TChain("analysis");
    chain_data16_F->AddFile(path+"ntuples-data-samples/data16_F.root");
    //if (proof == 1)  chain_data16_F->SetProof();
    chain_data16_F->Process("TTbarDilepAnalysis.C+","data16_F");
  
    TChain* chain_data16_G = new TChain("analysis");
    chain_data16_G->AddFile(path+"ntuples-data-samples/data16_G.root");
    //if (proof == 1)  chain_data16_G->SetProof();
    chain_data16_G->Process("TTbarDilepAnalysis.C+","data16_G");
  
    TChain* chain_data16_H = new TChain("analysis");
    chain_data16_H->AddFile(path+"ntuples-data-samples/data16_H.root");
    //if (proof == 1)  chain_data16_H->SetProof();
    chain_data16_H->Process("TTbarDilepAnalysis.C+","data16_H");
  }
  
  //////////////////////  MC samples
  
  if (option==2 || option==0){
    
    // ttbar samples
    TChain* chain_ttbar_nonallhad = new TChain("analysis");
    chain_ttbar_nonallhad->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.root");
    //if (proof == 1)  chain_ttbar_nonallhad->SetProof();
    chain_ttbar_nonallhad->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_nonallhad");
    
    TChain* chain_ttbar_dil = new TChain("analysis");
    chain_ttbar_dil->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410472.PhPy8EG_A14_ttbar_hdamp258p75_dil.root");
    //if (proof == 1)  chain_ttbar_dil->SetProof();
    chain_ttbar_dil->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_dil");

  }

  if (option==3 || option==0){

    //single top samples
    TChain* chain_Wt_DR_dilepton_top = new TChain("analysis");
    chain_Wt_DR_dilepton_top->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410648.PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top.root");
    //if (proof == 1)  chain_Wt_DR_dilepton_top->SetProof();
    chain_Wt_DR_dilepton_top->Process("TTbarDilepAnalysis.C+","PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top");

    TChain* chain_Wt_DR_dilepton_antitop = new TChain("analysis");
    chain_Wt_DR_dilepton_antitop->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410649.PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop.root");
    //if (proof == 1)  chain_Wt_DR_dilepton_antitop->SetProof();
    chain_Wt_DR_dilepton_antitop->Process("TTbarDilepAnalysis.C+","PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop");

    TChain* chain_Wt_DR_inclusive_top = new TChain("analysis");
    chain_Wt_DR_inclusive_top->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410646.PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top.root");
    //if (proof == 1)  chain_Wt_DR_inclusive_top->SetProof();
    chain_Wt_DR_inclusive_top->Process("TTbarDilepAnalysis.C+","PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top");

    TChain* chain_Wt_DR_inclusive_antitop = new TChain("analysis");
    chain_Wt_DR_inclusive_antitop->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410647.PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop.root");
    //if (proof == 1)  chain_Wt_DR_inclusive_antitop->SetProof();
    chain_Wt_DR_inclusive_antitop->Process("TTbarDilepAnalysis.C+","PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop");

    TChain* chain_tchan_BW50_lept_top = new TChain("analysis");
    chain_tchan_BW50_lept_top->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410658.PhPy8EG_A14_tchan_BW50_lept_top.root");
    //if (proof == 1)  chain_tchan_BW50_lept_top->SetProof();
    chain_tchan_BW50_lept_top->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_top");

    TChain* chain_tchan_BW50_lept_antitop = new TChain("analysis");
    chain_tchan_BW50_lept_antitop->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410659.PhPy8EG_A14_tchan_BW50_lept_antitop.root");
    //if (proof == 1)  chain_tchan_BW50_lept_antitop->SetProof();
    chain_tchan_BW50_lept_antitop->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_antitop");
  }

  if (option==4 || option==0){

    // diboson samples
    TChain* chain_llll = new TChain("analysis");
    chain_llll->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700600.Sh_2212_llll.root");
    //if (proof == 1)  chain_llll->SetProof();
    chain_llll->Process("TTbarDilepAnalysis.C+","Sh_2212_llll");

    TChain* chain_lllv = new TChain("analysis");
    chain_lllv->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700601.Sh_2212_lllv.root");
    //if (proof == 1)  chain_lllv->SetProof();
    chain_lllv->Process("TTbarDilepAnalysis.C+","Sh_2212_lllv");
    
    TChain* chain_llvv_os = new TChain("analysis");
    chain_llvv_os->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700602.Sh_2212_llvv_os.root");
    //if (proof == 1)  chain_llvv_os->SetProof();
    chain_llvv_os->Process("TTbarDilepAnalysis.C+","Sh_2212_llvv_os");

    TChain* chain_llvv_ss = new TChain("analysis");
    chain_llvv_ss->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700603.Sh_2212_llvv_ss.root");
    //if (proof == 1)  chain_llvv_ss->SetProof();
    chain_llvv_ss->Process("TTbarDilepAnalysis.C+","Sh_2212_llvv_ss");

    TChain* chain_lvvv = new TChain("analysis");
    chain_lvvv->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700604.Sh_2212_lvvv.root");
    //if (proof == 1)  chain_lvvv->SetProof();
    chain_lvvv->Process("TTbarDilepAnalysis.C+","Sh_2212_lvvv");

    TChain* chain_vvvv = new TChain("analysis");
    chain_vvvv->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700605.Sh_2212_vvvv.root");
    //if (proof == 1)  chain_vvvv->SetProof();
    chain_vvvv->Process("TTbarDilepAnalysis.C+","Sh_2212_vvvv");

    TChain* chain_WlvWqq = new TChain("analysis");
    chain_WlvWqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700488.Sh_2211_WlvWqq.root");
    //if (proof == 1)  chain_WlvWqq->SetProof();
    chain_WlvWqq->Process("TTbarDilepAnalysis.C+","Sh_2211_WlvWqq");

    TChain* chain_WlvZqq = new TChain("analysis");
    chain_WlvZqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700489.Sh_2211_WlvZqq.root");
    //if (proof == 1)  chain_WlvZqq->SetProof();
    chain_WlvZqq->Process("TTbarDilepAnalysis.C+","Sh_2211_WlvZqq");

    TChain* chain_WlvZbb = new TChain("analysis");
    chain_WlvZbb->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700490.Sh_2211_WlvZbb.root");
    //if (proof == 1)  chain_WlvZbb->SetProof();
    chain_WlvZbb->Process("TTbarDilepAnalysis.C+","Sh_2211_WlvZbb");   
  
    TChain* chain_ZqqZll = new TChain("analysis");
    chain_ZqqZll->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700493.Sh_2211_ZqqZll.root");
    //if (proof == 1)  chain_ZqqZll->SetProof();
    chain_ZqqZll->Process("TTbarDilepAnalysis.C+","Sh_2211_ZqqZll");

    TChain* chain_ZbbZll = new TChain("analysis");
    chain_ZbbZll->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700494.Sh_2211_ZbbZll.root");
    //if (proof == 1)  chain_ZbbZll->SetProof();
    chain_ZbbZll->Process("TTbarDilepAnalysis.C+","Sh_2211_ZbbZll");

    TChain* chain_ZqqZvv = new TChain("analysis");
    chain_ZqqZvv->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700495.Sh_2211_ZqqZvv.root");
    //if (proof == 1)  chain_ZqqZvv->SetProof();
    chain_ZqqZvv->Process("TTbarDilepAnalysis.C+","Sh_2211_ZqqZvv");
    
    TChain* chain_ZbbZvv = new TChain("analysis");
    chain_ZbbZvv->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700496.Sh_2211_ZbbZvv.root");
    //if (proof == 1)  chain_ZbbZvv->SetProof();
    chain_ZbbZvv->Process("TTbarDilepAnalysis.C+","Sh_2211_ZbbZvv");

    TChain* chain_ggZllZqq = new TChain("analysis");
    chain_ggZllZqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.364302.Sherpa_222_NNPDF30NNLO_ggZllZqq.root");
    //if (proof == 1)  chain_ggZllZqq->SetProof();
    chain_ggZllZqq->Process("TTbarDilepAnalysis.C+","Sherpa_222_NNPDF30NNLO_ggZllZqq");

    TChain* chain_ggZvvZqq = new TChain("analysis");
    chain_ggZvvZqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.364303.Sherpa_222_NNPDF30NNLO_ggZvvZqq.root");
    //if (proof == 1)  chain_ggZvvZqq->SetProof();
    chain_ggZvvZqq->Process("TTbarDilepAnalysis.C+","Sherpa_222_NNPDF30NNLO_ggZvvZqq");

    TChain* chain_ggWmlvWpqq = new TChain("analysis");
    chain_ggWmlvWpqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.364304.Sherpa_222_NNPDF30NNLO_ggWmlvWpqq.root");
    //if (proof == 1)  chain_ggWmlvWpqq->SetProof();
    chain_ggWmlvWpqq->Process("TTbarDilepAnalysis.C+","Sherpa_222_NNPDF30NNLO_ggWmlvWpqq");

    TChain* chain_ggWplvWmqq = new TChain("analysis");
    chain_ggWplvWmqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.364305.Sherpa_222_NNPDF30NNLO_ggWplvWmqq.root");
    //if (proof == 1)  chain_ggWplvWmqq->SetProof();
    chain_ggWplvWmqq->Process("TTbarDilepAnalysis.C+","Sherpa_222_NNPDF30NNLO_ggWplvWmqq");
    
  }

  if (option==5 || option==0){

    // V_plus_jets samples
    TChain* chain_Zee_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zee_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700320.Sh_2211_Zee_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_BFilter->SetProof();
    chain_Zee_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Zee_maxHTpTV2_BFilter");

    TChain* chain_Zee_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Zee_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700321.Sh_2211_Zee_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Zee_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zee_maxHTpTV2_CFilterBVeto");

    TChain* chain_Zee_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zee_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Zee_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zee_maxHTpTV2_CVetoBVeto");

    TChain* chain_Zmumu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700323.Sh_2211_Zmumu_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_BFilter->SetProof();
    chain_Zmumu_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_BFilter");

    TChain* chain_Zmumu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700324.Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Zmumu_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Zmumu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700325.Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Zmumu_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wenu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wenu_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700338.Sh_2211_Wenu_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_BFilter->SetProof();
    chain_Wenu_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_BFilter");

    TChain* chain_Wenu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700339.Sh_2211_Wenu_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wenu_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wenu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700340.Sh_2211_Wenu_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wenu_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wmunu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700341.Sh_2211_Wmunu_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_BFilter->SetProof();
    chain_Wmunu_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_BFilter");

    TChain* chain_Wmunu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700342.Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wmunu_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wmunu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700343.Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wmunu_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700344.Sh_2211_Wtaunu_L_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_BFilter->SetProof();
    chain_Wtaunu_L_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_L_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700345.Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700346.Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700347.Sh_2211_Wtaunu_H_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_BFilter->SetProof();
    chain_Wtaunu_H_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_H_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700348.Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700349.Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto");

    TChain* chain_Ztautau_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_BFilter->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700792.Sh_2214_Ztautau_maxHTpTV2_BFilter.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_BFilter->SetProof();
    chain_Ztautau_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_BFilter");
    
    TChain* chain_Ztautau_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700793.Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Ztautau_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto");

    TChain* chain_Ztautau_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->AddFile(path+"ntuples-mc-samples/mc20_13TeV.700794.Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Ztautau_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto");
  }

  if (option==6 || option==0){

    // tt_others
    TChain* chain_ttW = new TChain("analysis");
    chain_ttW->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW.root");
    //if (proof == 1)  chain_ttW->SetProof();
    chain_ttW->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW");

    TChain* chain_ttZnunu = new TChain("analysis");
    chain_ttZnunu->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410156.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu.root");
    //if (proof == 1)  chain_ttZnunu->SetProof();
    chain_ttZnunu->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu");

    TChain* chain_ttZqq = new TChain("analysis");
    chain_ttZqq->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410157.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq.root");
    //if (proof == 1)  chain_ttZqq->SetProof();
    chain_ttZqq->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq");

    TChain* chain_ttee = new TChain("analysis");
    chain_ttee->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.root");
    //if (proof == 1)  chain_ttee->SetProof();
    chain_ttee->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee");

    TChain* chain_ttmumu = new TChain("analysis");
    chain_ttmumu->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.root");
    //if (proof == 1)  chain_ttmumu->SetProof();
    chain_ttmumu->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu");

    TChain* chain_tttautau = new TChain("analysis");
    chain_tttautau->AddFile(path+"ntuples-mc-samples/mc20_13TeV.410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau.root");
    //if (proof == 1)  chain_tttautau->SetProof();
    chain_tttautau->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau");

  }
}
