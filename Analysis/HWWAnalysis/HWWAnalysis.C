/////////////////////////////////////////////////////////////
//// HWWAnalysis code
//// Author: ATLAS Collaboration (2018)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define HWWAnalysis_cxx

#include "HWWAnalysis.h"
#include "HWWAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void HWWAnalysis::Begin(TTree * )
{
}

void HWWAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());

  name=option;

  define_histograms();

  FillOutputList();
}

Bool_t HWWAnalysis::Process(Long64_t entry)
{
  fChain->GetTree()->GetEntry(entry);

  if(fChain->GetTree()->GetEntries()>0)
  {
    //Begin analysis

    //SF
    Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_TRIGGER;
    //EventW
    Float_t eventWeight = mcWeight*scaleFactor_PILEUP*scaleFactor_ZVERTEX;
    //weight = SF * EventW
    Float_t weight = scaleFactor*eventWeight;

    // Make difference between data and MC
    if (weight == 0.) weight = 1.;

    // Missing Et of the event in GeV
    Float_t missingEt = met_et/1000.;


    // Preselection cut for electron/muon trigger, Good Run List, and good vertex
    if(trigE || trigM)
    {
      if(passGRL)
      {
        if(hasGoodVertex)
        {
          // Preselection of good leptons
          int goodlep_index[2];
          int goodlep_n = 0;
          int lep_index =0;

          for(unsigned int i=0; i<lep_n; i++)
          {
           // is Tight
           if( bool(lep_flag[i] & 512)) 
            {
            // isolated
            if( lep_pt[i]>25000. && (lep_ptcone30[i]/lep_pt[i]) < 0.15 && (lep_etcone20[i]/lep_pt[i]) < 0.15)
            {
             // electron or muon
             if ( abs(lep_type[i])==11 ||  abs(lep_type[i])==13) {
              goodlep_n = goodlep_n + 1;
              goodlep_index[lep_index] = i;
              lep_index++;
              }
            }
          }
         }

          //Zero cut
          if(goodlep_n==2)
          {
            int goodlep1_index = goodlep_index[0];
            int goodlep2_index = goodlep_index[1];
              // TLorentzVector definitions
              TLorentzVector Lepton_1  = TLorentzVector();
              TLorentzVector Lepton_2  = TLorentzVector();
              TLorentzVector      MeT  = TLorentzVector();

              TLorentzVector   Lepton1_MeT = TLorentzVector();
              TLorentzVector   Lepton2_MeT = TLorentzVector();
              TLorentzVector Lepton_12_MeT = TLorentzVector();
              TLorentzVector     Lepton_12 = TLorentzVector();

              TLorentzVector     Phi_12 = TLorentzVector();
              TLorentzVector Phi_ll_met = TLorentzVector();


              Lepton_1.SetPtEtaPhiE(lep_pt[goodlep1_index], lep_eta[goodlep1_index], lep_phi[goodlep1_index],lep_E[goodlep1_index]);
              Lepton_2.SetPtEtaPhiE(lep_pt[goodlep2_index], lep_eta[goodlep2_index], lep_phi[goodlep2_index],lep_E[goodlep2_index]);
              MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);


              //Calculation of the Invariant Mass using TLorentz vectors (First Lepton + MeT)
              Lepton1_MeT = Lepton_1 + MeT;
              float InvMass1       = Lepton1_MeT.Mag();
              float InvMass1_inGeV = InvMass1/1000.;


              //Calculation of the Invariant Mass using TLorentz vectors (Second Lepton + MeT)
              Lepton2_MeT = Lepton_2 + MeT;
              float InvMass2       = Lepton2_MeT.Mag();
              float InvMass2_inGeV = InvMass2/1000.;


              //Calculation of the Invariant Mass using TLorentz vectors (First + Second Lepton + MeT)
              Lepton_12_MeT = Lepton1_MeT + Lepton2_MeT;
              float InvMass = Lepton_12_MeT.Mag();
              float InvMass_inGeV = InvMass/1000.;


              //Calculation of the Invariant Mass using TLorentz vectors (First + Second Lepton)
              Lepton_12 = Lepton_1 + Lepton_2;
              float InvMass_Leptons = Lepton_12.Mag();
              float InvMass_Leptons_inGeV = InvMass_Leptons/1000.;


              //First cut : Exactly two good leptons with pT>25GeV
              if(goodlep_n==2 && lep_pt[goodlep1_index] >25000. && lep_pt[goodlep2_index] >25000.)
              {
                //second cut : Leptons have opposite charge
                int OS = lep_charge[goodlep1_index]*lep_charge[goodlep2_index];
                if(OS == -1)
                {
                  //thirt cut : No jets with pT> 25GeV
                  int goodjet_n = 0;
                  for(unsigned int i=0; i<jet_n; i++)
                  {
                     if(jet_pt[i]>25000. && abs(jet_eta[i]) < 2.5)
 			{
                        // JVF cleaning
                        bool jvf_pass=true;
                        if (jet_pt[i] < 50000. && abs(jet_eta[i]) < 2.4 && jet_jvf[i] < 0.50) jvf_pass=false;
                        if (jvf_pass) goodjet_n++;
                       }
                  }

                  if (goodjet_n == 0)
                  {
                    // fourth cut : if Leptons have the same flavour
                    int type_one = lep_type[goodlep1_index];
                    int type_two = lep_type[goodlep2_index];
                    if(TMath::Abs(type_one) == TMath::Abs(type_two))
                    {
                      if(InvMass_Leptons_inGeV > 12.)
                      {
                        if(TMath::Abs(InvMass_Leptons_inGeV - 91.18) > 15.)
                        {
                          if(met_et > 40000.)
                          {
                            //Sixth cut Transverse momentum of the two leptons
                            if(Lepton_12.Pt() > 30000.)
                            {
                              //Seventh cut : Azimutal angle between the two leptons and the missing energy transverse
                              Double_t Phi_ll_met = Lepton_12.DeltaPhi(MeT);
                              if (Phi_ll_met > TMath::Pi()/2)
                              {
                                //eighth cut: Invariant mass less than 55 GeV
                                if(InvMass_Leptons_inGeV < 55.)
                                {
                                  //nineth cut : Azimutal angle between the two leptons
                                  Double_t Phi_12 = (Lepton_1.DeltaPhi(Lepton_2)); // should be abs(xxx)
				  if (Phi_12 < 1.8)
                                  {
                                    // Filling histograms
                                    float Leptons_pT = Lepton_12.Pt();
                                    float Leptons_pT_inGeV  =  Leptons_pT/1000.;

                                    double names_of_global_variable[]={InvMass_Leptons_inGeV, Leptons_pT_inGeV, abs(Phi_12), missingEt, vxp_z, (double)pvxp_n};
                                    double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge[goodlep1_index], (double)lep_type[goodlep1_index], lep_ptcone30[goodlep1_index]/lep_pt[goodlep1_index], lep_etcone20[goodlep1_index]/lep_pt[goodlep1_index], lep_z0[goodlep1_index], lep_trackd0pvunbiased[goodlep1_index]};
                                    double names_of_subleadlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), lep_charge[goodlep2_index], (double)lep_type[goodlep2_index], lep_ptcone30[goodlep2_index]/lep_pt[goodlep2_index], lep_etcone20[goodlep2_index]/lep_pt[goodlep2_index], lep_z0[goodlep2_index], lep_trackd0pvunbiased[goodlep2_index]};

                                    TString histonames_of_global_variable[]={"hist_vismass", "hist_ptLL","hist_deltaPhiLL","hist_etmiss","hist_vxp_z","hist_pvxp_n"};
                                    TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
                                    TString histonames_of_subleadlep_variable[]={"hist_subleadleptpt", "hist_subleadlepteta","hist_subleadleptE","hist_subleadleptphi","hist_subleadleptch","hist_subleadleptID","hist_subleadlept_ptc","hist_subleadleptetc","hist_subleadlepz0","hist_subleadlepd0"};

                                    int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
                                    int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
                                    int length_subleadlep = sizeof(names_of_subleadlep_variable)/sizeof(names_of_subleadlep_variable[0]);

                                    for (int i=0; i<length_global; i++)
                                    {
                                      FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
                                    }
                                    for (int i=0; i<length_leadlep; i++)
                                    {
                                      FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
                                    }
                                    for (int i=0; i<length_subleadlep; i++)
                                    {
                                      FillHistogramsSubleadlept( names_of_subleadlep_variable[i], weight, histonames_of_subleadlep_variable[i]);
                                    }

                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                    else
                    {
                      if(InvMass_Leptons_inGeV > 10.)
                      {
                        if(met_et > 20000.)
                        {
                          //Sixth cut Transverse momentum of the two leptons
                          if(Lepton_12.Pt() > 30000.)
                          {
                            //Seventh cut : Azimutal angle between the two leptons
                            //and the missing energy transverse
                            Double_t Phi_ll_met = Lepton_12.DeltaPhi(MeT);
                            if (Phi_ll_met > TMath::Pi()/2)
                            {
                              //eighth cut: Invariant mass less than 55 GeV
                              if(InvMass_Leptons_inGeV < 55.)
                              {
                                //nineth cut : Azimutal angle between the two leptons
                                Double_t Phi_12 = (Lepton_1.DeltaPhi(Lepton_2)); // should be abs
                                if (Phi_12 < 1.8)
                                {
                                  // Filling histograms
                                  float Leptons_pT = Lepton_12.Pt();
                                  float Leptons_pT_inGeV  =  Leptons_pT/1000.;

                                  double names_of_global_variable[]={InvMass_Leptons_inGeV, Leptons_pT_inGeV, abs(Phi_12), missingEt, vxp_z, (double)pvxp_n};
                                  double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), lep_charge[goodlep1_index], (double)lep_type[goodlep1_index], lep_ptcone30[goodlep1_index]/lep_pt[goodlep1_index], lep_etcone20[goodlep1_index]/lep_pt[goodlep1_index], lep_z0[goodlep1_index], lep_trackd0pvunbiased[goodlep1_index]};
                                  double names_of_subleadlep_variable[]={Lepton_2.Pt()/1000., Lepton_2.Eta(), Lepton_2.E()/1000., Lepton_2.Phi(), lep_charge[goodlep2_index], (double)lep_type[goodlep2_index], lep_ptcone30[goodlep2_index]/lep_pt[goodlep2_index], lep_etcone20[goodlep2_index]/lep_pt[goodlep2_index], lep_z0[goodlep2_index], lep_trackd0pvunbiased[goodlep2_index]};

                                  TString histonames_of_global_variable[]={"hist_vismass", "hist_ptLL","hist_deltaPhiLL","hist_etmiss","hist_vxp_z","hist_pvxp_n"};
                                  TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
                                  TString histonames_of_subleadlep_variable[]={"hist_subleadleptpt", "hist_subleadlepteta","hist_subleadleptE","hist_subleadleptphi","hist_subleadleptch","hist_subleadleptID","hist_subleadlept_ptc","hist_subleadleptetc","hist_subleadlepz0","hist_subleadlepd0"};

                                  int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
                                  int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
                                  int length_subleadlep = sizeof(names_of_subleadlep_variable)/sizeof(names_of_subleadlep_variable[0]);

                                  for (int i=0; i<length_global; i++)
                                  {
                                    FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
                                  }
                                  for (int i=0; i<length_leadlep; i++)
                                  {
                                    FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
                                  }
                                  for (int i=0; i<length_subleadlep; i++)
                                  {
                                    FillHistogramsSubleadlept( names_of_subleadlep_variable[i], weight, histonames_of_subleadlep_variable[i]);
                                  }

                                }
                              }
                            }
                          }
                        }
                      }
                    }
                }
              }
            }
          }
        }
      }
    }
  }
  return kTRUE;
}

void HWWAnalysis::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
}

void HWWAnalysis::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  name="Output_HWWAnalysis/"+name+".root";
  const char* filename = name.c_str();

  TFile physicsoutput(filename,"recreate");
  WriteHistograms();
  physicsoutput.Close();


}
