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
#define DEBUG 0

// yields flag, set to 1 top print data and MC yields
#define YIELDS 0

// normalised signal flag, set to 1 to add normalised signal to the plots (can be used for Higgs, SingleTop, ZPrime, SUSY)
#define NORMSIG 0

// save to pdf flag, by default plots saved as png
#define SAVEPDF 0

// save to root format flag
#define SAVEROOT 0

//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  
  if(argc < 3){
    std::cout<<"usage: ./plot [ WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, SingleTopAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, ZTauTauAnalysis, HyyAnalysis, SUSYAnalysis, ZPrimeBoostedAnalysis ]  [ location of OutputDir_AnalysisName ]"<<std::endl;
    std::cout<<"output stored in a directory \'histograms\' " <<std::endl;
    exit(1);
  }
  
  Plotting* m = new Plotting();
  
  m->SetLumi(10064); // luminosity set by hand to 10fb-1
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
  if( option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos ) { ifile = "inputfiles/Files_base.txt" ;}
  if(option.find("WBosonAnalysis")        != option.npos || option.find("SingleTopAnalysis") != option.npos)  {   ifile = "inputfiles/Files_WBoson.txt";}
  if(option.find("ZPrimeBoostedAnalysis") != option.npos){   ifile = "inputfiles/Files_ZPrime.txt";}
  if(option.find("HWWAnalysis")           != option.npos){   ifile = "inputfiles/Files_HWW.txt";}
  if(option.find("SUSYAnalysis")          != option.npos){   ifile = "inputfiles/Files_SUSY.txt";}
  if(option.find("HZZAnalysis")           != option.npos){   ifile = "inputfiles/Files_HZZ.txt";}
  if(option.find("ZTauTauAnalysis")       != option.npos){   ifile = "inputfiles/Files_ZTauTau.txt";}
  if(option.find("HyyAnalysis")           != option.npos){   ifile = "inputfiles/Files_Hyy.txt";}
 
  std::cout << "Analysis: " << option << ", reading input from: " << ifile.c_str() << " \n " << std::endl;

  ifstream input(ifile.c_str());
  std::string line;
  while(getline(input,line)){
    if (line.find("#") != line.npos )continue; // a # is a comment and not read
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
  std::cout << "Reading files from: " << readname << " \n " << std::endl;
  
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

  std::cout << "\n" << std::endl;

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
  
  //Higgs to WW
  std::map<std::string,TH1F*> ggH125_WW2lep;
  std::map<std::string,TH1F*> VBFH125_WW2lep;

  //Higgs to ZZ
  std::map<std::string,TH1F*>  ggH125_ZZ4lep;
  std::map<std::string,TH1F*>  ZH125_ZZ4lep;
  std::map<std::string,TH1F*>  WH125_ZZ4lep;
  std::map<std::string,TH1F*>  VBFH125_ZZ4lep;

  // Higgs to photons (yy)
  std::map<std::string,TH1F*>  ggH125_gamgam;
  std::map<std::string,TH1F*> ttH125_gamgam;
  std::map<std::string,TH1F*> VBFH125_gamgam;
  std::map<std::string,TH1F*> WH125_gamgam;
  std::map<std::string,TH1F*> ZH125_gamgam;

  // SUSY sample (pair sleptons)
  std::map<std::string,TH1F*> slep600DM300;

  // Zprime with Z'(1 TeV)->tt sample
  std::map<std::string,TH1F*> ZPrime1000;

  // default top pair production, only single + dilepton decays of ttbar
  std::map<std::string,TH1F*> ttbar_lep;   
  
  // Z boson Powheg samples (one sample per decay flavour) = not supposed to describe well large jet multiplicity regions
  std::map<std::string,TH1F*> Zee;
  std::map<std::string,TH1F*> Zmumu;
  std::map<std::string,TH1F*> Ztautau;
    
  // Diboson Sherpa (WW, WZ, ZZ) 
  std::map<std::string,TH1F*>  WlvZqq; 
  std::map<std::string,TH1F*>  WplvWmqq; 
  std::map<std::string,TH1F*>  WpqqWmlv; 
  std::map<std::string,TH1F*>  ZqqZll; 
  std::map<std::string,TH1F*>  WqqZll; 
  std::map<std::string,TH1F*>  llll;
  std::map<std::string,TH1F*>  lllv;
  std::map<std::string,TH1F*>  llvv;
  std::map<std::string,TH1F*>  lvvv;
  
  // W+jets Powheg samples (one sample per charge and decay flavour) = not supposed to describe well large jet multiplicity regions
  std::map<std::string,TH1F*> Wplusenu;
  std::map<std::string,TH1F*> Wplusmunu;
  std::map<std::string,TH1F*> Wplustaunu;
  std::map<std::string,TH1F*> Wminusenu;
  std::map<std::string,TH1F*> Wminusmunu;
  std::map<std::string,TH1F*> Wminustaunu;
  
  // single top (t, s, tW-channels)
  std::map<std::string,TH1F*> single_top_tchan;
  std::map<std::string,TH1F*> single_antitop_tchan;
  std::map<std::string,TH1F*> single_top_wtchan;
  std::map<std::string,TH1F*> single_antitop_wtchan;
  std::map<std::string,TH1F*> single_top_schan;
  std::map<std::string,TH1F*> single_antitop_schan;
  
 
  // V+jets Sherpa samples (containing leptonic decays of a W or Z bosons with associated jets) = describe well large jet multiplicity, generated with different b- and c-hadron requierements, need to merge all of them int one (done later)
  std::map<std::string,TH1F*>  Wenu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Wenu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Wenu_PTV1000; std::map<std::string,TH1F*>  Wenu_PTV140_280_BFilter; std::map<std::string,TH1F*>  Wenu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Wenu_PTV280_500_BFilter; std::map<std::string,TH1F*>  Wenu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*> Wenu_PTV500_1000; std::map<std::string,TH1F*>  Wenu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Wenu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*>  Wenu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Wmunu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*> Wmunu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV1000; std::map<std::string,TH1F*>  Wmunu_PTV140_280_BFilter; std::map<std::string,TH1F*>  Wmunu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Wmunu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV280_500_BFilter; std::map<std::string,TH1F*> Wmunu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Wmunu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*>  Wmunu_PTV500_1000; std::map<std::string,TH1F*>  Wmunu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Wmunu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*> Wmunu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Wtaunu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV1000; std::map<std::string,TH1F*>  Wtaunu_PTV140_280_BFilter; std::map<std::string,TH1F*> Wtaunu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV280_500_BFilter; std::map<std::string,TH1F*>  Wtaunu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*> Wtaunu_PTV500_1000; std::map<std::string,TH1F*>  Wtaunu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Wtaunu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*>  Wtaunu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Zee_PTV0_70_BFilter; std::map<std::string,TH1F*>  Zee_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*> Zee_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Zee_PTV1000; std::map<std::string,TH1F*>  Zee_PTV140_280_BFilter; std::map<std::string,TH1F*>  Zee_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Zee_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Zee_PTV280_500_BFilter; std::map<std::string,TH1F*> Zee_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*>  Zee_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*>  Zee_PTV500_1000; std::map<std::string,TH1F*>  Zee_PTV70_140_BFilter; std::map<std::string,TH1F*>  Zee_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*> Zee_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu_PTV0_70_BFilter; std::map<std::string,TH1F*>  Zmumu_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*>  Zmumu_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu_PTV1000; std::map<std::string,TH1F*>  Zmumu_PTV140_280_BFilter; std::map<std::string,TH1F*> Zmumu_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Zmumu_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu_PTV280_500_BFilter; std::map<std::string,TH1F*>  Zmumu_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*> Zmumu_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*>  Zmumu_PTV500_1000; std::map<std::string,TH1F*>  Zmumu_PTV70_140_BFilter; std::map<std::string,TH1F*>  Zmumu_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*>  Zmumu_PTV70_140_CVetoBVeto; std::map<std::string,TH1F*> Ztautau_PTV0_70_BFilter; std::map<std::string,TH1F*>  Ztautau_PTV0_70_CFilterBVeto; std::map<std::string,TH1F*>  Ztautau_PTV0_70_CVetoBVeto; std::map<std::string,TH1F*>  Ztautau_PTV1000; std::map<std::string,TH1F*>  Ztautau_PTV140_280_BFilter; std::map<std::string,TH1F*> Ztautau_PTV140_280_CFilterBVeto; std::map<std::string,TH1F*>  Ztautau_PTV140_280_CVetoBVeto; std::map<std::string,TH1F*>  Ztautau_PTV280_500_BFilter; std::map<std::string,TH1F*>  Ztautau_PTV280_500_CFilterBVeto; std::map<std::string,TH1F*> Ztautau_PTV280_500_CVetoBVeto; std::map<std::string,TH1F*>  Ztautau_PTV500_1000; std::map<std::string,TH1F*>  Ztautau_PTV70_140_BFilter; std::map<std::string,TH1F*>  Ztautau_PTV70_140_CFilterBVeto; std::map<std::string,TH1F*>  Ztautau_PTV70_140_CVetoBVeto;
  
  
  ///////////////////////////////////////////////////////////////////////
  // Actual reading of the input files
  // The names must be the same as in Files_***.txt 

  // read data
  data = histo["data"];
  
  // read H->ZZ
  if(option.find("HZZAnalysis") != option.npos){
    ggH125_ZZ4lep = histo["ggH125_ZZ4lep"];
    ZH125_ZZ4lep  = histo["ZH125_ZZ4lep"];
    WH125_ZZ4lep  = histo["WH125_ZZ4lep"];
    VBFH125_ZZ4lep= histo["VBFH125_ZZ4lep"];
  }
  
  // read H->WW (very minor WH and ZH contributions are neglected)
  if(option.find("HWWAnalysis") != option.npos){
    ggH125_WW2lep = histo["ggH125_WW2lep"];
    VBFH125_WW2lep = histo["VBFH125_WW2lep"];
  }

  // read H->yy 
  if(option.find("HyyAnalysis") != option.npos){
    ggH125_gamgam = histo["ggH125_gamgam"];
    ttH125_gamgam = histo["ttH125_gamgam"];;
    VBFH125_gamgam = histo["VBFH125_gamgam"];;
    WH125_gamgam = histo["WH125_gamgam"];;
    ZH125_gamgam = histo["ZH125_gamgam"];;
  }

  // reading ttbar 
  ttbar_lep = histo["ttbar_lep"];
  
  // reading Powheg Z+jets samples, used in HZZ, ZZDiBoson, SingleTop, TTbar, WBoson, ZPrimeBoosted, ZBoson, HWW, WZDiBoson ... analyses 
  if( option.find("HZZAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("HWWAnalysis") != option.npos ||  option.find("ZBosonAnalysis") != option.npos || option.find("ZPrimeBoostedAnalysis") != option.npos || option.find("WBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("SingleTopAnalysis") != option.npos )
    {
      Zee = histo["Zee"];
      Zmumu = histo["Zmumu"];
      Ztautau = histo["Ztautau"];
    }
  
  // reading Powheg W+jets samples, used in HZZ, HWW, ZZDiBoson, WZDiBoson, TTbar, ZBoson, SUSY ... analyses 
  if( option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos) 
    {
      Wplusenu = histo["Wplusenu"];
      Wplusmunu= histo["Wplusmunu"];
      Wplustaunu= histo["Wplustaunu"];  
      Wminusenu= histo["Wminusenu"];
      Wminusmunu= histo["Wminusmunu"];
      Wminustaunu= histo["Wminustaunu"];
    }
  
  // reading Sherpa W+jets samples, used in WBoson, ZTauTau, SingleTop, ZPrimeBoosted ... analyses
  if( option.find("SUSYAnalysis") != option.npos || option.find("ZPrimeBoostedAnalysis") != option.npos || option.find("SingleTopAnalysis") != option.npos || option.find("ZTauTauAnalysis") != option.npos ||   option.find("WBosonAnalysis") != option.npos )
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
  
  // reading Sherpa Z+jets samples, used in ZTaTau and SUSY analyses
  if(option.find("ZTauTauAnalysis") != option.npos ||   option.find("SUSYAnalysis") != option.npos )
    {
      Zee_PTV0_70_BFilter = histo["Zee_PTV0_70_BFilter"];
      Zee_PTV0_70_CFilterBVeto = histo["Zee_PTV0_70_CFilterBVeto"];
      Zee_PTV0_70_CVetoBVeto = histo["Zee_PTV0_70_CVetoBVeto"];
      Zee_PTV1000 = histo["Zee_PTV1000"];
      Zee_PTV140_280_BFilter = histo["Zee_PTV140_280_BFilter"];
      Zee_PTV140_280_CFilterBVeto = histo["Zee_PTV140_280_CFilterBVeto"];
      Zee_PTV140_280_CVetoBVeto = histo["Zee_PTV140_280_CVetoBVeto"];
      Zee_PTV280_500_BFilter = histo["Zee_PTV280_500_BFilter"];
      Zee_PTV280_500_CFilterBVeto = histo["Zee_PTV280_500_CFilterBVeto"];
      Zee_PTV280_500_CVetoBVeto = histo["Zee_PTV280_500_CVetoBVeto"];
      Zee_PTV500_1000 = histo["Zee_PTV500_1000"];
      Zee_PTV70_140_BFilter = histo["Zee_PTV70_140_BFilter"];
      Zee_PTV70_140_CFilterBVeto = histo["Zee_PTV70_140_CFilterBVeto"];
      Zee_PTV70_140_CVetoBVeto = histo["Zee_PTV70_140_CVetoBVeto"];
      Zmumu_PTV0_70_BFilter = histo["Zmumu_PTV0_70_BFilter"];
      Zmumu_PTV0_70_CFilterBVeto = histo["Zmumu_PTV0_70_CFilterBVeto"];
      Zmumu_PTV0_70_CVetoBVeto = histo["Zmumu_PTV0_70_CVetoBVeto"];
      Zmumu_PTV1000 = histo["Zmumu_PTV1000"];
      Zmumu_PTV140_280_BFilter = histo["Zmumu_PTV140_280_BFilter"];
      Zmumu_PTV140_280_CFilterBVeto = histo["Zmumu_PTV140_280_CFilterBVeto"];
      Zmumu_PTV140_280_CVetoBVeto = histo["Zmumu_PTV140_280_CVetoBVeto"];
      Zmumu_PTV280_500_BFilter = histo["Zmumu_PTV280_500_BFilter"];
      Zmumu_PTV280_500_CFilterBVeto = histo["Zmumu_PTV280_500_CFilterBVeto"];
      Zmumu_PTV280_500_CVetoBVeto = histo["Zmumu_PTV280_500_CVetoBVeto"];
      Zmumu_PTV500_1000 = histo["Zmumu_PTV500_1000"];
      Zmumu_PTV70_140_BFilter = histo["Zmumu_PTV70_140_BFilter"];
      Zmumu_PTV70_140_CFilterBVeto = histo["Zmumu_PTV70_140_CFilterBVeto"];
      Zmumu_PTV70_140_CVetoBVeto = histo["Zmumu_PTV70_140_CVetoBVeto"];
      Ztautau_PTV0_70_BFilter = histo["Ztautau_PTV0_70_BFilter"];
      Ztautau_PTV0_70_CFilterBVeto = histo["Ztautau_PTV0_70_CFilterBVeto"];
      Ztautau_PTV0_70_CVetoBVeto = histo["Ztautau_PTV0_70_CVetoBVeto"];
      Ztautau_PTV1000 = histo["Ztautau_PTV1000"];
      Ztautau_PTV140_280_BFilter = histo["Ztautau_PTV140_280_BFilter"];
      Ztautau_PTV140_280_CFilterBVeto = histo["Ztautau_PTV140_280_CFilterBVeto"];
      Ztautau_PTV140_280_CVetoBVeto = histo["Ztautau_PTV140_280_CVetoBVeto"];
      Ztautau_PTV280_500_BFilter = histo["Ztautau_PTV280_500_BFilter"];
      Ztautau_PTV280_500_CFilterBVeto = histo["Ztautau_PTV280_500_CFilterBVeto"];
      Ztautau_PTV280_500_CVetoBVeto = histo["Ztautau_PTV280_500_CVetoBVeto"];
      Ztautau_PTV500_1000 = histo["Ztautau_PTV500_1000"];
      Ztautau_PTV70_140_BFilter = histo["Ztautau_PTV70_140_BFilter"];
      Ztautau_PTV70_140_CFilterBVeto = histo["Ztautau_PTV70_140_CFilterBVeto"];
      Ztautau_PTV70_140_CVetoBVeto = histo["Ztautau_PTV70_140_CVetoBVeto"];
    }
  
  
  // reading diboson samples, used in all analyses
  WlvZqq= histo["WlvZqq"];
  WplvWmqq= histo["WplvWmqq"];
  WpqqWmlv= histo["WpqqWmlv"];
  ZqqZll= histo["ZqqZll"];
  WqqZll= histo["WqqZll"];
  llll= histo["llll"];
  lllv= histo["lllv"];
  llvv= histo["llvv"];
  lvvv= histo["lvvv"];
  
  // special SUSY sample
  if( option.find("SUSYAnalysis") != option.npos )
    {
      slep600DM300 = histo["slep600DM300"];
    }
 
  // special Zprime sample
  if(option.find("ZPrimeBoostedAnalysis") != option.npos){
      ZPrime1000 = histo["ZPrime1000_tt"];
  }
  
  // reading single top samples, used in all analyses
  single_top_tchan= histo["single_top_tchan"];
  single_antitop_tchan= histo["single_antitop_tchan"];
  single_top_wtchan= histo["single_top_wtchan"];
  single_antitop_wtchan= histo["single_antitop_wtchan"];
  single_top_schan= histo["single_top_schan"];
  single_antitop_schan= histo["single_antitop_schan"];  
  

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
    // some options for Hyy
    if(option.find("HyyAnalysis") != option.npos) TGaxis::SetMaxDigits(3);
    fIter->second->GetYaxis()->SetTitleOffset(1.2);
    if(!(option.find("HyyAnalysis") != option.npos))  fIter->second->Draw("E1");
    if(option.find("HyyAnalysis") != option.npos){
      fIter->second->Draw("E");
      gStyle->SetEndErrorSize(0.);
      gStyle->SetErrorX(0.0);
    }

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

    // merge for HWW _Analysis
    if(option.find("HWWAnalysis") != option.npos){
      
      Higgs = (TH1F*)ggH125_WW2lep[fIter->first]->Clone();
      Higgs->Add(VBFH125_WW2lep[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);

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
      diboson->Scale(1.3); //normalisation scaling, from WW control region we need a factor of 1.3, underestimation of WZ cross section requires a normalisation factor of 1.15-1.2, also contributions with misidentified leptons are not estimated nor added => a total of 1.3 is taken

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
 
      Z = (TH1F*)Zee_PTV0_70_BFilter[fIter->first]->Clone();
      Z->Add(Zee_PTV0_70_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV0_70_CVetoBVeto[fIter->first]);
      Z->Add(Zee_PTV1000[fIter->first]);
      Z->Add(Zee_PTV140_280_BFilter[fIter->first]);
      Z->Add(Zee_PTV140_280_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV140_280_CVetoBVeto[fIter->first]);
      Z->Add(Zee_PTV280_500_BFilter[fIter->first]);
      Z->Add(Zee_PTV280_500_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV280_500_CVetoBVeto[fIter->first]);
      Z->Add(Zee_PTV500_1000[fIter->first]);
      Z->Add(Zee_PTV70_140_BFilter[fIter->first]);
      Z->Add(Zee_PTV70_140_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV70_140_CVetoBVeto[fIter->first]);
      
      Z->Add(Zmumu_PTV0_70_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV0_70_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV0_70_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV1000[fIter->first]);
      Z->Add(Zmumu_PTV140_280_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV140_280_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV140_280_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV280_500_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV280_500_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV280_500_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV500_1000[fIter->first]);
      Z->Add(Zmumu_PTV70_140_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV70_140_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV70_140_CVetoBVeto[fIter->first]);
      
      Z->Add(Ztautau_PTV0_70_BFilter[fIter->first]);
      Z->Add(Ztautau_PTV0_70_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau_PTV0_70_CVetoBVeto[fIter->first]);
      Z->Add(Ztautau_PTV1000[fIter->first]);
      Z->Add(Ztautau_PTV140_280_BFilter[fIter->first]);
      Z->Add(Ztautau_PTV140_280_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau_PTV140_280_CVetoBVeto[fIter->first]);
      Z->Add(Ztautau_PTV280_500_BFilter[fIter->first]);
      Z->Add(Ztautau_PTV280_500_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau_PTV280_500_CVetoBVeto[fIter->first]);
      Z->Add(Ztautau_PTV500_1000[fIter->first]);
      Z->Add(Ztautau_PTV70_140_BFilter[fIter->first]);
      Z->Add(Ztautau_PTV70_140_CFilterBVeto[fIter->first]);
      Z->Add(Ztautau_PTV70_140_CVetoBVeto[fIter->first]);
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

    // merging for HZZ
    if(option.find("HZZAnalysis") != option.npos){

      // merge all minor bkgs
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
      V->Add(WplvWmqq[fIter->first]); // WW
      V->Add(WpqqWmlv[fIter->first]); // WW
      V->Add(lllv[fIter->first]);  // // W->lv Z->ll
      V->Add(lvvv[fIter->first]); // W->lv Z->vv
      V->Add(WqqZll[fIter->first]); // W->qq Z->ll
      V->Add(WlvZqq[fIter->first]);  // W->lv Z->qq
      V->SetFillColor(kBlue-6);
      V->SetLineWidth(0);

      // only ZZ
      Z_Z = (TH1F*)llll[fIter->first]->Clone(); // Z->ll Z->ll
      Z_Z->Add(ZqqZll[fIter->first]); // Z->qq Z->ll
      Z_Z->Add(llvv[fIter->first]); // Z->ll Z->vv
      Z_Z->SetFillColor(kAzure+8);
      Z_Z->SetLineWidth(0);
      Z_Z->Scale(1.3); // loop-induced gluon–gluon gg->ZZ is not included in the current MCs

      Higgs = (TH1F*)ggH125_ZZ4lep[fIter->first]->Clone();
      Higgs->Add(ZH125_ZZ4lep[fIter->first]);
      Higgs->Add(WH125_ZZ4lep[fIter->first]);
      Higgs->Add(VBFH125_ZZ4lep[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);

    }

    // merge for ZTauTauAnalysis
    if(option.find("ZTauTauAnalysis") != option.npos){

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

      // single top
      stop = (TH1F*)single_top_tchan[fIter->first]->Clone();
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->Add(single_top_schan[fIter->first]);
      stop->Add(single_antitop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

      // merge minor bkgs
      topV = (TH1F*)ttbar->Clone();
      topV->Add(stop);
      topV->Add(diboson);
      topV->SetFillColor(kOrange-3);
      topV->SetLineWidth(0);

      // sliced Sherpa W+jets samples
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

      // sliced Sherpa Z+jets samples
      // merge Z->ee and Z->mumu
      Z = (TH1F*)Zee_PTV0_70_BFilter[fIter->first]->Clone();
      Z->Add(Zee_PTV0_70_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV0_70_CVetoBVeto[fIter->first]);
      Z->Add(Zee_PTV1000[fIter->first]);
      Z->Add(Zee_PTV140_280_BFilter[fIter->first]);
      Z->Add(Zee_PTV140_280_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV140_280_CVetoBVeto[fIter->first]);
      Z->Add(Zee_PTV280_500_BFilter[fIter->first]);
      Z->Add(Zee_PTV280_500_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV280_500_CVetoBVeto[fIter->first]);
      Z->Add(Zee_PTV500_1000[fIter->first]);
      Z->Add(Zee_PTV70_140_BFilter[fIter->first]);
      Z->Add(Zee_PTV70_140_CFilterBVeto[fIter->first]);
      Z->Add(Zee_PTV70_140_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV0_70_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV0_70_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV0_70_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV1000[fIter->first]);
      Z->Add(Zmumu_PTV140_280_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV140_280_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV140_280_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV280_500_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV280_500_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV280_500_CVetoBVeto[fIter->first]);
      Z->Add(Zmumu_PTV500_1000[fIter->first]);
      Z->Add(Zmumu_PTV70_140_BFilter[fIter->first]);
      Z->Add(Zmumu_PTV70_140_CFilterBVeto[fIter->first]);
      Z->Add(Zmumu_PTV70_140_CVetoBVeto[fIter->first]);
      Z->SetFillColor(kPink+9);
      Z->SetLineWidth(0);

      // Z->tau tau      
      Z_tautau = (TH1F*)Ztautau_PTV0_70_BFilter[fIter->first]->Clone();
      Z_tautau->Add(Ztautau_PTV0_70_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV0_70_CVetoBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV1000[fIter->first]);
      Z_tautau->Add(Ztautau_PTV140_280_BFilter[fIter->first]);
      Z_tautau->Add(Ztautau_PTV140_280_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV140_280_CVetoBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV280_500_BFilter[fIter->first]);
      Z_tautau->Add(Ztautau_PTV280_500_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV280_500_CVetoBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV500_1000[fIter->first]);
      Z_tautau->Add(Ztautau_PTV70_140_BFilter[fIter->first]);
      Z_tautau->Add(Ztautau_PTV70_140_CFilterBVeto[fIter->first]);
      Z_tautau->Add(Ztautau_PTV70_140_CVetoBVeto[fIter->first]);
      Z_tautau->SetFillColor(kAzure+7);
      Z_tautau->SetLineWidth(0);
     
     }

    // merge for HyyAnalysis
    if(option.find("HyyAnalysis") != option.npos){
      Higgs = (TH1F*)ggH125_gamgam[fIter->first]->Clone();
      Higgs->Add(ttH125_gamgam[fIter->first]);
      Higgs->Add(VBFH125_gamgam[fIter->first]);
      Higgs->Add(WH125_gamgam[fIter->first]);
      Higgs->Add(ZH125_gamgam[fIter->first]);
      Higgs->SetLineColor(kBlack);
      Higgs->SetLineWidth(2);
    }

    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // main stack of MCs
    THStack* stack = new THStack();
   
    // statistical error histogram
    TH1F* histstack = new TH1F();
      
    // The order of the stack defines which samples will appear on top of each other
    if(option.find("WBosonAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(diboson);
      stack->Add(Z);
      stack->Add(W);
    
      histstack = (TH1F*)ttbar->Clone();
      histstack->Add(Z);
      histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
    }
    
    if(option.find("TTbarAnalysis") != option.npos || option.find("ZPrimeBoostedAnalysis") != option.npos){
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
   
    if(option.find("ZBosonAnalysis") != option.npos){
      stack->Add(W);
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(diboson);
      stack->Add(Z);

      histstack = (TH1F*)ttbar->Clone();
      histstack->Add(Z);
      histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
    }

    if(option.find("WZDiBosonAnalysis") != option.npos){
      stack->Add(top);
      stack->Add(V);
      stack->Add(VV);
      stack->Add(W_Z);

      histstack = (TH1F*)top->Clone();
      histstack->Add(V);
      histstack->Add(VV);
      histstack->Add(W_Z);
    }

    if(option.find("ZZDiBosonAnalysis") != option.npos){
      stack->Add(topV);
      stack->Add(WWZ);
      stack->Add(Z_Z);

      histstack = (TH1F*)topV->Clone();
      histstack->Add(WWZ);
      histstack->Add(Z_Z);
    }
  
    if(option.find("HZZAnalysis") != option.npos){
      stack->Add(V);
      stack->Add(Z_Z);
      stack->Add(Higgs);

      histstack = (TH1F*)V->Clone();
      histstack->Add(Higgs);
      histstack->Add(Z_Z);
    }
    
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

   if(option.find("SUSYAnalysis") != option.npos){
      stack->Add(W);
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(diboson);
      stack->Add(Z);

      histstack = (TH1F*)ttbar->Clone();
      histstack->Add(Z);
      histstack->Add(diboson);
      histstack->Add(W);
      histstack->Add(stop);
    }
    
    if(option.find("HyyAnalysis") != option.npos){
      stack->Add(Higgs);
      histstack = (TH1F*)Higgs->Clone();
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
      Higgs_normsig = (TH1F*)Higgs->Clone();
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
    
    if(option.find("WBosonAnalysis")    != option.npos){l.DrawLatex(0.18,0.71,"W #rightarrow l#nu");}
    if(option.find("TTbarAnalysis")     != option.npos){l.DrawLatex(0.18,0.71,"t#bar{t} #rightarrow l#nub q#bar{q}b");}
    if(option.find("SingleTopAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"t #rightarrow l#nub + q");}
    if(option.find("ZPrimeBoostedAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z' #rightarrow t#bar{t} (boosted)");}
    if(option.find("ZBosonAnalysis")    != option.npos){l.DrawLatex(0.18,0.71,"Z #rightarrow l^{+}l^{-}");}
    if(option.find("HWWAnalysis")       != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow WW* #rightarrow e#nu #mu#nu, N_{jet} #leq 1");}
    if(option.find("WZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"WZ #rightarrow l#nu ll");}
    if(option.find("ZZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"ZZ #rightarrow l^{+}l^{-} l^{+}l^{-}");}
    if(option.find("HZZAnalysis")       != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow ZZ* #rightarrow 4l");}
    if(option.find("ZTauTauAnalysis")   != option.npos){l.DrawLatex(0.18,0.71,"Z #rightarrow #tau_{l}#tau_{h}");}

    if(option.find("SUSYAnalysis")      != option.npos){
        if(fIter->first.find("SR_loose") != option.npos) l.DrawLatex(0.18,0.71,"2l + 0 jets, SR loose");
	else if(fIter->first.find("SR_tight") != option.npos) l.DrawLatex(0.18,0.71,"2l + 0 jets, SR tight");
	else l.DrawLatex(0.18,0.71,"2l + 0 jets");
    }

    if(option.find("HyyAnalysis")       != option.npos){
        if(fIter->first.find("_cat_") != option.npos) l.DrawLatex(0.18,0.71,"H #rightarrow #gamma #gamma, unconv. central");
        else l.DrawLatex(0.18,0.71,"H #rightarrow #gamma #gamma");
    }

    TLatex l2;
    l2.SetNDC();
    l2.SetTextSize(0.04);  
    l2.SetTextColor(kBlack);
    l2.DrawLatex(0.18,0.79, Form("#sqrt{s} = 13 TeV, 10 fb^{-1}")); 
    
    
    //create legend
    TLegend* leg;
    leg  = new TLegend();
    leg  = new TLegend(0.70,0.50,0.93,0.925);
    if(option.find("HyyAnalysis")       != option.npos) leg  = new TLegend(0.60,0.45,0.93,0.825);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(32);
    leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetMargin(0.22);
    leg->SetTextAlign(32);
    
    // fill legend depending on the analysis, the order reflects the stack order

    if(option.find("ZBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z,  "Z #rightarrow l^{+}l^{-}", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  Z: " << Z->Integral()  << 
              ",  W: " << W->Integral()  <<
              ",  diboson: " << diboson->Integral()  <<
              ",  ttbar: " << ttbar ->Integral()  <<
              ",  stop: " <<  stop->Integral()  <<
              ",  Total pred.: "<< diboson->Integral() + W->Integral() + Z->Integral() + ttbar ->Integral() + stop->Integral() <<
              endl;
      }
    }

    // ------------------------------------------------------- //
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

    // ------------------------------------------------------- //	
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
    
    // ------------------------------------------------------- // 
    if(option.find("ZZDiBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z_Z , "ZZ", "f");
      leg-> AddEntry(WWZ , "WW,WZ", "f");
      leg-> AddEntry(topV,  "Other", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  ZZ: " <<  Z_Z->Integral()  <<
              ",  WW, WZ: " <<  WWZ->Integral()  <<
              ",  top, single top, V+jets: " << topV->Integral()  <<
              ",  Total pred.: "<< WWZ->Integral() + Z_Z->Integral() + topV->Integral()  <<
                endl;
      }

    }

    // ------------------------------------------------------- //    
    if(option.find("WZDiBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(W_Z , "WZ", "f");
      leg-> AddEntry(VV , "ZZ,WW", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(top, "Other", "f"); // ttbar + single top
      leg-> AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  WZ: " << W_Z->Integral()  << 
              ",  ZZ,WW: " << VV->Integral()  <<
              ",  V+jets: " << V ->Integral()  <<
              ",  ttbar+stop: " <<  top->Integral()  <<
              ",  Total pred.: "<< W_Z->Integral() + VV->Integral() + V->Integral() + top->Integral() <<
              endl;
      }
      
    }

    // ------------------------------------------------------- //   
    if(option.find("TTbarAnalysis") != option.npos || option.find("ZPrimeBoostedAnalysis") != option.npos ) {
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

    // ------------------------------------------------------- //    
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
    if(option.find("SUSYAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z,  "Z+jets", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(W,  "W+jets", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");

      if(YIELDS){
              cout << "Yields:" << "Data: " << data[fIter->first]->Integral() <<
              ",  diboson: " << diboson->Integral()  <<
              ",  Z+jets: " << Z->Integral()  <<
              ",  W+jets: " << W->Integral()  <<
              ",  single top: " <<  stop->Integral()  <<
              ",  ttbar: " <<  ttbar->Integral()  <<
              ",  Total pred.: "<< diboson->Integral() + Z->Integral() + W->Integral() + ttbar->Integral() + stop->Integral() <<
                endl;
      }
    }

    //////////////////////////////////////////////////////////////
        
    // only for SUSY
    TLegend* leg2;     leg2  = new TLegend();              leg2  = new TLegend(0.45,0.45,0.93,0.50);
    leg2->SetFillStyle(0);     leg2->SetBorderSize(0);     leg2->SetTextAlign(32);
    leg2->SetTextFont(42);     leg2->SetTextSize(0.05);    leg2->SetMargin(0.22);     leg2->SetTextAlign(32);
    if(option.find("SUSYAnalysis") != option.npos) if(NORMSIG) leg2-> AddEntry(slep600DM300_normsig, "m(#tilde{l},#chi^{0}_{1})=(600,300) GeV" ,"l");

    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");
    
    // draw the normalised signal in the plots
    if(NORMSIG){
      if(option.find("HZZAnalysis")          != option.npos){Higgs_normsig->Draw("HISTsame");}
      if(option.find("HWWAnalysis")          != option.npos){if(fIter->first.find("histI") != option.npos)Higgs_normsig->Draw("HISTsame");}
      if(option.find("SingleTopAnalysis")    != option.npos){stop_normsig->Draw("HISTsame");}
      if(option.find("SUSYAnalysis")         != option.npos){slep600DM300_normsig->Draw("HISTsame"); leg2->Draw("same");}
      if(option.find("ZPrimeBoostedAnalysis")!= option.npos){if(fIter->first.find("LR") != option.npos) ZPrime_normsig->Draw("HISTsame"); }
    }
    

    // ------------------------------------------------------- //
    // for Hyy case, we only have data and Higgs MC
    if(option.find("HyyAnalysis") != option.npos){

      // print expected yields
      if(YIELDS){  
      cout << "Expected signal events (ggH): " <<   ggH125_gamgam[fIter->first]->Integral() <<  endl;
      cout << "Expected signal events (VBF): " <<   VBFH125_gamgam[fIter->first]->Integral() <<  endl;
      cout << "Expected signal events (WH): " <<    WH125_gamgam[fIter->first]->Integral() <<  endl;
      cout << "Expected signal events (ZH): " <<    ZH125_gamgam[fIter->first]->Integral() <<  endl;
      cout << "Expected signal events (ttH): " <<   ttH125_gamgam[fIter->first]->Integral() <<  endl;
      cout << "Expected signal events (all): " <<   Higgs->Integral() <<  endl;
      }

 
      // The signal distribution is empirically modeled as a single Gaussian in the mass window 120 - 130 GeV
      // In case you want to run this fit, do:
      //Higgs->Fit("gaus" ,"","",120.,130.);

      // The total fit function is then the sum of Higgs signal (Gauss) and background (polynomial)
      cout << " === Fitting a 3rd-order polynomial + Gaussian to data == " << endl;
      fit = new TF1("fit", "([0]+[1]*x+[2]*x^2+[3]*x^3)+[4]*exp(-0.5*((x-[5])/[6])^2)", 105, 160);

      // We set the values of the fitted parameters from Gaussian fit
      fit->FixParameter(5,125.0); // always fixed to 125 GeV

      if(fIter->first.find("mYY_bin1") != option.npos){
        fit->FixParameter(4,119.1); // this value was obtained from the Gaussian fit
        fit->FixParameter(6,2.38);  // this value was obtained from the Gaussian fit
      }
      if(fIter->first.find("mYY_cat_bin1") != option.npos){
        fit->FixParameter(4,23.2); // this value was obtained from the Gaussian fit
        fit->FixParameter(6,1.83);  // this value was obtained from the Gaussian fit
      }

      // here we are finally fitting 
      data[fIter->first]->Fit("fit","","same:e",105.,160.);
      TF1 *fitresult = data[fIter->first]->GetFunction("fit");
      cout << "Chi2/NDF: "<< fitresult->GetChisquare() / fitresult->GetNDF() << endl;
      cout << " ================================ " << endl;

      // The functional form to model the background distribution is chosen to be a third-order polynomial restricted to 105 < m(yy) < 160 GeV
      bgd = new TF1("bgd", "([0]+[1]*x+[2]*x^2+[3]*x^3)", 105, 160);
      // we build it using the parameters from the previous fit
      bgd->SetParameter(0,fit->GetParameter(0));
      bgd->SetParameter(1,fit->GetParameter(1));
      bgd->SetParameter(2,fit->GetParameter(2));
      bgd->SetParameter(3,fit->GetParameter(3));

      // set plots style
      bgd->SetLineColor(4);
      bgd->SetLineStyle(2);
      bgd->SetLineWidth(2);
      bgd->Draw("same");
 
      fit->SetLineColor(2);
      fit->SetLineStyle(1);
      fit->SetLineWidth(2);
      fit->Draw("same:e");

      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(bgd ,   "Background", "l");
      leg-> AddEntry(fit ,   "Signal + bkg", "l");
      leg-> AddEntry(Higgs , "Signal", "l");

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
   
    if(option.find("HyyAnalysis") != option.npos){
      // create the rest plot
      h_ratio->Add(bgd,-1);
      h_ratio->GetYaxis()->SetTitle("Data - bkg      ");
   
      float errore;
      int nbine = data[fIter->first]->GetNbinsX();
      for(int i_bin=0;i_bin<=nbine;i_bin++){
        errore = data[fIter->first]->GetBinError(i_bin);
        h_ratio->SetBinError(i_bin, errore);
      } 

      TH1F *copy_fit = new TH1F("copy_fit","copy_fit",5500,105,160); //  smooth
      copy_fit->Eval(fit);
      copy_fit->SetLineColor(2);
      copy_fit->SetLineStyle(1);
      copy_fit->SetLineWidth(2);

      h_ratio2 = (TH1F*)copy_fit->Clone("h_ratio2");
      h_ratio2->Add(bgd,-1);
      delete copy_fit;
    }

    // add a line in 1
    TLine *hline;
    hline = new TLine(h_ratio->GetXaxis()->GetXmin(),1,h_ratio->GetXaxis()->GetXmax(),1);
    hline->SetLineColor(kGray+2);
    hline->SetLineWidth(2);
    hline->SetLineStyle(1);

    if(option.find("HyyAnalysis") != option.npos){
      hline = new TLine(h_ratio->GetXaxis()->GetXmin(),0,h_ratio->GetXaxis()->GetXmax(),0);
      hline->SetLineColor(4);
      hline->SetLineWidth(2);
      hline->SetLineStyle(2);
    }

    gStyle->SetEndErrorSize(1.);
    h_ratio->GetYaxis()->CenterTitle();
    h_ratio->GetYaxis()->SetNdivisions(504,false);
    if(option.find("HyyAnalysis") != option.npos)     h_ratio->GetYaxis()->SetNdivisions(503,false);

    h_ratio->Draw("0E1");
    hline->Draw();

    // cosmetics
    h_ratio->SetMinimum(0);
    h_ratio->SetMaximum(2);
    if(option.find("HyyAnalysis") != option.npos){
        if(fIter->first.find("_cat_") != option.npos){ h_ratio->SetMinimum(-30);      h_ratio->SetMaximum(60); }
	else{    h_ratio->SetMinimum(-125);      h_ratio->SetMaximum(250); }
    }

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
    if(option.find("HyyAnalysis") != option.npos) h_ratio2->Draw("SAME");

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

    if(option.find("WBosonAnalysis") != option.npos){
      pad0->SetLogy(1);
      fIter->second->SetMinimum(100);
      fIter->second->SetMaximum(1e12);
      if(fIter->first.find("leptch") != option.npos)      fIter->second->SetMaximum(1e14);
    }

    if(option.find("ZBosonAnalysis") != option.npos){
     pad0->SetLogy(1);
     fIter->second->SetMinimum(30);
     fIter->second->SetMaximum(1e10);
     if(fIter->first.find("leptch") != option.npos)      fIter->second->SetMaximum(1e12);
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
      if(fIter->first.find("SFOS") != option.npos){
        pad0->SetLogy(1);
        fIter->second->SetMinimum(10);
        fIter->second->SetMaximum(1e11);
      }
      if(fIter->first.find("SR") != option.npos){
        pad0->SetLogy(1);
        fIter->second->SetMinimum(0.02);
        fIter->second->SetMaximum(1e5);
      }
    }

    if(option.find("HZZAnalysis") != option.npos)
    {
     if(fIter->first.find("mLL1") != option.npos) fIter->second->SetMaximum(150);
     if(fIter->first.find("mLL2") != option.npos) fIter->second->SetMaximum(100);
     if(fIter->first.find("mass_four") != option.npos) fIter->second->SetMaximum(35);
     if(fIter->first.find("mass_ext") != option.npos) fIter->second->SetMaximum(40);
    }

    if(option.find("HyyAnalysis") != option.npos){
      if(fIter->first.find("bin1") != option.npos) { 
        if(fIter->first.find("_cat_") != option.npos){ fIter->second->SetMaximum(1000);}
	else fIter->second->SetMaximum(8e3);
      }
      if(fIter->first.find("bin2") != option.npos) {
	     if(fIter->first.find("_cat_") != option.npos){fIter->second->SetMaximum(500);}
	     else 	      fIter->second->SetMaximum(4500);
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
  if( option.find("ZPrimeBoostedAnalysis") != option.npos ||  option.find("SingleTopAnalysis") != option.npos || option.find("ZTauTauAnalysis") != option.npos ||  option.find("WBosonAnalysis") != option.npos ||  option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("HyyAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos || option.find("SUSYAnalysis") != option.npos) cout << "Analysis option found, proceeding..." << endl;
  else { cout << "Analysis option not found! \n usage: ./plot [ WBosonAnalysis, ZBosonAnalysis, TTbarAnalysis, SingleTopAnalysis, WZDiBosonAnalysis, ZZDiBosonAnalysis, HWWAnalysis, HZZAnalysis, ZTauTauAnalysis, HyyAnalysis, SUSYAnalysis, ZPrimeBoostedAnalysis ]  [ location of OutputDir_AnalysisName ] \n " << endl; exit(1);}

 
  // save names of the histograms for later  
  hset.clear();
  
  // read in configuration file
  std::string ifile;

  if(option.find("WBosonAnalysis")        != option.npos){ifile = "list_histos/HistoList_WBosonAnalysis.txt";}
  if(option.find("TTbarAnalysis")         != option.npos){ifile = "list_histos/HistoList_TTbarAnalysis.txt";}
  if(option.find("SingleTopAnalysis")     != option.npos){ifile = "list_histos/HistoList_SingleTopAnalysis.txt";}
  if(option.find("ZPrimeBoostedAnalysis") != option.npos){ifile = "list_histos/HistoList_ZPrimeBoostedAnalysis.txt";}
  if(option.find("ZBosonAnalysis")        != option.npos){ifile = "list_histos/HistoList_ZBosonAnalysis.txt";}
  if(option.find("HWWAnalysis")           != option.npos){ifile = "list_histos/HistoList_HWWAnalysis.txt";}
  if(option.find("SUSYAnalysis")          != option.npos){ifile = "list_histos/HistoList_SUSYAnalysis.txt";}
  if(option.find("WZDiBosonAnalysis")     != option.npos){ifile = "list_histos/HistoList_WZDiBosonAnalysis.txt";}
  if(option.find("ZZDiBosonAnalysis")     != option.npos){ifile = "list_histos/HistoList_ZZDiBosonAnalysis.txt";}
  if(option.find("HZZAnalysis")           != option.npos){ifile = "list_histos/HistoList_HZZAnalysis.txt";}
  if(option.find("ZTauTauAnalysis")       != option.npos){ifile = "list_histos/HistoList_ZTauTauAnalysis.txt";}
  if(option.find("HyyAnalysis")           != option.npos){ifile = "list_histos/HistoList_HyyAnalysis.txt";}

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
