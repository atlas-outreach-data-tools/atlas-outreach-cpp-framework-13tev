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
    TH1F* ttbar_dilep = new TH1F();
    TH1F* single_top = new TH1F();
    TH1F* diboson = new TH1F();
    TH1F* v_plus_jets = new TH1F();
   
    // Special
    TH1F* Higgs = new TH1F();
    TH1F* tt_others = new TH1F();

    // ttbar
    //ttbar_dilep = (TH1F*)PhPy8EG_A14_ttbar_hdamp258p75_dil[fIter->first]->Clone();
    ttbar_dilep = (TH1F*)PhPy8EG_A14_ttbar_hdamp258p75_nonallhad[fIter->first]->Clone();
    ttbar_dilep->SetFillColor(kOrange-3);
    ttbar_dilep->SetLineWidth(0);
    
    // Single top
    /*
    single_top = (TH1F*)PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top[fIter->first]->Clone();
    single_top->Add(PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop[fIter->first]);
    single_top->Add(PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top[fIter->first]);
    single_top->Add(PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop[fIter->first]);
    */
    //single_top->Add(PhPy8EG_A14_tchan_BW50_lept_top[fIter->first]);
    single_top = (TH1F*)PhPy8EG_A14_tchan_BW50_lept_top[fIter->first]->Clone();
    single_top->Add(PhPy8EG_A14_tchan_BW50_lept_antitop[fIter->first]);
    single_top->SetFillColor(kAzure+8);
    single_top->SetLineWidth(0);
    
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
    v_plus_jets = (TH1F*)Sh_2211_Zee_maxHTpTV2_BFilter[fIter->first]->Clone();
    //v_plus_jets->Add(Sh_2211_Zee_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Zee_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Zmumu_maxHTpTV2_BFilter[fIter->first]);
    v_plus_jets->Add(Sh_2211_Zmumu_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wenu_maxHTpTV2_BFilter[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wenu_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wenu_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wmunu_maxHTpTV2_BFilter[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wmunu_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wmunu_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wtaunu_L_maxHTpTV2_BFilter[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wtaunu_L_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wtaunu_H_maxHTpTV2_BFilter[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2211_Wtaunu_H_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2214_Ztautau_maxHTpTV2_BFilter[fIter->first]);
    v_plus_jets->Add(Sh_2214_Ztautau_maxHTpTV2_CFilterBVeto[fIter->first]);
    v_plus_jets->Add(Sh_2214_Ztautau_maxHTpTV2_CVetoBVeto[fIter->first]);
    v_plus_jets->SetFillColor(kGreen-3);
    v_plus_jets->SetLineWidth(0);
    
    // merge for HWWAnalysis
    if(option.find("HWWAnalysis") != option.npos){

      // Higgs
      Higgs = (TH1F*)PowhegPythia8EvtGen_NNLOPS_NN30_ggH125_WWlvlv_EF_15_5[fIter->first]->Clone();
      Higgs->Add(PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_WWlvlv[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);
      
    }
    
    // merge for TTbarDilepAnalysis
    if(option.find("TTbarDilepAnalysis") != option.npos){

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
      stack->Add(single_top);
      stack->Add(ttbar_dilep);
      stack->Add(v_plus_jets);
      stack->Add(diboson);
      stack->Add(Higgs);
      
      histstack = (TH1F*)ttbar_dilep->Clone();
      histstack->Add(single_top);
      histstack->Add(diboson);
      histstack->Add(v_plus_jets);
      histstack->Add(Higgs);
    }
	
    if(option.find("TTbarDilepAnalysis") != option.npos){
      stack->Add(diboson);
      stack->Add(v_plus_jets);
      stack->Add(tt_others);
      stack->Add(single_top);
      stack->Add(ttbar_dilep);

      histstack = (TH1F*)ttbar_dilep->Clone();
      histstack->Add(single_top);
      histstack->Add(diboson);
      histstack->Add(v_plus_jets);
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
      leg->AddEntry(data[fIter->first] , "Data" ,"lep");
      leg->AddEntry(Higgs , "Higgs", "f");
      leg->AddEntry(diboson , "Diboson", "f");
      leg->AddEntry(v_plus_jets,  "V+jets", "f");
      leg->AddEntry(ttbar_dilep, "t#bar{t}", "f");
      leg->AddEntry(single_top, "Single top", "f");
      leg->AddEntry(histstack,"Stat. unc.","f");
      
      //if(NORMSIG) if(fIter->first.find("histI") != option.npos) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");
      
      if(YIELDS){
	cout << "Number of events:" << "Data: " << data[fIter->first]->Integral() << 
	  ",  Higgs: " << Higgs->Integral()  << 
	  ",  Diboson: " << diboson->Integral()  <<
	  ",  V+jets: " << v_plus_jets->Integral()  <<
	  ",  ttbar: " << ttbar_dilep ->Integral()  <<
	  ",  stop: " <<  single_top->Integral()  <<
	  ",  Total pred.: "<< Higgs->Integral()+diboson->Integral()+v_plus_jets->Integral()+ttbar_dilep->Integral()+single_top->Integral() << endl;
      }
    }
    
    if(option.find("TTbarDilepAnalysis") != option.npos){
      leg->AddEntry(data[fIter->first] , "Data" ,"lep");
      leg->AddEntry(ttbar_dilep,  "t#bar{t}", "f");
      leg->AddEntry(single_top, "Single top","f");
      leg->AddEntry(tt_others, "t#bar{t}V, t#bar{t}jj, t#bar{t}Vjj","f");
      leg->AddEntry(v_plus_jets, "V+jets","f");
      leg->AddEntry(diboson, "VV+jets","f");
      leg->AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
	cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
	  ",  ttbar: " << ttbar_dilep->Integral() <<
	  ",  single_top: " << single_top->Integral() <<
	  ",  tt+others: " << tt_others->Integral() <<
	  ",  V+jets: " << v_plus_jets->Integral() <<
	  ",  diboson: " << diboson->Integral() <<
	  ",  Total pred.: "<< tt_others->Integral()+diboson->Integral()+v_plus_jets->Integral()+ttbar_dilep->Integral()+single_top->Integral() << endl;
      }
    }
    
    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");
    
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
