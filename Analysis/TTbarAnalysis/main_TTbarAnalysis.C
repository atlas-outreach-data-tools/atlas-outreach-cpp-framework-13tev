//////////////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_TTbarAnalysis(int proof)
{
  // path to your local directory *or* URL, please change the default one!

  /* Local path example */
  TString path = "/afs/cern.ch/user/l/lserkin/Desktop/work/OUTREACH/Outreach/data/";
  
  /* The URL to the ATLAS Open Data website repository */
  //TString path = "http://opendata.atlas.cern/release/samples/";

  //////////////////////////////////////////////////////////////////////////////////////////
  // adding chains of all MC and data samples

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"ttbar.root");
  chain_ttbar_lep->Process("TTbarAnalysis.C+","ttbar_lep");

/*  
  TChain* chain_WW = new TChain("mini");
  chain_WW->AddFile(path+"MC/mc_105985.WW.root");
  chain_WW->Process("TTbarAnalysis.C+","WW");

  TChain* chain_ZZ = new TChain("mini");
  chain_ZZ->AddFile(path+"MC/mc_105986.ZZ.root");
  chain_ZZ->Process("TTbarAnalysis.C+","ZZ");

  TChain* chain_WZ = new TChain("mini");
  chain_WZ->AddFile(path+"MC/mc_105987.WZ.root");
  chain_WZ->Process("TTbarAnalysis.C+","WZ");

  TChain* chain_stop_tchan_top = new TChain("mini");
  chain_stop_tchan_top->AddFile(path+"MC/mc_110090.stop_tchan_top.root");
  chain_stop_tchan_top->Process("TTbarAnalysis.C+","stop_tchan_top");

  TChain* chain_stop_tchan_antitop = new TChain("mini");
  chain_stop_tchan_antitop->AddFile(path+"MC/mc_110091.stop_tchan_antitop.root");
  chain_stop_tchan_antitop->Process("TTbarAnalysis.C+","stop_tchan_antitop");

  TChain* chain_stop_schan = new TChain("mini");
  chain_stop_schan->AddFile(path+"MC/mc_110119.stop_schan.root");
  chain_stop_schan->Process("TTbarAnalysis.C+","stop_schan");

  TChain* chain_stop_wtchan = new TChain("mini");
  chain_stop_wtchan->AddFile(path+"MC/mc_110140.stop_wtchan.root");
  chain_stop_wtchan->Process("TTbarAnalysis.C+","stop_wtchan");

  TChain* chain_ZPrime1000 = new TChain("mini");
  chain_ZPrime1000->AddFile(path+"MC/mc_110903.ZPrime1000.root");
  chain_ZPrime1000->Process("TTbarAnalysis.C+","ZPrime1000");

  TChain* chain_ttbar_had = new TChain("mini");
  chain_ttbar_had->AddFile(path+"MC/mc_117049.ttbar_had.root");
  chain_ttbar_had->Process("TTbarAnalysis.C+","ttbar_had");

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc_117050.ttbar_lep.root");
  chain_ttbar_lep->Process("TTbarAnalysis.C+","ttbar_lep");

  TChain* chain_Zee = new TChain("mini");
  chain_Zee->AddFile(path+"MC/mc_147770.Zee.root");
  chain_Zee->Process("TTbarAnalysis.C+","Zee");

  TChain* chain_Zmumu = new TChain("mini");
  chain_Zmumu->AddFile(path+"MC/mc_147771.Zmumu.root");
  chain_Zmumu->Process("TTbarAnalysis.C+","Zmumu");

  TChain* chain_Ztautau = new TChain("mini");
  chain_Ztautau->AddFile(path+"MC/mc_147772.Ztautau.root");
  chain_Ztautau->Process("TTbarAnalysis.C+","Ztautau");

  TChain* chain_ggH125_WW2lep = new TChain("mini");
  chain_ggH125_WW2lep->AddFile(path+"MC/mc_161005.ggH125_WW2lep.root");
  chain_ggH125_WW2lep->Process("TTbarAnalysis.C+","ggH125_WW2lep");

  TChain* chain_VBFH125_WW2lep = new TChain("mini");
  chain_VBFH125_WW2lep->AddFile(path+"MC/mc_161055.VBFH125_WW2lep.root");
  chain_VBFH125_WW2lep->Process("TTbarAnalysis.C+","VBFH125_WW2lep");

  TChain* chain_Wenu_PTVnuWithB = new TChain("mini");
  chain_Wenu_PTVnuWithB->AddFile(path+"MC/mc_167740.Wenu_PTVnuWithB.root");
  chain_Wenu_PTVnuWithB->Process("TTbarAnalysis.C+","Wenu_PTVnuWithB");

  TChain* chain_Wenu_PTVnuJetsBVeto = new TChain("mini");
  chain_Wenu_PTVnuJetsBVeto->AddFile(path+"MC/mc_167741.Wenu_PTVnuJetsBVeto.root");
  chain_Wenu_PTVnuJetsBVeto->Process("TTbarAnalysis.C+","Wenu_PTVnuJetsBVeto");

  TChain* chain_Wenu_PTVnuNoJetsBVeto = new TChain("mini");
  chain_Wenu_PTVnuNoJetsBVeto->AddFile(path+"MC/mc_167742.Wenu_PTVnuNoJetsBVeto.root");
  chain_Wenu_PTVnuNoJetsBVeto->Process("TTbarAnalysis.C+","Wenu_PTVnuNoJetsBVeto");

  TChain* chain_Wmunu_PTVnuWithB = new TChain("mini");
  chain_Wmunu_PTVnuWithB->AddFile(path+"MC/mc_167743.Wmunu_PTVnuWithB.root");
  chain_Wmunu_PTVnuWithB->Process("TTbarAnalysis.C+","Wmunu_PTVnuWithB");

  TChain* chain_Wmunu_PTVnuJetsBVeto = new TChain("mini");
  chain_Wmunu_PTVnuJetsBVeto->AddFile(path+"MC/mc_167744.Wmunu_PTVnuJetsBVeto.root");
  chain_Wmunu_PTVnuJetsBVeto->Process("TTbarAnalysis.C+","Wmunu_PTVnuJetsBVeto");

  TChain* chain_Wmunu_PTVnuNoJetsBVeto = new TChain("mini");
  chain_Wmunu_PTVnuNoJetsBVeto->AddFile(path+"MC/mc_167745.Wmunu_PTVnuNoJetsBVeto.root");
  chain_Wmunu_PTVnuNoJetsBVeto->Process("TTbarAnalysis.C+","Wmunu_PTVnuNoJetsBVeto");

  TChain* chain_Wtaunu_PTVnuWithB = new TChain("mini");
  chain_Wtaunu_PTVnuWithB->AddFile(path+"MC/mc_167746.Wtaunu_PTVnuWithB.root");
  chain_Wtaunu_PTVnuWithB->Process("TTbarAnalysis.C+","Wtaunu_PTVnuWithB");

  TChain* chain_Wtaunu_PTVnuJetsBVeto = new TChain("mini");
  chain_Wtaunu_PTVnuJetsBVeto->AddFile(path+"MC/mc_167747.Wtaunu_PTVnuJetsBVeto.root");
  chain_Wtaunu_PTVnuJetsBVeto->Process("TTbarAnalysis.C+","Wtaunu_PTVnuJetsBVeto");

  TChain* chain_Wtaunu_PTVnuNoJetsBVeto = new TChain("mini");
  chain_Wtaunu_PTVnuNoJetsBVeto->AddFile(path+"MC/mc_167748.Wtaunu_PTVnuNoJetsBVeto.root");
  chain_Wtaunu_PTVnuNoJetsBVeto->Process("TTbarAnalysis.C+","Wtaunu_PTVnuNoJetsBVeto");

  TChain* chain_DYeeM08to15 = new TChain("mini");
  chain_DYeeM08to15->AddFile(path+"MC/mc_173041.DYeeM08to15.root");
  chain_DYeeM08to15->Process("TTbarAnalysis.C+","DYeeM08to15");

  TChain* chain_DYeeM15to40 = new TChain("mini");
  chain_DYeeM15to40->AddFile(path+"MC/mc_173042.DYeeM15to40.root");
  chain_DYeeM15to40->Process("TTbarAnalysis.C+","DYeeM15to40");

  TChain* chain_DYmumuM08to15 = new TChain("mini");
  chain_DYmumuM08to15->AddFile(path+"MC/mc_173043.DYmumuM08to15.root");
  chain_DYmumuM08to15->Process("TTbarAnalysis.C+","DYmumuM08to15");

  TChain* chain_DYmumuM15to40 = new TChain("mini");
  chain_DYmumuM15to40->AddFile(path+"MC/mc_173044.DYmumuM15to40.root");
  chain_DYmumuM15to40->Process("TTbarAnalysis.C+","DYmumuM15to40");

  TChain* chain_DYtautauM08to15 = new TChain("mini");
  chain_DYtautauM08to15->AddFile(path+"MC/mc_173045.DYtautauM08to15.root");
  chain_DYtautauM08to15->Process("TTbarAnalysis.C+","DYtautauM08to15");

  TChain* chain_DYtautauM15to40 = new TChain("mini");
  chain_DYtautauM15to40->AddFile(path+"MC/mc_173046.DYtautauM15to40.root");
  chain_DYtautauM15to40->Process("TTbarAnalysis.C+","DYtautauM15to40");

  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/DataEgamma.root");
  chain_data->AddFile(path+"Data/DataMuons.root");
  chain_data->Process("TTbarAnalysis.C+","data");


  if (proof == 1)
  {
    TProof::Open("");

    chain_WW->SetProof();
    chain_WZ->SetProof();
    chain_ZZ->SetProof();
    chain_stop_tchan_top->SetProof();
    chain_stop_tchan_antitop->SetProof();
    chain_stop_schan->SetProof();
    chain_stop_wtchan->SetProof();
    chain_ZPrime1000->SetProof();
    chain_ttbar_had->SetProof();
    chain_ttbar_lep->SetProof();
    chain_Zee->SetProof();
    chain_Zmumu->SetProof();
    chain_Ztautau->SetProof();
    chain_ggH125_WW2lep->SetProof();
    chain_VBFH125_WW2lep->SetProof();
    chain_Wenu_PTVnuWithB->SetProof();
    chain_Wenu_PTVnuJetsBVeto->SetProof();
    chain_Wenu_PTVnuNoJetsBVeto->SetProof();
    chain_Wmunu_PTVnuWithB->SetProof();
    chain_Wmunu_PTVnuJetsBVeto->SetProof();
    chain_Wmunu_PTVnuNoJetsBVeto->SetProof();
    chain_Wtaunu_PTVnuWithB->SetProof();
    chain_Wtaunu_PTVnuJetsBVeto->SetProof();
    chain_Wtaunu_PTVnuNoJetsBVeto->SetProof();
    chain_DYeeM08to15->SetProof();
    chain_DYeeM15to40->SetProof();
    chain_DYmumuM08to15->SetProof();
    chain_DYmumuM15to40->SetProof();
    chain_DYtautauM08to15->SetProof();
    chain_DYtautauM15to40->SetProof();
    chain_data->SetProof();

  }
  */
  
}
