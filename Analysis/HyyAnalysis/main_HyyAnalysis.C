//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_HyyAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!

  /* Local path example */
  //TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/renamedLargeRJets/GamGam/";
  
  /* The URL to the ATLAS Open Data website repository */
  //TString path = "https://atlas-opendata.web.cern.ch/atlas-opendata/samples/2020/GamGam/";

  /* The URL to the CERN Open Data portal repository */
  TString path = "http://opendata.cern.ch/eos/opendata/atlas/OutreachDatasets/2020-01-22/GamGam/"
  
  /* The XROOTD path to the CERN Open Data portal repository */
  //TString path = "root://eospublic.cern.ch//eos/opendata/atlas/OutreachDatasets/2020-01-22/GamGam/"
  
  /* An external mirror */
  //TString path = "http://www.universidad.ch/ATLAS/outreach/open-data-2020/GamGam/"

  //***************************************************************************************************//
  // We run only over data and Higgs MC
  // option==0 will run all one by one
  // Currently 1 option for MC (2) and 1 for data (1) which can be run in parallel
  //***************************************************************************************************//
 
  if (proof == 1)  TProof::Open("");

  if (option==1 || option==0){

  //data
  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/data_A.GamGam.root");
  chain_data->AddFile(path+"Data/data_B.GamGam.root");
  chain_data->AddFile(path+"Data/data_C.GamGam.root");
  chain_data->AddFile(path+"Data/data_D.GamGam.root");
  if (proof == 1)  chain_data->SetProof();
  chain_data->Process("HyyAnalysis.C+","data");
  } // option 1

  if (option==2 || option==0){
  // Higgs MC, ggH production
  TChain* chain_ggH125 = new TChain("mini");
  chain_ggH125->AddFile(path+"MC/mc_343981.ggH125_gamgam.GamGam.root");
  if (proof == 1)  chain_ggH125->SetProof();
  chain_ggH125->Process("HyyAnalysis.C+","ggH125_gamgam");

  // VBF Higgs production
  TChain* chain_VBFH125 = new TChain("mini");
  chain_VBFH125->AddFile(path+"MC/mc_345041.VBFH125_gamgam.GamGam.root");
  if (proof == 1)  chain_VBFH125->SetProof();
  chain_VBFH125->Process("HyyAnalysis.C+","VBFH125_gamgam");

  // WH production
  TChain* chain_WH125 = new TChain("mini");
  chain_WH125->AddFile(path+"MC/mc_345318.WpH125J_Wincl_gamgam.GamGam.root");
  if (proof == 1)  chain_WH125->SetProof();
  chain_WH125->Process("HyyAnalysis.C+","WH125_gamgam");

  // ZH production
  TChain* chain_ZH125 = new TChain("mini");
  chain_ZH125->AddFile(path+"MC/mc_345319.ZH125J_Zincl_gamgam.GamGam.root");
  if (proof == 1)  chain_ZH125->SetProof();
  chain_ZH125->Process("HyyAnalysis.C+","ZH125_gamgam");

  // ttH production
  TChain* chain_ttH125 = new TChain("mini");
  chain_ttH125->AddFile(path+"MC/mc_341081.ttH125_gamgam.GamGam.root");
  if (proof == 1)  chain_ttH125->SetProof();
  chain_ttH125->Process("HyyAnalysis.C+","ttH125_gamgam");
  }//option 2
}
