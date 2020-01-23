//////////////////////////////////////////////////
#ifndef PLOTTING_H
#define PLOTTING_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <TF1.h>
#include <TH1.h>
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

using namespace std;


class HistoHandler{
  
 public:
  HistoHandler();
  HistoHandler(std::string name);
  ~HistoHandler();
  std::string GetName();

 private:
  std::string _name;
  
};

class Plotting{

 public:
  Plotting();
  ~Plotting();
  void run();
  void SetLumi(double l);
  void SetOption(std::string analysis);
  void SetInputLocation(string loc);



 private:
  void Disclaimer();
  void getHistoSettings();
  void AtlasStyle();
  void ATLASLabel(Double_t x,Double_t y);
  void WhichFiles();
  void readFiles();
  void createHistoSet(TFile* file, std::string proc);
  void createHistogram(TFile* file, std::string hname,  std::string proc);
  void makePlots();
  void PrintCanvas(TCanvas* c1, string title);

  std::vector<std::string> filename;
  std::map<std::string,std::pair<double,double> > SF;
  std::map<std::string,std::map<std::string, TH1F*> > histo;
  
  double lumi;
  std::string option;
  string readname;

  // histogram settings
  std::vector<HistoHandler*> hset;

  // fitting
  TF1* bgd; 
  TF1* fit;
  TH1F* h_ratio2;

};

#endif
