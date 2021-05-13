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
  //TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/renamedLargeRJets/1lep/";

  /* The URL to the ATLAS Open Data website repository */
//TString path = "https://atlas-opendata.web.cern.ch/atlas-opendata/samples/2020/1lep/";

  /* The URL to the CERN Open Data portal repository */
  TString path = "http://opendata.cern.ch/eos/opendata/atlas/OutreachDatasets/2020-01-22/1lep/"

  /* The XROOTD path to the CERN Open Data portal repository */
  //TString path = "root://eospublic.cern.ch//eos/opendata/atlas/OutreachDatasets/2020-01-22/1lep/"

  /* An external mirror */
  //TString path = "http://www.universidad.ch/ATLAS/outreach/open-data-2020/1lep/"
  
  //***************************************************************************************************//
  // adding chains of all MC and data samples
  // option==0 will run all one by one
  // Currently 4 options for MC (2,3,41,42,43,44) and 4 for data (11,12,13,14) which can be run in parallel
  // If using the options (11,12,13,14) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//
  if (proof == 1)  TProof::Open("");
  
  
  if (option==11 || option==0){
    TChain* chain_dataA = new TChain("mini");
    chain_dataA->AddFile(path+"Data/data_A.1lep.root");
    if (proof == 1)  chain_dataA->SetProof();
    chain_dataA->Process("WBosonAnalysis.C+","dataA");
  }
  
  if (option==12 || option==0){
    TChain* chain_dataB = new TChain("mini");
    chain_dataB->AddFile(path+"Data/data_B.1lep.root");
    if (proof == 1)  chain_dataB->SetProof();
    chain_dataB->Process("WBosonAnalysis.C+","dataB");
  }
  
  if (option==13 || option==0){
    TChain* chain_dataC = new TChain("mini");
    chain_dataC->AddFile(path+"Data/data_C.1lep.root");
    if (proof == 1)  chain_dataC->SetProof();
    chain_dataC->Process("WBosonAnalysis.C+","dataC");
  }
  
  if (option==14 || option==0){
    TChain* chain_dataD = new TChain("mini");
    chain_dataD->AddFile(path+"Data/data_D.1lep.root");
    if (proof == 1)  chain_dataD->SetProof();
    chain_dataD->Process("WBosonAnalysis.C+","dataD");
  }
   
  
  //////////////////////  MC samples
  
  if (option==2 || option==0)   {

    // diboson
    TChain* chain_ZqqZll = new TChain("mini");
    chain_ZqqZll->AddFile(path+"MC/mc_363356.ZqqZll.1lep.root");
    if (proof == 1)  chain_ZqqZll->SetProof();
    chain_ZqqZll->Process("WBosonAnalysis.C+","ZqqZll");
    
    TChain* chain_WqqZll = new TChain("mini");
    chain_WqqZll->AddFile(path+"MC/mc_363358.WqqZll.1lep.root");
    if (proof == 1)  chain_WqqZll->SetProof();
    chain_WqqZll->Process("WBosonAnalysis.C+","WqqZll");
    
    TChain* chain_WpqqWmlv = new TChain("mini");
    chain_WpqqWmlv->AddFile(path+"MC/mc_363359.WpqqWmlv.1lep.root");
    if (proof == 1)  chain_WpqqWmlv->SetProof();
    chain_WpqqWmlv->Process("WBosonAnalysis.C+","WpqqWmlv");
    
    TChain* chain_WplvWmqq = new TChain("mini");
    chain_WplvWmqq->AddFile(path+"MC/mc_363360.WplvWmqq.1lep.root");
    if (proof == 1)  chain_WplvWmqq->SetProof();
    chain_WplvWmqq->Process("WBosonAnalysis.C+","WplvWmqq");
    
    TChain* chain_WlvZqq = new TChain("mini");
    chain_WlvZqq->AddFile(path+"MC/mc_363489.WlvZqq.1lep.root");
    if (proof == 1)  chain_WlvZqq->SetProof();
    chain_WlvZqq->Process("WBosonAnalysis.C+","WlvZqq");
    
    TChain* chain_llll = new TChain("mini");
    chain_llll->AddFile(path+"MC/mc_363490.llll.1lep.root");
    if (proof == 1)  chain_llll->SetProof();
    chain_llll->Process("WBosonAnalysis.C+","llll");
    
    TChain* chain_lllv = new TChain("mini");
    chain_lllv->AddFile(path+"MC/mc_363491.lllv.1lep.root");
    if (proof == 1)  chain_lllv->SetProof();
    chain_lllv->Process("WBosonAnalysis.C+","lllv");
    
    TChain* chain_llvv = new TChain("mini");
    chain_llvv->AddFile(path+"MC/mc_363492.llvv.1lep.root");
    if (proof == 1)  chain_llvv->SetProof();
    chain_llvv->Process("WBosonAnalysis.C+","llvv");
    
    TChain* chain_lvvv = new TChain("mini");
    chain_lvvv->AddFile(path+"MC/mc_363493.lvvv.1lep.root");
    if (proof == 1)  chain_lvvv->SetProof();
    chain_lvvv->Process("WBosonAnalysis.C+","lvvv");
    
    // Z+jets inclusive
    TChain* chain_Zee = new TChain("mini");
    chain_Zee->AddFile(path+"MC/mc_361106.Zee.1lep.root");
    if (proof == 1)  chain_Zee->SetProof();
    chain_Zee->Process("WBosonAnalysis.C+","Zee");
   
    TChain* chain_Zmumu = new TChain("mini");
    chain_Zmumu->AddFile(path+"MC/mc_361107.Zmumu.1lep.root");
    if (proof == 1)  chain_Zmumu->SetProof();
    chain_Zmumu->Process("WBosonAnalysis.C+","Zmumu");
   
    TChain* chain_Ztautau = new TChain("mini");
    chain_Ztautau->AddFile(path+"MC/mc_361108.Ztautau.1lep.root");
    if (proof == 1)  chain_Ztautau->SetProof();
    chain_Ztautau->Process("WBosonAnalysis.C+","Ztautau");
    


  }// option 2
  
  if (option==3 || option==0)   {
    //single top
    TChain* chain_single_top_tchan = new TChain("mini");
    chain_single_top_tchan->AddFile(path+"MC/mc_410011.single_top_tchan.1lep.root");
    if (proof == 1)  chain_single_top_tchan->SetProof();
    chain_single_top_tchan->Process("WBosonAnalysis.C+","single_top_tchan");
    
    TChain* chain_single_antitop_tchan = new TChain("mini");
    chain_single_antitop_tchan->AddFile(path+"MC/mc_410012.single_antitop_tchan.1lep.root");
    if (proof == 1)  chain_single_antitop_tchan->SetProof();
    chain_single_antitop_tchan->Process("WBosonAnalysis.C+","single_antitop_tchan");
    
    TChain* chain_single_top_schan = new TChain("mini");
    chain_single_top_schan->AddFile(path+"MC/mc_410025.single_top_schan.1lep.root");
    if (proof == 1)  chain_single_top_schan->SetProof();
    chain_single_top_schan->Process("WBosonAnalysis.C+","single_top_schan");
    
    TChain* chain_single_antitop_schan = new TChain("mini");
    chain_single_antitop_schan->AddFile(path+"MC/mc_410026.single_antitop_schan.1lep.root");
    if (proof == 1)  chain_single_antitop_schan->SetProof();
    chain_single_antitop_schan->Process("WBosonAnalysis.C+","single_antitop_schan");
    
    TChain* chain_single_top_wtchan = new TChain("mini");
    chain_single_top_wtchan->AddFile(path+"MC/mc_410013.single_top_wtchan.1lep.root");
    if (proof == 1)  chain_single_top_wtchan->SetProof();
    chain_single_top_wtchan->Process("WBosonAnalysis.C+","single_top_wtchan");
    
    TChain* chain_single_antitop_wtchan = new TChain("mini");
    chain_single_antitop_wtchan->AddFile(path+"MC/mc_410014.single_antitop_wtchan.1lep.root");
    if (proof == 1)  chain_single_antitop_wtchan->SetProof();
    chain_single_antitop_wtchan->Process("WBosonAnalysis.C+","single_antitop_wtchan");
    
    //ttbar
    TChain* chain_ttbar_lep = new TChain("mini");
    chain_ttbar_lep->AddFile(path+"MC/mc_410000.ttbar_lep.1lep.root");
    if (proof == 1)  chain_ttbar_lep->SetProof();
    chain_ttbar_lep->Process("WBosonAnalysis.C+","ttbar_lep");
    
  } // option 3
  
  
  // Sherpa W+jets sliced samples
  if (option > 40 || option==0)   {
    
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
    
    
    chain_Wmunu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364156.Wmunu_PTV0_70_CVetoBVeto.1lep.root");
    chain_Wmunu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364157.Wmunu_PTV0_70_CFilterBVeto.1lep.root");
    chain_Wmunu_PTV0_70_BFilter->AddFile(path+"MC/mc_364158.Wmunu_PTV0_70_BFilter.1lep.root");
    chain_Wmunu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364159.Wmunu_PTV70_140_CVetoBVeto.1lep.root");
    chain_Wmunu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364160.Wmunu_PTV70_140_CFilterBVeto.1lep.root");
    chain_Wmunu_PTV70_140_BFilter->AddFile(path+"MC/mc_364161.Wmunu_PTV70_140_BFilter.1lep.root");
    chain_Wmunu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364162.Wmunu_PTV140_280_CVetoBVeto.1lep.root");
    chain_Wmunu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364163.Wmunu_PTV140_280_CFilterBVeto.1lep.root");
    chain_Wmunu_PTV140_280_BFilter->AddFile(path+"MC/mc_364164.Wmunu_PTV140_280_BFilter.1lep.root");
    chain_Wmunu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364165.Wmunu_PTV280_500_CVetoBVeto.1lep.root");
    chain_Wmunu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364166.Wmunu_PTV280_500_CFilterBVeto.1lep.root");
    chain_Wmunu_PTV280_500_BFilter->AddFile(path+"MC/mc_364167.Wmunu_PTV280_500_BFilter.1lep.root");
    chain_Wmunu_PTV500_1000->AddFile(path+"MC/mc_364168.Wmunu_PTV500_1000.1lep.root");
    chain_Wmunu_PTV1000_E_CMS->AddFile(path+"MC/mc_364169.Wmunu_PTV1000_E_CMS.1lep.root");
    chain_Wenu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364170.Wenu_PTV0_70_CVetoBVeto.1lep.root");
    chain_Wenu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364171.Wenu_PTV0_70_CFilterBVeto.1lep.root");
    chain_Wenu_PTV0_70_BFilter->AddFile(path+"MC/mc_364172.Wenu_PTV0_70_BFilter.1lep.root");
    chain_Wenu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364173.Wenu_PTV70_140_CVetoBVeto.1lep.root");
    chain_Wenu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364174.Wenu_PTV70_140_CFilterBVeto.1lep.root");
    chain_Wenu_PTV70_140_BFilter->AddFile(path+"MC/mc_364175.Wenu_PTV70_140_BFilter.1lep.root");
    chain_Wenu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364176.Wenu_PTV140_280_CVetoBVeto.1lep.root");
    chain_Wenu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364177.Wenu_PTV140_280_CFilterBVeto.1lep.root");
    chain_Wenu_PTV140_280_BFilter->AddFile(path+"MC/mc_364178.Wenu_PTV140_280_BFilter.1lep.root");
    chain_Wenu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364179.Wenu_PTV280_500_CVetoBVeto.1lep.root");
    chain_Wenu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364180.Wenu_PTV280_500_CFilterBVeto.1lep.root");
    chain_Wenu_PTV280_500_BFilter->AddFile(path+"MC/mc_364181.Wenu_PTV280_500_BFilter.1lep.root");
    chain_Wenu_PTV500_1000->AddFile(path+"MC/mc_364182.Wenu_PTV500_1000.1lep.root");
    chain_Wenu_PTV1000_E_CMS->AddFile(path+"MC/mc_364183.Wenu_PTV1000_E_CMS.1lep.root");
    chain_Wtaunu_PTV0_70_CVetoBVeto->AddFile(path+"MC/mc_364184.Wtaunu_PTV0_70_CVetoBVeto.1lep.root");
    chain_Wtaunu_PTV0_70_CFilterBVeto->AddFile(path+"MC/mc_364185.Wtaunu_PTV0_70_CFilterBVeto.1lep.root");
    chain_Wtaunu_PTV0_70_BFilter->AddFile(path+"MC/mc_364186.Wtaunu_PTV0_70_BFilter.1lep.root");
    chain_Wtaunu_PTV70_140_CVetoBVeto->AddFile(path+"MC/mc_364187.Wtaunu_PTV70_140_CVetoBVeto.1lep.root");
    chain_Wtaunu_PTV70_140_CFilterBVeto->AddFile(path+"MC/mc_364188.Wtaunu_PTV70_140_CFilterBVeto.1lep.root");
    chain_Wtaunu_PTV70_140_BFilter->AddFile(path+"MC/mc_364189.Wtaunu_PTV70_140_BFilter.1lep.root");
    chain_Wtaunu_PTV140_280_CVetoBVeto->AddFile(path+"MC/mc_364190.Wtaunu_PTV140_280_CVetoBVeto.1lep.root");
    chain_Wtaunu_PTV140_280_CFilterBVeto->AddFile(path+"MC/mc_364191.Wtaunu_PTV140_280_CFilterBVeto.1lep.root");
    chain_Wtaunu_PTV140_280_BFilter->AddFile(path+"MC/mc_364192.Wtaunu_PTV140_280_BFilter.1lep.root");
    chain_Wtaunu_PTV280_500_CVetoBVeto->AddFile(path+"MC/mc_364193.Wtaunu_PTV280_500_CVetoBVeto.1lep.root");
    chain_Wtaunu_PTV280_500_CFilterBVeto->AddFile(path+"MC/mc_364194.Wtaunu_PTV280_500_CFilterBVeto.1lep.root");
    chain_Wtaunu_PTV280_500_BFilter->AddFile(path+"MC/mc_364195.Wtaunu_PTV280_500_BFilter.1lep.root");
    chain_Wtaunu_PTV500_1000->AddFile(path+"MC/mc_364196.Wtaunu_PTV500_1000.1lep.root");
    chain_Wtaunu_PTV1000_E_CM->AddFile(path+"MC/mc_364197.Wtaunu_PTV1000_E_CMS.1lep.root");
    
    
    if (proof == 1) {
      chain_Wmunu_PTV0_70_CVetoBVeto->SetProof();
      chain_Wmunu_PTV0_70_CFilterBVeto->SetProof();
      chain_Wmunu_PTV0_70_BFilter->SetProof();
      chain_Wmunu_PTV70_140_CVetoBVeto->SetProof();
      chain_Wmunu_PTV70_140_CFilterBVeto->SetProof();
      chain_Wmunu_PTV70_140_BFilter->SetProof();
      chain_Wmunu_PTV140_280_CVetoBVeto->SetProof();
      chain_Wmunu_PTV140_280_CFilterBVeto->SetProof();
      chain_Wmunu_PTV140_280_BFilter->SetProof();
      chain_Wmunu_PTV280_500_CVetoBVeto->SetProof();
      chain_Wmunu_PTV280_500_CFilterBVeto->SetProof();
      chain_Wmunu_PTV280_500_BFilter->SetProof();
      chain_Wmunu_PTV500_1000->SetProof();
      chain_Wmunu_PTV1000_E_CMS->SetProof();
      chain_Wenu_PTV0_70_CVetoBVeto->SetProof();
      chain_Wenu_PTV0_70_CFilterBVeto->SetProof();
      chain_Wenu_PTV0_70_BFilter->SetProof();
      chain_Wenu_PTV70_140_CVetoBVeto->SetProof();
      chain_Wenu_PTV70_140_CFilterBVeto->SetProof();
      chain_Wenu_PTV70_140_BFilter->SetProof();
      chain_Wenu_PTV140_280_CVetoBVeto->SetProof();
      chain_Wenu_PTV140_280_CFilterBVeto->SetProof();
      chain_Wenu_PTV140_280_BFilter->SetProof();
      chain_Wenu_PTV280_500_CVetoBVeto->SetProof();
      chain_Wenu_PTV280_500_CFilterBVeto->SetProof();
      chain_Wenu_PTV280_500_BFilter->SetProof();
      chain_Wenu_PTV500_1000->SetProof();
      chain_Wenu_PTV1000_E_CMS->SetProof();
      chain_Wtaunu_PTV0_70_CVetoBVeto->SetProof();
      chain_Wtaunu_PTV0_70_CFilterBVeto->SetProof();
      chain_Wtaunu_PTV0_70_BFilter->SetProof();
      chain_Wtaunu_PTV70_140_CVetoBVeto->SetProof();
      chain_Wtaunu_PTV70_140_CFilterBVeto->SetProof();
      chain_Wtaunu_PTV70_140_BFilter->SetProof();
      chain_Wtaunu_PTV140_280_CVetoBVeto->SetProof();
      chain_Wtaunu_PTV140_280_CFilterBVeto->SetProof();
      chain_Wtaunu_PTV140_280_BFilter->SetProof();
      chain_Wtaunu_PTV280_500_CVetoBVeto->SetProof();
      chain_Wtaunu_PTV280_500_CFilterBVeto->SetProof();
      chain_Wtaunu_PTV280_500_BFilter->SetProof();
      chain_Wtaunu_PTV500_1000->SetProof();
      chain_Wtaunu_PTV1000_E_CM->SetProof();
    } // option proof
    
    
    
    
    
    if (option == 41 || option==0)   {
      chain_Wmunu_PTV0_70_CVetoBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV0_70_CVetoBVeto");
      chain_Wmunu_PTV0_70_CFilterBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV0_70_CFilterBVeto");
      chain_Wmunu_PTV0_70_BFilter->Process("WBosonAnalysis.C+","Wmunu_PTV0_70_BFilter");
      chain_Wmunu_PTV70_140_CVetoBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV70_140_CVetoBVeto");
      chain_Wmunu_PTV70_140_CFilterBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV70_140_CFilterBVeto");
      chain_Wmunu_PTV70_140_BFilter->Process("WBosonAnalysis.C+","Wmunu_PTV70_140_BFilter");
      chain_Wmunu_PTV140_280_CVetoBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV140_280_CVetoBVeto");
      chain_Wmunu_PTV140_280_CFilterBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV140_280_CFilterBVeto");
      chain_Wmunu_PTV140_280_BFilter->Process("WBosonAnalysis.C+","Wmunu_PTV140_280_BFilter");
      chain_Wmunu_PTV280_500_CVetoBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV280_500_CVetoBVeto");
    }
    
    if (option == 42 || option==0)   {
      chain_Wmunu_PTV280_500_CFilterBVeto->Process("WBosonAnalysis.C+","Wmunu_PTV280_500_CFilterBVeto");
      chain_Wmunu_PTV280_500_BFilter->Process("WBosonAnalysis.C+","Wmunu_PTV280_500_BFilter");
      chain_Wmunu_PTV500_1000->Process("WBosonAnalysis.C+","Wmunu_PTV500_1000");
      chain_Wmunu_PTV1000_E_CMS->Process("WBosonAnalysis.C+","Wmunu_PTV1000");
      chain_Wenu_PTV0_70_CVetoBVeto->Process("WBosonAnalysis.C+","Wenu_PTV0_70_CVetoBVeto");
      chain_Wenu_PTV0_70_CFilterBVeto->Process("WBosonAnalysis.C+","Wenu_PTV0_70_CFilterBVeto");
      chain_Wenu_PTV0_70_BFilter->Process("WBosonAnalysis.C+","Wenu_PTV0_70_BFilter");
      chain_Wenu_PTV70_140_CVetoBVeto->Process("WBosonAnalysis.C+","Wenu_PTV70_140_CVetoBVeto");
      chain_Wenu_PTV70_140_CFilterBVeto->Process("WBosonAnalysis.C+","Wenu_PTV70_140_CFilterBVeto");
      chain_Wenu_PTV70_140_BFilter->Process("WBosonAnalysis.C+","Wenu_PTV70_140_BFilter");
    }
    
    if (option == 43 || option==0)   {
      chain_Wenu_PTV140_280_CVetoBVeto->Process("WBosonAnalysis.C+","Wenu_PTV140_280_CVetoBVeto");
      chain_Wenu_PTV140_280_CFilterBVeto->Process("WBosonAnalysis.C+","Wenu_PTV140_280_CFilterBVeto");
      chain_Wenu_PTV140_280_BFilter->Process("WBosonAnalysis.C+","Wenu_PTV140_280_BFilter");
      chain_Wenu_PTV280_500_CVetoBVeto->Process("WBosonAnalysis.C+","Wenu_PTV280_500_CVetoBVeto");
      chain_Wenu_PTV280_500_CFilterBVeto->Process("WBosonAnalysis.C+","Wenu_PTV280_500_CFilterBVeto");
      chain_Wenu_PTV280_500_BFilter->Process("WBosonAnalysis.C+","Wenu_PTV280_500_BFilter");
      chain_Wenu_PTV500_1000->Process("WBosonAnalysis.C+","Wenu_PTV500_1000");
      chain_Wenu_PTV1000_E_CMS->Process("WBosonAnalysis.C+","Wenu_PTV1000");
      chain_Wtaunu_PTV0_70_CVetoBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV0_70_CVetoBVeto");
      chain_Wtaunu_PTV0_70_CFilterBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV0_70_CFilterBVeto");
    }
    
    if (option == 44 || option==0)   {
      chain_Wtaunu_PTV0_70_BFilter->Process("WBosonAnalysis.C+","Wtaunu_PTV0_70_BFilter");
      chain_Wtaunu_PTV70_140_CVetoBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV70_140_CVetoBVeto");
      chain_Wtaunu_PTV70_140_CFilterBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV70_140_CFilterBVeto");
      chain_Wtaunu_PTV70_140_BFilter->Process("WBosonAnalysis.C+","Wtaunu_PTV70_140_BFilter");
      chain_Wtaunu_PTV140_280_CVetoBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV140_280_CVetoBVeto");
      chain_Wtaunu_PTV140_280_CFilterBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV140_280_CFilterBVeto");
      chain_Wtaunu_PTV140_280_BFilter->Process("WBosonAnalysis.C+","Wtaunu_PTV140_280_BFilter");
      chain_Wtaunu_PTV280_500_CVetoBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV280_500_CVetoBVeto");
      chain_Wtaunu_PTV280_500_CFilterBVeto->Process("WBosonAnalysis.C+","Wtaunu_PTV280_500_CFilterBVeto");
      chain_Wtaunu_PTV280_500_BFilter->Process("WBosonAnalysis.C+","Wtaunu_PTV280_500_BFilter");
      chain_Wtaunu_PTV500_1000->Process("WBosonAnalysis.C+","Wtaunu_PTV500_1000");
      chain_Wtaunu_PTV1000_E_CM->Process("WBosonAnalysis.C+","Wtaunu_PTV1000");
    }
    
  } // W+jets Sherpa
  
  
}
