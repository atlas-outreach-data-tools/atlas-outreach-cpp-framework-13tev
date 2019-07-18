//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
//#include "TProof.h"

void main_HyyAnalysis(int proof = 0, int option= 0)
{
  // path to your local directory *or* URL, please change the default one!

  /* Local path example */
  TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/GamGam/";
  
  /* The URL to the ATLAS Open Data website repository */
  //  TString path = "http://opendata.atlas.cern/release/samples/";

  //////////////////////////////////////////////////////////////////////////////////////////
  if (option==1 || option==0)
  {
  //data
  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/dataA_yy.root");
  chain_data->AddFile(path+"Data/dataB_yy.root");
  chain_data->AddFile(path+"Data/dataC_yy.root");
  chain_data->AddFile(path+"Data/data302737-303338_yy.root");
  chain_data->Process("HyyAnalysis.C+","data");
  }

  
  //////////////////////  MC samples
  if (option==2 || option==0)   {
  TChain* chain_ggH = new TChain("mini");
  chain_ggH->AddFile(path+"MC/mc15_13TeV.343981.PwPy8EG_NNLOPS_nnlo_30_ggH125_gamgam.gamgam_raw.root");
  chain_ggH->Process("HyyAnalysis.C+","ggH125_gamgam");

  // need to add other production modes
  }


}
