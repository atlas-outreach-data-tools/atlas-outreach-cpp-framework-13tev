//////////////////////////////////////////////////////////
#ifndef HWWAnalysis_h
#define HWWAnalysis_h

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TSelector.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include "TH1.h"
// Headers needed by this particular selector
#include "vector"
#include <set>
#include "ROOT/RVec.hxx"

class HWWAnalysis : public TSelector {
  public :
  TTreeReader     fReader;  //!the tree reader                                                                                               
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  //////////////////////////////////////////////////////////
  // histograms

  // Global variables histograms

  // Global variables histograms
  TH1F* hist_mLL;
  TH1F* hist_ptLL;
  TH1F* hist_dPhi_LL;
  TH1F* hist_dPhiLLmet;
  TH1F* hist_etmiss;
  TH1F* hist_mt;
  TH1F* hist_n_jets;
  TH1F* hist_n_bjets;
  
  // pre-cut
  TH1F* histI_mLL;
  TH1F* histI_ptLL;
  TH1F* histI_dPhi_LL;
  TH1F* histI_dPhiLLmet;
  TH1F* histI_etmiss;
  TH1F* histI_mt;
  TH1F* histI_n_jets;
  TH1F* histI_n_bjets;

  // Jet variables histograms
  TH1F* hist_leadjet_pt;
  TH1F* hist_leadjet_eta;
  
  // Leading Lepton histograms
  TH1F* hist_leadleptpt;
  TH1F* hist_leadlepteta;
  TH1F* hist_leadleptE;
  TH1F* hist_leadleptphi;
  TH1F* hist_leadleptch;
  TH1F* hist_leadleptID;
  TH1F* hist_leadlept_ptc;
  TH1F* hist_leadleptetc;
  TH1F* hist_leadlepz0;
  TH1F* hist_leadlepd0;

  // Subleading Lepton histograms
  TH1F* hist_subleadleptpt;
  TH1F* hist_subleadlepteta;
  TH1F* hist_subleadleptE;
  TH1F* hist_subleadleptphi;
  TH1F* hist_subleadleptch;
  TH1F* hist_subleadleptID;
  TH1F* hist_subleadlept_ptc;
  TH1F* hist_subleadleptetc;
  TH1F* hist_subleadlepz0;
  TH1F* hist_subleadlepd0;
  
  TH1F *hist_scale_factors  = 0;
  
  int muon_n = 0;
  int electron_n = 0;
  int trigger_cut = 0;

  int dPhiLLmet_cut = 0;
  int mLL_cut = 0;
  int ptLL_cut = 0;
  int dPhi_LL_cut = 0;

  int good_lepton_n_cut = 0;
  int OP_charge_leptons_cut = 0;
  int type_leptons_cut = 0;
  int bjets_cut = 0;

  
  //////////////////////////////////////////////////////////
  // Declaration of leaf types
  
  Float_t ScaleFactor_PILEUP;
  Float_t mcWeight;
  Double_t xsec;
  Double_t filteff;
  Double_t kfac;
  
  Bool_t trigE;
  Bool_t trigM;

  Float_t ScaleFactor_FTAG;
  Float_t ScaleFactor_BTAG;
  Float_t ScaleFactor_JVT;
  Int_t jet_n;
  
  ROOT::VecOps::RVec<float> *jet_pt;
  ROOT::VecOps::RVec<float> *jet_eta;
  ROOT::VecOps::RVec<float> *jet_phi;
  ROOT::VecOps::RVec<float> *jet_e;
  ROOT::VecOps::RVec<int> *jet_btag_quantile;
  ROOT::VecOps::RVec<bool> *jet_jvt;

  Float_t ScaleFactor_ELE;
  Float_t ScaleFactor_MUON;
  Float_t ScaleFactor_LepTRIGGER;
  
  Int_t lep_n;

  ROOT::VecOps::RVec<int> *lep_type;
  ROOT::VecOps::RVec<float> *lep_pt;
  ROOT::VecOps::RVec<float> *lep_eta;
  ROOT::VecOps::RVec<float> *lep_phi;
  ROOT::VecOps::RVec<float> *lep_e;
  ROOT::VecOps::RVec<int> *lep_charge;

  ROOT::VecOps::RVec<float> *lep_ptvarcone30;
  ROOT::VecOps::RVec<float> *lep_topoetcone20;
  ROOT::VecOps::RVec<float> *lep_z0;
  ROOT::VecOps::RVec<float> *lep_d0;
  ROOT::VecOps::RVec<float> *lep_d0sig;
    
  ROOT::VecOps::RVec<bool> *lep_isTightID;
  ROOT::VecOps::RVec<bool> *lep_isTightIso;
  ROOT::VecOps::RVec<bool> *lep_isTrigMatched;
  
  Float_t ScaleFactor_PHOTON;
  Float_t ScaleFactor_TAU;
  Float_t met;
  Float_t met_phi;
  Float_t met_mpx;
  Float_t met_mpy;

  Float_t initial_events;
  Double_t initial_sum_of_weights;
  Float_t initial_sum_of_weights_squared;
  
  // List of branches
  
  TBranch *b_ScaleFactor_PILEUP;
  TBranch *b_mcWeight;
  TBranch *b_xsec;
  TBranch *b_filteff;
  TBranch *b_kfac;
  
  TBranch *b_trigE;
  TBranch *b_trigM;

  TBranch *b_ScaleFactor_FTAG;
  TBranch *b_ScaleFactor_BTAG;
  TBranch *b_ScaleFactor_JVT;
  TBranch *b_jet_n;

  TBranch *b_jet_pt;
  TBranch *b_jet_eta;
  TBranch *b_jet_phi;
  TBranch *b_jet_e;
  TBranch *b_jet_btag_quantile;
  TBranch *b_jet_jvt;
  TBranch *b_ScaleFactor_ELE;
  TBranch *b_ScaleFactor_MUON;
  TBranch *b_ScaleFactor_LepTRIGGER;
  
  TBranch *b_lep_n;
  TBranch *b_lep_type;
  TBranch *b_lep_pt;
  TBranch *b_lep_eta;
  TBranch *b_lep_phi;
  TBranch *b_lep_e;
  TBranch *b_lep_charge;
  
  TBranch *b_lep_ptvarcone30;
  TBranch *b_lep_topoetcone20;
  TBranch *b_lep_z0;
  TBranch *b_lep_d0;
  TBranch *b_lep_d0sig;

  TBranch *b_lep_isTightID;
  TBranch *b_lep_isTightIso;
  TBranch *b_lep_isTrigMatched;
  
  TBranch *b_ScaleFactor_PHOTON;
  TBranch *b_ScaleFactor_TAU;
  TBranch *b_met;
  TBranch *b_met_phi;
  TBranch *b_met_mpx;
  TBranch *b_met_mpy;

  TBranch *b_initial_events;
  TBranch *b_initial_sum_of_weights;
  TBranch *b_initial_sum_of_weights_squared;
  
  HWWAnalysis(TTree * =0) : fChain(0) { }
  virtual ~HWWAnalysis() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();

  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }

  virtual void    FillHistogramsGlobal( double m, float w , TString s);
  virtual void    FillHistogramsLeadlept( double m, float w , TString s);
  virtual void    FillHistogramsSubleadlept( double m, float w , TString s);
  //virtual void    FillHistogramsLeadJet( double m, float w , TString s);
  
  // Get Output List to save our histograms in the output file
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    define_histograms();
  virtual void    FillOutputList();
  virtual void    WriteHistograms();
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  
  int nEvents;
  std::set<float> uniqueWeights;

  Double_t xsec_SF;
  Double_t totalSumOfWeights_SF;
  Double_t filteff_SF;
  Double_t kfac_SF;
  
  ClassDef(HWWAnalysis,0);
  
};

#endif

#ifdef HWWAnalysis_cxx
void HWWAnalysis::Init(TTree *tree)
{

  //fReader.SetTree(tree);

  jet_pt = 0;
  jet_eta = 0;
  jet_phi = 0;
  jet_e = 0;
  jet_btag_quantile = 0;
  jet_jvt = 0;
  lep_type = 0;
  lep_pt = 0;
  lep_eta = 0;
  lep_phi = 0;
  lep_e = 0;
  lep_charge = 0;
  lep_ptvarcone30 = 0;
  lep_topoetcone20 = 0;
  lep_z0 = 0;
  lep_d0 = 0;
  lep_d0sig = 0;
  lep_isTightID = 0;
  lep_isTightIso = 0;
  lep_isTrigMatched = 0;
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("ScaleFactor_PILEUP", &ScaleFactor_PILEUP, &b_ScaleFactor_PILEUP);
  fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
  fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
  fChain->SetBranchAddress("filteff", &filteff, &b_filteff);
  fChain->SetBranchAddress("kfac", &kfac, &b_kfac);
  fChain->SetBranchAddress("trigE", &trigE, &b_trigE);
  fChain->SetBranchAddress("trigM", &trigM, &b_trigM);

  fChain->SetBranchAddress("ScaleFactor_FTAG", &ScaleFactor_FTAG, &b_ScaleFactor_FTAG);
  fChain->SetBranchAddress("ScaleFactor_BTAG", &ScaleFactor_BTAG, &b_ScaleFactor_BTAG);
  fChain->SetBranchAddress("ScaleFactor_JVT", &ScaleFactor_JVT, &b_ScaleFactor_JVT);
  fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
  fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
  fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
  fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
  fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
  fChain->SetBranchAddress("jet_btag_quantile", &jet_btag_quantile, &b_jet_btag_quantile);
  fChain->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);

  fChain->SetBranchAddress("ScaleFactor_ELE", &ScaleFactor_ELE, &b_ScaleFactor_ELE);
  fChain->SetBranchAddress("ScaleFactor_MUON", &ScaleFactor_MUON, &b_ScaleFactor_MUON);
  fChain->SetBranchAddress("ScaleFactor_LepTRIGGER", &ScaleFactor_LepTRIGGER, &b_ScaleFactor_LepTRIGGER);

  fChain->SetBranchAddress("lep_n", &lep_n, &b_lep_n);
  fChain->SetBranchAddress("lep_type", &lep_type, &b_lep_type);
  fChain->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
  fChain->SetBranchAddress("lep_eta", &lep_eta, &b_lep_eta);
  fChain->SetBranchAddress("lep_phi", &lep_phi, &b_lep_phi);
  fChain->SetBranchAddress("lep_e", &lep_e, &b_lep_e);
  fChain->SetBranchAddress("lep_charge", &lep_charge, &b_lep_charge);
  fChain->SetBranchAddress("lep_ptvarcone30", &lep_ptvarcone30, &b_lep_ptvarcone30);
  fChain->SetBranchAddress("lep_topoetcone20", &lep_topoetcone20, &b_lep_topoetcone20);
  fChain->SetBranchAddress("lep_z0", &lep_z0, &b_lep_z0);
  fChain->SetBranchAddress("lep_d0", &lep_d0, &b_lep_d0);
  fChain->SetBranchAddress("lep_d0sig", &lep_d0sig, &b_lep_d0sig);

  fChain->SetBranchAddress("lep_isTightID", &lep_isTightID, &b_lep_isTightID);
  fChain->SetBranchAddress("lep_isTightIso", &lep_isTightIso, &b_lep_isTightIso);
  fChain->SetBranchAddress("lep_isTrigMatched", &lep_isTrigMatched, &b_lep_isTrigMatched);
  fChain->SetBranchAddress("ScaleFactor_PHOTON", &ScaleFactor_PHOTON, &b_ScaleFactor_PHOTON);
  fChain->SetBranchAddress("ScaleFactor_TAU", &ScaleFactor_TAU, &b_ScaleFactor_TAU);
  fChain->SetBranchAddress("met", &met, &b_met);
  fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
  fChain->SetBranchAddress("met_mpx", &met_mpx, &b_met_mpx);
  fChain->SetBranchAddress("met_mpy", &met_mpy, &b_met_mpy);

  fChain->SetBranchAddress("sum_of_weights", &initial_sum_of_weights, &b_initial_sum_of_weights);
  
}

Bool_t HWWAnalysis::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef HWWAnalysis_cxx
