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
  //TString path = "/home/student/cpp-13tev/datasets-13-tev/Input/GammaGamma/";
  
  /* The URL to the ATLAS Open Data website repository */
  //TString path = "http://opendata.atlas.cern/release/samples/2019/GamGam/";
  TString path = "/eos/user/t/thsteven/OpenData/opentuplepostprocess/renamed/GamGam/";

  //////////////////////////////////////////////////////////////////////////////////////////
  if (option==1 || option==0)
  {
  //data
  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/data_A.yy.root");
  chain_data->AddFile(path+"Data/data_B.yy.root");
  chain_data->AddFile(path+"Data/data_C.yy.root");
  chain_data->AddFile(path+"Data/data_D.yy.root");
  chain_data->Process("HyyAnalysis.C+","data");
  }

  
  //////////////////////  MC samples
  if (option==2 || option==0)   {
  TChain* chain_ggH = new TChain("mini");
  chain_ggH->AddFile(path+"MC/mc_343981.ggH125_gamgam.gamgam.root");
  chain_ggH->Process("HyyAnalysis.C+","ggH125_gamgam");

  // need to add other production modes
  }


}
