# C++ Analysis Framework for 13 TeV ATLAS Open Data

> [!WARNING]
> ### Migration process to implement the newest release of ATLAS Open Data
> Currently some analyses are being migrated due to the publication of the [third release of educational open data](https://opendata.atlas.cern/docs/data/for_education/13TeV25_details). At the moment, **4 analyses** have been modified to use the newly released datasets: `HWWAnalysis`, `ZTauTauAnalysis`, `TTbarAnalysis`, `TTbarDilepAnalysis`.
>
> The previous analyses documented in the **second release** are under migration process and will be uploaded in the future. If you want to run these analyses now, check the tag **[10fb-legacy](https://github.com/atlas-outreach-data-tools/atlas-outreach-cpp-framework-13tev/tags)**, which contains the backup of the second release analyses.


The framework avaible in this repository makes use of the [C++ language](http://www.cplusplus.com/doc/tutorial/) and is interfaced with [ROOT](https://root.cern.ch/). After cloning/downloading the repository, you need: to have the ROOT framework (see [here](https://root.cern/install/) for a quick start on ROOT) and a [gcc compiler](https://gcc.gnu.org/). The current version of the framework was compiled using gcc v6.20 and ROOT v6.10.04.

The framework includes **two steps**: 

+ the **analysis** step, located within the `Analysis` directory: performs the particular object selection and stores the output histograms;
+ the **plotting** step, located within the `Plotting` directory: makes the final Data / Prediction plots, using the histograms from the previous step.

The 13 TeV ATLAS Open Data are **hosted** on the [CERN Open Data portal](http://opendata.cern.ch/). Information about the data can be found in the [ATLAS Open Data portal](https://opendata.atlas.cern/docs/data).

The framework can access the samples in two ways:

+ Reading them online directly (streaming them);
+ Reading them from a local storage (the samples need to be downloaded locally).

This can be configured within the framework.

## Table of Contents:

- [How to use the framework](#how_to)
  - [First-time setup](#first_time)
  - [The analysis step](#analysis)
  - [The plotting step](#plotting)
  - [How to add a new variable to the analysis](#new_variable)
- [Contribution guide](#contributing)
- [License](#license)

---

## How to use the framework <a name="how_to"></a>
### First-time setup <a name="first_time"></a>

If you are able to run natively on your computer, you are free to do so. If you would prefer, you can run in a docker container:

```
# Start the docker container
docker run -it -p 8888:8888 ghcr.io/atlas-outreach-data-tools/notebooks-collection-opendata:latest /usr/bin/bash
# This is only necessary if you don’t have a local version of the repository already
git clone https://github.com/atlas-outreach-data-tools/atlas-outreach-cpp-framework-13tev.git
cd atlas-outreach-cpp-framework-13tev/Analysis/TTbarAnalysis
# If you need to make any changes to e.g. where the files are stored, do that now
./run.sh
```

In addition, if there are local files you’d like to use, for example to mount the directory `/path/to/directory` so that it’s available in the Docker container as `/something`, run:

```
docker run -it -p 8888:8888 --mount type=bind,src=/path/to/directory,dst=/something ghcr.io/atlas-outreach-data-tools/notebooks-collection-opendata:latest /usr/bin/bash
```

You can use multiple `--mount` options to mount multiple directories, for example if one area holds code, another area holds input files, and a third area is where you would like to store your output files.

---

### The analysis step <a name="analysis"></a>

The analysis code is located in the `analysis` folder, with each sub-folders corresponding to a different physics analysis. The naming of the sub-folders follows a simple rule: "NNAnalysis", where NN can gives an indication of the process that it analyzes.

Each analysis sub-folder contains the following files:

+ Main code (`NNAnalysis.C`): it makes all the selection and stores the output histograms;
+ Main header (`NNAnalysis.h`): it defines the histograms and gives access to the variables stored in the input samples;
+ Histogram header (`NNAnalysisHistograms.h`): it defines the name of output histograms;
+ Main-control code (`main_NNAnalysis.C`): it controls which input samples are going to be used and their location;
+ A [bash script](https://www.shellscript.sh/) (`run.sh`), executed via a Linux/UNIX shell called [source](https://linuxize.com/post/bash-source-command/): helps you in running the analysis interactively.
+ *In case you used the welcome script*, the output directory (`Output_NNAnalysis`) will be created: this is the place where the output of the analysis code (*one file with histograms per each input sample*) will be stored. **Warning**: if the output directory does not exist, the code will fail, please create always an empty one!

As an example, in the case of the HWWAnalysis, the sub-folder looks like this (Output_HWWAnalysis was not created yet):

```
HWWAnalysis.C  HWWAnalysis.h  HWWAnalysisHistograms.h  main_HWWAnalysis.C  run.sh
```

#### Hands-on analysing!

In the main directory, do the first setup of the code by typing in the terminal:
```
./welcome.sh 
```
or in case you have installed the source shell:
```
source welcome.sh 
```
This will ask you if you want to create automatically all the output directories in all the 12 analysis sub-folders, or to erase their contents in case it is needed.

Then, change to any of the analysis sub-folders and open using your preferred text-editor the analysis main-control code (`main_NNAnalysis.C`): it controls **the location of the input samples**, please find the line:
```
// path to your local directory *or* URL, please change the default one!
TString path = "";
```
and adapt it properly to your specific case. 

Subsequently, execute the code via the command line using:
```
./run.sh
```
or
```
source run.sh
```
The script will interactively ask you if you want to run over *all the samples* one-by-one, or to run over *only data* or *only simulated samples*; you can type directly (0, 1,..) in the terminal and hit "ENTER" to answer. The latter options can help you to speed up the analysis, as you can run several samples in several terminals. 

After you choose the analysis, the code will compile and create the needed ROOT shared libraries, and the analysis selection will begin: it will run over each input sample defined in `main_NNAnalysis.C`.

If everything was successful, the code will create in the output directory (`Output_NNAnalysis`) a new file with the name of the corresponding sample (data, ttbar,...).

To clean all shared and linked libraries after running, you can use a script called `clean.sh` located in the main directory.

---

### The plotting step <a name="plotting"></a>
The plotting code is located in the `plotting` folder and contains the following files:

+ Main code (`Plotting.cxx`): it makes all plot magic and controls automatically what to do for each of the analyses;
+ Main header (`Plotting.h`): it defines all the needed bits and pieces for the plotting code;
+ Helper directory (`list_histos`): inside it you will find control files with names `HistoList_ANALYSISNAME.txt`, each of these controls which histograms are going to be used and plotted for each analysis;
+ Helper directory (`inputfiles`): inside it you will find control files with names `Files_ANALYSISNAME.txt`, each of these controls which input samples exactly are going to be used for this particular analysis, their cross-section and sum of weights. DO NOT CHANGE!!!
+ bash script (`plotme.sh`): helps you in running the plotting code interactively, please use it!
+ a makefile (`Makefile`): a set of directives used by a [make](https://www.gnu.org/software/make/manual/html_node/Introduction.html) build automation tool to generate the output executable;
+ *in case you used the welcome script*, the output directory (**histograms**): it will contain the output plots! Do not forget to rename it in case you run over several analyses!

#### Hands-on plotting!

In the main Plotting directory, execute in the terminal:
```
./plotme.sh 
```
or in case you have installed the source shell:
```
source plotme.sh 
```

The script will interactively rompt you  for **two inputs** which you can type directly (0, 1,..) in the terminal and hit "ENTER":

+ **First input**: asks which analysis out of the available ones you want to plot.
+ **Second input**: asks for the location of the `Output_NNAnalysis` directory that was created by running the Analysis code.

After you input the information, the code will compile and create the needed ROOT shared libraries, and the plotting will begin. If everything was successful, the code will create in the output directory (`histograms`) the corresponding plots defined in `HistoList_ANALYSISNAME.txt`.

To clean all shared and linked libraries after running, you can use a script called *clean.sh* located in the main directory.

#### Additional information about the plotting code

+ In case you want to see the data and MC event yields: change "#define YIELDS 0" to "#define YIELDS 1" in `Plotting.cxx` and remake the plots;

+ In case you want to add the normalised signal to the plots: change "#define NORMSIG 0" to "#define NORMSIG 1" in `Plotting.cxx` and remake the plots;

+ In case something is not working: by changing "#define DEBUG 0" to "#define DEBUG 1" in `Plotting.cxx`, a lot of debug information will appear, this can help you trace the origin of any possible problem (usually, these could be: the directory *histograms* does not exist, a wrong path for the location of the input files is given, a wrong or non-existent histogram name is requested, one or several input files from the analysis are missing or failed,..) 

+ In case you want to compile the code instead of using the plotme script, type "make clean; make" and then run the code with *./plot [NNAnalysis]  [location of Output_NNAnalysis]*

---

### How to add a new variable to the analysis <a name="new_variable"></a>

To add a new variable called *new_variable* (which, as an example, will contain the information of *something*), save it as a new histogram called *h_new* and make a plot of it, follow the instructions below:

(1) Add in the header (`NNAnalysis.h`) the new histogram (in the function `public TSelector` where you see the definitions of other histograms):
```
TH1F *h_new      = 0;
```

(2) Add in the histogram header (`NNAnalysisHistograms.h`) four new lines:

inside the function `define_histograms()` add:
```
h_new            = new TH1F("h_new", "Description of the new variable; X axis name ; Y axis name ", number of bins , minimum bin value , maximum bin value);
```

inside the function `FillOutputList()` add:
```
GetOutputList()->Add(h_new);
```

inside the function `WriteHistograms()` add:
```
h_new->Write();
```

inside the function `FillHistogramsGlobal()` add:
```
if (s.Contains("h_new")) h_new->Fill(m,w);
```

(3) And finally, inside the main analysis code `NNAnalysis.C` you need to define a new variable (in this case an integer called *new_variable*), connect it to the value of the branch *something* that *exists* in the input samples (those are listed in the analysis header `NNAnalysis.h` after "Declaration of leaf types") and save the newly created histogram inside the function *Process* after the line that reads the content of the TTree `(fChain->GetTree()->GetEntries()>0)`

```
int new_variable = something;

FillHistogramsGlobal( new_variable, weight, "h_new");
```
where the *weight* is the multiplication of scale factors and Monte Carlo weight.

(4) Now run the analysis code as usual again over all the samples and check that the new histogram *h_new* appears in the produced output files.

(5) *Analysis* part is done, go to *Plotting* part and in the *list_histos* directory in `HistoList_ANALYSISNAME.txt` file add one new line:
```
h_new
```
(with no empty lines before or after it!). 

(6) Execute the plotting code as usual (no need to change the code itself at all), and you will find the new histogram in *histograms/h_new.png*!

---

## Contribution guide <a name="contributing"></a>
We appreciate the willingness to participate in the ATLAS Open Data project. Below you can find some steps to help you contribute successfully (inspired by [The Turing Way](https://book.the-turing-way.org) contribution guidelines):

### 1. Comment on an existing issue or open a new issue referencing your addition
Before creating a pull request (PR), discuss the change you want to make. That's the easiest way we can check that the work is not overlapping with current work and that it aligns with the goals of the Open Data project. 

In [this blog](https://www.igvita.com/2011/12/19/dont-push-your-pull-requests/) you can find some reasons why putting this work in upfront is so useful to everyone involved.

When opening a new issue be sure to fill all the information necessary. The issue template should help you doing so.

### 2. Fork the repository
Make a fork of the repository in the upper right corner of the repository page in GitHub. In this new copy, changes won't affect anyone else's work, and you can make as many changes as you want. 

Make sure to keep the fork up to date (or develop from a branch based on the main repository's main branch) to avoid conflicts when merging. If you already have conflicts, check [GitHub's guide to resolving a merge conflict](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/resolving-a-merge-conflict-on-github).

### 3. Make the changes you've discussed
Please keep the changes targeted to what was discussed. While making your changes, commit often and write explanatory commit messages.

Please do not re-write history! That is, please do not use the rebase command to edit previous commit messages, combine multiple commits into one, or delete or revert commits that are no longer necessary.

### 4. Submit a pull request
Once you are done with your changes, open a PR. We encourage you to open a PR as early in your contributing process as possible so that everyone can see what is being worked on.

When submitting your PR you will see a template. It will ask:
- To describe the problem you are trying to fix an reference related issues. 
- List the changes you are proposing
- Tell us what we should focus our review on.

Please give us all the details, this makes it easier for us to review the contribution!

## License
This software is licensed under the terms of the [European Union Public Licence
V. 1.1](LICENSE)

@2025
