//////////////////////////////////////////////////////////
#ifndef HyyAnalysis_h
#define HyyAnalysis_h

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TSelector.h"
#include "TH1.h"
// Headers needed by this particular selector
#include "vector"

class HyyAnalysis : public TSelector {
  public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain


  // Global variables histograms
  TH1F *hist_mYY_bin1        = 0;
  TH1F *hist_mYY_cat_bin1        = 0;



  //////////////////////////////////////////////////////////
  // Declaration of leaf types
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           channelNumber;
   Float_t         mcWeight;
   Float_t         scaleFactor_PILEUP;
   Float_t         scaleFactor_ELE;
   Float_t         scaleFactor_MUON;
   Float_t         scaleFactor_PHOTON;
   Float_t         scaleFactor_TAU;
   Float_t         scaleFactor_BTAG;
   Float_t         scaleFactor_LepTRIGGER;
   Float_t         scaleFactor_PhotonTRIGGER;
   Float_t         scaleFactor_TauTRIGGER;
   Float_t         scaleFactor_DiTauTRIGGER;
   Bool_t          trigE;
   Bool_t          trigM;
   Bool_t          trigP;
   Bool_t          trigT;
   Bool_t          trigDT;
   UInt_t          lep_n;
   vector<bool>    *lep_truthMatched;
   vector<bool>    *lep_trigMatched;
   vector<float>   *lep_pt;
   vector<float>   *lep_eta;
   vector<float>   *lep_phi;
   vector<float>   *lep_E;
   vector<float>   *lep_z0;
   vector<int>     *lep_charge;
   vector<unsigned int> *lep_type;
   vector<bool>    *lep_isTightID;
   vector<float>   *lep_ptcone30;
   vector<float>   *lep_etcone20;
   vector<float>   *lep_trackd0pvunbiased;
   vector<float>   *lep_tracksigd0pvunbiased;
   Float_t         met_et;
   Float_t         met_phi;
   UInt_t          jet_n;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_E;
   vector<float>   *jet_jvt;
   vector<int>     *jet_trueflav;
   vector<bool>    *jet_truthMatched;
   vector<float>   *jet_MV2c10;
   UInt_t          photon_n;
   vector<bool>    *photon_truthMatched;
   vector<bool>    *photon_trigMatched;
   vector<float>   *photon_pt;
   vector<float>   *photon_eta;
   vector<float>   *photon_phi;
   vector<float>   *photon_E;
   vector<bool>    *photon_isTightID;
   vector<float>   *photon_ptcone30;
   vector<float>   *photon_etcone20;
   vector<int>     *photon_convType; // 0=unconverted photon, 1=one track only, with Si hits, 2=one track only, no Si hits (TRT only), 3=two tracks, both with Si hits, 4=two tracks, none with Si hits (TRT only), 5=two tracks, only one with Si hits
   UInt_t          largeRjet_n;
   vector<float>   *largeRjet_pt;
   vector<float>   *largeRjet_eta;
   vector<float>   *largeRjet_phi;
   vector<float>   *largeRjet_E;
   vector<float>   *largeRjet_m;
   vector<int>     *largeRjet_truthMatched;
   vector<float>   *largeRjet_D2;
   vector<float>   *largeRjet_tau32;
   UInt_t          tau_n;
   vector<float>   *tau_pt;
   vector<float>   *tau_eta;
   vector<float>   *tau_phi;
   vector<float>   *tau_E;
   vector<bool>    *tau_isTightID;
   vector<bool>    *tau_truthMatched;
   vector<bool>    *tau_trigMatched;
   vector<int>     *tau_nTracks;
   vector<float>   *tau_BDTid;
   Float_t         ditau_m;
   vector<float>   *truth_pt;
   vector<float>   *truth_eta;
   vector<float>   *truth_phi;
   vector<float>   *truth_E;
   vector<int>     *truth_pdgid;
   vector<float>   *lep_pt_syst;
   Float_t         met_et_syst;
   vector<float>   *jet_pt_syst;
   vector<float>   *photon_pt_syst;
   vector<float>   *largeRjet_pt_syst;
   vector<float>   *tau_pt_syst;


  // List of branches

  TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_scaleFactor_PILEUP;   //!
   TBranch        *b_scaleFactor_ELE;   //!
   TBranch        *b_scaleFactor_MUON;   //!
   TBranch        *b_scaleFactor_PHOTON;   //!
   TBranch        *b_scaleFactor_TAU;   //!
   TBranch        *b_scaleFactor_BTAG;   //!
   TBranch        *b_scaleFactor_LepTRIGGER;   //!
   TBranch        *b_scaleFactor_PhotonTRIGGER;   //!
   TBranch        *b_scaleFactor_TauTRIGGER;   //!
   TBranch        *b_scaleFactor_DiTauTRIGGER;   //!
   TBranch        *b_trigE;   //!
   TBranch        *b_trigM;   //!
   TBranch        *b_trigP;   //!
   TBranch        *b_trigT;   //!
   TBranch        *b_trigDT;   //!
   TBranch        *b_lep_n;   //!
   TBranch        *b_lep_truthMatched;   //!
   TBranch        *b_lep_trigMatched;   //!
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_E;   //!
   TBranch        *b_lep_z0;   //!
   TBranch        *b_lep_charge;   //!
   TBranch        *b_lep_type;   //!
   TBranch        *b_lep_isTightID;   //!
   TBranch        *b_lep_ptcone30;   //!
   TBranch        *b_lep_etcone20;   //!
   TBranch        *b_lep_trackd0pvunbiased;   //!
   TBranch        *b_lep_tracksigd0pvunbiased;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_jvt;   //!
   TBranch        *b_jet_trueflav;   //!
   TBranch        *b_jet_truthMatched;   //!
   TBranch        *b_jet_MV2c10;   //!
   TBranch        *b_photon_n;   //!
   TBranch        *b_photon_truthMatched;   //!
   TBranch        *b_photon_trigMatched;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_photon_eta;   //!
   TBranch        *b_photon_phi;   //!
   TBranch        *b_photon_E;   //!
   TBranch        *b_photon_isTightID;   //!
   TBranch        *b_photon_ptcone30;   //!
   TBranch        *b_photon_etcone20;   //!
   TBranch        *b_photon_convType;   //! 
   TBranch        *b_largeRjet_n;   //!
   TBranch        *b_largeRjet_pt;   //!
   TBranch        *b_largeRjet_eta;   //!
   TBranch        *b_largeRjet_phi;   //!
   TBranch        *b_largeRjet_E;   //!
   TBranch        *b_largeRjet_m;   //!
   TBranch        *b_largeRjet_truthMatched;   //!
   TBranch        *b_largeRjet_D2;   //!
   TBranch        *b_largeRjet_tau32;   //!
   TBranch        *b_tau_n;   //!
   TBranch        *b_tau_pt;   //!
   TBranch        *b_tau_eta;   //!
   TBranch        *b_tau_phi;   //!
   TBranch        *b_tau_E;   //!
   TBranch        *b_tau_isTightID;   //!
   TBranch        *b_tau_truthMatched;   //!
   TBranch        *b_tau_trigMatched;   //!
   TBranch        *b_tau_nTracks;   //!
   TBranch        *b_tau_BDTid;   //!
   TBranch        *b_ditau_m;   //!
   TBranch        *b_truth_pt;   //!
   TBranch        *b_truth_eta;   //!
   TBranch        *b_truth_phi;   //!
   TBranch        *b_truth_E;   //!
   TBranch        *b_truth_pdgid;   //!
   TBranch        *b_lep_pt_syst;   //!
   TBranch        *b_met_et_syst;   //!
   TBranch        *b_jet_pt_syst;   //!
   TBranch        *b_photon_pt_syst;   //!
   TBranch        *b_largeRjet_pt_syst;   //!
   TBranch        *b_tau_pt_syst;   //!


  HyyAnalysis(TTree * =0) : fChain(0) { }
  virtual ~HyyAnalysis() { }
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

  // Get Output List t osave our histograms in the output file
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
 
  float nEvent;
  float nEvent2;
  float nEvent3;
  float nEvent4;
  float nEvent5;
  float nEvent6;


  ClassDef(HyyAnalysis,0);
};

#endif

#ifdef HyyAnalysis_cxx
void HyyAnalysis::Init(TTree *tree)
{
  

   lep_truthMatched = 0;
   lep_trigMatched = 0;
   lep_pt = 0;
   lep_eta = 0;
   lep_phi = 0;
   lep_E = 0;
   lep_z0 = 0;
   lep_charge = 0;
   lep_type = 0;
   lep_isTightID = 0;
   lep_ptcone30 = 0;
   lep_etcone20 = 0;
   lep_trackd0pvunbiased = 0;
   lep_tracksigd0pvunbiased = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_E = 0;
   jet_jvt = 0;
   jet_trueflav = 0;
   jet_truthMatched = 0;
   jet_MV2c10 = 0;
   photon_truthMatched = 0;
   photon_trigMatched = 0;
   photon_pt = 0;
   photon_eta = 0;
   photon_phi = 0;
   photon_E = 0;
   photon_isTightID = 0;
   photon_ptcone30 = 0;
   photon_etcone20 = 0;
   photon_convType = 0;
   largeRjet_pt = 0;
   largeRjet_eta = 0;
   largeRjet_phi = 0;
   largeRjet_E = 0;
   largeRjet_m = 0;
   largeRjet_truthMatched = 0;
   largeRjet_D2 = 0;
   largeRjet_tau32 = 0;
   tau_pt = 0;
   tau_eta = 0;
   tau_phi = 0;
   tau_E = 0;
   tau_isTightID = 0;
   tau_truthMatched = 0;
   tau_trigMatched = 0;
   tau_nTracks = 0;
   tau_BDTid = 0;
   truth_pt = 0;
   truth_eta = 0;
   truth_phi = 0;
   truth_E = 0;
   truth_pdgid = 0;
   lep_pt_syst = 0;
   jet_pt_syst = 0;
   photon_pt_syst = 0;
   largeRjet_pt_syst = 0;
   tau_pt_syst = 0;

   
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("channelNumber", &channelNumber, &b_channelNumber);
   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("scaleFactor_PILEUP", &scaleFactor_PILEUP, &b_scaleFactor_PILEUP);
   fChain->SetBranchAddress("scaleFactor_ELE", &scaleFactor_ELE, &b_scaleFactor_ELE);
   fChain->SetBranchAddress("scaleFactor_MUON", &scaleFactor_MUON, &b_scaleFactor_MUON);
   fChain->SetBranchAddress("scaleFactor_PHOTON", &scaleFactor_PHOTON, &b_scaleFactor_PHOTON);
   fChain->SetBranchAddress("scaleFactor_TAU", &scaleFactor_TAU, &b_scaleFactor_TAU);
   fChain->SetBranchAddress("scaleFactor_BTAG", &scaleFactor_BTAG, &b_scaleFactor_BTAG);
   fChain->SetBranchAddress("scaleFactor_LepTRIGGER", &scaleFactor_LepTRIGGER, &b_scaleFactor_LepTRIGGER);
   fChain->SetBranchAddress("scaleFactor_PhotonTRIGGER", &scaleFactor_PhotonTRIGGER, &b_scaleFactor_PhotonTRIGGER);
   fChain->SetBranchAddress("trigE", &trigE, &b_trigE);
   fChain->SetBranchAddress("trigM", &trigM, &b_trigM);
   fChain->SetBranchAddress("trigP", &trigP, &b_trigP);
   fChain->SetBranchAddress("lep_n", &lep_n, &b_lep_n);
   fChain->SetBranchAddress("lep_truthMatched", &lep_truthMatched, &b_lep_truthMatched);
   fChain->SetBranchAddress("lep_trigMatched", &lep_trigMatched, &b_lep_trigMatched);
   fChain->SetBranchAddress("lep_pt", &lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", &lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", &lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_E", &lep_E, &b_lep_E);
   fChain->SetBranchAddress("lep_z0", &lep_z0, &b_lep_z0);
   fChain->SetBranchAddress("lep_charge", &lep_charge, &b_lep_charge);
   fChain->SetBranchAddress("lep_type", &lep_type, &b_lep_type);
   fChain->SetBranchAddress("lep_isTightID", &lep_isTightID, &b_lep_isTightID);
   fChain->SetBranchAddress("lep_ptcone30", &lep_ptcone30, &b_lep_ptcone30);
   fChain->SetBranchAddress("lep_etcone20", &lep_etcone20, &b_lep_etcone20);
   fChain->SetBranchAddress("lep_trackd0pvunbiased", &lep_trackd0pvunbiased, &b_lep_trackd0pvunbiased);
   fChain->SetBranchAddress("lep_tracksigd0pvunbiased", &lep_tracksigd0pvunbiased, &b_lep_tracksigd0pvunbiased);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);
   fChain->SetBranchAddress("jet_trueflav", &jet_trueflav, &b_jet_trueflav);
   fChain->SetBranchAddress("jet_truthMatched", &jet_truthMatched, &b_jet_truthMatched);
   fChain->SetBranchAddress("jet_MV2c10", &jet_MV2c10, &b_jet_MV2c10);
   fChain->SetBranchAddress("photon_n", &photon_n, &b_photon_n);
   fChain->SetBranchAddress("photon_truthMatched", &photon_truthMatched, &b_photon_truthMatched);
   fChain->SetBranchAddress("photon_trigMatched", &photon_trigMatched, &b_photon_trigMatched);
   fChain->SetBranchAddress("photon_pt", &photon_pt, &b_photon_pt);
   fChain->SetBranchAddress("photon_eta", &photon_eta, &b_photon_eta);
   fChain->SetBranchAddress("photon_phi", &photon_phi, &b_photon_phi);
   fChain->SetBranchAddress("photon_E", &photon_E, &b_photon_E);
   fChain->SetBranchAddress("photon_isTightID", &photon_isTightID, &b_photon_isTightID);
   fChain->SetBranchAddress("photon_ptcone30", &photon_ptcone30, &b_photon_ptcone30);
   fChain->SetBranchAddress("photon_etcone20", &photon_etcone20, &b_photon_etcone20);
   fChain->SetBranchAddress("photon_convType", &photon_convType, &b_photon_convType);
   fChain->SetBranchAddress("lep_pt_syst", &lep_pt_syst, &b_lep_pt_syst);
   fChain->SetBranchAddress("met_et_syst", &met_et_syst, &b_met_et_syst);
   fChain->SetBranchAddress("jet_pt_syst", &jet_pt_syst, &b_jet_pt_syst);
   fChain->SetBranchAddress("photon_pt_syst", &photon_pt_syst, &b_photon_pt_syst);
   fChain->SetBranchAddress("largeRjet_pt_syst", &largeRjet_pt_syst, &b_largeRjet_pt_syst);
   fChain->SetBranchAddress("tau_pt_syst", &tau_pt_syst, &b_tau_pt_syst);

}

Bool_t HyyAnalysis::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef HyyAnalysis_cxx
