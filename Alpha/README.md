# ATLAS Open Data C++ framework for 13 TeV analyses

## About
This is the C++ analysis code that may be used to analyse the data of the ATLAS published dataset.

More information can be found in: CDS link to the PUB note [to appear]

The code is made of two parts: **analysis** code and **plotting** code.

## Setup
After checking out the repository, you need to setup ROOT framework ( and gcc compiler preferentially). The current version was compiled using gcc v6.20 and root v6.10.04

## Samples
For now, the analysis code can be run using samples located in eos:

"/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/renamed/"

## Analysis Code
The analysis code is located in the **Analysis** folder. It is used to make the selection and  create histograms for each individual input file, and those are then used by the plotting code.

Currently, 12 different analyses named "NNAnalysis" are supported, where NN = WBoson, ZBoson, TTbar, SingleTop, WZDiBoson, ZZDiBoson, HZZ, HWW, Hyy, ZPrimeBoosted, ZTauTau and SUSY

Each analysis code contains: 
- the analysis header (*NNAnalysis.h*) which defines the histograms and provides access to the variables stored in the input samples
- the histogram header (*NNAnalysisHistograms.h*) which defines the name of the output histograms
- the analysis code (*NNAnalysis.C*) which makes all the selection and stores the output histograms
- the analysis main macro (*main_NNAnalysis.C*) which controls the input samples and their location
- the output directory (*Output_NNAnalysis*) is where the output histograms (one per each input sample) will be stored

First setup the code using:

./welcome.sh or source welcome.sh

To run the code:

./run.sh or source run.sh

Shared libraries will be created and the analysis will run over each input sample.

To clean all shared libraries:

./clean.sh or source clean.sh

## Plotting
The plotting code is located in the **Plotting** folder.
It can be compiled with "make" or 

To run the code:
./plotme.sh or source plotme.sh

and follow the instruction: you will have to choose 1.) which analysis you will run and 2.) where is the output of the analysis code you producedin the previous step

- The plots are saved inside the directory "**histograms**", don't forget to rename in case you run over several analyses

- Which histograms are being produced? This is controlled by the input file "*HistoList_ANALYSISNAME.txt*" inside *list_histos*

- Do you want to add a new plot? just add the name of it in this file (of course it has to exist in the output from the analysis code)

- In case you changed the *Plotting* code, clean first (use the clean.sh script) or you can re-compile with "make clean; make"

- Auxiliary: within *inputfiles/Files_NN.txt* the name, cross-section, sum of weights and efficiency for each of the MC samples is stored. DO NOT CHANGE!

## How to add a new variable and plot it
1. Add in the header (*NNAnalysis.h*) the new histogram:
```
TH1F *h_new      = 0;
```

2. Add in the main analysis code (*NNAnalysis.C*) the calculation of the new variable:
```
int new_variable = something;
```

3. Add in *NNAnalysisHistograms.h*
- in define_histograms():
```
  h_new            = new TH1F("h_new", "Description of the new variable; X axis name ; Y axis name ", number of bins , min bin , max bin);
```

- in FillOutputList()
```
  GetOutputList()->Add(h_new);
```

- in WriteHistograms()
```
  h_new->Write();
```

- in FillHistograms()
```
  if (s.Contains("h_new")) h_new->Fill(m,w);
```

4. Now finally add in *NNAnalysis.C* the connection between the new variable and the new histogram
```
FillHistograms( new_variable, weight, "h_new");
```
where "new_variable" is the new variable you calculated in step 2.

5. now run the code again over all the samples

6. When running the plotting code, just add a new line to the file: *list_histos/HistoList_NNAnalysis.txt* (corresponding to the analysis you modified)
```
  h_new
```

7. run the plotting code and you will find the new histogram stored in: "histograms/"
