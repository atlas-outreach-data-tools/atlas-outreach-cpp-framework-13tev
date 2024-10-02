

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
  //TString path = "/eos/user/g/garciarm/ntuple-production-samples/ntuples-open-data/";
  //TString path = "/eos/user/e/egramsta/OpenData/2J2LMET30/";
  TString path = "/eos/user/e/egramsta/OpenData/1LMET30/";
  
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
  // Currently 5 options for MC (2,3,4,5,6) and 1 for data (1) which can be run in parallel
  // If using the options (1) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//

  //if (proof == 1)  TProof::Open("");
  
  if (option==1 || option==0){

    //data15
    
    TChain* chain_data = new TChain("analysis");
    chain_data->AddFile(path+"Data/data15_periodD.root");
    chain_data->AddFile(path+"Data/data15_periodE.root");
    chain_data->AddFile(path+"Data/data15_periodF.root");
    chain_data->AddFile(path+"Data/data15_periodG.root");
    chain_data->AddFile(path+"Data/data15_periodH.root");
    chain_data->AddFile(path+"Data/data15_periodJ.root");
    
    //data16
    
    chain_data->AddFile(path+"Data/data16_periodA.root");
    chain_data->AddFile(path+"Data/data16_periodB.root");
    chain_data->AddFile(path+"Data/data16_periodC.root");
    chain_data->AddFile(path+"Data/data16_periodD.root");
    chain_data->AddFile(path+"Data/data16_periodE.root");
    chain_data->AddFile(path+"Data/data16_periodF.root");
    chain_data->AddFile(path+"Data/data16_periodG.root");
    chain_data->AddFile(path+"Data/data16_PeriodI.root");
    chain_data->AddFile(path+"Data/data16_periodK.root");
    chain_data->AddFile(path+"Data/data16_periodL.root");
    //if (proof == 1)  chain_data->SetProof();
    chain_data->Process("TTbarDilepAnalysis.C+","data");
    
  }
  
  //////////////////////  MC samples
  
  if (option==2 || option==0){
    
    // ttbar samples

    TChain* chain_ttbar_nonallhad = new TChain("analysis");
    chain_ttbar_nonallhad->AddFile(path+"MC/mc_410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.1LMET30.root");
    //if (proof == 1)  chain_ttbar_nonallhad->SetProof();
    chain_ttbar_nonallhad->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_nonallhad");

    TChain* chain_ttbar_allhad = new TChain("analysis");
    chain_ttbar_allhad->AddFile(path+"MC/mc_410471.PhPy8EG_A14_ttbar_hdamp258p75_allhad.1LMET30.root");
    //if (proof == 1)  chain_ttbar_allhad->SetProof();
    chain_ttbar_allhad->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_ttbar_hdamp258p75_allhad");

  }

  if (option==3 || option==0){

    //single top samples
 
    TChain* chain_tchan_BW50_lept_top = new TChain("analysis");
    chain_tchan_BW50_lept_top->AddFile(path+"MC/mc_410658.PhPy8EG_A14_tchan_BW50_lept_top.1LMET30.root");
    //if (proof == 1)  chain_tchan_BW50_lept_top->SetProof();
    chain_tchan_BW50_lept_top->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_top");

    TChain* chain_tchan_BW50_lept_antitop = new TChain("analysis");
    chain_tchan_BW50_lept_antitop->AddFile(path+"MC/mc_410659.PhPy8EG_A14_tchan_BW50_lept_antitop.1LMET30.root");
    //if (proof == 1)  chain_tchan_BW50_lept_antitop->SetProof();
    chain_tchan_BW50_lept_antitop->Process("TTbarDilepAnalysis.C+","PhPy8EG_A14_tchan_BW50_lept_antitop");
    
  }

  if (option==4 || option==0){

    // diboson samples
    TChain* chain_llll = new TChain("analysis");
    chain_llll->AddFile(path+"MC/mc_700600.Sh_2212_llll.1LMET30.root");
    //if (proof == 1)  chain_llll->SetProof();
    chain_llll->Process("TTbarDilepAnalysis.C+","Sh_2212_llll");

    TChain* chain_lllv = new TChain("analysis");
    chain_lllv->AddFile(path+"MC/mc_700601.Sh_2212_lllv.1LMET30.root");
    //if (proof == 1)  chain_lllv->SetProof();
    chain_lllv->Process("TTbarDilepAnalysis.C+","Sh_2212_lllv");
    
    TChain* chain_llvv_os = new TChain("analysis");
    chain_llvv_os->AddFile(path+"MC/mc_700602.Sh_2212_llvv_os.1LMET30.root");
    //if (proof == 1)  chain_llvv_os->SetProof();
    chain_llvv_os->Process("TTbarDilepAnalysis.C+","Sh_2212_llvv_os");

    TChain* chain_llvv_ss = new TChain("analysis");
    chain_llvv_ss->AddFile(path+"MC/mc_700603.Sh_2212_llvv_ss.1LMET30.root");
    //if (proof == 1)  chain_llvv_ss->SetProof();
    chain_llvv_ss->Process("TTbarDilepAnalysis.C+","Sh_2212_llvv_ss");

    TChain* chain_lvvv = new TChain("analysis");
    chain_lvvv->AddFile(path+"MC/mc_700604.Sh_2212_lvvv.1LMET30.root");
    //if (proof == 1)  chain_lvvv->SetProof();
    chain_lvvv->Process("TTbarDilepAnalysis.C+","Sh_2212_lvvv");

    TChain* chain_vvvv = new TChain("analysis");
    chain_vvvv->AddFile(path+"MC/mc_700605.Sh_2212_vvvv.1LMET30.root");
    //if (proof == 1)  chain_vvvv->SetProof();
    chain_vvvv->Process("TTbarDilepAnalysis.C+","Sh_2212_vvvv");

    TChain* chain_WlvWqq = new TChain("analysis");
    chain_WlvWqq->AddFile(path+"MC/mc_700488.Sh_2211_WlvWqq.1LMET30.root");
    //if (proof == 1)  chain_WlvWqq->SetProof();
    chain_WlvWqq->Process("TTbarDilepAnalysis.C+","Sh_2211_WlvWqq");

    TChain* chain_WlvZqq = new TChain("analysis");
    chain_WlvZqq->AddFile(path+"MC/mc_700489.Sh_2211_WlvZqq.1LMET30.root");
    //if (proof == 1)  chain_WlvZqq->SetProof();
    chain_WlvZqq->Process("TTbarDilepAnalysis.C+","Sh_2211_WlvZqq");

    TChain* chain_WlvZbb = new TChain("analysis");
    chain_WlvZbb->AddFile(path+"MC/mc_700490.Sh_2211_WlvZbb.1LMET30.root");
    //if (proof == 1)  chain_WlvZbb->SetProof();
    chain_WlvZbb->Process("TTbarDilepAnalysis.C+","Sh_2211_WlvZbb");   
  
    TChain* chain_ZqqZll = new TChain("analysis");
    chain_ZqqZll->AddFile(path+"MC/mc_700493.Sh_2211_ZqqZll.1LMET30.root");
    //if (proof == 1)  chain_ZqqZll->SetProof();
    chain_ZqqZll->Process("TTbarDilepAnalysis.C+","Sh_2211_ZqqZll");

    TChain* chain_ZbbZll = new TChain("analysis");
    chain_ZbbZll->AddFile(path+"MC/mc_700494.Sh_2211_ZbbZll.1LMET30.root");
    //if (proof == 1)  chain_ZbbZll->SetProof();
    chain_ZbbZll->Process("TTbarDilepAnalysis.C+","Sh_2211_ZbbZll");

    TChain* chain_ZqqZvv = new TChain("analysis");
    chain_ZqqZvv->AddFile(path+"MC/mc_700495.Sh_2211_ZqqZvv.1LMET30.root");
    //if (proof == 1)  chain_ZqqZvv->SetProof();
    chain_ZqqZvv->Process("TTbarDilepAnalysis.C+","Sh_2211_ZqqZvv");
    
    TChain* chain_ZbbZvv = new TChain("analysis");
    chain_ZbbZvv->AddFile(path+"MC/mc_700496.Sh_2211_ZbbZvv.1LMET30.root");
    //if (proof == 1)  chain_ZbbZvv->SetProof();
    chain_ZbbZvv->Process("TTbarDilepAnalysis.C+","Sh_2211_ZbbZvv");

  }

  if (option==5 || option==0){

    // V_plus_jets samples

    TChain* chain_Zee_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zee_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700320.Sh_2211_Zee_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_BFilter->SetProof();
    chain_Zee_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Zee_maxHTpTV2_BFilter");

    TChain* chain_Zee_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zee_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Zee_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Zee_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zee_maxHTpTV2_CVetoBVeto");

    TChain* chain_Zmumu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700323.Sh_2211_Zmumu_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_BFilter->SetProof();
    chain_Zmumu_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_BFilter");

    TChain* chain_Zmumu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700324.Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Zmumu_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Zmumu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Zmumu_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700325.Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Zmumu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Zmumu_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wenu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wenu_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700338.Sh_2211_Wenu_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_BFilter->SetProof();
    chain_Wenu_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_BFilter");

    TChain* chain_Wenu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700339.Sh_2211_Wenu_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wenu_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wenu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wenu_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700340.Sh_2211_Wenu_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wenu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wenu_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wenu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wmunu_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700341.Sh_2211_Wmunu_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_BFilter->SetProof();
    chain_Wmunu_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_BFilter");

    TChain* chain_Wmunu_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700342.Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wmunu_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wmunu_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wmunu_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700343.Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wmunu_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wmunu_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700344.Sh_2211_Wtaunu_L_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_BFilter->SetProof();
    chain_Wtaunu_L_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_L_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700345.Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wtaunu_L_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_L_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700346.Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wtaunu_L_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700347.Sh_2211_Wtaunu_H_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_BFilter->SetProof();
    chain_Wtaunu_H_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_BFilter");

    TChain* chain_Wtaunu_H_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700348.Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Wtaunu_H_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto");

    TChain* chain_Wtaunu_H_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700349.Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Wtaunu_H_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto");

    TChain* chain_Ztautau_maxHTpTV2_BFilter = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_BFilter->AddFile(path+"MC/mc_700792.Sh_2214_Ztautau_maxHTpTV2_BFilter.1LMET30.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_BFilter->SetProof();
    chain_Ztautau_maxHTpTV2_BFilter->Process("TTbarDilepAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_BFilter");
    
    TChain* chain_Ztautau_maxHTpTV2_CFilterBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CFilterBVeto->AddFile(path+"MC/mc_700793.Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto.1LMET30.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_CFilterBVeto->SetProof();
    chain_Ztautau_maxHTpTV2_CFilterBVeto->Process("TTbarDilepAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto");

    TChain* chain_Ztautau_maxHTpTV2_CVetoBVeto = new TChain("analysis");
    chain_Ztautau_maxHTpTV2_CVetoBVeto->AddFile(path+"MC/mc_700794.Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto.1LMET30.root");
    //if (proof == 1)  chain_Ztautau_maxHTpTV2_CVetoBVeto->SetProof();
    chain_Ztautau_maxHTpTV2_CVetoBVeto->Process("TTbarDilepAnalysis.C+","Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto");

  }

  if (option==6 || option==0){

    // tt_others

    TChain* chain_ttW = new TChain("analysis");
    chain_ttW->AddFile(path+"MC/mc_410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW.1LMET30.root");
    //if (proof == 1)  chain_ttW->SetProof();
    chain_ttW->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW");

    TChain* chain_ttZnunu = new TChain("analysis");
    chain_ttZnunu->AddFile(path+"MC/mc_410156.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu.1LMET30.root");
    //if (proof == 1)  chain_ttZnunu->SetProof();
    chain_ttZnunu->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu");

    TChain* chain_ttZqq = new TChain("analysis");
    chain_ttZqq->AddFile(path+"MC/mc_410157.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq.1LMET30.root");
    //if (proof == 1)  chain_ttZqq->SetProof();
    chain_ttZqq->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq");

    TChain* chain_ttee = new TChain("analysis");
    chain_ttee->AddFile(path+"MC/mc_410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.1LMET30.root");
    //if (proof == 1)  chain_ttee->SetProof();
    chain_ttee->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee");

    TChain* chain_ttmumu = new TChain("analysis");
    chain_ttmumu->AddFile(path+"MC/mc_410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.1LMET30.root");
    //if (proof == 1)  chain_ttmumu->SetProof();
    chain_ttmumu->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu");

    TChain* chain_tttautau = new TChain("analysis");
    chain_tttautau->AddFile(path+"MC/mc_410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau.1LMET30.root");
    //if (proof == 1)  chain_tttautau->SetProof();
    chain_tttautau->Process("TTbarDilepAnalysis.C+","aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau");

  }
}
