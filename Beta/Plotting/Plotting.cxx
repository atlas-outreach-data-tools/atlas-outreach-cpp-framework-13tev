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
#include "THStack.h"
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include "TCanvas.h"
#include <TStyle.h>
#include "TLatex.h"
#include "TImage.h"
#include "TLine.h"
#include "TColor.h"
#include "TROOT.h"
#include "TH2F.h"
#include "TMath.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TArrow.h"
#include <TGaxis.h>
#include "Plotting.h"



// OPTIONS flag, set to 0 or 1 for 
#define DEBUG 1 // debugging
#define YIELDS 1 // printing yields
#define HIGGSNORMSIG 0 // adding normalised Higgs signal




//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  
  if(argc < 3){
    std::cout<<"usage: ./plot [WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, ZTauTauAnalysis, HyyAnalysis]  [location of OutputDir_AnalysisName]"<<std::endl;
    std::cout<<"output stored in a directory \'histograms\' " <<std::endl;
    exit(1);
  }
  
  Plotting* m = new Plotting();
  
  m->SetLumi(10064); // luminosity set by hand to 10fb-1
  m->SetOption(argv[1]);
  m->SetInputLocation(argv[2]);
  
  string option = argv[1];
  if(option.find("ZTauTauAnalysis") != option.npos ||  option.find("WBosonAnalysis") != option.npos ||  option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("HyyAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos) cout << "Analysis option found, proceeding..." << endl;
  else { cout << "Analysis option not found! \n usage: ./plot [WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, HyyAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis]  [location of OutputDir_AnalysisName] \n " << endl; exit(1);}
 

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
  // read in file
  std::string ifile = "Files_base.txt";

  //options
  if(option.find("HZZAnalysis") != option.npos){   ifile = "Files_HZZ.txt";}
  if(option.find("HWWAnalysis") != option.npos){   ifile = "Files_HWW.txt";}
  if(option.find("ZTauTauAnalysis") != option.npos){   ifile = "Files_ZTauTau.txt";}
  if(option.find("WBosonAnalysis") != option.npos){   ifile = "Files_WBoson.txt";}

 
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

  //ttbar
  std::map<std::string,TH1F*> ttbar_lep;   
  
  //Z+jets
  std::map<std::string,TH1F*> Z_ee;
  std::map<std::string,TH1F*> Z_mumu;
  std::map<std::string,TH1F*> Z_tautau;
  
  // diboson
  std::map<std::string,TH1F*> WWlvlv;
  std::map<std::string,TH1F*> WWlvqq;

  std::map<std::string,TH1F*> ZZllll;
  std::map<std::string,TH1F*> ZZvvll;
  std::map<std::string,TH1F*> ZZqqll;
  
  std::map<std::string,TH1F*> WZlvll;
  std::map<std::string,TH1F*> WZlvvv;
  std::map<std::string,TH1F*> WZqqll;
  std::map<std::string,TH1F*> WZlvqq;

  
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
  std::map<std::string,TH1F*>  We0_70BFilter; std::map<std::string,TH1F*>  We0_70CFilterBVeto; std::map<std::string,TH1F*>  We0_70CVetoBVeto; std::map<std::string,TH1F*>  We1000; std::map<std::string,TH1F*>  We140_280BFilter; std::map<std::string,TH1F*>  We140_280CFilterBVeto; std::map<std::string,TH1F*>  We140_280CVetoBVeto; std::map<std::string,TH1F*>  We280_500BFilter; std::map<std::string,TH1F*>  We280_500CFilterBVeto; std::map<std::string,TH1F*>  We280_500CVetoBVeto; std::map<std::string,TH1F*> We500_1000; std::map<std::string,TH1F*>  We70_140BFilter; std::map<std::string,TH1F*>  We70_140CFilterBVeto; std::map<std::string,TH1F*>  We70_140CVetoBVeto; std::map<std::string,TH1F*>  Wmu0_70BFilter; std::map<std::string,TH1F*>  Wmu0_70CFilterBVeto; std::map<std::string,TH1F*> Wmu0_70CVetoBVeto; std::map<std::string,TH1F*>  Wmu1000; std::map<std::string,TH1F*>  Wmu140_280BFilter; std::map<std::string,TH1F*>  Wmu140_280CFilterBVeto; std::map<std::string,TH1F*>  Wmu140_280CVetoBVeto; std::map<std::string,TH1F*>  Wmu280_500BFilter; std::map<std::string,TH1F*> Wmu280_500CFilterBVeto; std::map<std::string,TH1F*>  Wmu280_500CVetoBVeto; std::map<std::string,TH1F*>  Wmu500_1000; std::map<std::string,TH1F*>  Wmu70_140BFilter; std::map<std::string,TH1F*>  Wmu70_140CFilterBVeto; std::map<std::string,TH1F*> Wmu70_140CVetoBVeto; std::map<std::string,TH1F*>  Wtau0_70BFilter; std::map<std::string,TH1F*>  Wtau0_70CFilterBVeto; std::map<std::string,TH1F*>  Wtau0_70CVetoBVeto; std::map<std::string,TH1F*>  Wtau1000; std::map<std::string,TH1F*>  Wtau140_280BFilter; std::map<std::string,TH1F*> Wtau140_280CFilterBVeto; std::map<std::string,TH1F*>  Wtau140_280CVetoBVeto; std::map<std::string,TH1F*>  Wtau280_500BFilter; std::map<std::string,TH1F*>  Wtau280_500CFilterBVeto; std::map<std::string,TH1F*>  Wtau280_500CVetoBVeto; std::map<std::string,TH1F*> Wtau500_1000; std::map<std::string,TH1F*>  Wtau70_140BFilter; std::map<std::string,TH1F*>  Wtau70_140CFilterBVeto; std::map<std::string,TH1F*>  Wtau70_140CVetoBVeto; std::map<std::string,TH1F*>  Zee0_70BFilter; std::map<std::string,TH1F*>  Zee0_70CFilterBVeto; std::map<std::string,TH1F*> Zee0_70CVetoBVeto; std::map<std::string,TH1F*>  Zee1000; std::map<std::string,TH1F*>  Zee140_280BFilter; std::map<std::string,TH1F*>  Zee140_280CFilterBVeto; std::map<std::string,TH1F*>  Zee140_280CVetoBVeto; std::map<std::string,TH1F*>  Zee280_500BFilter; std::map<std::string,TH1F*> Zee280_500CFilterBVeto; std::map<std::string,TH1F*>  Zee280_500CVetoBVeto; std::map<std::string,TH1F*>  Zee500_1000; std::map<std::string,TH1F*>  Zee70_140BFilter; std::map<std::string,TH1F*>  Zee70_140CFilterBVeto; std::map<std::string,TH1F*> Zee70_140CVetoBVeto; std::map<std::string,TH1F*>  Zmumu0_70BFilter; std::map<std::string,TH1F*>  Zmumu0_70CFilterBVeto; std::map<std::string,TH1F*>  Zmumu0_70CVetoBVeto; std::map<std::string,TH1F*>  Zmumu1000; std::map<std::string,TH1F*>  Zmumu140_280BFilter; std::map<std::string,TH1F*> Zmumu140_280CFilterBVeto; std::map<std::string,TH1F*>  Zmumu140_280CVetoBVeto; std::map<std::string,TH1F*>  Zmumu280_500BFilter; std::map<std::string,TH1F*>  Zmumu280_500CFilterBVeto; std::map<std::string,TH1F*> Zmumu280_500CVetoBVeto; std::map<std::string,TH1F*>  Zmumu500_1000; std::map<std::string,TH1F*>  Zmumu70_140BFilter; std::map<std::string,TH1F*>  Zmumu70_140CFilterBVeto; std::map<std::string,TH1F*>  Zmumu70_140CVetoBVeto; std::map<std::string,TH1F*> Ztautau0_70BFilter; std::map<std::string,TH1F*>  Ztautau0_70CFilterBVeto; std::map<std::string,TH1F*>  Ztautau0_70CVetoBVeto; std::map<std::string,TH1F*>  Ztautau1000; std::map<std::string,TH1F*>  Ztautau140_280BFilter; std::map<std::string,TH1F*> Ztautau140_280CFilterBVeto; std::map<std::string,TH1F*>  Ztautau140_280CVetoBVeto; std::map<std::string,TH1F*>  Ztautau280_500BFilter; std::map<std::string,TH1F*>  Ztautau280_500CFilterBVeto; std::map<std::string,TH1F*> Ztautau280_500CVetoBVeto; std::map<std::string,TH1F*>  Ztautau500_1000; std::map<std::string,TH1F*>  Ztautau70_140BFilter; std::map<std::string,TH1F*>  Ztautau70_140CFilterBVeto; std::map<std::string,TH1F*>  Ztautau70_140CVetoBVeto;



  
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
  
  ttbar_lep = histo["ttbar_lep"];

 
  Z_ee = histo["Z_ee"];
  Z_mumu = histo["Z_mumu"];
  Z_tautau = histo["Z_tautau"];


  // inclusive Powheg W+jets samples are used for all the analyses but ZTaTau and WBoson 
  if( option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos) 
  {
  Wplusenu = histo["Wplusenu"];
  Wplusmunu= histo["Wplusmunu"];
  Wplustaunu= histo["Wplustaunu"];  
  Wminusenu= histo["Wminusenu"];
  Wminusmunu= histo["Wminusmunu"];
  Wminustaunu= histo["Wminustaunu"];
  }

  // slices Sherpa W+jets samples are used for ZTaTau and WBoson analyses
  if(option.find("ZTauTauAnalysis") != option.npos ||   option.find("WBosonAnalysis") != option.npos )
  {
  
We0_70BFilter = histo["We0_70BFilter"];
We0_70CFilterBVeto = histo["We0_70CFilterBVeto"];
We0_70CVetoBVeto = histo["We0_70CVetoBVeto"];
We1000 = histo["We1000"];
We140_280BFilter = histo["We140_280BFilter"];
We140_280CFilterBVeto = histo["We140_280CFilterBVeto"];
We140_280CVetoBVeto = histo["We140_280CVetoBVeto"];
We280_500BFilter = histo["We280_500BFilter"];
We280_500CFilterBVeto = histo["We280_500CFilterBVeto"];
We280_500CVetoBVeto = histo["We280_500CVetoBVeto"];
We500_1000 = histo["We500_1000"];
We70_140BFilter = histo["We70_140BFilter"];
We70_140CFilterBVeto = histo["We70_140CFilterBVeto"];
We70_140CVetoBVeto = histo["We70_140CVetoBVeto"];
Wmu0_70BFilter = histo["Wmu0_70BFilter"];
Wmu0_70CFilterBVeto = histo["Wmu0_70CFilterBVeto"];
Wmu0_70CVetoBVeto = histo["Wmu0_70CVetoBVeto"];
Wmu1000 = histo["Wmu1000"];
Wmu140_280BFilter = histo["Wmu140_280BFilter"];
Wmu140_280CFilterBVeto = histo["Wmu140_280CFilterBVeto"];
Wmu140_280CVetoBVeto = histo["Wmu140_280CVetoBVeto"];
Wmu280_500BFilter = histo["Wmu280_500BFilter"];
Wmu280_500CFilterBVeto = histo["Wmu280_500CFilterBVeto"];
Wmu280_500CVetoBVeto = histo["Wmu280_500CVetoBVeto"];
Wmu500_1000 = histo["Wmu500_1000"];
Wmu70_140BFilter = histo["Wmu70_140BFilter"];
Wmu70_140CFilterBVeto = histo["Wmu70_140CFilterBVeto"];
Wmu70_140CVetoBVeto = histo["Wmu70_140CVetoBVeto"];
Wtau0_70BFilter = histo["Wtau0_70BFilter"];
Wtau0_70CFilterBVeto = histo["Wtau0_70CFilterBVeto"];
Wtau0_70CVetoBVeto = histo["Wtau0_70CVetoBVeto"];
Wtau1000 = histo["Wtau1000"];
Wtau140_280BFilter = histo["Wtau140_280BFilter"];
Wtau140_280CFilterBVeto = histo["Wtau140_280CFilterBVeto"];
Wtau140_280CVetoBVeto = histo["Wtau140_280CVetoBVeto"];
Wtau280_500BFilter = histo["Wtau280_500BFilter"];
Wtau280_500CFilterBVeto = histo["Wtau280_500CFilterBVeto"];
Wtau280_500CVetoBVeto = histo["Wtau280_500CVetoBVeto"];
Wtau500_1000 = histo["Wtau500_1000"];
Wtau70_140BFilter = histo["Wtau70_140BFilter"];
Wtau70_140CFilterBVeto = histo["Wtau70_140CFilterBVeto"];
Wtau70_140CVetoBVeto = histo["Wtau70_140CVetoBVeto"];
  }

  // slices Sherpa Z+jets samples are used for ZTaTau analyses
 if(option.find("ZTauTauAnalysis") != option.npos)
   {
Zee0_70BFilter = histo["Zee0_70BFilter"];
Zee0_70CFilterBVeto = histo["Zee0_70CFilterBVeto"];
Zee0_70CVetoBVeto = histo["Zee0_70CVetoBVeto"];
Zee1000 = histo["Zee1000"];
Zee140_280BFilter = histo["Zee140_280BFilter"];
Zee140_280CFilterBVeto = histo["Zee140_280CFilterBVeto"];
Zee140_280CVetoBVeto = histo["Zee140_280CVetoBVeto"];
Zee280_500BFilter = histo["Zee280_500BFilter"];
Zee280_500CFilterBVeto = histo["Zee280_500CFilterBVeto"];
Zee280_500CVetoBVeto = histo["Zee280_500CVetoBVeto"];
Zee500_1000 = histo["Zee500_1000"];
Zee70_140BFilter = histo["Zee70_140BFilter"];
Zee70_140CFilterBVeto = histo["Zee70_140CFilterBVeto"];
Zee70_140CVetoBVeto = histo["Zee70_140CVetoBVeto"];
Zmumu0_70BFilter = histo["Zmumu0_70BFilter"];
Zmumu0_70CFilterBVeto = histo["Zmumu0_70CFilterBVeto"];
Zmumu0_70CVetoBVeto = histo["Zmumu0_70CVetoBVeto"];
Zmumu1000 = histo["Zmumu1000"];
Zmumu140_280BFilter = histo["Zmumu140_280BFilter"];
Zmumu140_280CFilterBVeto = histo["Zmumu140_280CFilterBVeto"];
Zmumu140_280CVetoBVeto = histo["Zmumu140_280CVetoBVeto"];
Zmumu280_500BFilter = histo["Zmumu280_500BFilter"];
Zmumu280_500CFilterBVeto = histo["Zmumu280_500CFilterBVeto"];
Zmumu280_500CVetoBVeto = histo["Zmumu280_500CVetoBVeto"];
Zmumu500_1000 = histo["Zmumu500_1000"];
Zmumu70_140BFilter = histo["Zmumu70_140BFilter"];
Zmumu70_140CFilterBVeto = histo["Zmumu70_140CFilterBVeto"];
Zmumu70_140CVetoBVeto = histo["Zmumu70_140CVetoBVeto"];
Ztautau0_70BFilter = histo["Ztautau0_70BFilter"];
Ztautau0_70CFilterBVeto = histo["Ztautau0_70CFilterBVeto"];
Ztautau0_70CVetoBVeto = histo["Ztautau0_70CVetoBVeto"];
Ztautau1000 = histo["Ztautau1000"];
Ztautau140_280BFilter = histo["Ztautau140_280BFilter"];
Ztautau140_280CFilterBVeto = histo["Ztautau140_280CFilterBVeto"];
Ztautau140_280CVetoBVeto = histo["Ztautau140_280CVetoBVeto"];
Ztautau280_500BFilter = histo["Ztautau280_500BFilter"];
Ztautau280_500CFilterBVeto = histo["Ztautau280_500CFilterBVeto"];
Ztautau280_500CVetoBVeto = histo["Ztautau280_500CVetoBVeto"];
Ztautau500_1000 = histo["Ztautau500_1000"];
Ztautau70_140BFilter = histo["Ztautau70_140BFilter"];
Ztautau70_140CFilterBVeto = histo["Ztautau70_140CFilterBVeto"];
Ztautau70_140CVetoBVeto = histo["Ztautau70_140CVetoBVeto"];
}



  // diboson samples are for now in all but ZTauTau
  WWlvlv= histo["WWlvlv"];  
  WWlvqq= histo["WWlvqq"];
  WZlvll= histo["WZlvll"];
  WZlvvv= histo["WZlvvv"];
  WZqqll= histo["WZqqll"];
  WZlvqq= histo["WZlvqq"];
  ZZllll= histo["ZZllll"];
  ZZvvll= histo["ZZvvll"];  
  ZZqqll= histo["ZZqqll"]; 

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
    
    //////////////////// begin merging of different MC
    
    TH1F* diboson = new TH1F();
    TH1F* W = new TH1F();
    TH1F* Z = new TH1F();
    TH1F* ttbar = new TH1F();
    TH1F* stop = new TH1F();
    TH1F* V = new TH1F();
    TH1F* W_Z = new TH1F();
    TH1F* Z_Z = new TH1F();
    TH1F* Higgs = new TH1F();
    
    TH1F* Zee = new TH1F();
    TH1F* Zmumu = new TH1F();
    TH1F* Ztautau = new TH1F();

    // merge for W _Analysis
    if(option.find("WBosonAnalysis") != option.npos){
      
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
  
      // sliced W+jets samples
      W = (TH1F*)We0_70BFilter[fIter->first]->Clone();
      W->Add(We0_70CFilterBVeto[fIter->first]);
      W->Add(We0_70CVetoBVeto[fIter->first]);
      W->Add(We1000[fIter->first]);
      W->Add(We140_280BFilter[fIter->first]);
      W->Add(We140_280CFilterBVeto[fIter->first]);
      W->Add(We140_280CVetoBVeto[fIter->first]);
      W->Add(We280_500BFilter[fIter->first]);
      W->Add(We280_500CFilterBVeto[fIter->first]);
      W->Add(We280_500CVetoBVeto[fIter->first]);
      W->Add(We500_1000[fIter->first]);
      W->Add(We70_140BFilter[fIter->first]);
      W->Add(We70_140CFilterBVeto[fIter->first]);
      W->Add(We70_140CVetoBVeto[fIter->first]);
      W->Add(Wmu0_70BFilter[fIter->first]);
      W->Add(Wmu0_70CFilterBVeto[fIter->first]);
      W->Add(Wmu0_70CVetoBVeto[fIter->first]);
      W->Add(Wmu1000[fIter->first]);
      W->Add(Wmu140_280BFilter[fIter->first]);
      W->Add(Wmu140_280CFilterBVeto[fIter->first]);
      W->Add(Wmu140_280CVetoBVeto[fIter->first]);
      W->Add(Wmu280_500BFilter[fIter->first]);
      W->Add(Wmu280_500CFilterBVeto[fIter->first]);
      W->Add(Wmu280_500CVetoBVeto[fIter->first]);
      W->Add(Wmu500_1000[fIter->first]);
      W->Add(Wmu70_140BFilter[fIter->first]);
      W->Add(Wmu70_140CFilterBVeto[fIter->first]);
      W->Add(Wmu70_140CVetoBVeto[fIter->first]);
      W->Add(Wtau0_70BFilter[fIter->first]);
      W->Add(Wtau0_70CFilterBVeto[fIter->first]);
      W->Add(Wtau0_70CVetoBVeto[fIter->first]);
      W->Add(Wtau1000[fIter->first]);
      W->Add(Wtau140_280BFilter[fIter->first]);
      W->Add(Wtau140_280CFilterBVeto[fIter->first]);
      W->Add(Wtau140_280CVetoBVeto[fIter->first]);
      W->Add(Wtau280_500BFilter[fIter->first]);
      W->Add(Wtau280_500CFilterBVeto[fIter->first]);
      W->Add(Wtau280_500CVetoBVeto[fIter->first]);
      W->Add(Wtau500_1000[fIter->first]);
      W->Add(Wtau70_140BFilter[fIter->first]);
      W->Add(Wtau70_140CFilterBVeto[fIter->first]);
      W->Add(Wtau70_140CVetoBVeto[fIter->first]);
      W->SetFillColor(kGreen-3);
      W->SetLineWidth(0);

      // inlcusive samples     
      Z = (TH1F*)Z_mumu[fIter->first]->Clone();
      Z->Add(Z_tautau[fIter->first]);
      Z->Add(Z_ee[fIter->first]);
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
    
      Z = (TH1F*)Z_mumu[fIter->first]->Clone();
      Z->Add(Z_tautau[fIter->first]);
      Z->Add(Z_ee[fIter->first]);
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
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
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
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
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
    
    
    // merge for Top _Analysis
    if(option.find("TTbar") != option.npos){
      
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
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
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
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
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
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
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
W = (TH1F*)We0_70BFilter[fIter->first]->Clone();
W->Add(We0_70CFilterBVeto[fIter->first]);
W->Add(We0_70CVetoBVeto[fIter->first]);
W->Add(We1000[fIter->first]);
W->Add(We140_280BFilter[fIter->first]);
W->Add(We140_280CFilterBVeto[fIter->first]);
W->Add(We140_280CVetoBVeto[fIter->first]);
W->Add(We280_500BFilter[fIter->first]);
W->Add(We280_500CFilterBVeto[fIter->first]);
W->Add(We280_500CVetoBVeto[fIter->first]);
W->Add(We500_1000[fIter->first]);
W->Add(We70_140BFilter[fIter->first]);
W->Add(We70_140CFilterBVeto[fIter->first]);
W->Add(We70_140CVetoBVeto[fIter->first]);
W->Add(Wmu0_70BFilter[fIter->first]);
W->Add(Wmu0_70CFilterBVeto[fIter->first]);
W->Add(Wmu0_70CVetoBVeto[fIter->first]);
W->Add(Wmu1000[fIter->first]);
W->Add(Wmu140_280BFilter[fIter->first]);
W->Add(Wmu140_280CFilterBVeto[fIter->first]);
W->Add(Wmu140_280CVetoBVeto[fIter->first]);
W->Add(Wmu280_500BFilter[fIter->first]);
W->Add(Wmu280_500CFilterBVeto[fIter->first]);
W->Add(Wmu280_500CVetoBVeto[fIter->first]);
W->Add(Wmu500_1000[fIter->first]);
W->Add(Wmu70_140BFilter[fIter->first]);
W->Add(Wmu70_140CFilterBVeto[fIter->first]);
W->Add(Wmu70_140CVetoBVeto[fIter->first]);
W->Add(Wtau0_70BFilter[fIter->first]);
W->Add(Wtau0_70CFilterBVeto[fIter->first]);
W->Add(Wtau0_70CVetoBVeto[fIter->first]);
W->Add(Wtau1000[fIter->first]);
W->Add(Wtau140_280BFilter[fIter->first]);
W->Add(Wtau140_280CFilterBVeto[fIter->first]);
W->Add(Wtau140_280CVetoBVeto[fIter->first]);
W->Add(Wtau280_500BFilter[fIter->first]);
W->Add(Wtau280_500CFilterBVeto[fIter->first]);
W->Add(Wtau280_500CVetoBVeto[fIter->first]);
W->Add(Wtau500_1000[fIter->first]);
W->Add(Wtau70_140BFilter[fIter->first]);
W->Add(Wtau70_140CFilterBVeto[fIter->first]);
W->Add(Wtau70_140CVetoBVeto[fIter->first]);

W->SetFillColor(kGreen-3);
W->SetLineWidth(0);

Zee = (TH1F*)Zee0_70BFilter[fIter->first]->Clone();
Zee->Add(Zee0_70CFilterBVeto[fIter->first]);
Zee->Add(Zee0_70CVetoBVeto[fIter->first]);
Zee->Add(Zee1000[fIter->first]);
Zee->Add(Zee140_280BFilter[fIter->first]);
Zee->Add(Zee140_280CFilterBVeto[fIter->first]);
Zee->Add(Zee140_280CVetoBVeto[fIter->first]);
Zee->Add(Zee280_500BFilter[fIter->first]);
Zee->Add(Zee280_500CFilterBVeto[fIter->first]);
Zee->Add(Zee280_500CVetoBVeto[fIter->first]);
Zee->Add(Zee500_1000[fIter->first]);
Zee->Add(Zee70_140BFilter[fIter->first]);
Zee->Add(Zee70_140CFilterBVeto[fIter->first]);
Zee->Add(Zee70_140CVetoBVeto[fIter->first]);
Zee->SetFillColor(kBlue-6);
Zee->SetLineWidth(0);

Zmumu = (TH1F*)Zmumu0_70BFilter[fIter->first]->Clone();
Zmumu->Add(Zmumu0_70CFilterBVeto[fIter->first]);
Zmumu->Add(Zmumu0_70CVetoBVeto[fIter->first]);
Zmumu->Add(Zmumu1000[fIter->first]);
Zmumu->Add(Zmumu140_280BFilter[fIter->first]);
Zmumu->Add(Zmumu140_280CFilterBVeto[fIter->first]);
Zmumu->Add(Zmumu140_280CVetoBVeto[fIter->first]);
Zmumu->Add(Zmumu280_500BFilter[fIter->first]);
Zmumu->Add(Zmumu280_500CFilterBVeto[fIter->first]);
Zmumu->Add(Zmumu280_500CVetoBVeto[fIter->first]);
Zmumu->Add(Zmumu500_1000[fIter->first]);
Zmumu->Add(Zmumu70_140BFilter[fIter->first]);
Zmumu->Add(Zmumu70_140CFilterBVeto[fIter->first]);
Zmumu->Add(Zmumu70_140CVetoBVeto[fIter->first]);
Zmumu->SetFillColor(kPink+9);
Zmumu->SetLineWidth(0);


Ztautau = (TH1F*)Ztautau0_70BFilter[fIter->first]->Clone();
Ztautau->Add(Ztautau0_70CFilterBVeto[fIter->first]);
Ztautau->Add(Ztautau0_70CVetoBVeto[fIter->first]);
Ztautau->Add(Ztautau1000[fIter->first]);
Ztautau->Add(Ztautau140_280BFilter[fIter->first]);
Ztautau->Add(Ztautau140_280CFilterBVeto[fIter->first]);
Ztautau->Add(Ztautau140_280CVetoBVeto[fIter->first]);
Ztautau->Add(Ztautau280_500BFilter[fIter->first]);
Ztautau->Add(Ztautau280_500CFilterBVeto[fIter->first]);
Ztautau->Add(Ztautau280_500CVetoBVeto[fIter->first]);
Ztautau->Add(Ztautau500_1000[fIter->first]);
Ztautau->Add(Ztautau70_140BFilter[fIter->first]);
Ztautau->Add(Ztautau70_140CFilterBVeto[fIter->first]);
Ztautau->Add(Ztautau70_140CVetoBVeto[fIter->first]);
Ztautau->SetFillColor(kRed);
Ztautau->SetLineWidth(0);

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
    
    if(option.find("ZBosonAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(diboson);
      stack->Add(W);
      stack->Add(Z);
    }
    
    
    if(option.find("WBosonAnalysis") != option.npos){
    stack->Add(stop);
    stack->Add(ttbar);
    stack->Add(diboson);
    stack->Add(Z);
    stack->Add(W);
    }


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

    
    if(option.find("TTbar") != option.npos){
      stack->Add(diboson);
      stack->Add(stop);
      stack->Add(V);
      stack->Add(ttbar);
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
      stack->Add(Zee);
      stack->Add(Zmumu);
      stack->Add(Ztautau);
    }



    
    // statistical error histogram
    TH1F* histstack = new TH1F();

    if(option.find("ZBosonAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(Z);
      histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
    }
    
    if(option.find("WBosonAnalysis") != option.npos){
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
  
    if(option.find("TTbar") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(stop);
      histstack->Add(diboson);
      histstack->Add(V);
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
      histstack->Add(Zee);
      histstack->Add(Zmumu);
      histstack->Add(Ztautau);
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




    // set Yaxis maximum
    float yMaxScale = 2.;
    fIter->second->SetMaximum(yMaxScale*TMath::Max( TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()), Higgs_normsig->GetMaximum() ) );
    
    
    // latex options 
    TLatex l;
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.SetTextFont(42);
    l.SetTextSize(0.04);
    
    if(option.find("WBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"W \\rightarrow \\ell\\nu");}
    if(option.find("ZBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z \\rightarrow \\ell\\ell");}
    if(option.find("TTbarAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"t#bar{t} #rightarrow l#nub q#bar{q}b resolved");}
    if(option.find("WZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"WZ \\rightarrow \\ell\\nu \\ell\\ell");}
    if(option.find("ZZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"ZZ \\rightarrow \\ell^{+}\\ell^{-} \\ell^{+}\\ell^{-}");}
    if(option.find("HWWAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow WW^{*} #rightarrow e#nu #mu#nu, N_{jet} #leq 1");}
    if(option.find("HZZAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow ZZ^{*} #rightarrow 4l");}
    if(option.find("ZTauTauAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z #rightarrow #tau_{l}#tau_{h}");}

    
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
      leg-> AddEntry(W,  "W \\rightarrow \\ell\\nu", "f");
      leg-> AddEntry(Z,  "Z \\rightarrow \\ell\\ell", "f");
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
    }

   if(option.find("HZZAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Higgs , "Higgs", "f");
      leg-> AddEntry(Z_Z , "ZZ", "f");
      leg-> AddEntry(V,  "Other", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      if(HIGGSNORMSIG) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");

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
      if(HIGGSNORMSIG) leg-> AddEntry(Higgs_normsig, "Higgs_{norm}" ,"l");

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
      leg-> AddEntry(Ztautau,  "Z #rightarrow #tau#tau", "f");
      leg-> AddEntry(Zmumu,  "Z #rightarrow #mu#mu", "f");
      leg-> AddEntry(Zee,  "Z #rightarrow ee", "f");
//      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }

    
    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");
 
    // draw the normalised signal in the plots
    if(HIGGSNORMSIG){
      if(option.find("HZZAnalysis") != option.npos){Higgs_normsig->Draw("HISTsame");}
      if(option.find("HWWAnalysis") != option.npos){Higgs_normsig->Draw("HISTsame");}
    }

    leg->Draw("same");
    
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
    }


    if(option.find("ZBosonAnalysis") != option.npos){
     pad0->SetLogy(1);
     fIter->second->SetMinimum(100);
     fIter->second->SetMaximum(1e9);
    }

    if(option.find("TTbarAnalysis") != option.npos){
     if(fIter->first.find("mass") == option.npos){
     pad0->SetLogy(1);
     fIter->second->SetMinimum(10);
     fIter->second->SetMaximum(1e8);
     }
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
  
  // uncomment to get plot saved in pdf
  // std::string tpdf = outFolder+"/"+title+".pdf";
  // c1->SaveAs(tpdf.c_str());
  
  return;
}

///
void Plotting::getHistoSettings(){
  
  // save names of the histograms for later  
  hset.clear();
  
  // read in configuration file
  std::string ifile;

  if(option.find("WBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_WBosonAnalysis.txt";}
  if(option.find("ZBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_ZBosonAnalysis.txt";}
  if(option.find("TTbarAnalysis") != option.npos){ifile = "list_histos/HistoList_TTbarAnalysis.txt";}
  if(option.find("WZDiBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_WZDiBosonAnalysis.txt";}
  if(option.find("ZZDiBosonAnalysis") != option.npos){ifile = "list_histos/HistoList_ZZDiBosonAnalysis.txt";}
  if(option.find("HWWAnalysis") != option.npos){ifile = "list_histos/HistoList_HWWAnalysis.txt";}
  if(option.find("HZZAnalysis") != option.npos){ifile = "list_histos/HistoList_HZZAnalysis.txt";}
  if(option.find("ZTauTauAnalysis") != option.npos){ifile = "list_histos/HistoList_ZTauTauAnalysis.txt";}
  

  
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
