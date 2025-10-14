//////////////////////////////////////////////////////////
#ifndef HyyAnalysis_h
#define HyyAnalysis_h

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

class HyyAnalysis : public TSelector {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  
  // Global variables histograms
  TH1F *hist_mYY_bin1        = 0;
  TH1F *hist_mYY_cat_bin1        = 0;
  
  TH1F *hist_scale_factors  = 0;
  
  //////////////////////////////////////////////////////////
  // Declaration of leaf types
  
  Float_t ScaleFactor_PILEUP;
  Float_t mcWeight;
  Double_t xsec;
  Double_t filteff;
  Double_t kfac;
  
  Bool_t trigP;
  
  Int_t photon_n;
  
  ROOT::VecOps::RVec<float> *photon_pt;
  ROOT::VecOps::RVec<float> *photon_eta;
  ROOT::VecOps::RVec<float> *photon_phi;
  ROOT::VecOps::RVec<float> *photon_e;

  ROOT::VecOps::RVec<float> *photon_ptcone20;
    
  ROOT::VecOps::RVec<bool> *photon_isTightID;
  ROOT::VecOps::RVec<bool> *photon_isTightIso;
  
  Float_t ScaleFactor_PHOTON;

  Float_t initial_events;
  Double_t initial_sum_of_weights;
  Float_t initial_sum_of_weights_squared;
  
  // List of branches
  
  TBranch *b_ScaleFactor_PILEUP;
  TBranch *b_mcWeight;
  TBranch *b_xsec;
  TBranch *b_filteff;
  TBranch *b_kfac;
  
  TBranch *b_trigP;

  TBranch *b_photon_n;
  TBranch *b_photon_pt;
  TBranch *b_photon_eta;
  TBranch *b_photon_phi;
  TBranch *b_photon_e;
  
  TBranch *b_photon_ptcone20;
  
  TBranch *b_photon_isTightID;
  TBranch *b_photon_isTightIso;
  
  TBranch *b_ScaleFactor_PHOTON;
  
  TBranch *b_initial_events;
  TBranch *b_initial_sum_of_weights;
  TBranch *b_initial_sum_of_weights_squared;


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

  int accepted_events;
  int accepted_events_2;

  // std::set<float> uniqueWeights;

  Double_t xsec_SF;
  Double_t totalSumOfWeights_SF;
  Double_t filteff_SF;
  Double_t kfac_SF;

  ClassDef(HyyAnalysis,0);
};

#endif

#ifdef HyyAnalysis_cxx
void HyyAnalysis::Init(TTree *tree)
{

  //fReader.SetTree(tree);

  photon_pt = 0;
  photon_eta = 0;
  photon_phi = 0;
  photon_e = 0;
  photon_ptcone20 = 0;
  photon_isTightID = 0;
  photon_isTightIso = 0;
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("ScaleFactor_PILEUP", &ScaleFactor_PILEUP, &b_ScaleFactor_PILEUP);
  fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
  fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
  fChain->SetBranchAddress("filteff", &filteff, &b_filteff);
  fChain->SetBranchAddress("kfac", &kfac, &b_kfac);

  fChain->SetBranchAddress("trigP", &trigP, &b_trigP);
  
  fChain->SetBranchAddress("photon_n", &photon_n, &b_photon_n);
  fChain->SetBranchAddress("photon_pt", &photon_pt, &b_photon_pt);
  fChain->SetBranchAddress("photon_eta", &photon_eta, &b_photon_eta);
  fChain->SetBranchAddress("photon_phi", &photon_phi, &b_photon_phi);
  fChain->SetBranchAddress("photon_e", &photon_e, &b_photon_e);
  fChain->SetBranchAddress("photon_ptcone20", &photon_ptcone20, &b_photon_ptcone20);
  
  fChain->SetBranchAddress("photon_isTightID", &photon_isTightID, &b_photon_isTightID);
  fChain->SetBranchAddress("photon_isTightIso", &photon_isTightIso, &b_photon_isTightIso);
  fChain->SetBranchAddress("ScaleFactor_PHOTON", &ScaleFactor_PHOTON, &b_ScaleFactor_PHOTON);
  
  fChain->SetBranchAddress("sum_of_weights", &initial_sum_of_weights, &b_initial_sum_of_weights);

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
