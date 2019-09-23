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
#define NORMSIG 1

// save to pdf flag, by default plots saved as png
#define SAVEPDF 1


//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  
  if(argc < 3){
    std::cout<<"usage: ./plot [WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, SingleTopAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, ZTauTauAnalysis, HyyAnalysis, SUSYAnalysis, ZPrimeBoostedAnalysis]  [location of OutputDir_AnalysisName]"<<std::endl;
    std::cout<<"output stored in a directory \'histograms\' " <<std::endl;
    exit(1);
  }
  
  Plotting* m = new Plotting();
  
  m->SetLumi(10064); // luminosity set by hand to 10fb-1
  m->SetOption(argv[1]);
  m->SetInputLocation(argv[2]);
  
  string option = argv[1];
  if( option.find("ZPrimeBoostedAnalysis") != option.npos ||  option.find("SingleTopAnalysis") != option.npos || option.find("ZTauTauAnalysis") != option.npos ||  option.find("WBosonAnalysis") != option.npos ||  option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("HyyAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos || option.find("SUSYAnalysis") != option.npos) cout << "Analysis option found, proceeding..." << endl;
  else { cout << "Analysis option not found! \n usage: ./plot [WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, SingleTopAnalysis, HyyAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, SUSYAnalysis, ZPrimeBoostedAnalysis]  [location of OutputDir_AnalysisName] \n " << endl; exit(1);}
 

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
  l.SetTextFont(72);
  l.SetTextColor(kBlack);
  l.SetTextSize(0.06);  
  double delx = 0.16;
  l.DrawLatex(x,y,"ATLAS");
  TLatex p; 
  p.SetNDC();
  p.SetTextFont(42);
  p.SetTextColor(kBlack);
  p.SetTextSize(0.06);  
  p.DrawLatex(x+delx,y,"Open Data");

  return;
}

///
void Plotting::WhichFiles(){
  // read input file with the names of the samples
  std::string ifile = "Files_base.txt";

  //options
  if(option.find("WBosonAnalysis") != option.npos || option.find("SingleTopAnalysis") != option.npos){   ifile = "Files_WBoson.txt";}
  if(option.find("ZPrimeBoostedAnalysis") != option.npos){   ifile = "Files_ZPrime.txt";}

//  if(option.find("HZZAnalysis") != option.npos){   ifile = "Files_HZZ.txt";}
//  if(option.find("HWWAnalysis") != option.npos){   ifile = "Files_HWW.txt";}
//  if(option.find("ZTauTauAnalysis") != option.npos){   ifile = "Files_ZTauTau.txt";}
//  if(option.find("SUSYAnalysis") != option.npos){   ifile = "Files_SUSY.txt";}



  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("###") != line.npos )continue;
    std::string name, xsec, sumw, eff;
    istringstream linestream(line);
    getline(linestream, name, '|');
    getline(linestream, xsec, '|');
    getline(linestream, sumw, '|');
    getline(linestream, eff);
    if (DEBUG) cout << name << " " << xsec << " " << sumw << " " << eff << endl;
    float sumw_eff = atof(sumw.c_str()) * atof(eff.c_str());
    SF[name] = std::make_pair(atof(xsec.c_str()), sumw_eff);    
    
  }
  return;
}

///
void Plotting::readFiles(){
  std::cout << "\n Reading files from: " << readname << " \n " << std::endl;
  
  // THIS IS THE DIRECTORY FROM WHERE HISTOS ARE TAKEN
  if (option.find("WBosonAnalysis") != option.npos){
    std::cout<<"=====processing WBosonAnalysis====="<<std::endl;
  }
  if (option.find("ZBosonAnalysis") != option.npos){
    std::cout<<"=====processing ZBosonAnalysis====="<<std::endl;
  }
  if (option.find("TTbarAnalysis") != option.npos){
    std::cout<<"=====processing TTbarAnalysis====="<<std::endl;
  }
  if (option.find("SingleTopAnalysis") != option.npos){
    std::cout<<"=====processing SingleTopAnalysis====="<<std::endl;
  }
  if (option.find("HyyAnalysis") != option.npos){
    std::cout<<"=====processing HyyAnalysis====="<<std::endl;
  }
  if (option.find("WZDiBosonAnalysis") != option.npos){
    std::cout<<"=====processing WZDiBosonAnalysis====="<<std::endl;
  }
  if (option.find("ZZDiBosonAnalysis") != option.npos){
    std::cout<<"=====processing ZZDiBosonAnalysis====="<<std::endl;
  }
  if (option.find("HWWAnalysis") != option.npos){
    std::cout<<"=====processing HWWAnalysis====="<<std::endl;
  }
  if (option.find("HZZAnalysis") != option.npos){
    std::cout<<"=====processing HZZAnalysis====="<<std::endl;
  }
  if (option.find("ZTauTauAnalysis") != option.npos){
    std::cout<<"=====processing ZTauTauAnalysis====="<<std::endl;
  }
  if (option.find("SUSYAnalysis") != option.npos){
    std::cout<<"=====processing SUSYAnalysis====="<<std::endl;
  }
  if (option.find("ZPrimeBoostedAnalysis") != option.npos){
    std::cout<<"=====processing ZPrimeBoostedAnalysis====="<<std::endl;
  }


  std::map<std::string,std::pair<double,double> >::const_iterator SFiter;
  for(SFiter = SF.begin(); SFiter != SF.end(); SFiter++){
    std::string readme = readname + "/" + SFiter->first + ".root";
    if (DEBUG)  std::cout << "Reading file: " << readme << std::endl;
    TFile* file  = TFile::Open(readme.c_str(), "READ");
    
    createHistoSet(file, SFiter->first);
    
    // apply Scale Factors: scaling is done by calculating the luminosity of the sample via xsec/(sumw*red_eff) and  multiplying the target luminosity
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
	  if (DEBUG) std::cout<<"Scaling histogram: "<< fIter->first << " by a factor of: " << scf << std::endl;
	  fIter->second->Scale(scf);
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

 
  padX = new TPad("pad1","pad1",0.07, 0.27, 0.135, 0.29, 0, 0, 0);
  padX->SetTickx(false);
  padX->SetTicky(false);
  padX->SetTopMargin(0.0);
  padX->SetBottomMargin(0.5);
  padX->SetLeftMargin(0.14);
  padX->SetRightMargin(0.05);
  padX->SetFrameBorderMode(0);

  pad1->Draw();
  pad0->Draw();
  padX->Draw();

  pad0->cd();
  
  ///////////////////////////////////////////////////////////////////////
  
  //data
  std::map<std::string,TH1F*> data; 
  
  //Higgs to WW
  std::map<std::string,TH1F*> ggH125_WW2lep;
  std::map<std::string,TH1F*> VBFH125_WW2lep;

  //Higgs to ZZ
  std::map<std::string,TH1F*>  ggH125_ZZ4lep;
  std::map<std::string,TH1F*>  ZH125_ZZ4lep;
  std::map<std::string,TH1F*>  WH125_ZZ4lep;
  std::map<std::string,TH1F*>  VBFH125_ZZ4lep;

  // SUSY sample
  std::map<std::string,TH1F*> slep600DM300;

  // Zprime with Z'(1 TeV)->tt sample
  std::map<std::string,TH1F*> ZPrime1000;

  //ttbar
  std::map<std::string,TH1F*> ttbar_lep;   
  
  // Z boson inclusive Powheg samples
  std::map<std::string,TH1F*> Zee;
  std::map<std::string,TH1F*> Zmumu;
  std::map<std::string,TH1F*> Ztautau;
  
  
  // diboson Powheg, remove them later
  std::map<std::string,TH1F*> WWlvlv;
  std::map<std::string,TH1F*> WWlvqq;
  
  std::map<std::string,TH1F*> ZZllll;
  std::map<std::string,TH1F*> ZZvvll;
  std::map<std::string,TH1F*> ZZqqll;
  
  std::map<std::string,TH1F*> WZlvll;
  std::map<std::string,TH1F*> WZlvvv;
  std::map<std::string,TH1F*> WZqqll;
  std::map<std::string,TH1F*> WZlvqq;
  
  
  //diboson Sherpa 
  std::map<std::string,TH1F*>  WlvZqq; 
  std::map<std::string,TH1F*>  WplvWmqq; 
  std::map<std::string,TH1F*>  WpqqWmlv; 
  std::map<std::string,TH1F*>  ZqqZll; 
  std::map<std::string,TH1F*>  WqqZll; 
  std::map<std::string,TH1F*>  llll;
  std::map<std::string,TH1F*>  lllv;
  std::map<std::string,TH1F*>  llvv;
  std::map<std::string,TH1F*>  lvvv;
  
  
  //W+jets
  std::map<std::string,TH1F*> Wplusenu;
  std::map<std::string,TH1F*> Wplusmunu;
  std::map<std::string,TH1F*> Wplustaunu;
  std::map<std::string,TH1F*> Wminusenu;
  std::map<std::string,TH1F*> Wminusmunu;
  std::map<std::string,TH1F*> Wminustaunu;
  
  
  std::map<std::string,TH1F*> single_top_tchan;
  std::map<std::string,TH1F*> single_antitop_tchan;
  std::map<std::string,TH1F*> single_top_wtchan;
  std::map<std::string,TH1F*> single_antitop_wtchan;
  std::map<std::string,TH1F*> single_top_schan;
  std::map<std::string,TH1F*> single_antitop_schan;
  
 
  // sliced V+jets samples
  std::map<std::string,TH1F*>  Wenu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Wenu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Wenu_PTV1000; std::map<std::string,TH1F*>  Wenu_PTV140_280_BFilter; std::map<std::string,TH1F*>  Wenu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Wenu_PTV280_500_BFilter; std::map<std::string,TH1F*>  Wenu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*> Wenu_PTV500_1000; std::map<std::string,TH1F*>  Wenu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Wenu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Wmunu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*> Wmunu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV1000; std::map<std::string,TH1F*>  Wmunu_PTV140_280_BFilter; std::map<std::string,TH1F*>  Wmunu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Wmunu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV280_500_BFilter; std::map<std::string,TH1F*> Wmunu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Wmunu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV500_1000; std::map<std::string,TH1F*>  Wmunu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Wmunu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*> Wmunu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Wtaunu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV1000; std::map<std::string,TH1F*>  Wtaunu_PTV140_280_BFilter; std::map<std::string,TH1F*> Wtaunu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV280_500_BFilter; std::map<std::string,TH1F*>  Wtaunu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*> Wtaunu_PTV500_1000; std::map<std::string,TH1F*>  Wtaunu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Wtaunu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Zee0_70_BFilter; std::map<std::string,TH1F*>  Zee0_70_CFilterBVeto; std::map<std::string,TH1F*> Zee0_70_CVetoBVeto; std::map<std::string,TH1F*>  Zee1000; std::map<std::string,TH1F*>  Zee140_280_BFilter; std::map<std::string,TH1F*>  Zee140_280_CFilterBVeto; std::map<std::string,TH1F*>  Zee140_280_CVetoBVeto; std::map<std::string,TH1F*>  Zee280_500_BFilter; std::map<std::string,TH1F*> Zee280_500_CFilterBVeto; std::map<std::string,TH1F*>  Zee280_500_CVetoBVeto; std::map<std::string,TH1F*>  Zee500_1000; std::map<std::string,TH1F*>  Zee70_140_BFilter; std::map<std::string,TH1F*>  Zee70_140_CFilterBVeto; std::map<std::string,TH1F*> Zee70_140_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu0_70_BFilter; std::map<std::string,TH1F*>  Zmumu0_70_CFilterBVeto; std::map<std::string,TH1F*>  Zmumu0_70_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu1000; std::map<std::string,TH1F*>  Zmumu140_280_BFilter; std::map<std::string,TH1F*> Zmumu140_280_CFilterBVeto; std::map<std::string,TH1F*>  Zmumu140_280_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu280_500_BFilter; std::map<std::string,TH1F*>  Zmumu280_500_CFilterBVeto; std::map<std::string,TH1F*> Zmumu280_500_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu500_1000; std::map<std::string,TH1F*>  Zmumu70_140_BFilter; std::map<std::string,TH1F*>  Zmumu70_140_CFilterBVeto; std::map<std::string,TH1F*>  Zmumu70_140_CVetoBVeto; std::map<std::string,TH1F*> Ztautau0_70_BFilter; std::map<std::string,TH1F*>  Ztautau0_70_CFilterBVeto; std::map<std::string,TH1F*>  Ztautau0_70_CVetoBVeto; std::map<std::string,TH1F*>  Ztautau1000; std::map<std::string,TH1F*>  Ztautau140_280_BFilter; std::map<std::string,TH1F*> Ztautau140_280_CFilterBVeto; std::map<std::string,TH1F*>  Ztautau140_280_CVetoBVeto; std::map<std::string,TH1F*>  Ztautau280_500_BFilter; std::map<std::string,TH1F*>  Ztautau280_500_CFilterBVeto; std::map<std::string,TH1F*> Ztautau280_500_CVetoBVeto; std::map<std::string,TH1F*>  Ztautau500_1000; std::map<std::string,TH1F*>  Ztautau70_140_BFilter; std::map<std::string,TH1F*>  Ztautau70_140_CFilterBVeto; std::map<std::string,TH1F*>  Ztautau70_140_CVetoBVeto;
  
  
  
  
  // naming of the histos, must be the same as in Files.txt, and follow previous lines
  data = histo["data"];
  
  if(option.find("HZZAnalysis") != option.npos){
    ggH125_ZZ4lep = histo["ggH125_ZZ4lep"];
    ZH125_ZZ4lep  = histo["ZH125_ZZ4lep"];
    WH125_ZZ4lep= histo["WH125_ZZ4lep"];
    VBFH125_ZZ4lep= histo["VBFH125_ZZ4lep"];
  }
  
  
  if(option.find("HWWAnalysis") != option.npos){
    ggH125_WW2lep = histo["ggH125_WW2lep"];
    VBFH125_WW2lep = histo["VBFH125_WW2lep"];
  }
  
  // reading ttbar sample
  ttbar_lep = histo["ttbar_lep"];
  
  // reading Z Powheg samples, used in WBoson, TTbar, Zprime 
  if( option.find("ZPrimeBoostedAnalysis") != option.npos || option.find("WBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("SingleTopAnalysis") != option.npos )
    {
      Zee = histo["Zee"];
      Zmumu = histo["Zmumu"];
      Ztautau = histo["Ztautau"];
    }
  
  // inclusive Powheg W+jets samples are used for all the analyses but SingleTop, ZTaTau, WBoson, SUSY 
  if( option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos) 
    {
      Wplusenu = histo["Wplusenu"];
      Wplusmunu= histo["Wplusmunu"];
      Wplustaunu= histo["Wplustaunu"];  
      Wminusenu= histo["Wminusenu"];
      Wminusmunu= histo["Wminusmunu"];
      Wminustaunu= histo["Wminustaunu"];
    }
  
  // slices Sherpa W+jets samples
  if( option.find("ZPrimeBoostedAnalysis") != option.npos || option.find("SingleTopAnalysis") != option.npos || option.find("ZTauTauAnalysis") != option.npos ||   option.find("WBosonAnalysis") != option.npos ||   option.find("SUSYAnalysis") != option.npos)
    {
      
      Wenu_PTV0_70_BFilter = histo["Wenu_PTV0_70_BFilter"];
      Wenu_PTV0_70_CFilterBVeto = histo["Wenu_PTV0_70_CFilterBVeto"];
      Wenu_PTV0_70_CVetoBVeto = histo["Wenu_PTV0_70_CVetoBVeto"];
      Wenu_PTV1000 = histo["Wenu_PTV1000"];
      Wenu_PTV140_280_BFilter = histo["Wenu_PTV140_280_BFilter"];
      Wenu_PTV140_280_CFilterBVeto = histo["Wenu_PTV140_280_CFilterBVeto"];
      Wenu_PTV140_280_CVetoBVeto = histo["Wenu_PTV140_280_CVetoBVeto"];
      Wenu_PTV280_500_BFilter = histo["Wenu_PTV280_500_BFilter"];
      Wenu_PTV280_500_CFilterBVeto = histo["Wenu_PTV280_500_CFilterBVeto"];
      Wenu_PTV280_500_CVetoBVeto = histo["Wenu_PTV280_500_CVetoBVeto"];
      Wenu_PTV500_1000 = histo["Wenu_PTV500_1000"];
      Wenu_PTV70_140_BFilter = histo["Wenu_PTV70_140_BFilter"];
      Wenu_PTV70_140_CFilterBVeto = histo["Wenu_PTV70_140_CFilterBVeto"];
      Wenu_PTV70_140_CVetoBVeto = histo["Wenu_PTV70_140_CVetoBVeto"];
      Wmunu_PTV0_70_BFilter = histo["Wmunu_PTV0_70_BFilter"];
      Wmunu_PTV0_70_CFilterBVeto = histo["Wmunu_PTV0_70_CFilterBVeto"];
      Wmunu_PTV0_70_CVetoBVeto = histo["Wmunu_PTV0_70_CVetoBVeto"];
      Wmunu_PTV1000 = histo["Wmunu_PTV1000"];
      Wmunu_PTV140_280_BFilter = histo["Wmunu_PTV140_280_BFilter"];
      Wmunu_PTV140_280_CFilterBVeto = histo["Wmunu_PTV140_280_CFilterBVeto"];
      Wmunu_PTV140_280_CVetoBVeto = histo["Wmunu_PTV140_280_CVetoBVeto"];
      Wmunu_PTV280_500_BFilter = histo["Wmunu_PTV280_500_BFilter"];
      Wmunu_PTV280_500_CFilterBVeto = histo["Wmunu_PTV280_500_CFilterBVeto"];
      Wmunu_PTV280_500_CVetoBVeto = histo["Wmunu_PTV280_500_CVetoBVeto"];
      Wmunu_PTV500_1000 = histo["Wmunu_PTV500_1000"];
      Wmunu_PTV70_140_BFilter = histo["Wmunu_PTV70_140_BFilter"];
      Wmunu_PTV70_140_CFilterBVeto = histo["Wmunu_PTV70_140_CFilterBVeto"];
      Wmunu_PTV70_140_CVetoBVeto = histo["Wmunu_PTV70_140_CVetoBVeto"];
      Wtaunu_PTV0_70_BFilter = histo["Wtaunu_PTV0_70_BFilter"];
      Wtaunu_PTV0_70_CFilterBVeto = histo["Wtaunu_PTV0_70_CFilterBVeto"];
      Wtaunu_PTV0_70_CVetoBVeto = histo["Wtaunu_PTV0_70_CVetoBVeto"];
      Wtaunu_PTV1000 = histo["Wtaunu_PTV1000"];
      Wtaunu_PTV140_280_BFilter = histo["Wtaunu_PTV140_280_BFilter"];
      Wtaunu_PTV140_280_CFilterBVeto = histo["Wtaunu_PTV140_280_CFilterBVeto"];
      Wtaunu_PTV140_280_CVetoBVeto = histo["Wtaunu_PTV140_280_CVetoBVeto"];
      Wtaunu_PTV280_500_BFilter = histo["Wtaunu_PTV280_500_BFilter"];
      Wtaunu_PTV280_500_CFilterBVeto = histo["Wtaunu_PTV280_500_CFilterBVeto"];
      Wtaunu_PTV280_500_CVetoBVeto = histo["Wtaunu_PTV280_500_CVetoBVeto"];
      Wtaunu_PTV500_1000 = histo["Wtaunu_PTV500_1000"];
      Wtaunu_PTV70_140_BFilter = histo["Wtaunu_PTV70_140_BFilter"];
      Wtaunu_PTV70_140_CFilterBVeto = histo["Wtaunu_PTV70_140_CFilterBVeto"];
      Wtaunu_PTV70_140_CVetoBVeto = histo["Wtaunu_PTV70_140_CVetoBVeto"];
    }
  
  // slices Sherpa Z+jets samples are used for ZTaTau analyses
  if(option.find("ZTauTauAnalysis") != option.npos ||   option.find("SUSYAnalysis") != option.npos )
    {
      Zee0_70_BFilter = histo["Zee0_70_BFilter"];
      Zee0_70_CFilterBVeto = histo["Zee0_70_CFilterBVeto"];
      Zee0_70_CVetoBVeto = histo["Zee0_70_CVetoBVeto"];
      Zee1000 = histo["Zee1000"];
      Zee140_280_BFilter = histo["Zee140_280_BFilter"];
      Zee140_280_CFilterBVeto = histo["Zee140_280_CFilterBVeto"];
      Zee140_280_CVetoBVeto = histo["Zee140_280_CVetoBVeto"];
      Zee280_500_BFilter = histo["Zee280_500_BFilter"];
      Zee280_500_CFilterBVeto = histo["Zee280_500_CFilterBVeto"];
      Zee280_500_CVetoBVeto = histo["Zee280_500_CVetoBVeto"];
      Zee500_1000 = histo["Zee500_1000"];
      Zee70_140_BFilter = histo["Zee70_140_BFilter"];
      Zee70_140_CFilterBVeto = histo["Zee70_140_CFilterBVeto"];
      Zee70_140_CVetoBVeto = histo["Zee70_140_CVetoBVeto"];
      Zmumu0_70_BFilter = histo["Zmumu0_70_BFilter"];
      Zmumu0_70_CFilterBVeto = histo["Zmumu0_70_CFilterBVeto"];
      Zmumu0_70_CVetoBVeto = histo["Zmumu0_70_CVetoBVeto"];
      Zmumu1000 = histo["Zmumu1000"];
      Zmumu140_280_BFilter = histo["Zmumu140_280_BFilter"];
      Zmumu140_280_CFilterBVeto = histo["Zmumu140_280_CFilterBVeto"];
      Zmumu140_280_CVetoBVeto = histo["Zmumu140_280_CVetoBVeto"];
      Zmumu280_500_BFilter = histo["Zmumu280_500_BFilter"];
      Zmumu280_500_CFilterBVeto = histo["Zmumu280_500_CFilterBVeto"];
      Zmumu280_500_CVetoBVeto = histo["Zmumu280_500_CVetoBVeto"];
      Zmumu500_1000 = histo["Zmumu500_1000"];
      Zmumu70_140_BFilter = histo["Zmumu70_140_BFilter"];
      Zmumu70_140_CFilterBVeto = histo["Zmumu70_140_CFilterBVeto"];
      Zmumu70_140_CVetoBVeto = histo["Zmumu70_140_CVetoBVeto"];
      Ztautau0_70_BFilter = histo["Ztautau0_70_BFilter"];
      Ztautau0_70_CFilterBVeto = histo["Ztautau0_70_CFilterBVeto"];
      Ztautau0_70_CVetoBVeto = histo["Ztautau0_70_CVetoBVeto"];
      Ztautau1000 = histo["Ztautau1000"];
      Ztautau140_280_BFilter = histo["Ztautau140_280_BFilter"];
      Ztautau140_280_CFilterBVeto = histo["Ztautau140_280_CFilterBVeto"];
      Ztautau140_280_CVetoBVeto = histo["Ztautau140_280_CVetoBVeto"];
      Ztautau280_500_BFilter = histo["Ztautau280_500_BFilter"];
      Ztautau280_500_CFilterBVeto = histo["Ztautau280_500_CFilterBVeto"];
      Ztautau280_500_CVetoBVeto = histo["Ztautau280_500_CVetoBVeto"];
      Ztautau500_1000 = histo["Ztautau500_1000"];
      Ztautau70_140_BFilter = histo["Ztautau70_140_BFilter"];
      Ztautau70_140_CFilterBVeto = histo["Ztautau70_140_CFilterBVeto"];
      Ztautau70_140_CVetoBVeto = histo["Ztautau70_140_CVetoBVeto"];
    }
  
  
  // reading diboson samples
  WlvZqq= histo["WlvZqq"];
  WplvWmqq= histo["WplvWmqq"];
  WpqqWmlv= histo["WpqqWmlv"];
  ZqqZll= histo["ZqqZll"];
  WqqZll= histo["WqqZll"];
  llll= histo["llll"];
  lllv= histo["lllv"];
  llvv= histo["llvv"];
  lvvv= histo["lvvv"];
  
  
  if( option.find("SUSYAnalysis") != option.npos )
    {
      slep600DM300 = histo["slep600DM300"];
    }
 
  if(option.find("ZPrimeBoostedAnalysis") != option.npos){
      ZPrime1000 = histo["ZPrime1000_tt"];
  }
  
  // reading single top samples
  single_top_tchan= histo["single_top_tchan"];
  single_antitop_tchan= histo["single_antitop_tchan"];
  single_top_wtchan= histo["single_top_wtchan"];
  single_antitop_wtchan= histo["single_antitop_wtchan"];
  single_top_schan= histo["single_top_schan"];
  single_antitop_schan= histo["single_antitop_schan"];  
  

  ///////////////////////////////////////////////////////////////////////
  //begin plotting
  
  std::map<std::string,TH1F*>::const_iterator fIter;
  std::map<std::string,TH1F*>::const_iterator lIter;
  fIter = data.begin(); lIter = data.end();
  for(; fIter != lIter; ++fIter){
    
    std::cout<<"Plotting histogram: "<< fIter->first << std::endl;
    
    // data style
    fIter->second->SetMarkerStyle(20);
    fIter->second->SetMarkerColor(kBlack);
    fIter->second->SetMarkerSize(1.2);
    fIter->second->SetLineWidth(2);
    fIter->second->SetMinimum(0.1);
    fIter->second->Draw("E1");
    gStyle->SetEndErrorSize(1.); 
    TGaxis::SetMaxDigits(4);
    fIter->second->GetYaxis()->SetTitleOffset(1.2);
    //fIter->second->Rebin(2);
    
    // create histograms and merge several MCs into them
    
    TH1F* diboson = new TH1F();
    TH1F* W = new TH1F();
    TH1F* Z = new TH1F();
    TH1F* ttbar = new TH1F();
    TH1F* stop = new TH1F();
    TH1F* V = new TH1F();
    TH1F* W_Z = new TH1F();
    TH1F* Z_Z = new TH1F();
    TH1F* Higgs = new TH1F();
    
    TH1F* Z_ee = new TH1F();
    TH1F* Z_mumu = new TH1F();
    TH1F* Z_tautau = new TH1F();

    TH1F* stop_tq = new TH1F();
    TH1F* stop_tWtb = new TH1F();
    TH1F* ZVV = new TH1F();

    TH1F* ZPrime = new TH1F();
    
    // merge for W _Analysis
    if( option.find("WBosonAnalysis") != option.npos || 
        option.find("SingleTopAnalysis") != option.npos || 
	option.find("ZPrimeBoostedAnalysis") != option.npos )
    {
      
      // diboson samples 
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
	      if( !(fIter->first.find("leadLR") != option.npos )) ttbar->Scale(0.93); //change by hand the normalisation depending on large-R jets
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
      ZVV->Add(WpqqWmlv[fIter->first]);
      ZVV->Add(ZqqZll[fIter->first]);
      ZVV->Add(WqqZll[fIter->first]);
      ZVV->Add(llll[fIter->first]);
      ZVV->Add(lllv[fIter->first]);
      ZVV->Add(llvv[fIter->first]);
      ZVV->Add(lvvv[fIter->first]);
      ZVV->SetFillColor(kPink+9);
      ZVV->SetLineWidth(0);


    }
    
    
    // merge for Z _Analysis
    if(option.find("ZBosonAnalysis") != option.npos){
  	   

      diboson = (TH1F*)WWlvlv[fIter->first]->Clone();
      diboson->Add(WWlvqq[fIter->first]);
      diboson->Add(WZlvll[fIter->first]);
      diboson->Add(WZlvvv[fIter->first]);
      diboson->Add(WZqqll[fIter->first]);
      diboson->Add(WZlvqq[fIter->first]);
      diboson->Add(ZZqqll[fIter->first]); 
      diboson->Add(ZZllll[fIter->first]);
      diboson->Add(ZZvvll[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
      
      W = (TH1F*)Wplusenu[fIter->first]->Clone();
      W->Add(Wplusmunu[fIter->first]);
      W->Add(Wplustaunu[fIter->first]);
      W->Add(Wminusenu[fIter->first]);
      W->Add(Wminusmunu[fIter->first]);
      W->Add(Wminustaunu[fIter->first]);
      W->SetFillColor(kGreen-3);
      W->SetLineWidth(0);
    
      Z = (TH1F*)Zmumu[fIter->first]->Clone();
      Z->Add(Ztautau[fIter->first]);
      Z->Add(Zee[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);

      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);

      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

    }

    // merge for ZZ_Analysis
    if(option.find("ZZDiBosonAnalysis") != option.npos){
	    
      V = (TH1F*)Wplusenu[fIter->first]->Clone();
      V->Add(Wplusmunu[fIter->first]);
      V->Add(Wplustaunu[fIter->first]);
      V->Add(Wminusenu[fIter->first]);
      V->Add(Wminusmunu[fIter->first]);
      V->Add(Wminustaunu[fIter->first]);
      V->Add(Ztautau[fIter->first]);
      V->Add(Zee[fIter->first]);
      V->Add(Zmumu[fIter->first]);
      V->Add(single_top_schan[fIter->first]);
      V->Add(single_antitop_schan[fIter->first]);
      V->Add(single_top_tchan[fIter->first]);
      V->Add(single_antitop_tchan[fIter->first]);
      V->Add(single_top_wtchan[fIter->first]);
      V->Add(single_antitop_wtchan[fIter->first]);
      V->Add(ttbar_lep[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);
   
      diboson = (TH1F*)WWlvlv[fIter->first]->Clone();
      diboson->Add(WWlvqq[fIter->first]);
      diboson->Add(WZlvll[fIter->first]);
      diboson->Add(WZlvvv[fIter->first]);
      diboson->Add(WZqqll[fIter->first]);
      diboson->Add(WZlvqq[fIter->first]);
      diboson->SetFillColor(kRed-7);
      diboson->SetLineWidth(0);

      Z_Z = (TH1F*)ZZllll[fIter->first]->Clone();
      Z_Z->Add(ZZqqll[fIter->first]); 
      Z_Z->Add(ZZvvll[fIter->first]);
      Z_Z->SetFillColor(kBlue-6);
      Z_Z->SetLineWidth(0);
      //Z_Z->Scale(1.1); //change by hand the normalisation as the qq->ZZ is not used yet
    
    }

    // merge for WZ _Analysis
    if(option.find("WZDiBosonAnalysis") != option.npos){
      
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
      
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
     
      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

      diboson = (TH1F*)WWlvlv[fIter->first]->Clone();
      diboson->Add(WWlvqq[fIter->first]);
      diboson->Add(ZZqqll[fIter->first]); 
      diboson->Add(ZZllll[fIter->first]);
      diboson->Add(ZZvvll[fIter->first]);   
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
      
      W_Z = (TH1F*)WZlvll[fIter->first]->Clone();
      W_Z->Add(WZlvvv[fIter->first]);
      W_Z->Add(WZqqll[fIter->first]);
      W_Z->Add(WZlvqq[fIter->first]);  
      W_Z->SetFillColor(kRed-7);
      W_Z->SetLineWidth(0);
      W_Z->Scale(1.18); //normalisation scaled by a global factor of 1.18 to match the measured inclusive WZ cross section
 
    }
    
    
    // merge for Top 
    if(option.find("TTbar") != option.npos ){
      
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
    
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

      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);
    
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
     
    }


    if(option.find("HZZAnalysis") != option.npos){
      V = (TH1F*)Wplusenu[fIter->first]->Clone();
      V->Add(Wplusmunu[fIter->first]);
      V->Add(Wplustaunu[fIter->first]);
      V->Add(Wminusenu[fIter->first]);
      V->Add(Wminusmunu[fIter->first]);
      V->Add(Wminustaunu[fIter->first]);
      V->Add(Ztautau[fIter->first]);
      V->Add(Zee[fIter->first]);
      V->Add(Zmumu[fIter->first]);
      V->Add(single_top_schan[fIter->first]);
      V->Add(single_antitop_schan[fIter->first]);
      V->Add(single_top_tchan[fIter->first]);
      V->Add(single_antitop_tchan[fIter->first]);
      V->Add(single_top_wtchan[fIter->first]);
      V->Add(single_antitop_wtchan[fIter->first]);
      V->Add(WWlvlv[fIter->first]);
      V->Add(WWlvqq[fIter->first]);
      V->Add(WZlvll[fIter->first]);
      V->Add(WZlvvv[fIter->first]);
      V->Add(WZqqll[fIter->first]);
      V->Add(WZlvqq[fIter->first]);
      V->Add(ttbar_lep[fIter->first]);
      V->SetFillColor(kBlue-6);
      V->SetLineWidth(0);

      Z_Z = (TH1F*)ZZllll[fIter->first]->Clone();
      Z_Z->Add(ZZqqll[fIter->first]); 
      Z_Z->Add(ZZvvll[fIter->first]);
      Z_Z->SetFillColor(kAzure+8);
      Z_Z->SetLineWidth(0);
      Z_Z->Scale(1.4); //change by hand the normalisation to include qq->ZZ

      Higgs = (TH1F*)ggH125_ZZ4lep[fIter->first]->Clone();
      Higgs->Add(ZH125_ZZ4lep[fIter->first]);
      Higgs->Add(WH125_ZZ4lep[fIter->first]);
      Higgs->Add(VBFH125_ZZ4lep[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);
    }
   
    
    // merge for HWW _Analysis
    if(option.find("HWWAnalysis") != option.npos){
      
      Higgs = (TH1F*)ggH125_WW2lep[fIter->first]->Clone();
      Higgs->Add(VBFH125_WW2lep[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);

      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);

      diboson = (TH1F*)WWlvlv[fIter->first]->Clone();
      diboson->Add(WWlvqq[fIter->first]);
      diboson->Add(WZlvll[fIter->first]);
      diboson->Add(WZlvvv[fIter->first]);
      diboson->Add(WZqqll[fIter->first]);
      diboson->Add(WZlvqq[fIter->first]);
      diboson->Add(ZZqqll[fIter->first]);
      diboson->Add(ZZllll[fIter->first]);
      diboson->Add(ZZvvll[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
      diboson->Scale(1.4); //normalisation scaled by a global factor 

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

      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

    }

    // merge for ZTauTauAnalysis
    if(option.find("ZTauTauAnalysis") != option.npos){
      
      /* not there for now
	 diboson = (TH1F*)WWlvlv[fIter->first]->Clone();
	 diboson->Add(WWlvqq[fIter->first]);
	 diboson->Add(WZlvll[fIter->first]);
	 diboson->Add(WZlvvv[fIter->first]);
	 diboson->Add(WZqqll[fIter->first]);
	 diboson->Add(WZlvqq[fIter->first]);
	 diboson->Add(ZZqqll[fIter->first]);
	 diboson->Add(ZZllll[fIter->first]);
	 diboson->Add(ZZvvll[fIter->first]);
	 diboson->SetFillColor(kBlue-6);
	 diboson->SetLineWidth(0);
      */

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


      Z_ee = (TH1F*)Zee0_70_BFilter[fIter->first]->Clone();
      Z_ee->Add(Zee0_70_CFilterBVeto[fIter->first]);
      Z_ee->Add(Zee0_70_CVetoBVeto[fIter->first]);
      Z_ee->Add(Zee1000[fIter->first]);
      Z_ee->Add(Zee140_280_BFilter[fIter->first]);
      Z_ee->Add(Zee140_280_CFilterBVeto[fIter->first]);
      Z_ee->Add(Zee140_280_CVetoBVeto[fIter->first]);
      Z_ee->Add(Zee280_500_BFilter[fIter->first]);
      Z_ee->Add(Zee280_500_CFilterBVeto[fIter->first]);
      Z_ee->Add(Zee280_500_CVetoBVeto[fIter->first]);
      Z_ee->Add(Zee500_1000[fIter->first]);
      Z_ee->Add(Zee70_140_BFilter[fIter->first]);
      Z_ee->Add(Zee70_140_CFilterBVeto[fIter->first]);
      Z_ee->Add(Zee70_140_CVetoBVeto[fIter->first]);
      Z_ee->SetFillColor(kBlue-6);
      Z_ee->SetLineWidth(0);
      
      Z_mumu = (TH1F*)Zmumu0_70_BFilter[fIter->first]->Clone();
      Z_mumu->Add(Zmumu0_70_CFilterBVeto[fIter->first]);
      Z_mumu->Add(Zmumu0_70_CVetoBVeto[fIter->first]);
      Z_mumu->Add(Zmumu1000[fIter->first]);
      Z_mumu->Add(Zmumu140_280_BFilter[fIter->first]);
      Z_mumu->Add(Zmumu140_280_CFilterBVeto[fIter->first]);
      Z_mumu->Add(Zmumu140_280_CVetoBVeto[fIter->first]);
      Z_mumu->Add(Zmumu280_500_BFilter[fIter->first]);
      Z_mumu->Add(Zmumu280_500_CFilterBVeto[fIter->first]);
      Z_mumu->Add(Zmumu280_500_CVetoBVeto[fIter->first]);
      Z_mumu->Add(Zmumu500_1000[fIter->first]);
      Z_mumu->Add(Zmumu70_140_BFilter[fIter->first]);
      Z_mumu->Add(Zmumu70_140_CFilterBVeto[fIter->first]);
      Z_mumu->Add(Zmumu70_140_CVetoBVeto[fIter->first]);
      Z_mumu->SetFillColor(kPink+9);
      Z_mumu->SetLineWidth(0);

      Z_tautau = (TH1F*)Ztautau0_70_BFilter[fIter->first]->Clone();
      Z_tautau->Add(Ztautau0_70_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau0_70_CVetoBVeto[fIter->first]);
      Z_tautau->Add(Ztautau1000[fIter->first]);
      Z_tautau->Add(Ztautau140_280_BFilter[fIter->first]);
      Z_tautau->Add(Ztautau140_280_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau140_280_CVetoBVeto[fIter->first]);
      Z_tautau->Add(Ztautau280_500_BFilter[fIter->first]);
      Z_tautau->Add(Ztautau280_500_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau280_500_CVetoBVeto[fIter->first]);
      Z_tautau->Add(Ztautau500_1000[fIter->first]);
      Z_tautau->Add(Ztautau70_140_BFilter[fIter->first]);
      Z_tautau->Add(Ztautau70_140_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau70_140_CVetoBVeto[fIter->first]);
      Z_tautau->SetFillColor(kRed);
      Z_tautau->SetLineWidth(0);
      
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);

      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

    }


    // merge for SUSYAnalysis
    if(option.find("SUSYAnalysis") != option.npos){
      
      
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
      
      
      Z = (TH1F*)Zee0_70_BFilter[fIter->first]->Clone();
      Z->Add(Zee0_70_CFilterBVeto[fIter->first]);
      Z->Add(Zee0_70_CVetoBVeto[fIter->first]);
      Z->Add(Zee1000[fIter->first]);
      Z->Add(Zee140_280_BFilter[fIter->first]);
      Z->Add(Zee140_280_CFilterBVeto[fIter->first]);
      Z->Add(Zee140_280_CVetoBVeto[fIter->first]);
      Z->Add(Zee280_500_BFilter[fIter->first]);
      Z->Add(Zee280_500_CFilterBVeto[fIter->first]);
      Z->Add(Zee280_500_CVetoBVeto[fIter->first]);
      Z->Add(Zee500_1000[fIter->first]);
      Z->Add(Zee70_140_BFilter[fIter->first]);
      Z->Add(Zee70_140_CFilterBVeto[fIter->first]);
      Z->Add(Zee70_140_CVetoBVeto[fIter->first]);
      
      Z->Add(Zmumu0_70_BFilter[fIter->first]);
      Z->Add(Zmumu0_70_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu0_70_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu1000[fIter->first]);
      Z->Add(Zmumu140_280_BFilter[fIter->first]);
      Z->Add(Zmumu140_280_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu140_280_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu280_500_BFilter[fIter->first]);
      Z->Add(Zmumu280_500_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu280_500_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu500_1000[fIter->first]);
      Z->Add(Zmumu70_140_BFilter[fIter->first]);
      Z->Add(Zmumu70_140_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu70_140_CVetoBVeto[fIter->first]);
      
      Z->Add(Ztautau0_70_BFilter[fIter->first]);
      Z->Add(Ztautau0_70_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau0_70_CVetoBVeto[fIter->first]);
      Z->Add(Ztautau1000[fIter->first]);
      Z->Add(Ztautau140_280_BFilter[fIter->first]);
      Z->Add(Ztautau140_280_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau140_280_CVetoBVeto[fIter->first]);
      Z->Add(Ztautau280_500_BFilter[fIter->first]);
      Z->Add(Ztautau280_500_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau280_500_CVetoBVeto[fIter->first]);
      Z->Add(Ztautau500_1000[fIter->first]);
      Z->Add(Ztautau70_140_BFilter[fIter->first]);
      Z->Add(Ztautau70_140_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau70_140_CVetoBVeto[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);
      
      
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
      
      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

    }

 







    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // main stack of MCs
    THStack* stack = new THStack();
   
    // statistical error histogram
    TH1F* histstack = new TH1F();
      
    //DONe ======================
    if(option.find("WBosonAnalysis") != option.npos){
    stack->Add(stop);
    stack->Add(ttbar);
    stack->Add(diboson);
    stack->Add(Z);
    stack->Add(W);
    
    histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
    histstack->Add(Z);
    histstack->Add(diboson);
    histstack->Add(W);
    histstack->Add(stop);
    }
    
    if(option.find("TTbar") != option.npos || option.find("ZPrimeBoostedAnalysis") != option.npos){
      stack->Add(diboson);
      stack->Add(stop);
      stack->Add(V);
      stack->Add(ttbar);

      histstack = (TH1F*)ttbar->Clone();
      histstack->Add(stop);
      histstack->Add(diboson);
      histstack->Add(V);

    }
    
    if(option.find("SingleTopAnalysis") != option.npos){
      stack->Add(ZVV);
      stack->Add(W);
      stack->Add(stop_tWtb);
      stack->Add(stop_tq);
      
      histstack = (TH1F*)ZVV->Clone();
      histstack->Add(W);
      histstack->Add(stop_tq);
      histstack->Add(stop_tWtb);

    }
    //===============





    if(option.find("ZZDiBosonAnalysis") != option.npos){
      stack->Add(V);
      stack->Add(diboson);
      stack->Add(Z_Z);
    }

   if(option.find("WZDiBosonAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(V);
      stack->Add(diboson);
      stack->Add(W_Z);
    }
 
  if(option.find("ZBosonAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(diboson);
      stack->Add(W);
      stack->Add(Z);
    }

    
    if(option.find("HZZAnalysis") != option.npos){
      stack->Add(stop);

      stack->Add(V);
      stack->Add(Z_Z);
      stack->Add(Higgs);
    }
    
       
    
    if(option.find("HWWAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(V);
      stack->Add(diboson);
      stack->Add(Higgs);
    }
  

    if(option.find("ZTauTauAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      //stack->Add(diboson);
      stack->Add(W);
      stack->Add(Z_ee);
      stack->Add(Z_mumu);
      stack->Add(Z_tautau);
    }

   if(option.find("SUSYAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(diboson);
      stack->Add(W);
      stack->Add(Z);
    }

    
    if(option.find("ZBosonAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(Z);
      histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
    }

    if(option.find("ZZDiBosonAnalysis") != option.npos){
      histstack = (TH1F*)diboson->Clone();
      histstack->Add(V);
      histstack->Add(Z_Z);
    }

    if(option.find("WZDiBosonAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(stop);
      histstack->Add(diboson);
      histstack->Add(V);
      histstack->Add(W_Z);
    }
  
    if(option.find("HZZAnalysis") != option.npos){
      histstack = (TH1F*)V->Clone();
      histstack->Add(Z_Z);
      histstack->Add(Higgs);
    }
     
    if(option.find("HWWAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(diboson);
      histstack->Add(V);
      histstack->Add(stop);
      histstack->Add(Higgs);
    }
 
  if(option.find("ZTauTauAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
   //   histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
      histstack->Add(Z_ee);
      histstack->Add(Z_mumu);
      histstack->Add(Z_tautau);
    }

  if(option.find("SUSYAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(Z);
      histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
    }




//////////


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
    if(option.find("HZZAnalysis") != option.npos){
      Higgs_normsig = (TH1F*)ggH125_ZZ4lep[fIter->first]->Clone();
      Higgs_normsig->Add(ZH125_ZZ4lep[fIter->first]);
      Higgs_normsig->Add(WH125_ZZ4lep[fIter->first]);
      Higgs_normsig->Add(VBFH125_ZZ4lep[fIter->first]);
      Higgs_normsig->Scale(histstack->Integral()/Higgs_normsig->Integral());
      Higgs_normsig->SetLineColor(kRed);
      Higgs_normsig->SetFillStyle(0);
      Higgs_normsig->SetLineStyle(2);
      Higgs_normsig->SetFillColor(2);
      Higgs_normsig->SetLineWidth(2);
    }
  
    if(option.find("HWWAnalysis") != option.npos){
      Higgs_normsig = (TH1F*)ggH125_WW2lep[fIter->first]->Clone();
      Higgs_normsig->Scale(histstack->Integral()/Higgs_normsig->Integral());
      Higgs_normsig->SetLineColor(kRed);
      Higgs_normsig->SetFillStyle(0);
      Higgs_normsig->SetLineStyle(2);
      Higgs_normsig->SetFillColor(2);
      Higgs_normsig->SetLineWidth(2);
    }

    TH1F* stop_normsig = new TH1F();
    if(option.find("SingleTopAnalysis") != option.npos){
      stop_normsig = (TH1F*)stop_tq->Clone();
      stop_normsig->Scale(histstack->Integral()/stop_normsig->Integral());
      stop_normsig->SetLineColor(kRed);
      stop_normsig->SetFillStyle(0);
      stop_normsig->SetLineStyle(2);
      stop_normsig->SetFillColor(2);
      stop_normsig->SetLineWidth(2);
    }

    TH1F* ZPrime_normsig = new TH1F();
    if( option.find("ZPrimeBoostedAnalysis") != option.npos ){
      ZPrime_normsig = (TH1F*)ZPrime->Clone();
      ZPrime_normsig ->Scale(histstack->Integral()/ZPrime_normsig->Integral());
      ZPrime_normsig->SetLineColor(kRed);
      ZPrime_normsig->SetFillStyle(0);
      ZPrime_normsig->SetLineStyle(2);
      ZPrime_normsig->SetFillColor(2);
      ZPrime_normsig->SetLineWidth(2);
    }

    
    TH1F* slep600DM300_normsig = new TH1F();
    if(option.find("SUSYAnalysis") != option.npos){
      slep600DM300_normsig = (TH1F*)slep600DM300[fIter->first]->Clone();
      slep600DM300_normsig->SetLineColor(kRed);
      slep600DM300_normsig->SetFillStyle(0);
      slep600DM300_normsig->SetLineStyle(2);
      slep600DM300_normsig->SetFillColor(2);
      slep600DM300_normsig->SetLineWidth(2);
    }


    // set Yaxis maximum
    float yMaxScale = 2.;
    fIter->second->SetMaximum(yMaxScale*TMath::Max( TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()), Higgs_normsig->GetMaximum() ) );
    
    
    // latex options 
    TLatex l;
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.SetTextFont(42);
    l.SetTextSize(0.04);
    
    if(option.find("WBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"W #rightarrow l#nu");}
    if(option.find("TTbarAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"t#bar{t} #rightarrow l#nub q#bar{q}b");}
    if(option.find("SingleTopAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"t #rightarrow l#nub + q");}
    if(option.find("ZPrimeBoostedAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z' #rightarrow t#bar{t} (boosted)");}

    //  if(option.find("ZBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z \\rightarrow \\ell\\ell");}
    //  if(option.find("WZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"WZ \\rightarrow \\ell\\nu \\ell\\ell");}
    //  if(option.find("ZZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"ZZ \\rightarrow \\ell^{+}\\ell^{-} \\ell^{+}\\ell^{-}");}
    //  if(option.find("HWWAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow WW^{*} #rightarrow e#nu #mu#nu, N_{jet} #leq 1");}
    //  if(option.find("HZZAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow ZZ^{*} #rightarrow 4l");}
    //  if(option.find("ZTauTauAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z #rightarrow #tau_{l}#tau_{h}");}
    //  if(option.find("SUSYAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"2SF\\ell");}
    
    TLatex l2;
    l2.SetNDC();
    l2.SetTextSize(0.04);  
    l2.SetTextColor(kBlack);
    l2.DrawLatex(0.18,0.79, Form("#sqrt{s} = 13 TeV, #int L dt = 10 fb^{-1}")); 
    
    
    //create legend
    TLegend* leg;
    leg  = new TLegend();
    leg  = new TLegend(0.70,0.50,0.93,0.925);  
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(32);
    leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetMargin(0.22);
    leg->SetTextAlign(32);
    
    // fill legend

    if(option.find("ZBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z,  "Z+jets", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }

    if(option.find("WBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(Z,  "Z+jets", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    
      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  W: " << W->Integral()  <<
              ",  Z: " << Z->Integral()  <<
              ",  diboson: " << diboson->Integral()  <<
		",  ttbar: " << ttbar ->Integral()  <<
		",  stop: " <<  stop->Integral()  <<
		",  Total pred.: "<< diboson->Integral() + W->Integral() + Z->Integral() + ttbar ->Integral() + stop->Integral() <<
		endl;
      }
    }

	
    if(option.find("SingleTopAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(stop_tq, "tq", "f");
      leg-> AddEntry(ttbar, "t#bar{t},Wt,t#bar{b}", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(ZVV,  "Z,VV+jets", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      if(NORMSIG) leg-> AddEntry(stop_normsig, "tq_{norm}" ,"l");

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  stop (t-channel): " <<  stop_tq->Integral()  <<
              ",  ttbar and stop (Wt,tb): " <<  stop_tWtb->Integral()  <<
              ",  W: " << W->Integral()  <<
              ",  Z and diboson: " << ZVV->Integral()  <<
		",  Total pred.: "<< W->Integral() + ZVV->Integral() + stop_tWtb->Integral() + stop_tq->Integral() <<
		endl;
      }
    }
    
    
    
    if(option.find("ZZDiBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z_Z , "ZZ", "f");
      leg-> AddEntry(diboson , "WW,WZ", "f");
      leg-> AddEntry(V,  "Other", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }
    
    if(option.find("WZDiBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(W_Z , "WZ", "f");
      leg-> AddEntry(diboson , "WW,ZZ", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }
    
    if(option.find("TTbar") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  single top: " <<  stop->Integral()  <<
              ",  ttbar: " <<  ttbar->Integral()  <<
              ",  V+jets: " << V->Integral()  <<
              ",  diboson: " << diboson->Integral()  <<
                ",  Total pred.: "<< diboson->Integral() + V->Integral() + ttbar->Integral() + stop->Integral() <<
                endl;
      }
    }

    if(option.find("TTbar") != option.npos || option.find("ZPrimeBoostedAnalysis") != option.npos ) {
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      if(option.find("ZPrimeBoostedAnalysis") != option.npos && NORMSIG) 
      {
	if(fIter->first.find("LR") != option.npos) leg-> AddEntry(ZPrime_normsig, "m_{Z'}=1 TeV" ,"l");
      }

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  single top: " <<  stop->Integral()  <<
              ",  ttbar: " <<  ttbar->Integral()  <<
              ",  V+jets: " << V->Integral()  <<
              ",  diboson: " << diboson->Integral()  <<
                ",  Total pred.: "<< diboson->Integral() + V->Integral() + ttbar->Integral() + stop->Integral() <<
                endl;
      }
    }

    
    if(option.find("HZZAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Higgs , "Higgs", "f");
      leg-> AddEntry(Z_Z , "ZZ", "f");
      leg-> AddEntry(V,  "Other", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      if(NORMSIG) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");
      
      if(YIELDS){
	cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
	  ",  Higgs: " << Higgs->Integral()  <<
	  ",  ZZ: " << Z_Z->Integral()  <<
	  ",  Other: " << V->Integral()  <<
	  ",  Total pred.: "<< V->Integral() + Z_Z->Integral()  <<
	  endl;
      }
    }
    
    
    if(option.find("HWWAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Higgs , "Higgs", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      if(NORMSIG) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");
      
      // print yields
      if(YIELDS){
	cout << "Number of events:" << "Data: " << data[fIter->first]->Integral() << 
	  ",  Higgs: " << Higgs->Integral()  << 
	  ",  WW: " << diboson->Integral()  <<
	  ",  V+jets: " << V->Integral()  <<
	  ",  ttbar: " << ttbar ->Integral()  <<
	  ",  stop: " <<  stop->Integral()  <<
	  ",  Total pred.: "<< diboson->Integral() + V->Integral() + ttbar ->Integral() + stop->Integral() << 
	  endl;
      }
    }
    
    if(option.find("ZTauTauAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z_tautau,  "Z #rightarrow #tau#tau", "f");
      leg-> AddEntry(Z_mumu,  "Z #rightarrow #mu#mu", "f");
      leg-> AddEntry(Z_ee,  "Z #rightarrow ee", "f");
      //      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }
    
    if(option.find("SUSYAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z,  "Z+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }
    
    // only for SUSY
    TLegend* leg2;     leg2  = new TLegend();              leg2  = new TLegend(0.45,0.45,0.93,0.50);
    leg2->SetFillStyle(0);     leg2->SetBorderSize(0);     leg2->SetTextAlign(32);
    leg2->SetTextFont(42);     leg2->SetTextSize(0.05);    leg2->SetMargin(0.22);     leg2->SetTextAlign(32);
    if(option.find("SUSYAnalysis") != option.npos) leg2-> AddEntry(slep600DM300_normsig, "m(#tilde{l},#chi^{0}_{1})=(600,300) GeV" ,"l");

    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");
    
    // draw the normalised signal in the plots
    if(NORMSIG){
      if(option.find("HZZAnalysis") != option.npos){Higgs_normsig->Draw("HISTsame");}
      if(option.find("HWWAnalysis") != option.npos){Higgs_normsig->Draw("HISTsame");}
      if(option.find("SingleTopAnalysis") != option.npos){stop_normsig->Draw("HISTsame");}
      if(option.find("SUSYAnalysis") != option.npos){slep600DM300_normsig->Draw("HISTsame");}
      if(option.find("ZPrimeBoostedAnalysis") != option.npos){ if(fIter->first.find("LR") != option.npos) ZPrime_normsig->Draw("HISTsame"); }
    }
    
    leg->Draw("same");

    // in case of SUSY, we add the normalised signals 
    if(option.find("SUSYAnalysis") != option.npos && NORMSIG) leg2->Draw("same");
    
    
    ATLASLabel(0.18, 0.87);
    

    ////////////////////////////////////////////////////////////////////////////////
    // lower pad contains the ratio of data to MC
    pad1->cd();
    pad1->GetFrame()->SetY1(2);
    pad1->Draw();

    // create the ratio plot  
    TH1F *h_ratio = (TH1F*)data[fIter->first]->Clone("h_ratio");
    h_ratio->Divide((TH1F*)histstack->Clone());
    h_ratio->GetYaxis()->SetTitle("Data / Pred      ");


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
    h_ratio->GetYaxis()->SetTitleOffset(0.5);
    h_ratio->GetYaxis()->SetLabelSize(0.10);
 
    data[fIter->first]->GetXaxis()->SetLabelSize(0);
    gPad->RedrawAxis();
    pad1->cd();
    pad1->cd()->SetGridy();
    h_ratio->Draw("SAME0E1");
    h_ratio->Draw("SAMEAXIS");
    h_ratio->GetYaxis()->Draw();
    h_ratio->Draw("SAME0E1");
    
    pad0->cd();
    TAxis * Ay1 = NULL;
    Ay1 = fIter->second->GetXaxis();
    Ay1->SetLabelSize(0);
    Ay1->SetTitleSize(0);

    if(option.find("WBosonAnalysis") != option.npos){
      pad0->SetLogy(1);
      fIter->second->SetMinimum(100);
      fIter->second->SetMaximum(1e12);
      if(fIter->first.find("leptch") != option.npos)      fIter->second->SetMaximum(1e14);
    }


    if(option.find("ZBosonAnalysis") != option.npos){
     pad0->SetLogy(1);
     fIter->second->SetMinimum(100);
     fIter->second->SetMaximum(1e9);
    }
    
    if(option.find("TTbarAnalysis") != option.npos){
      pad0->SetLogy(1);
      fIter->second->SetMinimum(10);
      fIter->second->SetMaximum(1e8);
      if(fIter->first.find("Topmass") != option.npos){
	pad0->SetLogy(0);
	fIter->second->SetMinimum(1);
	fIter->second->SetMaximum(1e4);
      }
      if(fIter->first.find("Wmass") != option.npos){
	pad0->SetLogy(0);
	fIter->second->SetMinimum(1);
	fIter->second->SetMaximum(5e3);
      }
      if(fIter->first.find("leptch") != option.npos){
	pad0->SetLogy(1);
	fIter->second->SetMinimum(10);
	fIter->second->SetMaximum(1e9);
      }
    }
    
    if(option.find("SUSYAnalysis") != option.npos){
      pad0->SetLogy(1);
      fIter->second->SetMinimum(0.01);
      fIter->second->SetMaximum(1e12);
    }




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

  return;
}

///
void Plotting::getHistoSettings(){
  
  // save names of the histograms for later  
  hset.clear();
  
  // read in configuration file
  std::string ifile;

  if(option.find("WBosonAnalysis")        != option.npos){ifile = "list_histos/HistoList_WBosonAnalysis.txt";}
  if(option.find("TTbarAnalysis")         != option.npos){ifile = "list_histos/HistoList_TTbarAnalysis.txt";}
  if(option.find("SingleTopAnalysis")     != option.npos){ifile = "list_histos/HistoList_SingleTopAnalysis.txt";}
  if(option.find("ZPrimeBoostedAnalysis") != option.npos){ifile = "list_histos/HistoList_ZPrimeBoostedAnalysis.txt";}


//  if(option.find("ZBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_ZBosonAnalysis.txt";}
//  if(option.find("WZDiBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_WZDiBosonAnalysis.txt";}
//  if(option.find("ZZDiBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_ZZDiBosonAnalysis.txt";}
//  if(option.find("HWWAnalysis") != option.npos){ifile = "list_histos/HistoList_HWWAnalysis.txt";}
//  if(option.find("HZZAnalysis") != option.npos){ifile = "list_histos/HistoList_HZZAnalysis.txt";}
//  if(option.find("ZTauTauAnalysis") != option.npos){ifile = "list_histos/HistoList_ZTauTauAnalysis.txt";}
//  if(option.find("SUSYAnalysis") != option.npos){ifile = "list_histos/HistoList_SUSYAnalysis.txt";}


  
  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("#") != line.npos )continue;
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
