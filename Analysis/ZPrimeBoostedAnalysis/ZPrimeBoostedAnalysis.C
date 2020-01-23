/////////////////////////////////////////////////////////////
//// ZPrimeBoostedAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define ZPrimeBoostedAnalysis_cxx

#include "ZPrimeBoostedAnalysis.h"
#include "ZPrimeBoostedAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom3.h>

string name;

void ZPrimeBoostedAnalysis::Begin(TTree * )
{

  nEvents=0;

}

void ZPrimeBoostedAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t ZPrimeBoostedAnalysis::Process(Long64_t entry)
{
  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
  {
      // **********************************************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, Eur. Phys. J. C 78 (2018) 565 and JHEP 11 (2017) 191 //
      // **********************************************************************************************************************//
      
      //Scale factors (adding b-tagging as it is used)
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP*scaleFactor_BTAG;

      //MC weight
      Float_t m_mcWeight = mcWeight;

      // read input option
      TString option = GetOption();
      if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs

      //Total weight
      Float_t weight = scaleFactor*m_mcWeight;

      // Make difference between data and MC
      if(option.Contains("data")) {  weight = 1.; }

      // cut inmediately on at least one large-R jet
      if (largeRjet_n >= 1)
	{
	  
	  // MET > 20 GeV
	  if(met_et > 20000.)
	    {
	      
	      // Preselection cut for electron/muon trigger, Good Run List, and good vertex
	      if(trigE || trigM)
		{
		  
		  // Preselection of good leptons
		  int goodlep_index =0;
		  int goodlep_n = 0;
		  int lep_index =0;
		  
		  for(unsigned int i=0; i<lep_n; i++)
		    {
		      TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);
		      
                      // Lepton is Tight
                      if( lep_isTightID->at(i) )
                        {
                          // Lepton is isolated and hard 
                          if( lep_pt->at(i) > 30000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15 ) )
                            {
                              // electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
                              if ( lep_type->at(i)==11 && TMath::Abs(lep_eta->at(i)) < 2.47 && ( TMath::Abs(lep_eta->at(i)) < 1.37 || TMath::Abs(lep_eta->at(i)) > 1.52 ) ) {
                                if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 5 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
                                  goodlep_n = goodlep_n + 1;
                                  goodlep_index = i;
                                  lep_index++;
                                }
                              }
                              // muon selection
                              if ( lep_type->at(i) ==13 && TMath::Abs(lep_eta->at(i)) < 2.5 ) {
                                if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 3 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
				  
                                  goodlep_n = goodlep_n + 1;
                                  goodlep_index = i;
                                  lep_index++;
                                }
                              }
                            }
                        }
		    }
		  
		  
		  //Exactly one good lepton
		  if(goodlep_n==1)
		    {
		      
                      TLorentzVector Lepton_1  = TLorentzVector();
                      Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
		      
		      //Preselection of good jets
                      int goodjet_n = 0;
                      int goodbjet_n = 0;
                      int goodjet_afterdRlep_n = 0;
		      
                      int goodjet_index[jet_n];
                      int jet_index = 0;
		      
                      int goodbjet_index[jet_n];
                      int bjet_index = 0;
		      
                      int goodjet_afterdRlep_index[jet_n];
                      int jet_afterdRlep_index = 0;
		      
		      for(unsigned int i=0; i<jet_n; i++)
			{
                          if(jet_pt->at(i) > 30000. && TMath::Abs(jet_eta->at(i)) < 2.5)
                            {
                              // JVT cleaning
                              bool jvt_pass=true;
                              if (jet_pt->at(i) < 60000. && TMath::Abs(jet_eta->at(i)) < 2.4 && jet_jvt->at(i) < 0.59) jvt_pass=false;
                              if (jvt_pass)
                                {
                                  goodjet_n++;
                                  goodjet_index[jet_index] = i;
                                  jet_index++;
				  
                                  //  calculate jet close to the lepton
                                  TLorentzVector smallRjet  = TLorentzVector();
                                  smallRjet.SetPtEtaPhiE(jet_pt->at(i),jet_eta->at(i),jet_phi->at(i),jet_E->at(i));
                                  float dR_lep_jet = Lepton_1.DeltaR(smallRjet);
				  
                                  if(dR_lep_jet < 2.0) 
				    {
				      goodjet_afterdRlep_n++;
				      goodjet_afterdRlep_index[jet_afterdRlep_index] = i;  
				      jet_afterdRlep_index++;
				    }
				  
                                  // cut on 0.8244273 is 70% WP
                                  if (jet_MV2c10->at(i) >0.8244273 )
                                    {
                                      goodbjet_n++;
                                      goodbjet_index[bjet_index] = i;
                                      bjet_index++;
                                    }
                                }
                            }
			}
		      
                      // TLorentzVector definitions
                      TLorentzVector      MeT  = TLorentzVector();
                      MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);
		      
                      //Calculation of MTW
                      float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));
		      
                      // MET + mTW > 60 GeV
                      if( (met_et+mtw) > 60000.)
                        {
			  
			  //At least one b-tagged jet
                          if(goodbjet_n >= 1)
                            {
			     
			      // events are required to contain at least one small-R jet
			      if(goodjet_afterdRlep_n >= 1)
				{
			
				  int goodjet1_afterdRlep_index = goodjet_afterdRlep_index[0]; // jet identified with the expected b-jet from the leptonic top-quark decay, although no b-tagging requirement is enforced, highest pT is chosen

				  TLorentzVector goodsmallRjet  = TLorentzVector(); 
				  goodsmallRjet.SetPtEtaPhiE(jet_pt->at(goodjet1_afterdRlep_index),jet_eta->at(goodjet1_afterdRlep_index),jet_phi->at(goodjet1_afterdRlep_index),jet_E->at(goodjet1_afterdRlep_index));

				  // preselection of good top-tagged large-R jets
				  int TopLRjet_n = 0;
                                  int goodTopLRjet_index[largeRjet_n];
			          int TopLRjet_index = 0;

				  // from all the large-R jets, find those we are interested in
				  for(unsigned int l=0; l<largeRjet_n; l++)
				    {
				      // largeRjets are calibrated within: m > 50 GeV, pT > 300 GeV and pT < 1500, |eta| < 2
				      // simplified top-tagging requirement: tau32 < 0.75 
				      if( largeRjet_m->at(l)/1000. > 100 && largeRjet_pt->at(l)/1000. > 300 && largeRjet_pt->at(l)/1000. < 1500 && TMath::Abs(largeRjet_eta->at(l)) < 2.0 && largeRjet_tau32->at(l) < 0.75 )
					{
					  
					  TLorentzVector TopLRjet  = TLorentzVector(); // top-tagged large-R jet
					  TopLRjet.SetPtEtaPhiE(largeRjet_pt->at(l),largeRjet_eta->at(l),largeRjet_phi->at(l),largeRjet_E->at(l));
					  
					  // well separated from the lepton
					  float dPhi = TMath::Abs( Lepton_1.Phi() - TopLRjet.Phi() );
					  dPhi  = dPhi < TMath::Pi() ? dPhi : 2*TMath::Pi() - dPhi;
					  
					  // well separated from the quark associated to the leptonic top
					  float dR = goodsmallRjet.DeltaR(TopLRjet);
					  
                                          // In addition, it is required that the b-tagged small-R jet is either inside the large-R jet or it is the small-R jet associated with the lepton
					  bool btag_is_within_TopLR = false;
                                          bool btag_is_smallRjet = false; 
					  
					  // iterate over all b-jets, check requirement
					  for(int b=0; b<goodbjet_n; b++)
					    {
					      TLorentzVector bjet = TLorentzVector(); 
					      bjet.SetPtEtaPhiE(jet_pt->at(goodbjet_index[b]),jet_eta->at(goodbjet_index[b]),jet_phi->at(goodbjet_index[b]),jet_E->at(goodbjet_index[b]));
					      float dR_bjet_TopLR = bjet.DeltaR(TopLRjet);
					      float dR_bjet_smallRjet = bjet.DeltaR(goodsmallRjet);
					      
					      if(dR_bjet_TopLR<1.0) btag_is_within_TopLR=true;     
					      if(dR_bjet_smallRjet<0.01) btag_is_smallRjet=true;
					      
					    }
					  
					  if(dR > 1.5 && dPhi > 1.0 && ( btag_is_within_TopLR || btag_is_smallRjet ) )
					    {
					      TopLRjet_n++;
                                              goodTopLRjet_index[TopLRjet_index] = l;
                                              TopLRjet_index++;
					    }
					}					
				    } // iterator over largeRjet 
				
			      // before top-tagging, plot Large-R jets 
                              for(unsigned int n=0; n<largeRjet_n; n++)
			      {
		   	         if( largeRjet_m->at(n)/1000. > 50 && largeRjet_pt->at(n)/1000. > 250 && TMath::Abs(largeRjet_eta->at(n)) < 2.0  ) 
				 {

                                      double names_of_boost_variable[]={(double)largeRjet_n, largeRjet_pt->at(n)/1000., largeRjet_eta->at(n),largeRjet_phi->at(n),largeRjet_m->at(n)/1000.,largeRjet_tau32->at(n)};

                                      TString histonames_of_boost_variable[]={"hist_n_leadLRjets","hist_leadLRjet_pt","hist_leadLRjet_eta","hist_leadLRjet_phi","hist_leadLRjet_m","hist_leadLRjet_tau32"};

                                      int length_boost = sizeof(names_of_boost_variable)/sizeof(names_of_boost_variable[0]);

                                      for (int i=0; i<length_boost; i++)
                                        {
                                           FillHistogramsBoosted( names_of_boost_variable[i], weight, histonames_of_boost_variable[i]);
                                        }
			         }
			      } // iterator over largeRjets



				  // require exactly one good TopLRjet_n
				  if(TopLRjet_n == 1)
				    {

				      // In the ATLAS published analysis, the observable m_{reco}^{ttbar} is built. The four-momentum of the hadronic-top jet is used for the hadronic-top candidate. The leptonic-top candidate is constructed by summing the four-momenta of the charged lepton, the neutrino candidate, and the selected small-R jet. For that, the Z-component of the neutrino momentum is estimated by assuming that the neutrino and the lepton come from an on-shell W boson decay and imposing a W mass constraint on the neutrino–lepton system. We leave to the interested party this calculation [a possible reference is: ATLAS Collaboration, JHEP 08 (2015) 148]
				      // Here, for simplicity, we are going to use the leptonic-top candidate without the neutrino
				      
				      int TopHad_index = goodTopLRjet_index[0]; 
				      TLorentzVector TopHad  = TLorentzVector(); // hadronic-top candidate
				      TopHad.SetPtEtaPhiE(largeRjet_pt->at(TopHad_index),largeRjet_eta->at(TopHad_index),largeRjet_phi->at(TopHad_index),largeRjet_E->at(TopHad_index));
				      
				      TLorentzVector TopLep_almost = TLorentzVector(); //  leptonic-top candidate
				      // check that  the selected small-R jet is b-tagged
				      if (jet_MV2c10->at(goodjet1_afterdRlep_index) >0.8244273 ) {
					TopLep_almost = goodsmallRjet + Lepton_1;
					TLorentzVector TTbar = TopHad + TopLep_almost; // Top-tagged Large-R jet + Small-R jet (b-tagged) + Lepton
					FillHistogramsBoosted( TTbar.M()/1000., weight, "hist_ttbarMLR");

				      }
				      
				      // fill histograms	  
				      double names_of_global_variable[]={met_et/1000., mtw/1000.};
				      
				      double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index)};
				      
				      double names_of_jet_variable[]={(double)goodjet_afterdRlep_n, goodsmallRjet.Pt()/1000., goodsmallRjet.Eta(), (double)goodbjet_n, jet_pt->at(goodbjet_index[0])/1000.,jet_eta->at(goodbjet_index[0])};
				      
				      TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw"};
				      TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID"};
				      TString histonames_of_jet_variable[]={"hist_n_jets","hist_leadjet_pt","hist_leadjet_eta","hist_n_bjets","hist_leadbjet_pt","hist_leadbjet_eta"};
				      
				      int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
				      int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
				      int length_leadjet = sizeof(names_of_jet_variable)/sizeof(names_of_jet_variable[0]);
				      
				      for (int i=0; i<length_global; i++)
					{
					  FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
					}
				      
				      for (int i=0; i<length_leadlep; i++)
					{
					  FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
					}
				      for (int i=0; i<length_leadjet; i++)
					{
					  FillHistogramsLeadJet( names_of_jet_variable[i], weight, histonames_of_jet_variable[i]);
					}
				      
				      // save histos of top-tagged large-R jets
				      double names_of_boost_variable[]={(double)TopLRjet_n, largeRjet_pt->at(goodTopLRjet_index[0])/1000., largeRjet_eta->at(goodTopLRjet_index[0]),largeRjet_phi->at(goodTopLRjet_index[0]),largeRjet_m->at(goodTopLRjet_index[0])/1000.,largeRjet_tau32->at(goodTopLRjet_index[0])};

				      TString histonames_of_boost_variable[]={"hist_n_TopLRjets","hist_leadTopLRjet_pt","hist_leadTopLRjet_eta","hist_leadTopLRjet_phi","hist_leadTopLRjet_m","hist_leadTopLRjet_tau32"};
				      
				      int length_boost = sizeof(names_of_boost_variable)/sizeof(names_of_boost_variable[0]);
				      
				      for (int i=0; i<length_boost; i++)
   				        {
  			  		  FillHistogramsBoosted( names_of_boost_variable[i], weight, histonames_of_boost_variable[i]);
				        }
				      
				      
				      // systematic uncertainty on largeRjets 
				      TRandom3* gRand = new TRandom3(0);
				      Double_t      mean  = largeRjet_pt->at(goodTopLRjet_index[0]) / 1000.;
				      Double_t      sigma = largeRjet_pt_syst->at(goodTopLRjet_index[0]) / 1000. ;
				      float largeRjet_pt_variation = gRand->Gaus(mean,sigma);
				      if(largeRjet_pt_variation>300) FillHistogramsBoosted( largeRjet_pt_variation, weight, "hist_leadTopLRjet_syst_pt");
				      
				      
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

void ZPrimeBoostedAnalysis::SlaveTerminate()
{
}

void ZPrimeBoostedAnalysis::Terminate()
{
  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_ZPrimeBoostedAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_ZPrimeBoosted(filename,"recreate");
  WriteHistograms();
  physicsoutput_ZPrimeBoosted.Close();
}
