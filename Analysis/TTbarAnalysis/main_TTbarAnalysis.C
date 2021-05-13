//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_TTbarAnalysis(int proof = 0, int option= 0)
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
  // Currently 4 options for MC (2,3,4,5) and 4 for data (11,12,13,14) which can be run in parallel
  // If using the options (11,12,13,14) of splitting data, 
  // you need to add the samples later with: hadd data.root dataA.root dataB.root dataC.root dataD.root
  //***************************************************************************************************//
  if (proof == 1)  TProof::Open("");
  
  
  if (option==11 || option==0){
    TChain* chain_dataA = new TChain("mini");
    chain_dataA->AddFile(path+"Data/data_A.1lep.root");
    if (proof == 1)  chain_dataA->SetProof();
    chain_dataA->Process("TTbarAnalysis.C+","dataA");
  }
  
  if (option==12 || option==0){
    TChain* chain_dataB = new TChain("mini");
    chain_dataB->AddFile(path+"Data/data_B.1lep.root");
    if (proof == 1)  chain_dataB->SetProof();
    chain_dataB->Process("TTbarAnalysis.C+","dataB");
  }
  
  if (option==13 || option==0){
    TChain* chain_dataC = new TChain("mini");
    chain_dataC->AddFile(path+"Data/data_C.1lep.root");
    if (proof == 1)  chain_dataC->SetProof();
    chain_dataC->Process("TTbarAnalysis.C+","dataC");
  }
  
  if (option==14 || option==0){
    TChain* chain_dataD = new TChain("mini");
    chain_dataD->AddFile(path+"Data/data_D.1lep.root");
    if (proof == 1)  chain_dataD->SetProof();
    chain_dataD->Process("TTbarAnalysis.C+","dataD");
  }
   
  
  //////////////////////  MC samples
  
  if (option==2 || option==0)   {
    
    // diboson
    TChain* chain_ZqqZll = new TChain("mini");
    chain_ZqqZll->AddFile(path+"MC/mc_363356.ZqqZll.1lep.root");
    if (proof == 1)  chain_ZqqZll->SetProof();
    chain_ZqqZll->Process("TTbarAnalysis.C+","ZqqZll");
    
    TChain* chain_WqqZll = new TChain("mini");
    chain_WqqZll->AddFile(path+"MC/mc_363358.WqqZll.1lep.root");
    if (proof == 1)  chain_WqqZll->SetProof();
    chain_WqqZll->Process("TTbarAnalysis.C+","WqqZll");
    
    TChain* chain_WpqqWmlv = new TChain("mini");
    chain_WpqqWmlv->AddFile(path+"MC/mc_363359.WpqqWmlv.1lep.root");
    if (proof == 1)  chain_WpqqWmlv->SetProof();
    chain_WpqqWmlv->Process("TTbarAnalysis.C+","WpqqWmlv");
    
    TChain* chain_WplvWmqq = new TChain("mini");
    chain_WplvWmqq->AddFile(path+"MC/mc_363360.WplvWmqq.1lep.root");
    if (proof == 1)  chain_WplvWmqq->SetProof();
    chain_WplvWmqq->Process("TTbarAnalysis.C+","WplvWmqq");
    
    TChain* chain_WlvZqq = new TChain("mini");
    chain_WlvZqq->AddFile(path+"MC/mc_363489.WlvZqq.1lep.root");
    if (proof == 1)  chain_WlvZqq->SetProof();
    chain_WlvZqq->Process("TTbarAnalysis.C+","WlvZqq");
    
    TChain* chain_llll = new TChain("mini");
    chain_llll->AddFile(path+"MC/mc_363490.llll.1lep.root");
    if (proof == 1)  chain_llll->SetProof();
    chain_llll->Process("TTbarAnalysis.C+","llll");
    
    TChain* chain_lllv = new TChain("mini");
    chain_lllv->AddFile(path+"MC/mc_363491.lllv.1lep.root");
    if (proof == 1)  chain_lllv->SetProof();
    chain_lllv->Process("TTbarAnalysis.C+","lllv");
    
    TChain* chain_llvv = new TChain("mini");
    chain_llvv->AddFile(path+"MC/mc_363492.llvv.1lep.root");
    if (proof == 1)  chain_llvv->SetProof();
    chain_llvv->Process("TTbarAnalysis.C+","llvv");
    
    TChain* chain_lvvv = new TChain("mini");
    chain_lvvv->AddFile(path+"MC/mc_363493.lvvv.1lep.root");
    if (proof == 1)  chain_lvvv->SetProof();
    chain_lvvv->Process("TTbarAnalysis.C+","lvvv");
    
    
    // Z+jets inclusive
    TChain* chain_Zee = new TChain("mini");
    chain_Zee->AddFile(path+"MC/mc_361106.Zee.1lep.root");
    if (proof == 1)  chain_Zee->SetProof();
    chain_Zee->Process("TTbarAnalysis.C+","Zee");
    
    TChain* chain_Zmumu = new TChain("mini");
    chain_Zmumu->AddFile(path+"MC/mc_361107.Zmumu.1lep.root");
    if (proof == 1)  chain_Zmumu->SetProof();
    chain_Zmumu->Process("TTbarAnalysis.C+","Zmumu");
    
    TChain* chain_Ztautau = new TChain("mini");
    chain_Ztautau->AddFile(path+"MC/mc_361108.Ztautau.1lep.root");
    if (proof == 1)  chain_Ztautau->SetProof();
    chain_Ztautau->Process("TTbarAnalysis.C+","Ztautau");
  }// option 2
  

  if (option==3 || option==0)   {
    //single top
    TChain* chain_single_top_tchan = new TChain("mini");
    chain_single_top_tchan->AddFile(path+"MC/mc_410011.single_top_tchan.1lep.root");
    if (proof == 1)  chain_single_top_tchan->SetProof();
    chain_single_top_tchan->Process("TTbarAnalysis.C+","single_top_tchan");
    
    TChain* chain_single_antitop_tchan = new TChain("mini");
    chain_single_antitop_tchan->AddFile(path+"MC/mc_410012.single_antitop_tchan.1lep.root");
    if (proof == 1)  chain_single_antitop_tchan->SetProof();
    chain_single_antitop_tchan->Process("TTbarAnalysis.C+","single_antitop_tchan");
    
    TChain* chain_single_top_schan = new TChain("mini");
    chain_single_top_schan->AddFile(path+"MC/mc_410025.single_top_schan.1lep.root");
    if (proof == 1)  chain_single_top_schan->SetProof();
    chain_single_top_schan->Process("TTbarAnalysis.C+","single_top_schan");
    
    TChain* chain_single_antitop_schan = new TChain("mini");
    chain_single_antitop_schan->AddFile(path+"MC/mc_410026.single_antitop_schan.1lep.root");
    if (proof == 1)  chain_single_antitop_schan->SetProof();
    chain_single_antitop_schan->Process("TTbarAnalysis.C+","single_antitop_schan");
    
    TChain* chain_single_top_wtchan = new TChain("mini");
    chain_single_top_wtchan->AddFile(path+"MC/mc_410013.single_top_wtchan.1lep.root");
    if (proof == 1)  chain_single_top_wtchan->SetProof();
    chain_single_top_wtchan->Process("TTbarAnalysis.C+","single_top_wtchan");
    
    TChain* chain_single_antitop_wtchan = new TChain("mini");
    chain_single_antitop_wtchan->AddFile(path+"MC/mc_410014.single_antitop_wtchan.1lep.root");
    if (proof == 1)  chain_single_antitop_wtchan->SetProof();
    chain_single_antitop_wtchan->Process("TTbarAnalysis.C+","single_antitop_wtchan");

    //ttbar
    TChain* chain_ttbar_lep = new TChain("mini");
    chain_ttbar_lep->AddFile(path+"MC/mc_410000.ttbar_lep.1lep.root");
    if (proof == 1)  chain_ttbar_lep->SetProof();
    chain_ttbar_lep->Process("TTbarAnalysis.C+","ttbar_lep");
    
  } // option 3
  
  
  if (option==4 || option==0)   {
  // W+jets inclusive
  TChain* chain_Wplusenu = new TChain("mini");
  chain_Wplusenu->AddFile(path+"MC/mc_361100.Wplusenu.1lep.root");
  if (proof == 1)  chain_Wplusenu->SetProof();
  chain_Wplusenu->Process("TTbarAnalysis.C+","Wplusenu");

  TChain* chain_Wplusmunu = new TChain("mini");
  chain_Wplusmunu->AddFile(path+"MC/mc_361101.Wplusmunu.1lep.root");
  if (proof == 1)  chain_Wplusmunu->SetProof();
  chain_Wplusmunu->Process("TTbarAnalysis.C+","Wplusmunu");

  TChain* chain_Wplustaunu = new TChain("mini");
  chain_Wplustaunu->AddFile(path+"MC/mc_361102.Wplustaunu.1lep.root");
  if (proof == 1)  chain_Wplustaunu->SetProof();
  chain_Wplustaunu->Process("TTbarAnalysis.C+","Wplustaunu");
  } // option 4

  if (option==5 || option==0)   {
  TChain* chain_Wminusenu = new TChain("mini");
  chain_Wminusenu->AddFile(path+"MC/mc_361103.Wminusenu.1lep.root");
  if (proof == 1)  chain_Wminusenu->SetProof();
  chain_Wminusenu->Process("TTbarAnalysis.C+","Wminusenu");

  TChain* chain_Wminusmunu = new TChain("mini");
  chain_Wminusmunu->AddFile(path+"MC/mc_361104.Wminusmunu.1lep.root");
  if (proof == 1)  chain_Wminusmunu->SetProof();
  chain_Wminusmunu->Process("TTbarAnalysis.C+","Wminusmunu");

  TChain* chain_Wminustaunu = new TChain("mini");
  chain_Wminustaunu->AddFile(path+"MC/mc_361105.Wminustaunu.1lep.root");
  if (proof == 1)  chain_Wminustaunu->SetProof();
  chain_Wminustaunu->Process("TTbarAnalysis.C+","Wminustaunu");
  } // option 5

  
}
