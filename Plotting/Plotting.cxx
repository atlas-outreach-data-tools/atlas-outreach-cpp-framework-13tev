/////////////////////////////////////////////////////////////
////// Plotting code
////// Author: ATLAS Collaboration (2019)
//////
//////
////// DISCLAIMER:
////// This Software is intended for educational use only!
////// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
///////////////////////////////////////////////////////////////

// include ROOT and C++ headers
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TEnv.h>
#include <THStack.h>
#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TImage.h>
#include <TLine.h>
#include <TColor.h>
#include <TROOT.h>
#include <TH2F.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TMathText.h>
#include <TFrame.h>
#include <TArrow.h>
#include <TGaxis.h>

// include main header located in the same directory
#include "Plotting.h"

//######################### F L A G S ###############################//

// debugging flag, set to 1 for checks
#define DEBUG 1

// yields flag, set to 1 top print data and MC yields
#define YIELDS 1

// normalised signal flag, set to 1 to add normalised signal to the plots (can be used for Higgs, SingleTop, ZPrime, SUSY)
#define NORMSIG 0

// save to pdf flag, by default plots saved as png
#define SAVEPDF 0

// save to root format flag
#define SAVEROOT 0

//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  
  if(argc < 3){
    std::cout<<"usage: ./plot [ WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, SingleTopAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, ZTauTauAnalysis, HyyAnalysis, SUSYAnalysis, ZPrimeBoostedAnalysis, TTbarDilepAnalysis]  [ location of OutputDir_AnalysisName ]"<<std::endl;
    std::cout<<"output stored in a directory \'histograms\' " <<std::endl;
    exit(1);
  }
  
  Plotting* m = new Plotting();
  
  m->SetLumi(36000); // luminosity set by hand to 36fb-1
  m->SetOption(argv[1]);
  m->SetInputLocation(argv[2]);
  string option = argv[1];

  
  // run main plotting code
  m->run();
  
  delete m;
  return 0;
}
///
Plotting::Plotting(){
  lumi = 0;
}

///
Plotting::~Plotting(){
}

///
void Plotting::SetLumi(double l){
  lumi = l;
}

void Plotting::SetOption(std::string analysis){
  option = analysis;
}

void Plotting::SetInputLocation(std::string loc){
  readname = loc;
}


///
void Plotting::run(){
  
  Disclaimer();
  
  getHistoSettings();
  
  AtlasStyle();
  
  WhichFiles();
  
  readFiles(); 
  
  makePlots();
  
  return;
}

///
void Plotting::Disclaimer(){
  
  std::cout << "\n ---------------------DISCLAIMER--------------------- \n" << std::endl ;
  std::cout << "This Software is intended for educational use only!" << std::endl ;
  std::cout << "Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results! " << std::endl ;
  std::cout << "\n ---------------------------------------------------- \n" << std::endl ;
  
}

///
void Plotting::AtlasStyle(){
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  atlasStyle->SetPaperSize(20,26);
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05); 
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16); 
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);
  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  atlasStyle->SetEndErrorSize(0.);
  atlasStyle->SetOptTitle(0);
  atlasStyle->SetOptStat(0);
  atlasStyle->SetOptFit(0);
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

///
void Plotting::ATLASLabel(Double_t x,Double_t y) 
{
  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(kBlack);
  l.SetTextSize(0.05);  
  l.DrawLatex(x,y,"ATLAS Open Data");

  TLatex o;
  o.SetNDC();
  o.SetTextFont(42);
  o.SetTextColor(kBlack);
  o.SetTextSize(0.04);
  double dely = 0.05; 
  o.DrawLatex(x,y-dely,"#it{for education}");

  return;
}

///
void Plotting::WhichFiles(){

  // read input file with the names of the samples
  std::string ifile;

  //options

  if(option.find("HWWAnalysis")           != option.npos){   ifile = "inputfiles/Files_HWW.txt";}
  if(option.find("TTbarDilepAnalysis")    != option.npos){   ifile = "inputfiles/Files_TTbarDilep.txt";}
  if(option.find("ZTauTauAnalysis")       != option.npos){   ifile = "inputfiles/Files_ZTauTau.txt";}
  
  std::cout << "Analysis: " << option << ", reading input from: " << ifile.c_str() << " \n " << std::endl;

  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("#") != line.npos )continue; // a # is a comment and not read
    std::string name;
    Float_t xsec = 1., sumw=1., eff=1., kfac=1.;
    istringstream linestream(line);
    getline(linestream, name);

    std::string readme = readname + "/" + name + ".root";
    TFile* file  = TFile::Open(readme.c_str(), "READ");
    TH1F* histo_SF = (TH1F*)file->Get("hist_scale_factors");
    if(!(name.find("data") != option.npos)){
      xsec = histo_SF->GetBinContent(0);
      sumw = histo_SF->GetBinContent(1);
      eff = histo_SF->GetBinContent(2);
      kfac = histo_SF->GetBinContent(3);
    }
    
    if (DEBUG) cout << name << " " << xsec << " " << sumw << " " << eff << " " << kfac << endl;
    //float sumw_eff = atof(sumw.c_str()) * atof(eff.c_str());
    float xsec_eff_kfac = xsec*eff*kfac;
    //float sumw_eff = atof(sumw.c_str()) / atof(eff.c_str());
    SF[name] = std::make_pair(xsec_eff_kfac, sumw);    
    
  }
  return;
 
}

///
void Plotting::readFiles(){

  std::cout << "Reading files from: " << readname << " \n " << std::endl;

  if (option.find("HWWAnalysis") != option.npos){
    std::cout<<"=====processing HWWAnalysis====="<<std::endl;
  }
  if (option.find("ZTauTauAnalysis") != option.npos){
    std::cout<<"=====processing ZTauTauAnalysis====="<<std::endl;
  }
  if (option.find("TTbarDilepAnalysis") != option.npos){
    std::cout<<"=====processing TTbarDilepAnalysis====="<<std::endl;
  }
 
  std::cout << "\n" << std::endl;

  std::map<std::string,std::pair<double,double> >::const_iterator SFiter;
  for(SFiter = SF.begin(); SFiter != SF.end(); SFiter++){
    std::string readme = readname + "/" + SFiter->first + ".root";
    if (DEBUG)  std::cout << "Reading file: " << readme << std::endl;
    TFile* file  = TFile::Open(readme.c_str(), "READ");
    
    createHistoSet(file, SFiter->first);
    
    // apply Scale Factors: scaling is done by calculating the luminosity of the sample via (xsec*red_eff*kfactor)/(sumw) and  multiplying the target luminosity
    if(std::strstr((SFiter->first).c_str(),"data") == NULL ){
      std::vector<std::string> v_n; v_n.clear();
      std::string n = SFiter->first;
      v_n.push_back(n);
      for(unsigned int i = 0; i < v_n.size(); ++i){
        std::map<std::string,TH1F*>::const_iterator fIter = histo[v_n[i]].begin();
        std::map<std::string,TH1F*>::const_iterator lIter = histo[v_n[i]].end();
        double scf = 1;
	scf = (lumi *  SFiter->second.first) / SFiter->second.second ;
        for(; fIter!=lIter;++fIter){
	  if (DEBUG) std::cout<<"lumi "<< lumi << "  xsec  " << SFiter->second.first << " sumw_eff " << SFiter->second.second << std::endl;
	  if (DEBUG) std::cout<<"Scaling histogram: "<< fIter->first << " by a factor of: " << scf << std::endl;
	  fIter->second->Scale(scf);

          // MC overflow
	  if(std::strstr((fIter->first).c_str(),"four_lep") == NULL )
          if( abs(fIter->second->GetBinContent(fIter->second->GetNbinsX()+1)) > 0){
            fIter->second->AddBinContent(fIter->second->GetNbinsX(), fIter->second->GetBinContent(fIter->second->GetNbinsX()+1));
          }

        }
      }
    }
    
  }
  return;
}

///
void Plotting::createHistoSet(TFile* file, std::string proc){
  
  std::vector<HistoHandler*>::iterator fIter = hset.begin();
  std::vector<HistoHandler*>::iterator lIter = hset.end();
  
  for(; fIter != lIter; ++fIter){
    std::string n;
    n  = (*fIter)->GetName();
    if (DEBUG) cout << "reading histogram: " << n << endl;
    createHistogram(file, n, proc);  
  }
  
  return;
}


///
void Plotting::createHistogram(TFile* file, std::string hname ,  std::string proc){
  
  histo[proc][hname] = (TH1F*)file->Get(hname.c_str()); 
  
  return;
}

///
void Plotting::makePlots(){
  
  TCanvas* c;
  c = new TCanvas("c","c",700,750);
  TPad* pad0; //upper
  TPad* pad1; //lower
  TPad* padX; //mask
  TPad* pad2X; //mask

  pad0 = new TPad("pad0","pad0",0,0.29,1,1,0,0,0);
  pad0->SetTickx(false);
  pad0->SetTicky(false);
  pad0->SetTopMargin(0.05);
  pad0->SetBottomMargin(0);
  pad0->SetLeftMargin(0.14);
  pad0->SetRightMargin(0.05);
  pad0->SetFrameBorderMode(0);
  pad0->SetTopMargin(0.06);

  pad1 = new TPad("pad1","pad1",0,0,1,0.29,0,0,0);
  pad1->SetTickx(false);
  pad1->SetTicky(false);
  pad1->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.5);
  pad1->SetLeftMargin(0.14);
  pad1->SetRightMargin(0.05);
  pad1->SetFrameBorderMode(0);
 
  padX = new TPad("pad1","pad1",0.08, 0.27, 0.135, 0.29, 0, 0, 0);
  padX->SetTickx(false);  padX->SetTicky(false);  padX->SetTopMargin(0.0);
  padX->SetBottomMargin(0.5);  padX->SetLeftMargin(0.14);  padX->SetRightMargin(0.05);  padX->SetFrameBorderMode(0);

  pad2X = new TPad("pad1","pad1",0.08, 0.132, 0.135, 0.16, 0, 0, 0);
  pad2X->SetTickx(false);  pad2X->SetTicky(false);  pad2X->SetTopMargin(0.0);
  pad2X->SetBottomMargin(0.5);  pad2X->SetLeftMargin(0.14);  pad2X->SetRightMargin(0.05);  pad2X->SetFrameBorderMode(0);

  pad1->Draw();
  pad0->Draw();
  padX->Draw();

  if(!(option.find("HyyAnalysis") != option.npos)) 	    pad2X->Draw();

  pad0->cd();
  
  ///////////////////////////////////////////////////////////////////////
  // we create the maps of the histograms for each sample

  // data
  std::map<std::string,TH1F*> data; 
  
  // TTbarDilep
  //std::map<std::string,TH1F*> PhPy8EG_A14_ttbar_hdamp258p75_dil;
  std::map<std::string,TH1F*> PhPy8EG_A14_ttbar_hdamp258p75_nonallhad;
  std::map<std::string,TH1F*> PhPy8EG_A14_ttbar_hdamp258p75_allhad;
  
  // HWW
  std::map<std::string, TH1F*> PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5;
  std::map<std::string, TH1F*> PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv;
  
  // Single top
  std::map<std::string, TH1F*> PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top;
  std::map<std::string, TH1F*> PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop;
  std::map<std::string, TH1F*> PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top;
  std::map<std::string, TH1F*> PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop;
  std::map<std::string, TH1F*> PhPy8EG_A14_tchan_BW50_lept_top;
  std::map<std::string, TH1F*> PhPy8EG_A14_tchan_BW50_lept_antitop;

  // Diboson
  std::map<std::string, TH1F*> Sh_2212_llll;
  std::map<std::string, TH1F*> Sh_2212_lllv;
  std::map<std::string, TH1F*> Sh_2212_llvv_os;
  std::map<std::string, TH1F*> Sh_2212_llvv_ss;
  std::map<std::string, TH1F*> Sh_2212_lvvv;
  std::map<std::string, TH1F*> Sh_2212_vvvv;
  std::map<std::string, TH1F*> Sh_2211_WlvWqq;
  std::map<std::string, TH1F*> Sh_2211_WlvZqq;
  std::map<std::string, TH1F*> Sh_2211_WlvZbb;
  std::map<std::string, TH1F*> Sh_2211_ZqqZll;
  std::map<std::string, TH1F*> Sh_2211_ZbbZll;
  std::map<std::string, TH1F*> Sh_2211_ZqqZvv;
  std::map<std::string, TH1F*> Sh_2211_ZbbZvv;
  std::map<std::string, TH1F*> Sherpa_222_NNPDF30NNLO_ggZllZqq;
  std::map<std::string, TH1F*> Sherpa_222_NNPDF30NNLO_ggZvvZqq;
  std::map<std::string, TH1F*> Sherpa_222_NNPDF30NNLO_ggWmlvWpqq;
  std::map<std::string, TH1F*> Sherpa_222_NNPDF30NNLO_ggWplvWmqq;

  // V_plus_jets
  std::map<std::string, TH1F*> Sh_2211_Zee_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2211_Zee_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2211_Zee_maxHTpTV2_CVetoBVeto;
  std::map<std::string, TH1F*> Sh_2211_Zmumu_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wenu_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2211_Wenu_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wenu_maxHTpTV2_CVetoBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wmunu_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wtaunu_L_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wtaunu_H_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto;
  std::map<std::string, TH1F*> Sh_2214_Ztautau_maxHTpTV2_BFilter;
  std::map<std::string, TH1F*> Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto;
  std::map<std::string, TH1F*> Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto;

  // tt_others
  std::map<std::string, TH1F*> aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW;
  std::map<std::string, TH1F*> aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu;
  std::map<std::string, TH1F*> aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq;
  std::map<std::string, TH1F*> aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee;
  std::map<std::string, TH1F*> aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu;
  std::map<std::string, TH1F*> aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau;

  ///////////////////////////////////////////////////////////////////////
  // Actual reading of the input files
  // The names must be the same as in Files_***.txt 

  // read data
  data = histo["data"];

  // samples to be used for all the analyses

  //ttbar
  //PhPy8EG_A14_ttbar_hdamp258p75_dil = histo["PhPy8EG_A14_ttbar_hdamp258p75_dil"];
  PhPy8EG_A14_ttbar_hdamp258p75_nonallhad = histo["PhPy8EG_A14_ttbar_hdamp258p75_nonallhad"];
  PhPy8EG_A14_ttbar_hdamp258p75_allhad = histo["PhPy8EG_A14_ttbar_hdamp258p75_allhad"];
  
  // Single top
  //PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top = histo["PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top"];
  //PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop = histo["PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop"];
  //PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top = histo["PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top"];
  //PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop = histo["PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop"];
  PhPy8EG_A14_tchan_BW50_lept_top = histo["PhPy8EG_A14_tchan_BW50_lept_top"];
  PhPy8EG_A14_tchan_BW50_lept_antitop = histo["PhPy8EG_A14_tchan_BW50_lept_antitop"];

  // Diboson
  Sh_2212_llll = histo["Sh_2212_llll"];
  Sh_2212_lllv = histo["Sh_2212_lllv"];
  Sh_2212_llvv_os = histo["Sh_2212_llvv_os"];
  Sh_2212_llvv_ss = histo["Sh_2212_llvv_ss"];
  Sh_2212_lvvv = histo["Sh_2212_lvvv"];
  //Sh_2212_vvvv = histo["Sh_2212_vvvv"];
  Sh_2211_WlvWqq = histo["Sh_2211_WlvWqq"];
  Sh_2211_WlvZqq = histo["Sh_2211_WlvZqq"];
  Sh_2211_WlvZbb = histo["Sh_2211_WlvZbb"];
  Sh_2211_ZqqZll = histo["Sh_2211_ZqqZll"];
  Sh_2211_ZbbZll = histo["Sh_2211_ZbbZll"];
  Sh_2211_ZqqZvv = histo["Sh_2211_ZqqZvv"];
  Sh_2211_ZbbZvv = histo["Sh_2211_ZbbZvv"];
  //Sherpa_222_NNPDF30NNLO_ggZllZqq = histo["Sherpa_222_NNPDF30NNLO_ggZllZqq"];
  //Sherpa_222_NNPDF30NNLO_ggZvvZqq = histo["Sherpa_222_NNPDF30NNLO_ggZvvZqq"];
  //Sherpa_222_NNPDF30NNLO_ggWmlvWpqq = histo["Sherpa_222_NNPDF30NNLO_ggWmlvWpqq"];
  //Sherpa_222_NNPDF30NNLO_ggWplvWmqq = histo["Sherpa_222_NNPDF30NNLO_ggWplvWmqq"];
  
  // V_plus_jets
  Sh_2211_Zee_maxHTpTV2_BFilter = histo["Sh_2211_Zee_maxHTpTV2_BFilter"];
  //Sh_2211_Zee_maxHTpTV2_CFilterBVeto = histo["Sh_2211_Zee_maxHTpTV2_CFilterBVeto"];
  Sh_2211_Zee_maxHTpTV2_CVetoBVeto = histo["Sh_2211_Zee_maxHTpTV2_CVetoBVeto"];
  Sh_2211_Zmumu_maxHTpTV2_BFilter = histo["Sh_2211_Zmumu_maxHTpTV2_BFilter"];
  Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto = histo["Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto"];
  Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto = histo["Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto"];
  Sh_2211_Wenu_maxHTpTV2_BFilter = histo["Sh_2211_Wenu_maxHTpTV2_BFilter"];
  Sh_2211_Wenu_maxHTpTV2_CFilterBVeto = histo["Sh_2211_Wenu_maxHTpTV2_CFilterBVeto"];
  Sh_2211_Wenu_maxHTpTV2_CVetoBVeto = histo["Sh_2211_Wenu_maxHTpTV2_CVetoBVeto"];
  Sh_2211_Wmunu_maxHTpTV2_BFilter = histo["Sh_2211_Wmunu_maxHTpTV2_BFilter"];
  Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto = histo["Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto"];
  Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto = histo["Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto"];
  Sh_2211_Wtaunu_L_maxHTpTV2_BFilter = histo["Sh_2211_Wtaunu_L_maxHTpTV2_BFilter"];
  Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto = histo["Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto"];
  Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto = histo["Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto"];
  Sh_2211_Wtaunu_H_maxHTpTV2_BFilter = histo["Sh_2211_Wtaunu_H_maxHTpTV2_BFilter"];
  Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto = histo["Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto"];
  Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto = histo["Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto"];
  Sh_2214_Ztautau_maxHTpTV2_BFilter = histo["Sh_2214_Ztautau_maxHTpTV2_BFilter"];
  Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto = histo["Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto"];
  Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto = histo["Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto"];

  // reading HWW samples used
  if(option.find("HWWAnalysis") != option.npos){

    // H->WW
    PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5 = histo["PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5"];
    PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv = histo["PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv"];

  }
  
  // reading TTbarDilep samples used
  if(option.find("TTbarDilepAnalysis") != option.npos){

    // tt_others
    aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW = histo["aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW"];
    aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu = histo["aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu"];
    aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq = histo["aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq"];
    aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee = histo["aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee"];
    aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu = histo["aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu"];
    aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau = histo["aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau"];
    
  }

  ///////////////////////////////////////////////////////////////////////
  // Finally, the plotting part begins here
  
  std::map<std::string,TH1F*>::const_iterator fIter;
  std::map<std::string,TH1F*>::const_iterator lIter;
  fIter = data.begin(); lIter = data.end();

  // iterator over the names of the histograms per file
  for(; fIter != lIter; ++fIter){
    
    std::cout<<"Plotting histogram: "<< fIter->first << std::endl;
    
    // data style
    fIter->second->SetMarkerStyle(20);
    fIter->second->SetMarkerColor(kBlack);
    fIter->second->SetMarkerSize(1.2);
    fIter->second->SetLineWidth(2);
    fIter->second->SetMinimum(0.1);
    gStyle->SetEndErrorSize(1.); 
    TGaxis::SetMaxDigits(4); // maximum digits in Y axis title

    if(!(option.find("HyyAnalysis") != option.npos))  fIter->second->Draw("E1");
    
    // create histograms and merge several MCs into them
    // general
    TH1F* diboson = new TH1F();
    TH1F* W = new TH1F();
    TH1F* Z = new TH1F();
    TH1F* ttbar = new TH1F();
    TH1F* stop = new TH1F();
    
    //special
    TH1F* V = new TH1F();
    TH1F* W_Z = new TH1F();
    TH1F* Z_Z = new TH1F();
    TH1F* WWZ = new TH1F();
    TH1F* VV = new TH1F();
    TH1F* top = new TH1F();
    TH1F* topV = new TH1F();
    TH1F* Higgs = new TH1F();
    TH1F* Z_tautau = new TH1F();
    TH1F* stop_tq = new TH1F();
    TH1F* stop_tWtb = new TH1F();
    TH1F* ZVV = new TH1F();
    TH1F* ZPrime = new TH1F();
    TH1F* tt_others = new TH1F();

    /*
    // merge for WBoson and SingleTop and ZPrimeBoosted analyses
    if( option.find("WBosonAnalysis") != option.npos || 
        option.find("SingleTopAnalysis") != option.npos || 
	option.find("ZPrimeBoostedAnalysis") != option.npos )
    {
      
      // diboson samples 
      diboson = (TH1F*)WlvZqq[fIter->first]->Clone();
      diboson->Add(WplvWmqq[fIter->first]);
      if(!(option.find("ZPrimeBoostedAnalysis") != option.npos))  diboson->Add(WpqqWmlv[fIter->first]);
      diboson->Add(ZqqZll[fIter->first]); 
      diboson->Add(WqqZll[fIter->first]);
      if(!(option.find("ZPrimeBoostedAnalysis") != option.npos))  diboson->Add(llll[fIter->first]); 
      diboson->Add(lllv[fIter->first]);
      diboson->Add(llvv[fIter->first]);
      diboson->Add(lvvv[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
  
      // sliced W+jets samples
      W = (TH1F*)Wenu_PTV0_70_BFilter[fIter->first]->Clone();
      W->Add(Wenu_PTV0_70_CFilterBVeto[fIter->first]);
      W->Add(Wenu_PTV0_70_CVetoBVeto[fIter->first]);
      W->Add(Wenu_PTV1000[fIter->first]);
      W->Add(Wenu_PTV140_280_BFilter[fIter->first]);
      W->Add(Wenu_PTV140_280_CFilterBVeto[fIter->first]);
      W->Add(Wenu_PTV140_280_CVetoBVeto[fIter->first]);
      W->Add(Wenu_PTV280_500_BFilter[fIter->first]);
      W->Add(Wenu_PTV280_500_CFilterBVeto[fIter->first]);
      W->Add(Wenu_PTV280_500_CVetoBVeto[fIter->first]);
      W->Add(Wenu_PTV500_1000[fIter->first]);
      W->Add(Wenu_PTV70_140_BFilter[fIter->first]);
      W->Add(Wenu_PTV70_140_CFilterBVeto[fIter->first]);
      W->Add(Wenu_PTV70_140_CVetoBVeto[fIter->first]);
      W->Add(Wmunu_PTV0_70_BFilter[fIter->first]);
      W->Add(Wmunu_PTV0_70_CFilterBVeto[fIter->first]);
      W->Add(Wmunu_PTV0_70_CVetoBVeto[fIter->first]);
      W->Add(Wmunu_PTV1000[fIter->first]);
      W->Add(Wmunu_PTV140_280_BFilter[fIter->first]);
      W->Add(Wmunu_PTV140_280_CFilterBVeto[fIter->first]);
      W->Add(Wmunu_PTV140_280_CVetoBVeto[fIter->first]);
      W->Add(Wmunu_PTV280_500_BFilter[fIter->first]);
      W->Add(Wmunu_PTV280_500_CFilterBVeto[fIter->first]);
      W->Add(Wmunu_PTV280_500_CVetoBVeto[fIter->first]);
      W->Add(Wmunu_PTV500_1000[fIter->first]);
      W->Add(Wmunu_PTV70_140_BFilter[fIter->first]);
      W->Add(Wmunu_PTV70_140_CFilterBVeto[fIter->first]);
      W->Add(Wmunu_PTV70_140_CVetoBVeto[fIter->first]);
      W->Add(Wtaunu_PTV0_70_BFilter[fIter->first]);
      W->Add(Wtaunu_PTV0_70_CFilterBVeto[fIter->first]);
      W->Add(Wtaunu_PTV0_70_CVetoBVeto[fIter->first]);
      W->Add(Wtaunu_PTV1000[fIter->first]);
      W->Add(Wtaunu_PTV140_280_BFilter[fIter->first]);
      W->Add(Wtaunu_PTV140_280_CFilterBVeto[fIter->first]);
      W->Add(Wtaunu_PTV140_280_CVetoBVeto[fIter->first]);
      W->Add(Wtaunu_PTV280_500_BFilter[fIter->first]);
      W->Add(Wtaunu_PTV280_500_CFilterBVeto[fIter->first]);
      W->Add(Wtaunu_PTV280_500_CVetoBVeto[fIter->first]);
      W->Add(Wtaunu_PTV500_1000[fIter->first]);
      W->Add(Wtaunu_PTV70_140_BFilter[fIter->first]);
      W->Add(Wtaunu_PTV70_140_CFilterBVeto[fIter->first]);
      W->Add(Wtaunu_PTV70_140_CVetoBVeto[fIter->first]);
      W->SetFillColor(kGreen-3);
      W->SetLineWidth(0);
      if( option.find("SingleTopAnalysis") != option.npos ) W->Scale(1.1); //change by hand the normalisation from validation region
      

      // inclusive Z samples (also could use sliced samples, however this speeds up the process as this is a minor background)     
      Z = (TH1F*)Zmumu[fIter->first]->Clone();
      Z->Add(Ztautau[fIter->first]);
      Z->Add(Zee[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);
    
      V = (TH1F*)W->Clone();
      V->Add(Ztautau[fIter->first]);
      V->Add(Zee[fIter->first]);
      V->Add(Zmumu[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);

      if( option.find("ZPrimeBoostedAnalysis") != option.npos){
        ZPrime = (TH1F*)ZPrime1000[fIter->first]->Clone();
        ZPrime->SetFillColor(kRed);
        ZPrime->SetLineWidth(0);
      }

      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
      if( option.find("ZPrimeBoostedAnalysis") != option.npos) {
	      if( !(fIter->first.find("leadLR") != option.npos )) ttbar->Scale(0.91); //change by hand the normalisation depending on large-R jets
      }

      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

      // only t-channel single top
      stop_tq = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop_tq->Add(single_antitop_tchan[fIter->first]);
      stop_tq->SetFillColor(kAzure+8);
      stop_tq->SetLineWidth(0);

      // other single top (tW, s-channel) and ttbar
      stop_tWtb = (TH1F*)single_top_wtchan[fIter->first]->Clone();
      stop_tWtb->Add(single_antitop_wtchan[fIter->first]);
      stop_tWtb->Add(single_top_schan[fIter->first]);
      stop_tWtb->Add(single_antitop_schan[fIter->first]);
      stop_tWtb->Add(ttbar_lep[fIter->first]);
      stop_tWtb->SetFillColor(kOrange-3);
      stop_tWtb->SetLineWidth(0);

      // special Z and diboson
      ZVV = (TH1F*)Zmumu[fIter->first]->Clone();
      ZVV->Add(Ztautau[fIter->first]);
      ZVV->Add(Zee[fIter->first]);
      ZVV->Add(WlvZqq[fIter->first]);
      ZVV->Add(WplvWmqq[fIter->first]);
      if(!(option.find("ZPrimeBoostedAnalysis") != option.npos))  ZVV->Add(WpqqWmlv[fIter->first]);
      ZVV->Add(ZqqZll[fIter->first]);
      ZVV->Add(WqqZll[fIter->first]);
      if(!(option.find("ZPrimeBoostedAnalysis") != option.npos))  ZVV->Add(llll[fIter->first]);
      ZVV->Add(lllv[fIter->first]);
      ZVV->Add(llvv[fIter->first]);
      ZVV->Add(lvvv[fIter->first]);
      ZVV->SetFillColor(kPink+9);
      ZVV->SetLineWidth(0);


    }

    // merge for Top 
    if(option.find("TTbarAnalysis") != option.npos || option.find("ZBosonAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos || option.find("ZZDiBosonAnalysis") != option.npos ){

      //ttbar
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);

      // all diboson
      diboson = (TH1F*)WlvZqq[fIter->first]->Clone();
      diboson->Add(WplvWmqq[fIter->first]);
      diboson->Add(WpqqWmlv[fIter->first]);
      diboson->Add(ZqqZll[fIter->first]);
      diboson->Add(WqqZll[fIter->first]);
      diboson->Add(llll[fIter->first]);
      diboson->Add(lllv[fIter->first]);
      diboson->Add(llvv[fIter->first]);
      diboson->Add(lvvv[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);

      // split diboson into WW+ZZ
      VV = (TH1F*)WplvWmqq[fIter->first]->Clone(); // WW
      VV->Add(WpqqWmlv[fIter->first]); // WW
      VV->Add(ZqqZll[fIter->first]); // Z->qq Z->ll
      VV->Add(llll[fIter->first]); // Z->ll Z->ll
      VV->Add(llvv[fIter->first]); // Z->ll Z->vv
      VV->SetFillColor(kBlue-6);
      VV->SetLineWidth(0);
      
      // only WZ
      W_Z = (TH1F*)lllv[fIter->first]->Clone(); // W->lv Z->ll
      W_Z->Add(lvvv[fIter->first]); // W->lv Z->vv
      W_Z->Add(WqqZll[fIter->first]); // W->qq Z->ll
      W_Z->Add(WlvZqq[fIter->first]);  // W->lv Z->qq
      W_Z->SetFillColor(kRed-7);
      W_Z->SetLineWidth(0);


      // split diboson into WW+WZ
      WWZ = (TH1F*)WplvWmqq[fIter->first]->Clone(); // WW
      WWZ->Add(WpqqWmlv[fIter->first]); // WW
      WWZ->Add(lllv[fIter->first]);  // // W->lv Z->ll
      WWZ->Add(lvvv[fIter->first]); // W->lv Z->vv
      WWZ->Add(WqqZll[fIter->first]); // W->qq Z->ll
      WWZ->Add(WlvZqq[fIter->first]);  // W->lv Z->qq
      WWZ->SetFillColor(kRed-7);
      WWZ->SetLineWidth(0);

      // only ZZ
      Z_Z = (TH1F*)llll[fIter->first]->Clone(); // Z->ll Z->ll
      Z_Z->Add(ZqqZll[fIter->first]); // Z->qq Z->ll
      Z_Z->Add(llvv[fIter->first]); // Z->ll Z->vv
      Z_Z->SetFillColor(kBlue-6);
      Z_Z->SetLineWidth(0);
      //      Z_Z->Scale(1.08); // loop-induced gluon–gluon gg->ZZ is not included in the current MCs, which can be seen from the 4 lepton control region


      // single top
      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

      // add ttbar and single top
      top = (TH1F*)ttbar->Clone();
      top->Add(stop);
      top->SetFillColor(kOrange-3);
      top->SetLineWidth(0);

      // V+jets, both W and Z
      V = (TH1F*)Wplusenu[fIter->first]->Clone();
      V->Add(Wplusmunu[fIter->first]);
      V->Add(Wplustaunu[fIter->first]);
      V->Add(Wminusenu[fIter->first]);
      V->Add(Wminusmunu[fIter->first]);
      V->Add(Wminustaunu[fIter->first]);
      V->Add(Ztautau[fIter->first]);
      V->Add(Zee[fIter->first]);
      V->Add(Zmumu[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);
    
      
      // ttbar, single top, V+jets
      topV = (TH1F*)top->Clone();
      topV->Add(V);
      topV->SetFillColor(kGreen-3);
      topV->SetLineWidth(0);

 
 
      Z = (TH1F*)Zmumu[fIter->first]->Clone();
      Z->Add(Ztautau[fIter->first]);
      Z->Add(Zee[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);

      W = (TH1F*)Wplusenu[fIter->first]->Clone();
      W->Add(Wplusmunu[fIter->first]);
      W->Add(Wplustaunu[fIter->first]);
      W->Add(Wminusenu[fIter->first]);
      W->Add(Wminusmunu[fIter->first]);
      W->Add(Wminustaunu[fIter->first]);
      W->SetFillColor(kGreen-3);
      W->SetLineWidth(0);

    }

    */

    // merge for HWW _Analysis
    if(option.find("HWWAnalysis") != option.npos){

      // Higgs
      Higgs = (TH1F*)PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5[fIter->first]->Clone();
      Higgs->Add(PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);

      // ttbar
      ttbar = (TH1F*)PhPy8EG_A14_ttbar_hdamp258p75_nonallhad[fIter->first]->Clone();
      ttbar->Add(PhPy8EG_A14_ttbar_hdamp258p75_allhad[fIter->first]); 
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);

      // Diboson
      diboson = (TH1F*)Sh_2212_llll[fIter->first]->Clone();
      diboson->Add(Sh_2212_lllv[fIter->first]);
      diboson->Add(Sh_2212_llvv_os[fIter->first]);
      diboson->Add(Sh_2212_llvv_ss[fIter->first]);
      diboson->Add(Sh_2212_lvvv[fIter->first]);
      //diboson->Add(Sh_2212_vvvv[fIter->first]);
      diboson->Add(Sh_2211_WlvWqq[fIter->first]);
      diboson->Add(Sh_2211_WlvZqq[fIter->first]);
      diboson->Add(Sh_2211_WlvZbb[fIter->first]);
      diboson->Add(Sh_2211_ZqqZll[fIter->first]);
      diboson->Add(Sh_2211_ZbbZll[fIter->first]);
      diboson->Add(Sh_2211_ZqqZvv[fIter->first]);
      diboson->Add(Sh_2211_ZbbZvv[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
      diboson->Scale(1.3); //normalisation scaling, from WW control region we need a factor of 1.3, underestimation of WZ cross section requires a normalisation factor of 1.15-1.2, also contributions with misidentified leptons are not estimated nor added => a total of 1.3 is taken

      // V_plus_jets

      V = (TH1F*)Sh_2211_Wenu_maxHTpTV2_BFilter[fIter->first]->Clone();
      V->Add(Sh_2211_Wenu_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Wenu_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2211_Wmunu_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2211_Wtaunu_L_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2211_Wtaunu_H_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2211_Zee_maxHTpTV2_BFilter[fIter->first]);
      //V->Add(Sh_2211_Zee_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Zee_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2211_Zmumu_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2214_Ztautau_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);

      // single top
      stop = (TH1F*)PhPy8EG_A14_tchan_BW50_lept_top[fIter->first]->Clone();
      stop->Add(PhPy8EG_A14_tchan_BW50_lept_antitop[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

    }

    // merge for ZTauTauAnalysis
    if(option.find("ZTauTauAnalysis") != option.npos){

      // ttbar

      ttbar = (TH1F*)PhPy8EG_A14_ttbar_hdamp258p75_nonallhad[fIter->first]->Clone();
      ttbar->Add(PhPy8EG_A14_ttbar_hdamp258p75_allhad[fIter->first]);
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);

      // all diboson

      diboson = (TH1F*)Sh_2212_llll[fIter->first]->Clone();
      diboson->Add(Sh_2212_lllv[fIter->first]);
      diboson->Add(Sh_2212_llvv_os[fIter->first]);
      diboson->Add(Sh_2212_llvv_ss[fIter->first]);
      diboson->Add(Sh_2212_lvvv[fIter->first]);
      //diboson->Add(Sh_2212_vvvv[fIter->first]);
      diboson->Add(Sh_2211_WlvWqq[fIter->first]);
      diboson->Add(Sh_2211_WlvZqq[fIter->first]);
      diboson->Add(Sh_2211_WlvZbb[fIter->first]);
      diboson->Add(Sh_2211_ZqqZll[fIter->first]);
      diboson->Add(Sh_2211_ZbbZll[fIter->first]);
      diboson->Add(Sh_2211_ZqqZvv[fIter->first]);
      diboson->Add(Sh_2211_ZbbZvv[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);

      // single top

      stop = (TH1F*)PhPy8EG_A14_tchan_BW50_lept_top[fIter->first]->Clone();
      stop->Add(PhPy8EG_A14_tchan_BW50_lept_antitop[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

      // merge minor bkgs
      
      topV = (TH1F*)ttbar->Clone();
      topV->Add(stop);
      topV->Add(diboson);
      topV->SetFillColor(kOrange-3);
      topV->SetLineWidth(0);

      // sliced Sherpa W+jets samples

      W = (TH1F*)Sh_2211_Wenu_maxHTpTV2_BFilter[fIter->first]->Clone();
      W->Add(Sh_2211_Wenu_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wenu_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->Add(Sh_2211_Wmunu_maxHTpTV2_BFilter[fIter->first]);
      W->Add(Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_L_maxHTpTV2_BFilter[fIter->first]);
      W->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_H_maxHTpTV2_BFilter[fIter->first]);
      W->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->SetFillColor(kGreen-3);
      W->SetLineWidth(0);

      // sliced Sherpa Z+jets samples
      // merge Z->ee and Z->mumu

      Z = (TH1F*)Sh_2211_Zee_maxHTpTV2_BFilter[fIter->first]->Clone();
      //Z->Add(Sh_2211_Zee_maxHTpTV2_CFilterBVeto[fIter->first]);
      Z->Add(Sh_2211_Zee_maxHTpTV2_CVetoBVeto[fIter->first]);
      Z->Add(Sh_2211_Zmumu_maxHTpTV2_BFilter[fIter->first]);
      Z->Add(Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto[fIter->first]);
      Z->Add(Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);

      // Z->tau tau      

      Z_tautau = (TH1F*)Sh_2214_Ztautau_maxHTpTV2_BFilter[fIter->first]->Clone();
      Z_tautau->Add(Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto[fIter->first]);
      Z_tautau->SetFillColor(kAzure+7);
      Z_tautau->SetLineWidth(0);
     
     }


    // merge for ZTauTauAnalysis
    if(option.find("TTbarDilepAnalysis") != option.npos){
      
      // ttbar
      
      ttbar = (TH1F*)PhPy8EG_A14_ttbar_hdamp258p75_nonallhad[fIter->first]->Clone();
      ttbar->Add(PhPy8EG_A14_ttbar_hdamp258p75_allhad[fIter->first]); 
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
      
      // stop
      stop = (TH1F*)PhPy8EG_A14_tchan_BW50_lept_top[fIter->first]->Clone();
      stop->Add(PhPy8EG_A14_tchan_BW50_lept_antitop[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);
      
      // Diboson
      diboson = (TH1F*)Sh_2212_llll[fIter->first]->Clone();
      diboson->Add(Sh_2212_lllv[fIter->first]);
      diboson->Add(Sh_2212_llvv_os[fIter->first]);
      diboson->Add(Sh_2212_llvv_ss[fIter->first]);
      diboson->Add(Sh_2212_lvvv[fIter->first]);
      //diboson->Add(Sh_2212_vvvv[fIter->first]);
      diboson->Add(Sh_2211_WlvWqq[fIter->first]);
      diboson->Add(Sh_2211_WlvZqq[fIter->first]);
      diboson->Add(Sh_2211_WlvZbb[fIter->first]);
      diboson->Add(Sh_2211_ZqqZll[fIter->first]);
      diboson->Add(Sh_2211_ZbbZll[fIter->first]);
      diboson->Add(Sh_2211_ZqqZvv[fIter->first]);
      diboson->Add(Sh_2211_ZbbZvv[fIter->first]);
      /*
	diboson->Add(Sherpa_222_NNPDF30NNLO_ggZllZqq[fIter->first]);
	diboson->Add(Sherpa_222_NNPDF30NNLO_ggZvvZqq[fIter->first]);
	diboson->Add(Sherpa_222_NNPDF30NNLO_ggWmlvWpqq[fIter->first]);
	diboson->Add(Sherpa_222_NNPDF30NNLO_ggWplvWmqq[fIter->first]);
      */
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
      
      // V_plus_jets
      
      W = (TH1F*)Sh_2211_Wenu_maxHTpTV2_BFilter[fIter->first]->Clone();
      W->Add(Sh_2211_Wenu_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wenu_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->Add(Sh_2211_Wmunu_maxHTpTV2_BFilter[fIter->first]);
      W->Add(Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_L_maxHTpTV2_BFilter[fIter->first]);
      W->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_H_maxHTpTV2_BFilter[fIter->first]);
      W->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto[fIter->first]);
      W->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto[fIter->first]);
      W->SetFillColor(kGreen-3);
      W->SetLineWidth(0);
      
      Z = (TH1F*)Sh_2211_Zee_maxHTpTV2_BFilter[fIter->first]->Clone();
      //Z->Add(Sh_2211_Zee_maxHTpTV2_CFilterBVeto[fIter->first]);
      Z->Add(Sh_2211_Zee_maxHTpTV2_CVetoBVeto[fIter->first]);
      Z->Add(Sh_2211_Zmumu_maxHTpTV2_BFilter[fIter->first]);
      Z->Add(Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto[fIter->first]);
      Z->Add(Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto[fIter->first]);
      Z->Add(Sh_2214_Ztautau_maxHTpTV2_BFilter[fIter->first]);
      Z->Add(Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto[fIter->first]);
      Z->Add(Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);
      
      V = (TH1F*)W->Clone();
      V->Add(Sh_2211_Zee_maxHTpTV2_BFilter[fIter->first]);
      //V->Add(Sh_2211_Zee_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Zee_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2211_Zmumu_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->Add(Sh_2214_Ztautau_maxHTpTV2_BFilter[fIter->first]);
      V->Add(Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto[fIter->first]);
      V->Add(Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);

      // tt_others
      tt_others = (TH1F*)aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW[fIter->first]->Clone();
      tt_others->Add(aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu[fIter->first]);
      tt_others->Add(aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq[fIter->first]);
      tt_others->Add(aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee[fIter->first]);
      tt_others->Add(aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu[fIter->first]);
      tt_others->Add(aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau[fIter->first]);
      tt_others->SetFillColor(kCyan);
      tt_others->SetLineWidth(0);
      
    }
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // main stack of MCs
    THStack* stack = new THStack();
   
    // statistical error histogram
    TH1F* histstack = new TH1F();
      
    // The order of the stack defines which samples will appear on top of each other

    if(option.find("HWWAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(V);
      stack->Add(diboson);
      stack->Add(Higgs);

      histstack = (TH1F*)ttbar->Clone();
      histstack->Add(diboson);
      histstack->Add(V);
      histstack->Add(stop);
      histstack->Add(Higgs);
    }

    if(option.find("ZTauTauAnalysis") != option.npos){
      stack->Add(topV);
      stack->Add(W);
      stack->Add(Z);
      stack->Add(Z_tautau);
      
      histstack = (TH1F*)topV->Clone();
      histstack->Add(W);
      histstack->Add(Z);
      histstack->Add(Z_tautau);
    }
    
    if(option.find("TTbarDilepAnalysis") != option.npos){
      stack->Add(diboson);
      stack->Add(V);
      stack->Add(tt_others);
      stack->Add(stop);
      stack->Add(ttbar);

      histstack = (TH1F*)ttbar->Clone();
      histstack->Add(stop);
      histstack->Add(diboson);
      histstack->Add(V);
      histstack->Add(tt_others);
    }

    // data overflow
    if(std::strstr((fIter->first).c_str(),"four_lep") == NULL ){
      if( abs(fIter->second->GetBinContent(fIter->second->GetNbinsX()+1)) > 0){
	fIter->second->AddBinContent(fIter->second->GetNbinsX(), fIter->second->GetBinContent(fIter->second->GetNbinsX()+1));
      }
    }
    /////////////////////////////////////////////////////////////////////////////
    // BEGIN PLOTTING //

    histstack->SetFillStyle(3454);
    histstack->SetFillColor(kBlue+2);
    histstack->SetLineColor(kBlack);
    histstack->SetLineWidth(2);
    histstack->SetMarkerSize(0);
    histstack->SetLineColor(kWhite);
    
    // obtain the statistical uncertainty
    float err;
    int nbin = histstack->GetNbinsX();
    for(int i_bin=0;i_bin<=nbin;i_bin++){
      err = histstack->GetBinError(i_bin);
      histstack->SetBinError(i_bin, err ); 
    }

    // calculate normalized signals
    TH1F* Higgs_normsig = new TH1F();
    
    if(option.find("HWWAnalysis") != option.npos){
      Higgs_normsig = (TH1F*)Higgs->Clone();
      Higgs_normsig->Scale(histstack->Integral()/Higgs_normsig->Integral());
      Higgs_normsig->SetLineColor(kRed);
      Higgs_normsig->SetFillStyle(0);
      Higgs_normsig->SetLineStyle(2);
      Higgs_normsig->SetFillColor(2);
      Higgs_normsig->SetLineWidth(2);
    }
    
    // set Yaxis maximum
    float yMaxScale = 2.0;
    //fIter->second->SetMaximum(yMaxScale*TMath::Max( TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()), Higgs_normsig->GetMaximum() ) );
    fIter->second->SetMaximum(yMaxScale*TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()));
        
    // latex options 
    TLatex l;
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.SetTextFont(42);
    l.SetTextSize(0.04);

    if(option.find("HWWAnalysis")     != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow WW* #rightarrow e#nu#mu#nu, N_{jet} #leq 1");}
    if(option.find("ZTauTauAnalysis")   != option.npos){l.DrawLatex(0.18,0.71,"Z #rightarrow #tau_{l}#tau_{h}");}
    if(option.find("TTbarDilepAnalysis")     != option.npos){l.DrawLatex(0.18,0.71,"t#bar{t} #rightarrow W^{-}W^{+}b#bar{b} #rightarrow e#nu #mu#nu b#bar{b}");}

    TLatex l2;
    l2.SetNDC();
    l2.SetTextSize(0.04);  
    l2.SetTextColor(kBlack);
    l2.DrawLatex(0.18,0.79, Form("#sqrt{s} = 13 TeV, 36 fb^{-1}")); 
    
    
    //create legend
    TLegend* leg;
    leg  = new TLegend();
    leg  = new TLegend(0.70,0.55,0.93,0.90);

    //0.7, 0.55, 0.85, 0.90
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(32);
    leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetMargin(0.22);
    leg->SetTextAlign(32);
    
    // fill legend depending on the analysis, the order reflects the stack order

    // ------------------------------------------------------- //
    
    if(option.find("HWWAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Higgs , "Higgs", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      if(NORMSIG) if(fIter->first.find("histI") != option.npos) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");
      
      if(YIELDS){
	cout << "Number of events:" << "Data: " << data[fIter->first]->Integral() << 
	  ",  Higgs: " << Higgs->Integral()  << 
	  ",  Diboson: " << diboson->Integral()  <<
	  ",  V+jets: " << V->Integral()  <<
	  ",  ttbar: " << ttbar ->Integral()  <<
	  ",  stop: " <<  stop->Integral()  <<
	  ",  Total pred.: "<< diboson->Integral() + V->Integral() + ttbar ->Integral() + stop->Integral() << 
	  endl;
      }
    }

    // ------------------------------------------------------- //    
    if(option.find("ZTauTauAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z_tautau,  "Z #rightarrow #tau#tau", "f");
      leg-> AddEntry(Z,  "Z #rightarrow ee, #mu#mu", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(topV , "Other", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      
      if(YIELDS){
	cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
	  ",  Z->tautau: " << Z_tautau->Integral()  <<             
	  ",  Z->ee,mumu: " << Z->Integral()  <<
	  ",  W+jets: " << W->Integral()  <<
	  ",  ttbar, single top, diboson: " <<  topV->Integral()  <<
	  ",  Total pred.: "<< Z->Integral() + Z_tautau->Integral() + W->Integral() + topV->Integral() <<
	  endl;
      }
    }
    
    // ------------------------------------------------------- //
    
    if(option.find("TTbarDilepAnalysis") != option.npos){
      leg->AddEntry(data[fIter->first] , "Data" ,"lep");
      leg->AddEntry(ttbar,  "t#bar{t}", "f");
      leg->AddEntry(stop, "Single top","f");
      leg->AddEntry(tt_others, "t#bar{t}V, t#bar{t}jj, t#bar{t}Vjj","f");
      leg->AddEntry(V, "V+jets","f");
      leg->AddEntry(diboson, "VV+jets","f");
      leg->AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
	cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
	  ",  ttbar: " << ttbar->Integral() <<
	  ",  single_top: " << stop->Integral() <<
	  ",  tt+others: " << tt_others->Integral() <<
	  ",  V+jets: " << V->Integral() <<
	  ",  diboson: " << diboson->Integral() <<
	  ",  Total pred.: "<< tt_others->Integral()+diboson->Integral()+V->Integral()+ttbar->Integral()+stop->Integral() << endl;
      }
    }
    
    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");

    // draw the normalised signal in the plots
    if(NORMSIG){
      //if(option.find("HZZAnalysis")          != option.npos){Higgs_normsig->Draw("HISTsame");}
      if(option.find("HWWAnalysis")          != option.npos){if(fIter->first.find("histI") != option.npos)Higgs_normsig->Draw("HISTsame");}
      //if(option.find("SingleTopAnalysis")    != option.npos){stop_normsig->Draw("HISTsame");}
      //if(option.find("SUSYAnalysis")         != option.npos){slep600DM300_normsig->Draw("HISTsame"); leg2->Draw("same");}
      //if(option.find("ZPrimeBoostedAnalysis")!= option.npos){if(fIter->first.find("LR") != option.npos) ZPrime_normsig->Draw("HISTsame"); }
    }
    
    leg->Draw("same");

    ATLASLabel(0.18, 0.87);
    

    ////////////////////////////////////////////////////////////////////////////////
    // lower pad contains the ratio of data to MC
    // for Hyy, it contains the rest of data and fit
    pad1->cd();
    pad1->GetFrame()->SetY1(2);
    pad1->Draw();

    // create the ratio plot  
    TH1F *h_ratio = (TH1F*)data[fIter->first]->Clone("h_ratio");

    if(! (option.find("HyyAnalysis") != option.npos) ){
      h_ratio->Divide((TH1F*)histstack->Clone());
      h_ratio->GetYaxis()->SetTitle("Data / Pred   ");
      //      h_ratio->GetYaxis()->SetTitle("Data / Pred      ");
    }
    
    // add a line in 1
    TLine *hline;
    hline = new TLine(h_ratio->GetXaxis()->GetXmin(),1,h_ratio->GetXaxis()->GetXmax(),1);
    hline->SetLineColor(kGray+2);
    hline->SetLineWidth(2);
    hline->SetLineStyle(1);

    gStyle->SetEndErrorSize(1.);
    h_ratio->GetYaxis()->CenterTitle();
    h_ratio->GetYaxis()->SetNdivisions(504,false);

    h_ratio->Draw("0E1");
    hline->Draw();

    // cosmetics
    h_ratio->SetMinimum(0);
    h_ratio->SetMaximum(2);

    h_ratio->GetXaxis()->SetTitle(  fIter->second->GetXaxis()->GetTitle()  );
    h_ratio->GetXaxis()->SetTitleSize(0.15);
    h_ratio->GetXaxis()->SetLabelSize(0.13);
    h_ratio->GetXaxis()->SetTitleOffset(1.2);
    h_ratio->GetYaxis()->SetTitleSize(0.12);
    h_ratio->GetYaxis()->SetTitleOffset(0.45);
    h_ratio->GetYaxis()->SetLabelSize(0.10);
    h_ratio->GetYaxis()->SetLabelOffset(0.01);
    h_ratio->GetXaxis()->SetLabelOffset(0.035);

    data[fIter->first]->GetXaxis()->SetLabelSize(0);
    gPad->RedrawAxis();
    pad1->cd();

    if( ! (option.find("HyyAnalysis") != option.npos)) pad1->cd()->SetGridy();
    
    h_ratio->Draw("SAME0E1");
    h_ratio->Draw("SAMEAXIS");
    h_ratio->GetYaxis()->Draw();
    h_ratio->Draw("SAME0E1");

    pad0->cd();
    TAxis * Ay1 = NULL;
    Ay1 = fIter->second->GetXaxis();
    Ay1->SetLabelSize(0);
    Ay1->SetTitleSize(0);


    ///////////////////////////////////////////////////////////////
    // Drawing options 

    if(option.find("TTbarDilepAnalysis") != option.npos){
      if(fIter->first.find("hist_lep_pt") != option.npos){
        pad0->SetLogy(1);
        fIter->second->SetMinimum(0.1);
        fIter->second->SetMaximum(100*TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()));
      }
      else{
	pad0->SetLogy(0);
      }
    }

    ////////////////////////////////////////////////////////
    gPad->RedrawAxis();
 
    // printing the canvas to a png (pdf...) file    
    PrintCanvas(c,fIter->first);
    
  }
  
  return;
}

///
void Plotting::PrintCanvas(TCanvas* c1, string title){
  
  string outFolder="histograms";
  std::string tpng = outFolder+"/"+title+".png";
  c1->SaveAs(tpng.c_str());
 
  if (SAVEPDF)
   { 
     std::string tpdf = outFolder+"/"+title+".pdf";
     c1->SaveAs(tpdf.c_str());
   }

  if (SAVEROOT)
   { 
     std::string troot = outFolder+"/"+title+".root";
     c1->SaveAs(troot.c_str());
   }

  return;
}

///
void Plotting::getHistoSettings(){

  // we check the naming of the 12 analyses
  if( option.find("ZPrimeBoostedAnalysis") != option.npos ||  option.find("SingleTopAnalysis") != option.npos || option.find("ZTauTauAnalysis") != option.npos ||  option.find("WBosonAnalysis") != option.npos ||  option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("HyyAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos || option.find("SUSYAnalysis") != option.npos  || option.find("TTbarDilepAnalysis") != option.npos ) cout << "Analysis option found, proceeding..." << endl;
  else { cout << "Analysis option not found! \n usage: ./plot [ WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, SingleTopAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, ZTauTauAnalysis, HyyAnalysis, SUSYAnalysis, ZPrimeBoostedAnalysis ]  [ location of OutputDir_AnalysisName ] \n " << endl; exit(1);}

 
  // save names of the histograms for later  
  hset.clear();
  
  // read in configuration file
  std::string ifile;

  if(option.find("HWWAnalysis")           != option.npos){ifile = "list_histos/HistoList_HWWAnalysis.txt";}
  if(option.find("ZTauTauAnalysis")       != option.npos){ifile = "list_histos/HistoList_ZTauTauAnalysis.txt";}
  if(option.find("TTbarDilepAnalysis")    != option.npos){ifile = "list_histos/HistoList_TTbarDilepAnalysis.txt";}

  std::cout << "Reading list of histograms from: " << ifile.c_str() << " \n " << std::endl;

  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("#") != line.npos )continue; // a # is a comment and not read
    std::string n;
    istringstream linestream(line);
    getline(linestream, n, '\n');
    HistoHandler* h = new HistoHandler(n);
    hset.push_back(h); 
  }
  return;
}

///
HistoHandler::HistoHandler(){
}

///
HistoHandler:: HistoHandler(std::string name){
  _name = name;
}

///
HistoHandler::~HistoHandler(){
}

///
std::string HistoHandler::GetName(){
  return _name;
}
///////////////////////////////////////////////////////
