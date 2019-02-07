//////////////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TProof.h"

void main_WBosonAnalysis(int proof)
{
  // path to your local directory *or* URL, please change the default one!

  /* Local path example */
  //TString path = "/username/atlas-outreach-cpp-framework/Input/";
  
  /* The URL to the ATLAS Open Data website repository */
  TString path = "http://opendata.atlas.cern/release/samples/";

  //////////////////////////////////////////////////////////////////////////////////////////
  // adding chains of all MC and data samples

  TChain* chain_WW = new TChain("mini");
  chain_WW->AddFile(path+"MC/mc_105985.WW.root");
  chain_WW->Process("WBosonAnalysis.C+","WW");

  TChain* chain_ZZ = new TChain("mini");
  chain_ZZ->AddFile(path+"MC/mc_105986.ZZ.root");
  chain_ZZ->Process("WBosonAnalysis.C+","ZZ");

  TChain* chain_WZ = new TChain("mini");
  chain_WZ->AddFile(path+"MC/mc_105987.WZ.root");
  chain_WZ->Process("WBosonAnalysis.C+","WZ");

  TChain* chain_stop_tchan_top = new TChain("mini");
  chain_stop_tchan_top->AddFile(path+"MC/mc_110090.stop_tchan_top.root");
  chain_stop_tchan_top->Process("WBosonAnalysis.C+","stop_tchan_top");

  TChain* chain_stop_tchan_antitop = new TChain("mini");
  chain_stop_tchan_antitop->AddFile(path+"MC/mc_110091.stop_tchan_antitop.root");
  chain_stop_tchan_antitop->Process("WBosonAnalysis.C+","stop_tchan_antitop");

  TChain* chain_stop_schan = new TChain("mini");
  chain_stop_schan->AddFile(path+"MC/mc_110119.stop_schan.root");
  chain_stop_schan->Process("WBosonAnalysis.C+","stop_schan");

  TChain* chain_stop_wtchan = new TChain("mini");
  chain_stop_wtchan->AddFile(path+"MC/mc_110140.stop_wtchan.root");
  chain_stop_wtchan->Process("WBosonAnalysis.C+","stop_wtchan");

  TChain* chain_ZPrime1000 = new TChain("mini");
  chain_ZPrime1000->AddFile(path+"MC/mc_110903.ZPrime1000.root");
  chain_ZPrime1000->Process("WBosonAnalysis.C+","ZPrime1000");

  TChain* chain_ttbar_had = new TChain("mini");
  chain_ttbar_had->AddFile(path+"MC/mc_117049.ttbar_had.root");
  chain_ttbar_had->Process("WBosonAnalysis.C+","ttbar_had");

  TChain* chain_ttbar_lep = new TChain("mini");
  chain_ttbar_lep->AddFile(path+"MC/mc_117050.ttbar_lep.root");
  chain_ttbar_lep->Process("WBosonAnalysis.C+","ttbar_lep");

  TChain* chain_Z_ee = new TChain("mini");
  chain_Z_ee->AddFile(path+"MC/mc_147770.Zee.root");
  chain_Z_ee->Process("WBosonAnalysis.C+","Z_ee");

  TChain* chain_Z_mumu = new TChain("mini");
  chain_Z_mumu->AddFile(path+"MC/mc_147771.Zmumu.root");
  chain_Z_mumu->Process("WBosonAnalysis.C+","Z_mumu");

  TChain* chain_Z_tautau = new TChain("mini");
  chain_Z_tautau->AddFile(path+"MC/mc_147772.Ztautau.root");
  chain_Z_tautau->Process("WBosonAnalysis.C+","Z_tautau");

  TChain* chain_ggH125_WW2lep = new TChain("mini");
  chain_ggH125_WW2lep->AddFile(path+"MC/mc_161005.ggH125_WW2lep.root");
  chain_ggH125_WW2lep->Process("WBosonAnalysis.C+","ggH125_WW2lep");

  TChain* chain_VBFH125_WW2lep = new TChain("mini");
  chain_VBFH125_WW2lep->AddFile(path+"MC/mc_161055.VBFH125_WW2lep.root");
  chain_VBFH125_WW2lep->Process("WBosonAnalysis.C+","VBFH125_WW2lep");

  TChain* chain_WenuWithB = new TChain("mini");
  chain_WenuWithB->AddFile(path+"MC/mc_167740.WenuWithB.root");
  chain_WenuWithB->Process("WBosonAnalysis.C+","WenuWithB");

  TChain* chain_WenuJetsBVeto = new TChain("mini");
  chain_WenuJetsBVeto->AddFile(path+"MC/mc_167741.WenuJetsBVeto.root");
  chain_WenuJetsBVeto->Process("WBosonAnalysis.C+","WenuJetsBVeto");

  TChain* chain_WenuNoJetsBVeto = new TChain("mini");
  chain_WenuNoJetsBVeto->AddFile(path+"MC/mc_167742.WenuNoJetsBVeto.root");
  chain_WenuNoJetsBVeto->Process("WBosonAnalysis.C+","WenuNoJetsBVeto");

  TChain* chain_WmunuWithB = new TChain("mini");
  chain_WmunuWithB->AddFile(path+"MC/mc_167743.WmunuWithB.root");
  chain_WmunuWithB->Process("WBosonAnalysis.C+","WmunuWithB");

  TChain* chain_WmunuJetsBVeto = new TChain("mini");
  chain_WmunuJetsBVeto->AddFile(path+"MC/mc_167744.WmunuJetsBVeto.root");
  chain_WmunuJetsBVeto->Process("WBosonAnalysis.C+","WmunuJetsBVeto");

  TChain* chain_WmunuNoJetsBVeto = new TChain("mini");
  chain_WmunuNoJetsBVeto->AddFile(path+"MC/mc_167745.WmunuNoJetsBVeto.root");
  chain_WmunuNoJetsBVeto->Process("WBosonAnalysis.C+","WmunuNoJetsBVeto");

  TChain* chain_WtaunuWithB = new TChain("mini");
  chain_WtaunuWithB->AddFile(path+"MC/mc_167746.WtaunuWithB.root");
  chain_WtaunuWithB->Process("WBosonAnalysis.C+","WtaunuWithB");

  TChain* chain_WtaunuJetsBVeto = new TChain("mini");
  chain_WtaunuJetsBVeto->AddFile(path+"MC/mc_167747.WtaunuJetsBVeto.root");
  chain_WtaunuJetsBVeto->Process("WBosonAnalysis.C+","WtaunuJetsBVeto");

  TChain* chain_WtaunuNoJetsBVeto = new TChain("mini");
  chain_WtaunuNoJetsBVeto->AddFile(path+"MC/mc_167748.WtaunuNoJetsBVeto.root");
  chain_WtaunuNoJetsBVeto->Process("WBosonAnalysis.C+","WtaunuNoJetsBVeto");

  TChain* chain_DYeeM08to15 = new TChain("mini");
  chain_DYeeM08to15->AddFile(path+"MC/mc_173041.DYeeM08to15.root");
  chain_DYeeM08to15->Process("WBosonAnalysis.C+","DYeeM08to15");

  TChain* chain_DYeeM15to40 = new TChain("mini");
  chain_DYeeM15to40->AddFile(path+"MC/mc_173042.DYeeM15to40.root");
  chain_DYeeM15to40->Process("WBosonAnalysis.C+","DYeeM15to40");

  TChain* chain_DYmumuM08to15 = new TChain("mini");
  chain_DYmumuM08to15->AddFile(path+"MC/mc_173043.DYmumuM08to15.root");
  chain_DYmumuM08to15->Process("WBosonAnalysis.C+","DYmumuM08to15");

  TChain* chain_DYmumuM15to40 = new TChain("mini");
  chain_DYmumuM15to40->AddFile(path+"MC/mc_173044.DYmumuM15to40.root");
  chain_DYmumuM15to40->Process("WBosonAnalysis.C+","DYmumuM15to40");

  TChain* chain_DYtautauM08to15 = new TChain("mini");
  chain_DYtautauM08to15->AddFile(path+"MC/mc_173045.DYtautauM08to15.root");
  chain_DYtautauM08to15->Process("WBosonAnalysis.C+","DYtautauM08to15");

  TChain* chain_DYtautauM15to40 = new TChain("mini");
  chain_DYtautauM15to40->AddFile(path+"MC/mc_173046.DYtautauM15to40.root");
  chain_DYtautauM15to40->Process("WBosonAnalysis.C+","DYtautauM15to40");

  TChain* chain_data = new TChain("mini");
  chain_data->AddFile(path+"Data/DataEgamma.root");
  chain_data->AddFile(path+"Data/DataMuons.root");
  chain_data->Process("WBosonAnalysis.C+","data");

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
    chain_Z_ee->SetProof();
    chain_Z_mumu->SetProof();
    chain_Z_tautau->SetProof();
    chain_ggH125_WW2lep->SetProof();
    chain_VBFH125_WW2lep->SetProof();
    chain_WenuWithB->SetProof();
    chain_WenuJetsBVeto->SetProof();
    chain_WenuNoJetsBVeto->SetProof();
    chain_WmunuWithB->SetProof();
    chain_WmunuJetsBVeto->SetProof();
    chain_WmunuNoJetsBVeto->SetProof();
    chain_WtaunuWithB->SetProof();
    chain_WtaunuJetsBVeto->SetProof();
    chain_WtaunuNoJetsBVeto->SetProof();
    chain_DYeeM08to15->SetProof();
    chain_DYeeM15to40->SetProof();
    chain_DYmumuM08to15->SetProof();
    chain_DYmumuM15to40->SetProof();
    chain_DYtautauM08to15->SetProof();
    chain_DYtautauM15to40->SetProof();
    chain_data->SetProof();
  }


}
