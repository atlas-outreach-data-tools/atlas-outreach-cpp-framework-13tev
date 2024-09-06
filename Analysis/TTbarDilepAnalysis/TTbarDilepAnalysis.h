//////////////////////////////////////////////////////////
#ifndef TTbarDilepAnalysis_h
#define TTbarDilepAnalysis_h

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

class TTbarDilepAnalysis : public TSelector {
  public :
  TTreeReader     fReader;  //!the tree reader                                                                                               
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  //////////////////////////////////////////////////////////
  // histograms

  // Global variables histograms
  TH1F *hist_met      = 0;
  TH1F *hist_lep_pt   = 0;
  TH1F *hist_lep_eta  = 0;
  TH1F *hist_scale_factors  = 0;

  int muon_n = 0;
  int electron_n = 0;
  int trigger_cut = 0;
  int good_lepton_n_cut = 0;
  int OP_charge_leptons_cut = 0;
  int type_leptons_cut = 0;
  int bjets_cut = 0;

  
  //////////////////////////////////////////////////////////
  // Declaration of leaf types
  
  Float_t ScaleFactor_PILEUP;
  Float_t mcWeight;
  Float_t xsec;
  Float_t filteff;
  Float_t kfac;
  
  Bool_t trigE;
  Bool_t trigM;

  Float_t ScaleFactor_BTAG;
  Int_t jet_n;

  vector<float> *jet_pt;
  vector<float> *jet_eta;
  vector<float> *jet_phi;
  vector<float> *jet_e;
  vector<int> *jet_btag_quantile;
  vector<bool> *jet_jvt;
  /*
  Int_t largeRJet_n;
  vector<float> *largeRJet_pt;
  vector<float> *largeRJet_eta;
  vector<float> *largeRJet_phi;
  vector<float> *largeRJet_e;
  vector<float> *largeRJet_m;
  vector<float> *largeRJet_D2;
  */
  Float_t ScaleFactor_ELE;
  Float_t ScaleFactor_MUON;

  Int_t lep_n;
  vector<int> *lep_type;
  vector<float> *lep_pt;
  vector<float> *lep_eta;
  vector<float> *lep_phi;
  vector<float> *lep_e;
  vector<int> *lep_charge;

  vector<float> *lep_ptvarcone30;
  vector<float> *lep_topoetcone20;
  vector<float> *lep_z0;
  vector<float> *lep_d0;
  vector<float> *lep_d0sig;

  vector<bool> *lep_isTight;
  vector<bool> *lep_isTightID;
  vector<bool> *lep_isTightIso;
  
  Float_t ScaleFactor_PHOTON;
  /*
  Int_t photon_n;
  vector<float> *photon_pt;
  vector<float> *photon_eta;
  vector<float> *photon_phi;
  vector<float> *photon_e;
  vector<float> *photon_ptcone20;
  vector<float> *photon_topoetcone40;
  vector<bool> *photon_isTight;
  vector<bool> *photon_isTightID;
  vector<bool> *photon_isTightIso;
  */
  Float_t ScaleFactor_TAU;
  /*
  Int_t tau_n;
  vector<float> *tau_pt;
  vector<float> *tau_eta;
  vector<float> *tau_phi;
  vector<float> *tau_e;
  vector<float> *tau_charge;
  vector<int> *tau_nTracks;
  vector<bool> *tau_isTight;

  vector<float> *tau_RNNJetScore;
  vector<float> *tau_RNNEleScore;
  */
  Float_t met;
  Float_t met_phi;
  Float_t met_mpx;
  Float_t met_mpy;

  Float_t initial_events;
  Float_t initial_sum_of_weights;
  Float_t initial_sum_of_weights_squared;

  // List of branches
  
  TBranch *b_ScaleFactor_PILEUP;
  TBranch *b_mcWeight;
  TBranch *b_xsec;
  TBranch *b_filteff;
  TBranch *b_kfac;
  
  TBranch *b_trigE;
  TBranch *b_trigM;

  TBranch *b_ScaleFactor_BTAG;
  TBranch *b_jet_n;

  TBranch *b_jet_pt;
  TBranch *b_jet_eta;
  TBranch *b_jet_phi;
  TBranch *b_jet_e;
  TBranch *b_jet_btag_quantile;
  TBranch *b_jet_jvt;
  /*
  TBranch *b_largeRJet_n;
  TBranch *b_largeRJet_pt;
  TBranch *b_largeRJet_eta;
  TBranch *b_largeRJet_phi;
  TBranch *b_largeRJet_e;
  TBranch *b_largeRJet_m;
  TBranch *b_largeRJet_D2;
  */
  TBranch *b_ScaleFactor_ELE;
  TBranch *b_ScaleFactor_MUON;

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

  TBranch *b_lep_isTight;
  TBranch *b_lep_isTightID;
  TBranch *b_lep_isTightIso;

  TBranch *b_ScaleFactor_PHOTON;
  /*
  TBranch *b_photon_n;
  TBranch *b_photon_pt;
  TBranch *b_photon_eta;
  TBranch *b_photon_phi;
  TBranch *b_photon_e;
  TBranch *b_photon_ptcone20;
  TBranch *b_photon_topoetcone40;
  TBranch *b_photon_isTight;
  TBranch *b_photon_isTightID;
  TBranch *b_photon_isTightIso;
  */
  TBranch *b_ScaleFactor_TAU;
  /*
  TBranch *b_tau_n;
  TBranch *b_tau_pt;
  TBranch *b_tau_eta;
  TBranch *b_tau_phi;
  TBranch *b_tau_e;
  TBranch *b_tau_charge;
  TBranch *b_tau_nTracks;
  TBranch *b_tau_isTight;

  TBranch *b_tau_RNNJetScore;
  TBranch *b_tau_RNNEleScore;
  */
  TBranch *b_met;
  TBranch *b_met_phi;
  TBranch *b_met_mpx;
  TBranch *b_met_mpy;

  TBranch *b_initial_events;
  TBranch *b_initial_sum_of_weights;
  TBranch *b_initial_sum_of_weights_squared;
  

  TTbarDilepAnalysis(TTree * =0) : fChain(0) { }
  virtual ~TTbarDilepAnalysis() { }
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
  
  // Get Output List to save our histograms in the output file
  virtual TList  *GetOutputList() const { return fOutput; }
  //
  virtual void    define_histograms();
  //
  virtual void    FillOutputList();
  //
  virtual void    WriteHistograms();

  virtual void    SlaveTerminate();
  virtual void    Terminate();


  int nEvents;
  std::set<float> uniqueWeights;

  Float_t xsec_SF;
  Float_t totalSumOfWeights_SF;
  Float_t filteff_SF;
  Float_t kfac_SF;
  
  ClassDef(TTbarDilepAnalysis,0);
  
};

#endif

#ifdef TTbarDilepAnalysis_cxx
void TTbarDilepAnalysis::Init(TTree *tree)
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
  lep_isTight = 0;
  lep_isTightID = 0;
  lep_isTightIso = 0;
  
  
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
  fChain->SetBranchAddress("ScaleFactor_BTAG", &ScaleFactor_BTAG, &b_ScaleFactor_BTAG);
  fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
  fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
  fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
  fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
  fChain->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
  fChain->SetBranchAddress("jet_btag_quantile", &jet_btag_quantile, &b_jet_btag_quantile);
  fChain->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);
  /*
  fChain->SetBranchAddress("largeRJet_n", &largeRJet_n, &b_largeRJet_n);
  fChain->SetBranchAddress("largeRJet_pt", &largeRJet_pt, &b_largeRJet_pt);
  fChain->SetBranchAddress("largeRJet_eta", &largeRJet_eta, &b_largeRJet_eta);
  fChain->SetBranchAddress("largeRJet_phi", &largeRJet_phi, &b_largeRJet_phi);
  fChain->SetBranchAddress("largeRJet_e", &largeRJet_e, &b_largeRJet_e);
  fChain->SetBranchAddress("largeRJet_m", &largeRJet_m, &b_largeRJet_m);
  fChain->SetBranchAddress("largeRJet_D2", &largeRJet_D2, &b_largeRJet_D2);
  */
  fChain->SetBranchAddress("ScaleFactor_ELE", &ScaleFactor_ELE, &b_ScaleFactor_ELE);
  fChain->SetBranchAddress("ScaleFactor_MUON", &ScaleFactor_MUON, &b_ScaleFactor_MUON);
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
  fChain->SetBranchAddress("lep_isTight", &lep_isTight, &b_lep_isTight);
  fChain->SetBranchAddress("lep_isTightID", &lep_isTightID, &b_lep_isTightID);
  fChain->SetBranchAddress("lep_isTightIso", &lep_isTightIso, &b_lep_isTightIso);
  fChain->SetBranchAddress("ScaleFactor_PHOTON", &ScaleFactor_PHOTON, &b_ScaleFactor_PHOTON);
  /*
  fChain->SetBranchAddress("photon_n", &photon_n, &b_photon_n);
  fChain->SetBranchAddress("photon_pt", &photon_pt, &b_photon_pt);
  fChain->SetBranchAddress("photon_eta", &photon_eta, &b_photon_eta);
  fChain->SetBranchAddress("photon_phi", &photon_phi, &b_photon_phi);
  fChain->SetBranchAddress("photon_e", &photon_e, &b_photon_e);
  fChain->SetBranchAddress("photon_ptcone20", &photon_ptcone20, &b_photon_ptcone20);
  fChain->SetBranchAddress("photon_topoetcone40", &photon_topoetcone40, &b_photon_topoetcone40);
  fChain->SetBranchAddress("photon_isTight", &photon_isTight, &b_photon_isTight);
  fChain->SetBranchAddress("photon_isTightID", &photon_isTightID, &b_photon_isTightID);
  fChain->SetBranchAddress("photon_isTightIso", &photon_isTightIso, &b_photon_isTightIso);
  */
  fChain->SetBranchAddress("ScaleFactor_TAU", &ScaleFactor_TAU, &b_ScaleFactor_TAU);
  /*
  fChain->SetBranchAddress("tau_n", &tau_n, &b_tau_n);
  fChain->SetBranchAddress("tau_pt", &tau_pt, &b_tau_pt);
  fChain->SetBranchAddress("tau_eta", &tau_eta, &b_tau_eta);
  fChain->SetBranchAddress("tau_phi", &tau_phi, &b_tau_phi);
  fChain->SetBranchAddress("tau_e", &tau_e, &b_tau_e);
  fChain->SetBranchAddress("tau_charge", &tau_charge, &b_tau_charge);
  fChain->SetBranchAddress("tau_nTracks", &tau_nTracks, &b_tau_nTracks);
  fChain->SetBranchAddress("tau_isTight", &tau_isTight, &b_tau_isTight);
  fChain->SetBranchAddress("tau_RNNJetScore", &tau_RNNJetScore, &b_tau_RNNJetScore);
  fChain->SetBranchAddress("tau_RNNEleScore", &tau_RNNEleScore, &b_tau_RNNEleScore);
  */
  fChain->SetBranchAddress("met", &met, &b_met);
  fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
  fChain->SetBranchAddress("met_mpx", &met_mpx, &b_met_mpx);
  fChain->SetBranchAddress("met_mpy", &met_mpy, &b_met_mpy);
  

  //fChain->SetBranchAddress("initial_events", &initial_events, &b_initial_events);
  fChain->SetBranchAddress("initial_sum_of_weights", &initial_sum_of_weights, &b_initial_sum_of_weights);
  //fChain->SetBranchAddress("initial_sum_of_weights_squared", &initial_sum_of_weights_squared, &b_initial_sum_of_weights_squared);
  
}

Bool_t TTbarDilepAnalysis::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef TTbarAnalysis_cxx
