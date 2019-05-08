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

// include main header
#include "Plotting.h"

// debugging flag, set to 1 for checks
#define DEBUG 0


//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
  
  if(argc < 3){
    std::cout<<"usage: ./plot [WBosonAnalysis,ZBosonAnalysis,TTbarAnalysis,WZDiBosonAnalysis,ZZDiBosonAnalysis,HZZAnalysis]  [location of OutputDir_AnalysisName]"<<std::endl;
    std::cout<<"output stored in a directory \'histograms\' " <<std::endl;
    exit(1);
  }
  
  Plotting* m = new Plotting();
  
  m->SetLumi(10000); // luminosity set by hand to 10fb-1
  m->SetOption(argv[1]);
  m->SetInputLocation(argv[2]);
  
  string option = argv[1];
  if(option.find("WBosonAnalysis") != option.npos ||  option.find("ZBosonAnalysis") != option.npos || option.find("TTbarAnalysis") != option.npos || option.find("WZDiBosonAnalysis") != option.npos ||  option.find("ZZDiBosonAnalysis") != option.npos || option.find("HWWAnalysis") != option.npos || option.find("ZPrimeAnalysis") != option.npos || option.find("HZZAnalysis") != option.npos) cout << "Analysis option found, proceeding..." << endl;
  else { cout << "Analysis option not found! \n usage: ./plot [WBosonAnalysis,ZBosonAnalysis,TTbarAnalysis,WZDiBosonAnalysis,ZZDiBosonAnalysis,HWWAnalysis,ZPrimeAnalysis,HZZAnalysis]  [location of OutputDir_AnalysisName] \n " << endl; exit(1);}
  
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
  if (option.find("ZPrimeAnalysis") != option.npos){
    std::cout<<"===== NOT supported yet!!! ====="<<std::endl;
  }
  if (option.find("ZBosonAnalysis") != option.npos){
    std::cout<<"=====processing ZBosonAnalysis====="<<std::endl;
  }
  if (option.find("TTbarAnalysis") != option.npos){
    std::cout<<"=====processing TTbarAnalysis====="<<std::endl;
  }
  if (option.find("WZDiBosonAnalysis") != option.npos){
    std::cout<<"=====processing WZDiBosonAnalysis====="<<std::endl;
  }
  if (option.find("ZZDiBosonAnalysis") != option.npos){
    std::cout<<"=====processing ZZDiBosonAnalysis====="<<std::endl;
  }
  if (option.find("HWWAnalysis") != option.npos){
    std::cout<<"===== NOT supported yet!!! ====="<<std::endl;
  }
  if (option.find("HZZAnalysis") != option.npos){
    std::cout<<"=====processing HZZAnalysis====="<<std::endl;
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
        if (DEBUG) cout << " SF is: " << scf << endl;
        for(; fIter!=lIter;++fIter){
	  if (DEBUG) std::cout<<"Scaling histogram: "<< fIter->first << std::endl;
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
  
  std::map<std::string,TH1F*> ZPrime1000;
  
  
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

  Wplusenu = histo["Wplusenu"];
  Wplusmunu= histo["Wplusmunu"];
  Wplustaunu= histo["Wplustaunu"];  
  Wminusenu= histo["Wminusenu"];
  Wminusmunu= histo["Wminusmunu"];
  Wminustaunu= histo["Wminustaunu"];

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
 

  /*
  ZPrime1000 = histo["ZPrime1000"];
  */

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
    TH1F* ZPrime = new TH1F();
    
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
     
      stop = (TH1F*)single_top_wtchan[fIter->first]->Clone();
      stop->Add(single_antitop_wtchan[fIter->first]);
      //stop->Add(single_top_tchan[fIter->first]);
      //stop->Add(single_antitop_tchan[fIter->first]);
      //stop->Add(single_top_wtchan[fIter->first]);
      //stop->Add(single_antitop_wtchan[fIter->first]);
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

      stop = (TH1F*)single_top_schan[fIter->first]->Clone();
      stop->Add(single_antitop_schan[fIter->first]);
      //stop->Add(single_top_tchan[fIter->first]);
      //stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
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
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);
    
      stop = (TH1F*)single_top_schan[fIter->first]->Clone();
      stop->Add(single_antitop_schan[fIter->first]);
      stop->Add(single_top_tchan[fIter->first]);
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);

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
    
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
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
      
      stop = (TH1F*)single_top_schan[fIter->first]->Clone();
      stop->Add(single_antitop_schan[fIter->first]);
      stop->Add(single_top_tchan[fIter->first]);
      stop->Add(single_antitop_tchan[fIter->first]);
      stop->Add(single_top_wtchan[fIter->first]);
      stop->Add(single_antitop_wtchan[fIter->first]);
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
      cout << "INFO: scaling WZ by 1.18" <<endl;
      W_Z->Scale(1.18); //normalisation scaled by a global factor of 1.18 to match the measured inclusive WZ cross section
 
    }
    

    
    // merge for Top _Analysis
    if(option.find("TTbarAnalysis") != option.npos){
      
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
     
      stop = (TH1F*)single_top_wtchan[fIter->first]->Clone();
      stop->Add(single_antitop_wtchan[fIter->first]);
//      stop->Add(single_top_tchan[fIter->first]);
//      stop->Add(single_antitop_tchan[fIter->first]);
//      stop->Add(single_top_schan[fIter->first]);
//      stop->Add(single_antitop_schan[fIter->first]);
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
      cout << "INFO: scaling ZZ by 1.4" <<endl;
      Z_Z->Scale(1.4); //change by hand the normalisation as the qq->ZZ is not used yet

      Higgs = (TH1F*)ggH125_ZZ4lep[fIter->first]->Clone();
      Higgs->Add(ZH125_ZZ4lep[fIter->first]);
      Higgs->Add(WH125_ZZ4lep[fIter->first]);
      Higgs->Add(VBFH125_ZZ4lep[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);
    }

    
    /*
   
    
    // merge for HWW _Analysis
    if(option.find("HWWAnalysis") != option.npos){
      
      Higgs = (TH1F*)ggH125_WW2lep[fIter->first]->Clone();
      Higgs->Add(VBFH125_WW2lep[fIter->first]);
      Higgs->SetFillColor(kRed);
      Higgs->SetLineWidth(0);
      
      diboson = (TH1F*)WW[fIter->first]->Clone();
      diboson->Add(WZ[fIter->first]);
      diboson->Add(ZZ[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
      
      V = (TH1F*)WenuWithB[fIter->first]->Clone();
      V->Add(WenuJetsBVeto[fIter->first]);
      V->Add(WenuNoJetsBVeto[fIter->first]);
      V->Add(WmunuWithB[fIter->first]);
      V->Add(WmunuJetsBVeto[fIter->first]);
      V->Add(WmunuNoJetsBVeto[fIter->first]);
      V->Add(WtaunuWithB[fIter->first]);
      V->Add(WtaunuJetsBVeto[fIter->first]);
      V->Add(WtaunuNoJetsBVeto[fIter->first]);
      V->Add(DYeeM08to15[fIter->first]);
      V->Add(DYeeM15to40[fIter->first]);
      V->Add(DYmumuM08to15[fIter->first]);
      V->Add(DYmumuM15to40[fIter->first]);
      V->Add(DYtautauM08to15[fIter->first]);
      V->Add(DYtautauM15to40[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);
      
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->Add(ttbar_had[fIter->first]);
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
      
      stop = (TH1F*)stop_wtchan[fIter->first]->Clone();
      //stop->Add(stop_tchan_top[fIter->first]);
      //stop->Add(stop_tchan_antitop[fIter->first]);
      stop->Add(stop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);
    }
    
    // merge for ZPrime _Analysis
    if(option.find("ZPrimeAnalysis") != option.npos){
      
      ZPrime = (TH1F*)ZPrime1000[fIter->first]->Clone();
      ZPrime->SetFillColor(kRed);
      ZPrime->SetLineWidth(0);
      
      ttbar = (TH1F*)ttbar_lep[fIter->first]->Clone();
      ttbar->Add(ttbar_had[fIter->first]);
      ttbar->SetFillColor(kOrange-3);
      ttbar->SetLineWidth(0);
      ttbar->Scale(0.94); //change by hand the ttbar normalisation as the b-tagging scale factor is not applied
      
      V = (TH1F*)WenuWithB[fIter->first]->Clone();
      V->Add(WenuJetsBVeto[fIter->first]);
      V->Add(WenuNoJetsBVeto[fIter->first]);
      V->Add(WmunuWithB[fIter->first]);
      V->Add(WmunuJetsBVeto[fIter->first]);
      V->Add(WmunuNoJetsBVeto[fIter->first]);
      V->Add(WtaunuWithB[fIter->first]);
      V->Add(WtaunuJetsBVeto[fIter->first]);
      V->Add(WtaunuNoJetsBVeto[fIter->first]);
      V->Add(DYeeM08to15[fIter->first]);
      V->Add(DYeeM15to40[fIter->first]);
      V->Add(DYmumuM08to15[fIter->first]);
      V->Add(DYmumuM15to40[fIter->first]);
      V->Add(DYtautauM08to15[fIter->first]);
      V->Add(DYtautauM15to40[fIter->first]);
      V->Add(Z_mumu[fIter->first]);
      V->Add(Z_tautau[fIter->first]);
      V->Add(Z_ee[fIter->first]);
      V->SetFillColor(kGreen-3);
      V->SetLineWidth(0);
      
      stop = (TH1F*)stop_wtchan[fIter->first]->Clone();
      //stop->Add(stop_tchan_top[fIter->first]);
      //stop->Add(stop_tchan_antitop[fIter->first]);
      stop->Add(stop_schan[fIter->first]);
      stop->SetFillColor(kAzure+8);
      stop->SetLineWidth(0);
      
      diboson = (TH1F*)WW[fIter->first]->Clone();
      diboson->Add(WZ[fIter->first]);
      diboson->Add(ZZ[fIter->first]);
      diboson->SetFillColor(kBlue-6);
      diboson->SetLineWidth(0);
    }
    */
    
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
      stack->Add(stop);
      stack->Add(ttbar);
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

    
    if(option.find("TTbarAnalysis") != option.npos){
      stack->Add(diboson);
      stack->Add(stop);
      stack->Add(V);
      stack->Add(ttbar);
    }

    if(option.find("HZZAnalysis") != option.npos){
      stack->Add(V);
      stack->Add(Z_Z);
      stack->Add(Higgs);
    }
    
    /*   
    
    if(option.find("HWWAnalysis") != option.npos){
      stack->Add(stop);
      stack->Add(ttbar);
      stack->Add(V);
      stack->Add(diboson);
      stack->Add(Higgs);
    }
    
    if(option.find("ZPrimeAnalysis") != option.npos){
      stack->Add(diboson);
      stack->Add(stop);
      stack->Add(V);
      stack->Add(ttbar);
      //  stack->Add(ZPrime);
    }
    */
    
    // statistical error histogram, ttbar is by default taken
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
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(stop);
      histstack->Add(V);
      histstack->Add(diboson);
      histstack->Add(Z_Z);
    }

    if(option.find("WZDiBosonAnalysis") != option.npos){
      histstack = (TH1F*)ttbar_lep[fIter->first]->Clone();
      histstack->Add(stop);
      histstack->Add(diboson);
      histstack->Add(V);
      histstack->Add(W_Z);
    }
  
    if(option.find("TTbarAnalysis") != option.npos){
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
    
      /*
  
    
     
    if(option.find("HWWAnalysis") != option.npos){
      histstack->Add(V);
      histstack->Add(Z);
      histstack->Add(stop);
    }
    
    if(option.find("ZPrimeAnalysis") != option.npos){
      histstack->Add(Z);
      histstack->Add(V);
      histstack->Add(stop);
    }
    */
    
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
    
    // add normalized signals
    TH1F* ZP_normsig = new TH1F();
    if(option.find("ZPrimeAnalysis") != option.npos){
      ZP_normsig = (TH1F*)ZPrime1000[fIter->first]->Clone(); 
      ZP_normsig->Scale(histstack->Integral()/ZP_normsig->Integral());
      ZP_normsig->SetLineColor(kRed);
      ZP_normsig->SetFillStyle(0);
      ZP_normsig->SetLineStyle(2);
      ZP_normsig->SetFillColor(2);
      ZP_normsig->SetLineWidth(2);
    }
   
    
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
   

    // set Yaxis maximum
    float yMaxScale = 2.;
    fIter->second->SetMaximum(yMaxScale*TMath::Max( TMath::Max(fIter->second->GetMaximum(),histstack->GetMaximum()), ZP_normsig->GetMaximum() ) );
    
    
    // latex options 
    TLatex l;
    l.SetNDC();
    l.SetTextColor(kBlack);
    l.SetTextFont(42);
    l.SetTextSize(0.04);
    
    if(option.find("WBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"W #rightarrow l#nu ");}
    if(option.find("ZBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z #rightarrow ll");}
    if(option.find("TTbarAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"t#bar{t} #rightarrow l#nub q#bar{q}b ");}
    if(option.find("WZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"WZ #rightarrow l#nu ll");}
    if(option.find("ZZDiBosonAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"ZZ #rightarrow l^{+}l^{-} l^{+}l^{-}");}
    if(option.find("HWWAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow WW #rightarrow l#nu l#nu + 0 jet ");}
    if(option.find("ZPrimeAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"Z' (1TeV) #rightarrow l#nub q#bar{q}b ");}
    if(option.find("HZZAnalysis") != option.npos){l.DrawLatex(0.18,0.71,"H #rightarrow ZZ^{*} #rightarrow 4l");}

    
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
      leg-> AddEntry(W,  "W #rightarrow l#nu", "f");
      leg-> AddEntry(Z,  "Z #rightarrow ll", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }

    if(option.find("ZZDiBosonAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Z_Z , "ZZ", "f");
      leg-> AddEntry(diboson , "WW,WZ", "f");
      leg-> AddEntry(V,  "W/Z", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
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
  
    if(option.find("TTbarAnalysis") != option.npos){
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
 //     leg-> AddEntry(Higgs_normsig, "Higgs (norm)" ,"l");
   }
    
     
/*     
    if(option.find("HWWAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(Higgs , "Higgs", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(V,  "V+jets", "f");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
    }
    
    if(option.find("ZPrimeAnalysis") != option.npos){
      leg-> AddEntry(data[fIter->first] , "Data" ,"lep");
      leg-> AddEntry(ttbar, "t#bar{t}", "f");
      leg-> AddEntry(V , "V+jets", "f");
      leg-> AddEntry(stop, "Single top", "f");
      leg-> AddEntry(diboson , "Diboson", "f");
      leg-> AddEntry(histstack,"Stat. unc.","f");
      leg-> AddEntry(ZP_normsig, "Z' (norm)" ,"l");
    }
    */
    
    // draw everything 
    stack->Draw("HISTsame");
    histstack->Draw("e2same");
    fIter->second->Draw("sameE1");
  
    if(option.find("ZPrimeAnalysis") != option.npos){ZP_normsig->Draw("HISTsame");}
 //   if(option.find("HZZAnalysis") != option.npos){Higgs_normsig->Draw("HISTsame");}

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
  if(option.find("HWWAnalysis") != option.npos){ifile = "list_histos/HistoList_HWW.txt";}
  if(option.find("ZPrimeAnalysis") != option.npos){ifile = "list_histos/HistoList_ZPrime.txt";}
  if(option.find("HZZAnalysis") != option.npos){ifile = "list_histos/HistoList_HZZAnalysis.txt";}
    
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
